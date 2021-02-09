#include <functional>
#include <iostream>
#include <vector>

using namespace std;

template<typename T>
class RBTree{
    private:
        enum COLOR{ RED, BLACK};
        
        struct Node{
            T val;
            COLOR color;
            Node *parent = nullptr;
            Node *left = nullptr;
            Node *right = nullptr;
            
            Node(T val_) { val = val_;}
            Node(T val_, Node* parent_) { 
                val = val_;
                parent = parent_;
            }
            Node(T val_, COLOR clr) {
                val = val_;
                color = clr;
            }
        };

        Node *nil = nullptr;
        Node *root = nil;

        std::function<int (const T &o1,const T &o2)> compare = 
            [](T o1, T o2){ return o1-o2;};

        Node* findNode(T val){
            if(root == nil) return nil;
            auto ptr = root;
            while(ptr){
                if(compare(val, ptr->val) == 0) return ptr;
                else if(compare(val, ptr->val) > 0) ptr=ptr->right;
                else ptr = ptr->left;
            }
            return nil;
        }

        Node* successor(Node* node){
            auto ptr = node->right;
            while(ptr->left) ptr = ptr->left;
            return ptr;
        }

    public:
        int t(T o1, T o2) { return 1;}
        Node* getRoot(){ return root;}

        RBTree(){}
        RBTree(std::function<int (const T &o1, const T &o2)> f){
            compare = f;
        }

        ~RBTree(){ 
            delete root;
        }

        void insert(T val){
            if(not root){
                root = new Node(val, COLOR::BLACK);
                return;
            }

            auto ptr = root;
            while(ptr){
                if(compare(val, ptr->val) == 0) return;
                if(not ptr->left and not ptr->right){
                    if(compare(val, ptr->val) < 0){
                        ptr->left = new Node(val, ptr);
                    }else{
                        ptr->right = new Node(val, ptr);
                    }
                    return;
                }else if(not ptr->left and compare(val, ptr->val) < 0){
                    ptr->left = new Node(val, ptr);
                    return;
                }else if(not ptr->right and compare(val, ptr->val) > 0){
                    ptr->right = new Node(val, ptr);
                    return;
                }
                ptr = compare(val, ptr->val) > 0 ? ptr->right : ptr->left;
            }
        }

        void remove(T val){
            auto node = findNode(val);
            if(not node) return;

            if(node == root){
                if(not root->left and not root->right) {
                    delete root;
                    root = nil;
                }else if(not root->left){
                    root = root->right;
                    delete root->parent;
                    root->parent = nil;
                }else if(not root->right){
                    root = root->left;
                    delete root->parent;
                    root->parent = nil;
                }else{
                    auto successorNode = successor(root);
                    root->val = successorNode->val;
                    if(successorNode->parent->left == successorNode){
                        successorNode->parent->left = successorNode->right;
                        if(successorNode->right) successorNode->right->parent = successorNode->parent;
                    }else{
                        successorNode->parent->right = successorNode->right;
                        if(successorNode->right) successorNode->right->parent = successorNode->parent;
                    }
                    delete successorNode;
                }
            }else{
                auto removeNode = [](Node* cur, Node* next){
                    if(cur->parent->left == cur){
                        cur->parent->left = next;
                    }else{
                        cur->parent->right = next;
                    }
                    if(next) {
                        next->parent = cur->parent;
                    }
                    delete cur;
                };

                if(not node->left and not node->right){
                    removeNode(node, nil);
                }else if(not node->right){
                    removeNode(node, node->left);
                }else if(not node->left){
                    removeNode(node, node->right);
                }else {
                    auto successorNode = successor(node);
                    node->val = successorNode->val;
                    removeNode(successorNode, successorNode->right);
                }
            }
        }

        bool find(T val){
            if(not root) return false;
            auto ptr = root;
            while(ptr){
                if(compare(val, ptr->val) == 0) return true;
                else if(compare(val, ptr->val) >0) ptr = ptr->right;
                else ptr = ptr->left;
            }
            return false;
        }
};

void traverse(RBTree<int> &tree){
    auto ptr = tree.getRoot();
    vector<void*> l;
    while(1){
        while(ptr){
            l.push_back(ptr);
            ptr = ptr->left;
        }
        if(l.empty()) return;
        ptr = (decltype(ptr)) l.back();
        l.pop_back();
        cout<<ptr->val<<endl;
        ptr = ptr->right;
    }
}

void test06(){
    int *a = nullptr;
    if(!a) cout<<"... haah"<<endl;
}

void test05(){
    int n;
    cin>>n;
    int c=0;
    RBTree<int> tree;
    while(c<n){
        int t = rand()%n;
        if(tree.find(t)) continue;
        tree.insert(t);
        c+=1;
    }
    while(c>0){
        int t = rand()%n;
        if(not tree.find(t)) continue;
        cout<<"remove "<<t<<" ..."<<endl;
        tree.remove(t);
        traverse(tree);
        cout<<"=================="<<endl;
        c -= 1;
    }
}
void test04(){
    int n;
    cin>>n;
    RBTree<int> tree;
    int c = 0;
    while(c<n){
        int t = rand()%n;
        if(tree.find(t)) continue;
        tree.insert(t);
        cout<<"insert "<<t<<" finished..."<<endl;
        traverse(tree);
        cout<<"============="<<endl;
        c+=1;
    }
    return;
    vector<int> l = {4, 5, 3, 6, 2, 7, 1, 8};
    for(auto i:l) {
        tree.insert(i);
        cout<<"insert "<<i<<" finished..."<<endl;
        traverse(tree);
        cout<<"============="<<endl;
    }
}

void test03(){
    vector<int> l;
    l.pop_back();
    cout<<"hello ..."<<endl;
}

void test02(){
    int *p1 = nullptr;
    auto p2 = new int(1);
    if(p1 and p2){
        cout<<" p1 and p2 ..."<<endl;
    }
    if(p1 or p2){
        cout<<" p1 or p2 ..."<<endl;
    }
    if(not p1 and p2){
        cout<<" not p1 and p2 ..."<<endl;
    }

    if(p1){
        cout<<"yea pointer..."<<endl;
    }else{
        cout<<"nay pointer..."<<endl;
    }
}

void test00(){
    RBTree<int> tree([](int o1, int o2) { return o1-o2;});
    tree.insert(1);
    tree.insert(2);
}

void test01(){
    int *a = new int(1);
    a = nullptr;
    delete a;
    cout<<"delete ..."<<endl;
    delete a;
    cout<<"delete ..."<<endl;
}

int main(){
    test05();
    return 0;

    test04();
    return 0;

    test03();
    return 0;

    test02();
    return 0;

    test01();
    return 0;

    test00();
    return 0;
}

