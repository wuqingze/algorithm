#include <iostream>
#include <vector>

using namespace std;


struct Node{
    int val;
    Node* l;
    Node* r;
    Node* p;
    int clr;//black:0;red:1
    Node(){
        clr = 1;
        l = nullptr;
        r = nullptr;
        p = nullptr;
    }

    Node(int v,Node* prt,  Node* leaf){
        val = v;
        clr = 1;
        r = leaf;
        l = leaf;
        p = prt;
    }

    Node(int v, int c){
        val = v;
        clr = c;
    }
};

class Tree{
    Node* leaf = new Node();
    Node* root = nullptr;

    void fixinsert(Node* node){
    }

    void fixremove(Node* parent, Node* child){

    }


    void insert(int v){
        if(root == nullptr){
            root = new Node(v, 0);
            root->l = leaf;
            root->r = leaf;
            return;
        }
        auto ptr = root;
        while(ptr){
            if(ptr->val > v){
                if(ptr->r == leaf){
                    ptr->r = new Node(v, ptr, leaf);
                    fixinsert(ptr->r);
                    break;
                }else{
                    ptr = ptr->r;
                }
            }else{
                if(ptr->l == leaf){
                    ptr->l = new Node(v, ptr, leaf);
                    fixinsert(ptr->l);
                    break;
                }else{
                    ptr = ptr->l;
                }
            }
        }
    }

    Node* find(int key){
        auto ptr = root;
        while(ptr and ptr != leaf){
            if(ptr->val == key){
                return ptr;
            }else if(ptr->val < key){
                ptr = ptr->l;
            }else{
                ptr = ptr->r;
            }
        }
        return nullptr;
    }

    void rmchild(Node* node){
        if(node == root){
            root = nullptr;
        }else{
            if(node->p->l == node){
                node->p->l = leaf;
            }else{
                node->p->r = leaf;
            }
        }
    }

    Node* next(Node* ptr){
        while(ptr->l != leaf){
            ptr = ptr->l;
        }
        return ptr;
    }

    void remove(int key){
        auto ptr = find(key);
        if(not ptr){
            return;
        }
l:
        if(ptr->l == leaf and ptr->r == leaf){
            if(ptr->clr == 0){
                rmchild(ptr);
            }else{
                rmchild(ptr);
            }
        }else if(ptr->l == leaf){
            ptr->v = ptr->r->val;
            rmchild(ptr->r);
        }else if(ptr->r == leaf){
            ptr->v = ptr->l->val;
            rmchild(ptr->l);
        }else{
        }
    }


};

int main(){
    Node *node = new Node();

    return 0;
}
