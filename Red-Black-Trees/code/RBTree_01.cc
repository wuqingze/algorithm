#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>

using namespace std;

enum CLR{
    BLACK, RED
};

struct Node{
    Node* p;
    Node* l;
    Node* r;
    int val;
    CLR clr;
    Node(){
        cout<<"adfk"<<endl;
    }
    Node(int v, CLR clr_, Node* leaf){
        val = v;
        //Node(clr_, leaf);
        clr = clr_;
        l = leaf;
        r = leaf;
    }
    Node(CLR clr_, Node* leaf){
        clr = clr_;
        l = leaf;
        r = leaf;
    }
};


class Tree{
public:
    Node* root = nullptr;
    Node* leaf = nullptr;

    Tree(){
        leaf = new Node(CLR::BLACK, nullptr);
    }

    Node* find(int key){
        auto ptr = root;
        while(ptr != leaf){
            if(ptr->val == key) return ptr;
            else if(ptr->val < key){
                ptr = ptr->r;
            }else{
                ptr = ptr->l;
            }
        }
        return nullptr;
    }

    void leftrotate(Node* node){
        if(node == root){
            auto right = node->r;
            root = right;
            node->r = right->l;
            if(right->l != leaf){
                right->l->p = node;
            }
            right->l = node;
            node->p = right;
            right->p = nullptr;
        }else{
            auto right = node->r;
            auto p = node->p;
            bool isleft = node->p->l == node;
            node->r = right->l;
            if(right->l!=leaf){
                right->l->p = node;
            }
            right->l = node;
            node->p = right;
            if(isleft){
                p->l = right;
                right->p = p;
            }else{
                p->r = right;
                right->p = p;
            }
        }
    }

    void rightrotate(Node* node){
        if(node == root){
            auto left = node->l;
            root = left;
            node->l = left->r;
            if(left->r!= leaf){
                left->r->p = node;
            }
            left->r = node;
            node->p = left;
            left->p = nullptr;
        }else{
            bool isleft = node->p->l == node;
            auto p = node->p;
            auto left = node->l;
            node->l = left->r;
            if(left->r != leaf){
                left->r->p = node;
            }
            left->r = node;
            node->p = left;
            if(isleft){
                p->l = left;
                left->p = p;
            }else{
                p->r = left;
                left->p = p;
            }
        }
    }

    void fixinsert(Node* node){
        auto p = node->p;
        auto ptr = node;
        while(ptr != root and p!= root and p->clr == CLR::RED){
            if(p == p->p->l){
                auto uncle = p->p->r;
                if(uncle->clr == CLR::RED){
                    p->clr = CLR::BLACK;
                    uncle->clr = CLR::BLACK;
                    p->p->clr = CLR::RED;
                    ptr = p->p;
                    p = ptr->p;
                }else{
                    auto pp = p->p;
                    if(ptr == p->l){
                        swap(p->clr, p->p->clr);
                        rightrotate(p->p);
                    }else{
                        leftrotate(p);
                        swap(pp->clr, pp->l->clr);
                        rightrotate(pp);
                    }
                    break;
                }
            }else{
                auto uncle = p->p->l;
                if(uncle->clr == CLR::RED){
                    p->clr = CLR::BLACK;
                    uncle->clr = CLR::BLACK;
                    p->p->clr = CLR::RED;
                    ptr = p->p;
                    p = ptr->p;
                }else{
                    auto pp = p->p;
                    if(ptr == p->r){
                        swap(p->clr, p->p->clr);
                        leftrotate(p->p);
                    }else{
                        rightrotate(p);
                        swap(pp->clr, pp->r->clr);
                        leftrotate(pp);
                    }
                    break;
                }
            }
        }
        root->clr = CLR::BLACK;
    }

    void insert(int val){
        if(root == nullptr){
            root = new Node(val, CLR::BLACK, leaf);
            return;
        }

        auto ptr = root;
        while(true){
            if(ptr->val < val){
                if(ptr->r == leaf){
                    auto node = new Node(val, CLR::RED, leaf);
                    ptr->r = node;
                    node->p = ptr;
                    fixinsert(node);
                    break;
                }else{
                    ptr = ptr->r;
                }
            }else{
                if(ptr->l == leaf){
                    auto node = new Node(val, CLR::RED, leaf);
                    ptr->l = node;
                    node->p = ptr;
                    fixinsert(node);
                    break;
                }else{
                    ptr = ptr->l;
                }
            }
        }
    }

    Node* next(Node* node){
        auto ptr = node;
        while(ptr->l != leaf){
            ptr = ptr->l;
        }
        return ptr;
    }

    void fixremove(Node* ptr, Node* p){
        while(ptr != root and ptr->clr == CLR::BLACK){
            bool isleft = ptr == p->l;
            auto bro = isleft?p->r:p->l;
            if(bro->clr == CLR::RED){
                swap(p->clr, bro->clr);
                isleft?leftrotate(p):rightrotate(p);
            }else{
                if(bro->l->clr == CLR::BLACK and bro->r->clr == CLR::BLACK){
                    bro->clr = CLR::RED;
                    ptr = p;
                    p = ptr->p;
                }else if(isleft){
                    if(bro->r->clr == CLR::RED){
                        bro->r->clr = CLR::BLACK;
                        swap(p->clr, bro->clr);
                        leftrotate(p);
                        break;
                    }else{
                        swap(bro->clr, bro->l->clr);
                        rightrotate(bro);
                    }
                }else{
                    if(bro->l->clr == CLR::RED){
                        bro->l->clr = CLR::BLACK;
                        swap(bro->clr, p->clr);
                        rightrotate(p);
                        break;
                    }else{
                        swap(bro->clr, bro->r->clr);
                        leftrotate(bro);
                    }
                }
            }
        }
        ptr->clr = CLR::BLACK;
    }

    void remove(int key){
        auto ptr = find(key);
        if(ptr == nullptr) return;
l:
        if(ptr->l == leaf and ptr->r == leaf){
            if(ptr == root){
                delete ptr;
                root = nullptr;
                return;
            }

            bool isleft = ptr->p->l == ptr;
            if(ptr->clr == CLR::RED){
                isleft?ptr->p->l = leaf:ptr->p->r = leaf;
                delete ptr;
            }else{
                auto p = ptr->p;
                isleft?ptr->p->l = leaf:ptr->p->r = leaf;
                fixremove(leaf, p);
            }
        }else if(ptr->l == leaf){
            ptr->val = ptr->r->val;
            delete ptr->r;
            ptr->r = leaf;
        }else if(ptr->r == leaf){
            ptr->val = ptr->l->val;
            delete ptr->l;
            ptr->l = leaf;
        }else{
            auto tmp= next(ptr->r);
            ptr->val = tmp->val;
            ptr = tmp;
            goto l;
        }
    }

    void traverse(){
        if(root == nullptr) return;
        traverse(root);
    }
    
    void traverse(Node* node){
        if(node == leaf) return;
        if(node->l != leaf) traverse(node->l);
        if(node->clr == CLR::RED){
            cout<<node->val<<" [color=red];"<<endl;
        }else{
            cout<<node->val<<";"<<endl;
        }
        if(node->l == leaf){
            cout<<node->val<<" -> leaf;"<<endl;
        }else{
            cout<<node->val<<" -> "<<node->l->val<<";"<<endl;
        }
        if(node->r == leaf){
            cout<<node->val<<" -> leaf;"<<endl;
        }else{
            cout<<node->val<<" -> "<<node->r->val<<";"<<endl;
        }
        if(node->r != leaf) traverse(node->r);
    }
};


void f(Node* node){
    node = new Node(19, CLR::RED, nullptr);
}

int main(int argc, char* argv[]){
//    vector<int> args;
//    for(int i=1;i<argc;i++){
//        args.push_back(atoi(argv[i]));
//    }
//    srand(time(NULL));
    Tree tree;
    int cnt = atoi(argv[1]);
    vector<int> args(cnt);
    for(int i=1;i<=cnt;i++) args[i-1] = i;
    for(int i=0;i<cnt;i++){
        //tree.insert(rand()%cnt);
        int index = rand()%cnt;
        swap(args[i], args[index]);
    }

    for(auto i:args){
    //    cout<<i<<",";
        tree.insert(i);
    }
//    cout<<endl;;
//    tree.traverse();
//    cout<<endl;
    for(int i=0;i<cnt;i++){
        //tree.insert(rand()%cnt);
        int index = rand()%cnt;
        swap(args[i], args[index]);
    }
    for(int i=0;i<cnt/2;i++){
        tree.remove(args[i]);
    }
    tree.traverse();
//    Node* t = new Node();
//    Node* t1 = t;
//    delete t;
//    if(t1 == nullptr){
//        delete t1;
//        cout<<"deleted"<<endl;
//    }else{
//        cout<<"not deleted"<<endl;
//    }
//    return 0;
//
//    t->r = new Node();
//
//    delete t->r;
//    t->r = new Node();
//    cout<<"akldjf-----"<<endl;
//    return 0;
//    auto node = new Node(13, CLR::RED, nullptr);
//    f(node);
//    cout<<node->val<<endl;
//    if(t == nullptr) 
//    {cout<<"yes"<<endl;
//    }else cout<<"no"<<endl;
//
    return 0;
}
