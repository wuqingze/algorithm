#include <memory>
#include <iostream>

template<typename T>
struct Node{
    T val;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;
    std::shared_ptr<Node> parent;
    Node(T val_){ val = val_;}
};

template<typename T>
void treeInsert(std::shared_ptr<T> root, std::shared_ptr<T> node){
    auto ptr = root;
    while(ptr){
        if(not ptr->left and not ptr->right){
            if(node->val > ptr->val) ptr->right = node;
            else ptr->left = node;
            node->parent = ptr;
            return;
        }else if(not ptr->left and node->val <= ptr->val){
            ptr->left = node;
            node->parent = ptr;
            return;
        }else if(not ptr->right and node->val > ptr->val){
            ptr->right = node;
            node->parent = ptr;
            return;
        }
        ptr = node->val > ptr->val?ptr->right:ptr->left;
    }
}

template<typename T>
void travelTree(std::shared_ptr<T> root){
    if(not root) return;
    if(not root->left and not root->right){
        std::cout<<root->val<<std::endl;
        return;
    }
    travelTree(root->left);
    std::cout<<root->val<<std::endl;
    travelTree(root->right);
}

template<typename T>
std::shared_ptr<Node<T>> treeMinimum(std::shared_ptr<Node<T>> node){
    if(not node) return node;

    auto result = node;
    while(result){
        if(not result->left) return result;
        result = result->left;
    }
    return result;
}

template<typename T>
std::shared_ptr<Node<T>> treeSuccessor(std::shared_ptr<Node<T>> node){
    if(node->right) return treeMinimum(node->right);

    auto child = node;
    auto parent = child->parent;
    while( parent and parent->right == child){
        child = parent;
        parent = child->parent;
    }
    return parent;
}

int main(){
    int n;
    std::cin>>n;
    auto root = std::shared_ptr<Node<int>>(new Node<int>(rand()%n));
    for(int i=0;i<n-1;i++){
        auto t = std::shared_ptr<Node<int>>(new Node<int>(rand()%n));
        treeInsert(root, t);
    }
    travelTree(root);
    return 0;
}
