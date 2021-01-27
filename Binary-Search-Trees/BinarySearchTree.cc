#include <memory>
#include <iostream>
#include <functional>

template<typename T>
class BinarySearchTree{
    private:
        struct Node{
            T val;
            std::shared_ptr<Node> left;
            std::shared_ptr<Node> right;
            std::shared_ptr<Node> parent;
            Node(T val_){ val = val_;}
            Node(T val_, std::shared_ptr<Node> parent_){ 
                val = val_;
                parent = parent_;
            }
            bool lessThan(T val_) { return comapre(val, val_)<0;}
            bool greaterThan(T val_) { return compare(val, val_)>0;}
            bool equal(T val_) { return comapre(val, val_) == 0;}
        };

        std::shared_ptr<Node> root;
        std::function<int(T, T)> compare = [](T o1, T o2) { if(o1==o2) return 0; else return o1-o2; };

        std::shared_ptr<Node> __find(T val){
            if(not root) return nullptr;

            auto ptr = root;
            while(ptr){
                if(compare(ptr->val, val) == 0) return ptr;
                else if(compare(ptr->val, val) < 0) ptr = ptr->right;
                else ptr = ptr->left;
            }
            return nullptr;
        }

        std::shared_ptr<Node> minNode(std::shared_ptr<Node> node){
            if(not node) return nullptr;
            auto ptr = node;
            while(ptr->left) ptr=ptr->left;
            return ptr;
        }

        std::shared_ptr<Node> successor(std::shared_ptr<Node> node){
            if(not node) return nullptr;
            if(not node->left and not node->right) return node;

            if(not node->right){
                auto ptr = node;
                while(ptr and ptr->parent and ptr->parent->right == ptr) 
                    ptr = ptr->parent;
                if(not ptr) return nullptr;
                else return ptr->parent;
            }else return minNode(node);
        }

    public:

        BinarySearchTree(){}

        BinarySearchTree(std::function<int(T, T)> compare_ ){
            compare = compare_;
        }

        void insert(T val){
            if(not root) {
                root = std::shared_ptr<Node>(new Node(val));
                return;
            }

            auto ptr = root;
            while(ptr){
                if(compare(ptr->val, val) == 0){
                    ptr->val = val;
                    return ;
                }else if(compare(ptr->val, val) < 0 and not ptr->right){
                    ptr->right = std::shared_ptr<Node>(new Node(val), ptr);
                    return;
                }else if(compare(ptr->val, val) > 0 and not ptr->left){
                    ptr->left = std::shared_ptr<Node>(new Node(val), ptr);
                    return;
                }
                ptr = compare(ptr->val, val)>0?ptr->left:ptr->right;
            }
        }

        bool find(T val){
            if(not root) return false;

            auto ptr = root;
            while(ptr){
                if(compare(ptr->val, val) == 0) return true;
                else if(compare(ptr->val, val) < 0) ptr = ptr->right;
                else ptr = ptr->left;
            }
            return false;
        }

        void remove(T val){
            auto ptr = find_(val);
            if(not ptr) return;

            if(not ptr->parent){
                if(not ptr->left and not ptr->right){
                    root = nullptr;
                }else if(not ptr->right){
                    root = root->left;
                }else if(not ptr->left){
                    root = root->right;
                }else{
                    auto node = successor();
                    root->val = node->val;
                    if(node->parent->left == node) node->parent->left = nullptr;
                    else node->parent->right = nullptr;
                    node->parent = nullptr;
                }
            }else{
                auto f = [](std::shared_ptr<Node> src, std::shared_ptr<Node> desc){
                    if(src->parent->left == src) src->parent->left = desc;
                    else src->parent->right = desc;
                    src->parent = nullptr;
                };
                if(not ptr->left and not ptr->right){
                    f(ptr, nullptr);
                }else if(not ptr->left){
                    f(ptr, ptr->right);
                }else if(not ptr->right){
                    f(ptr, ptr->left);
                }else{
                    auto successorNode = successor();
                    ptr->val = successorNode->val;
                    f(successorNode, nullptr);
                }
            }
        }

};

int main(){
    std::shared_ptr<int> p;
    auto t = p == nullptr;
    std::cout<<t<<std::endl;
    return 0;
}

