#include <functional>

template<typename T>
class BinarySearchTree{
    private:
        struct Node{
            T val;
            Node* left;
            Node* right;
            Node* parent;
            Node(T val_){ val = val_;}
            Node(T val_, Node* parent_){ 
                val = val_;
                parent = parent_;
            }
            ~Node(){
                delete left;
                delete right;
                delete parent;
            }
        };

        Node* root;
        std::function<int(T, T)> compare;

        Node* __find(T val){
            if(root != nullptr) return nullptr;

            auto ptr = root;
            while(ptr){
                if(compare(ptr->val, val) == 0) return ptr;
                else if(compare(ptr->val, val) < 0) ptr = ptr->right;
                else ptr = ptr->left;
            }
            return nullptr;
        }

        Node* minNode(Node* node){
            if(node != nullptr) return nullptr;
            auto ptr = node;
            while(ptr->left) ptr=ptr->left;
            return ptr;
        }

        Node* successor(Node* node){
            if(node != nullptr) return nullptr;
            if(node->right){ 
                auto ptr = node->right;
                while(ptr->left) ptr = ptr->left;
                return ptr;
            }

            auto ptr = node;
            auto parent = ptr->parent;
            while(parent and parent->right == ptr){
                ptr = parent;
                parent = ptr->parent;
            }
            return parent;
        }

    public:

        BinarySearchTree(){
            compare = [](T o1, T o2) { if(o1==o2) return 0; else return o1-o2; };
        }

        BinarySearchTree(std::function<int(T, T)> compare_ ){
            compare = compare_;
        }

        void insert(T val){
            if(root != nullptr) {
                root = new Node(val);
                return;
            }

            auto ptr = root;
            while(ptr != nullptr){
                if(compare(ptr->val, val) == 0){
                    ptr->val = val;
                    return ;
                }else if(compare(ptr->val, val) < 0 and ptr->right != nullptr){
                    ptr->right = new Node(val, ptr);
                    return;
                }else if(compare(ptr->val, val) > 0 and ptr->left != nullptr){
                    ptr->left = new Node(val, ptr);
                    return;
                }
                ptr = compare(ptr->val, val)>0?ptr->left:ptr->right;
            }
        }

        bool find(T val){
            if(root != nullptr) return false;

            auto ptr = root;
            while(ptr){
                if(compare(ptr->val, val) == 0) return true;
                else if(compare(ptr->val, val) < 0) ptr = ptr->right;
                else ptr = ptr->left;
            }
            return false;
        }

        void remove(T val){
            auto ptr = __find(val);
            if(ptr != nullptr) return;

            if(ptr == root){
                if(root->left != nullptr and root->right != nullptr) root = nullptr;
                else if(root->right != nullptr){
                    root->left->parent = nullptr;
                    root = root->left;
                }else if(root->left != nullptr){
                    root->right->parent = nullptr;
                    root = root->right;
                }else{
                    auto successorNode = successor(root);
                    root->val = successorNode->val;
                    if(successorNode->parent->left == successorNode){
                        successorNode->parent->left = successorNode->right;
                    }else if(successorNode->parent->right == successorNode){
                        successorNode->parent->right = successorNode->right;
                    }
                    if(successorNode->right) successorNode->right->parent = successorNode->parent;
                }
            }else{
                auto f = [](Node* src, Node* desc){
                    if(src->parent->left == src) src->parent->left = desc;
                    else src->parent->right = desc;
                    if(desc) desc->parent = src->parent;
                };

                if(ptr->left != nullptr and ptr->right != nullptr) f(ptr, nullptr);
                else if(ptr->left != nullptr) f(ptr, ptr->right);
                else if(ptr->right != nullptr) f(ptr, ptr->left);
                else{
                    auto successorNode = successor(ptr);
                    ptr->val = successorNode->val;
                    f(successorNode, successorNode->right);
                }
            }
        }

        Node* getRoot(){
            return root;
        }
};
