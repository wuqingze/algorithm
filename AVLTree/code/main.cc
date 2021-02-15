#include "AVLTree.cc"
#include <iostream>
#include <memory>

class Hello{
    struct Fruit{
        int a;
        int v;
    };
    public:
        auto get(){
            return Fruit();
        }
};
using namespace std;

void test05(){
    int n;
    cin>>n;
    int c=0;
    AVLTree<int> tree;
    while(c<n){
        int t = rand()%n;
        if(not tree.isExist(t)){
            c += 1;
            tree.insert(t);
        }
    }

    while(c>0){
        int t = rand()%n;
        if(tree.isExist(t)){
            std::printf("remove %d==============\n", t);
            tree.remove(t);
            tree.traverse([](decltype(tree.getRoot()) node){
                    std::printf("%d\n", node->val);
                    }
            );
            c -= 1;
        }
    }
    std::printf("remove finished...\n");
}

void test04(){
    int n;
    cin>>n;
    int c = 0;
    AVLTree<int> tree;
    while(c<n){
        int t = rand()%n;
        if(not tree.isExist(t)){
            tree.insert(t);
            c+=1;
        }
    }

    c = 0;
    while(c<n/2){
        int t = rand()%n;
        if(tree.isExist(t)){
            c += 1;
            std::printf("remove %d=================\n", t);
            tree.remove(t);
            tree.traverse([](decltype(tree.getRoot()) node){
                std::printf("%d [ lable=%d ]\n", node->val, node->val);
                if(node->left) 
                    std::printf("%d -> %d\n", node->val, node->left->val);
                if(node->right) 
                    std::printf("%d -> %d\n", node->val, node->right->val);
                }
            );
        }
    }
}

void test03(){
    int n;
    cin>>n;
    AVLTree<int> tree;
    int c= 0;
    while(c<n){
        int t = rand()%n;
        if(not tree.isExist(t)){
            std::printf("insert %d==========================\n", t);
            tree.insert(t);
            tree.traverse([](decltype(tree.getRoot()) node){
                if(node == node->left or node == node->right){
                    std::printf("node %d repeated...\n", node->val);
                    exit(1);
                }
                std::printf("%d [ lable=%d ]\n", node->val, node->val);
                if(node->left) 
                    std::printf("%d -> %d\n", node->val, node->left->val);
                if(node->right) 
                    std::printf("%d -> %d\n", node->val, node->right->val);
                    }
            );
            c+=1;
        }
    }
}

void test02(){
    Hello h;
    decltype(h.get()) a;
}

void test01(){
    int n;
    cin>>n;
    int c = 0;
    AVLTree<int> tree;
    while(c<n){
       int t = rand()%n;
       if(not tree.isExist(t)){
           tree.insert(t);
          c += 1;
       }
    }

    while(c>0){
        int t = rand()%n;
      if(tree.isExist(t)){
           std::printf("remove %d ...\n", t);
           tree.remove(t);
           tree.traverse(
               [](decltype(tree.getRoot()) node){
                    std::printf("%d [ label=%d ]\n", node->val, node->val);
                    if(node->left) 
                        std::printf("%d -> %d\n", node->val, node->left->val);
                    if(node->right)
                        std::printf("%d -> %d\n", node->val, node->right->val);
               }
           );
           c -= 1;
           std::printf("==================\n");
       }
    }
    std::printf("remove finished...\n");
}

void test00(){
    int n;
    cin>>n;
    int c = 0;
    AVLTree<int> tree;
    while(c<n){
       int t = rand()%n;
       if(not tree.isExist(t)){
           std::printf("insert %d ===========\n", t);
           tree.insert(t);
           tree.traverse(
               [](decltype(tree.getRoot()) node){
                    std::printf("%d [ label=%d ]\n", node->val, node->val);
                    if(node->left) 
                        std::printf("%d -> %d\n", node->val, node->left->val);
                    if(node->right)
                        std::printf("%d -> %d\n", node->val, node->right->val);
               }
           );
           c += 1;
       }
    }
}

int main(){
    test04();
    return 0;

    test05();
    return 0;

    test04();
    return 0;

    test03();
    return 0;

    test01();
    return 0;

    test00();
    return 0;
}
