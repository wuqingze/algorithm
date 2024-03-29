#include <memory>
#include <functional>
#include <vector>
#include <iostream>
using namespace std;

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
            ~Node(){
                cout<<"node "<<val<<" destroyed..."<<endl;
            }
            bool lessThan(T val_) { return comapre(val, val_)<0;}
            bool greaterThan(T val_) { return compare(val, val_)>0;}
            bool equal(T val_) { return comapre(val, val_) == 0;}
        };

        std::shared_ptr<Node> root;
        std::function<int(T, T)> compare;

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
                    ptr->right = std::shared_ptr<Node>(new Node(val, ptr));
                    return;
                }else if(compare(ptr->val, val) > 0 and not ptr->left){
                    ptr->left = std::shared_ptr<Node>(new Node(val, ptr));
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
            auto ptr = __find(val);
            if(not ptr) return;

            if(ptr == root){
                if(not root->left and not root->right) root = nullptr;
                else if(not root->right){
                    root->left->parent = nullptr;
                    root = root->left;
                }else if(not root->left){
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
                    successorNode.reset();
                }
            }else{
                auto f = [](std::shared_ptr<Node> src, std::shared_ptr<Node> desc){
                    if(src->parent->left == src) src->parent->left = desc;
                    else src->parent->right = desc;
                    if(desc) desc->parent = src->parent;
                    src.reset();
                };

                if(not ptr->left and not ptr->right) f(ptr, nullptr);
                else if(not ptr->left) f(ptr, ptr->right);
                else if(not ptr->right) f(ptr, ptr->left);
                else{
                    auto successorNode = successor(ptr);
                    ptr->val = successorNode->val;
                    f(successorNode, successorNode->right);
                }
            }
        }

        void traverse(std::function<void(std::shared_ptr<Node>)> f){

            cout<<"digraph{"<<endl;
            std::vector<std::shared_ptr<Node>> l;
            auto ptr = root;
            while(ptr) {
                l.push_back(ptr);
                ptr = ptr->left;
            }
            while(not l.empty()){
                auto t = l.back();
                //f(t->val);
                f(t);
                l.pop_back();
                if(t->right){
                    ptr = t->right;
                    while(ptr){
                        l.push_back(ptr);
                        ptr = ptr->left;
                    }
                }
            }
            cout<<"}"<<endl;
        }

        std::shared_ptr<Node> getRoot(){
            return root;
        }
};
