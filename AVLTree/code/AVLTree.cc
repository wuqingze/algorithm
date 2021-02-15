#include <memory>
#include <functional>
#include <vector>

template<typename T>
class AVLTree{
    private:
        struct Node{
            T val;
            int height;
            std::shared_ptr<Node> left = nullptr;
            std::shared_ptr<Node> right = nullptr;
            std::shared_ptr<Node> parent = nullptr;
            Node(T val_, int height_, std::shared_ptr<Node> parent_):
                val(val_),
                height(height_),
                parent(parent_){}
        };

        std::shared_ptr<Node> root;
        std::function<int (const T &o1, const T &o2)> compare = 
            [](const T &o1, const T &o2){
                return o1-o2;
            };

        std::shared_ptr<Node> find(T val){
            if(not root) return nullptr;
            auto ptr = root;
            while(ptr){
                if(compare(val, ptr->val) == 0) return ptr;
                else if(compare(val, ptr->val) < 0)
                    ptr = ptr->left;
                else
                    ptr = ptr->right;
            }
            return nullptr;
        }

        void setLength(std::shared_ptr<Node> node){
            if(not node) return;

            int lh = node->left?node->left->height:0;
            int rh = node->right?node->right->height:0;
            node->height = std::max(lh, rh)+1;
        }

        std::shared_ptr<Node> successor(std::shared_ptr<Node> node){
            auto ptr = node->right;
            while(ptr->left) ptr = ptr->left;
            return ptr;
        }

        void leftRotation(std::shared_ptr<Node> node){
            if(not node or not node->right) return;
            auto A = node;
            auto B = node->right;

            if(A == root){
                B->parent = nullptr;
                root = B;

                A->right = B->left;
                if(A->right) A->right->parent = A;
                B->left = A;
                B->left->parent = B;
            }else{
                if(A == A->parent->left){
                    A->parent->left = B;
                    B->parent = A->parent;
                }else{
                    A->parent->right = B;
                    B->parent = A->parent;
                }

                A->right = B->left;
                if(A->right) A->right->parent = A;
                B->left = A;
                B->left->parent = B;
            }
        }

        void rightRotation(std::shared_ptr<Node> node){
            if(not node or not node->left) return;

            auto A = node;
            auto B = node->left;

            if(A == root){
                B->parent = nullptr;
                root = B;

                A->left = B->right;
                if(A->left) A->left->parent = A;
                B->right = A;
                B->right->parent = B;

            }else{
                if(A->parent->left == A){
                    A->parent->left = B;
                    B->parent = A->parent;
                }else{
                    A->parent->right = B;
                    B->parent = A->parent;
                }

                A->left = B->right;
                if(A->left) A->left->parent = A;
                B->right = A;
                B->right->parent = B;
            }
        }

        int getLength(std::shared_ptr<Node> node){
            if(not node) return 0;
            int lh = node->left?node->left->height:0;
            int rh = node->right?node->right->height:0;
            return std::max(lh, rh)+1;
        }

        bool checkHeight(std::shared_ptr<Node> node){
                int lh = getLength(node->left);
                int rh = getLength(node->right);
                if(lh+rh+1 == node->height) 
                    return true;
                else 
                    return false;
        }

        void fixup(std::shared_ptr<Node> node){
            while(not checkHeight(node)){
                int lh = getLength(node->left);
                int rh = getLength(node->right);
                bool isRoot = node == root;
                if(lh-rh<-1){
                    if(getLength(node->right->left) > getLength(node->right->right)){
                        rightRotation(node->right);
                        setLength(node->right->right);
                        setLength(node->right);
                        leftRotation(node);
                        setLength(node);
                        setLength(node->parent);
                        node = node->parent;
                    }else{
                        leftRotation(node);
                        setLength(node);
                        setLength(node->parent);
                        node = node->parent;
                    }
                }else if(lh-rh>1){
                    if(getLength(node->left->left) < getLength(node->left->right)){
                        leftRotation(node->left);
                        setLength(node->left->left);
                        setLength(node->left);
                        rightRotation(node);
                        setLength(node);
                        setLength(node->parent);
                        node = node->parent;
                    }else{
                        rightRotation(node);
                        setLength(node);
                        setLength(node->parent);
                        node = node->parent;
                    }
                }else{
                    node->height = std::max(rh, lh) + 1;
                }
                if(isRoot){
                    root = node;
                    return;
                }
                node = node->parent;
           }
        }

    public:
        AVLTree(){}
        AVLTree(std::function<int(const T &o1, const T &o2)> compare_){
            compare = compare_;
        }
        std::shared_ptr<Node> getRoot(){ return root;}

        void insert(T val){
            if(not root){
                root = std::make_shared<Node>(val, 1, nullptr);
                return;
            }

            auto ptr = root;
            while(1){
                if(compare(val, ptr->val) == 0) return;
                if(not ptr->left and compare(val, ptr->val) < 0){
                    ptr->left = std::make_shared<Node>(val, 1, ptr);
                    fixup(ptr);
                    return;
                } else if(not ptr->right and compare(val, ptr->val) > 0){
                    ptr->right = std::make_shared<Node>(val, 1, ptr);
                    fixup(ptr);
                    return;
                } else{
                    ptr = compare(val, ptr->val) < 0?ptr->left:ptr->right;
                }
            }
        }

        void remove(T val){
            auto ptr = find(val);
            if(not ptr) return;
            if(ptr == root){
                if(not root->left and not root->right){
                    root = nullptr;
                }else if(not root->left){
                    root = root->right;
                }else if(not root->right){
                    root = root->left;
                }else{
                    auto successorNode = successor(root);
                    root->val = successorNode->val;
                    if(successorNode == successorNode->parent->left){
                        successorNode->parent->left = successorNode->right;
                    }else{
                        successorNode->parent->right = successorNode->right;
                    }
                    if(successorNode->right) 
                        successorNode->right->parent  = successorNode->parent;
                    fixup(successorNode->parent);
                }
            }else{
                auto transplant = [=](std::shared_ptr<Node> cur, std::shared_ptr<Node> next){
                    if(cur == cur->parent->left){
                        cur->parent->left = next;
                        if(next) next->parent = cur->parent;
                    }else{
                        cur->parent->right = next;
                        if(next) next->parent = cur->parent;
                    }
                    fixup(cur->parent);
                };

                if(not ptr->left and not ptr->right){
                    transplant(ptr, nullptr);
                }else if(not ptr->left){
                    transplant(ptr, ptr->right);
                }else if(not ptr->right){
                    transplant(ptr, ptr->left);
                }else{
                    auto successorNode = successor(ptr);
                    ptr->val = successorNode->val;
                    transplant(successorNode, successorNode->right);
                }
            }
        }

        bool isExist(T val){
            if(not root) return false;
            auto ptr = root;
            while(ptr){
                if(compare(val, ptr->val) == 0) return true;
                else if(compare(val, ptr->val) < 0) ptr = ptr->left;
                else ptr = ptr->right;
            }
            return false;
        }

        void traverse(std::function<void(std::shared_ptr<Node>)> run){
            if(not root) return;
            auto ptr = root;
            std::vector<std::shared_ptr<Node>> l;
            while(1){
                while(ptr){
                    l.push_back(ptr);
                    ptr = ptr->left;
                }
                if(l.empty()) return;
                ptr = l.back();
                run(ptr);
                l.pop_back();
                ptr = ptr->right;
            }
        }
};
