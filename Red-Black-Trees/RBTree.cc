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
            Node(T val_, Node* parent_, COLOR clr) { 
                val = val_;
                parent = parent_;
                color = clr;
            }
            Node(T val_, COLOR clr) {
                val = val_;
                color = clr;
            }
            Node(COLOR clr): color(clr){}
         };

        Node *nil = new Node(COLOR::RED);
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

        bool check(){
            if(not root) return true;
            auto ptr = root;
            vector<Node*> l;
            while(1){
                while(ptr){
                    l.push_back(ptr);
                    ptr = ptr->left;
                }
                if(l.empty()) return true;
                ptr = l.back();
                if(ptr->left and ptr->val < ptr->left->val) return false;
                if(ptr->right and ptr->val > ptr->right->val) return false;
                l.pop_back();
                ptr = ptr->right;
            }
            return true;
        }

        void traverse(){
            if(not root) return;
            vector<Node*> l;
            l.push_back(root);
            while(not l.empty()){
                vector<Node*> t;
                for(auto p:l){
                    if(p->parent)
                        cout<<p->val<<"("<<p->parent->val<<") ";
                    else
                        cout<<p->val<<"(nil) ";
                    if(p->left) t.push_back(p->left);
                    if(p->right) t.push_back(p->right);
                }
                cout<<endl;
                l = t;
            }
            cout<<"-------------------"<<endl;
        }

        void leftRotion(Node* node){
            if(not node or not node->right) 
                return;
            auto A = node;
            auto B = node->right;
            if(not A->parent){
                A->right = B->left;
                if(A->right) A->right->parent = A;
                B->left = A;
                if(B->left) B->left->parent = B;
                B->parent = nil;
                root = B;
            }else{
                auto parent = A->parent;
                A->right = B->left;
                if(A->right) A->right->parent = A;
                B->left = A;
                if(B->left) B->left->parent = B;
                if(parent->left == A){ 
                    parent->left = B;
                    parent->left->parent = parent;
                }else{ 
                    parent->right = B;
                    parent->right->parent = parent;
                }
            }
        }

        void rightRotation(Node* node){
            if(not node or not node->left)
                return;
            auto A = node;
            auto B = A->left;
            if(not A->parent){
                A->left = B->right;
                if(A->left) A->left->parent = A;
                B->right = A;
                if(B->right) B->right->parent = B;
                B->parent = nil;
                root = B;
            }else{
                auto parent = A->parent;
                A->left = B->right;
                if(A->left) A->left->parent = A;
                B->right = A;
                if(B->right) B->right->parent = B;
                if(parent->left == A){ 
                    parent->left = B;
                    parent->left->parent = parent;
                }else{ 
                    parent->right = B;
                    parent->right->parent = parent;
                }
            }
        }

        void insertFixup(Node* node){
            auto x = node;
            while(x->parent and x->parent->color == COLOR::RED){
                if(x->parent == x->parent->parent->left){
                    auto uncle = x->parent->parent->right;
                    if(uncle and uncle->color==COLOR::RED){
                        uncle->color = COLOR::BLACK;
                        x->parent->color = COLOR::BLACK;
                        x->parent->parent->color = COLOR::RED;
                        x = x->parent->parent;
                    }else{
                        if(x == x->parent->right){
                            x = x->parent;
                            leftRotion(x);
                        }
                        x->parent->color = COLOR::BLACK;
                        x->parent->parent->color = COLOR::RED;
                        rightRotation(x->parent->parent);
                    }
                }else{
                    auto uncle = x->parent->parent->left;
                    if(uncle and uncle->color==COLOR::RED){
                        uncle->color = COLOR::BLACK;
                        x->parent->color = COLOR::BLACK;
                        x->parent->parent->color = COLOR::RED;
                        x = x->parent->parent;
                    }else{
                        if(x == x->parent->left){
                            x = x->parent;
                            rightRotation(x);
                        }
                        x->parent->color = COLOR::BLACK;
                        x->parent->parent->color = COLOR::RED;
                        leftRotion(x->parent->parent);
                    }
                }
            }
            root->color = COLOR::BLACK;
        }

        void removeFixup(Node* node){
            auto x = node;
            while(x != root and x->color == COLOR::BLACK){
                if(x == x->parent->left){
                    auto sibling = x->parent->right;
                    if(sibling and sibling->color == COLOR::RED){
                        x->parent->color = COLOR::RED;
                        sibling->color = COLOR::BLACK;
                        leftRotion(x->parent);
                        sibling = x->parent->right;
                    }

                    if(not(sibling->left and sibling->left->color == COLOR::RED) and
                            not(sibling->right and sibling->right->color == COLOR::RED)){
                        sibling->color = COLOR::RED;
                        x = x->parent;
                    }else{
                        if(not(sibling->right and sibling->right->color == COLOR::RED)){
                            sibling->color = COLOR::RED;
                            sibling->left->color = COLOR::BLACK;
                            rightRotation(sibling);
                            sibling = sibling->parent;
                        }
                        sibling->color = sibling->parent->color;
                        x->parent->color = COLOR::BLACK;
                        sibling->right->color = COLOR::BLACK;
                        leftRotion(x->parent);
                        x = root;
                    }
                }else{
                    auto sibling = x->parent->left;
                    if(sibling and sibling->color == COLOR::BLACK){
                        sibling->color = COLOR::BLACK;
                        x->parent->color = COLOR::RED;
                        rightRotation(x->parent);
                        sibling = x->parent->left;
                    }

                    if(not(sibling and sibling->color == COLOR::BLACK) and
                            not(sibling and sibling->color == COLOR::BLACK)){
                        sibling->color = COLOR::RED;
                        x = x->parent;
                    }else{
                        if(not(sibling->left and sibling->left->color == COLOR::RED)){
                            sibling->right->color = COLOR::BLACK;
                            sibling->color = COLOR::RED;
                            leftRotion(sibling);
                            sibling = sibling->parent;
                        }
                        sibling->color = x->parent->color;
                        x->parent->color = COLOR::BLACK;
                        sibling->left->color = COLOR::BLACK;
                        rightRotation(x->parent);
                        x = root;
                    }
                }
            }
            x->color = COLOR::BLACK;
        }

    public:
        RBTree(){}
        RBTree(std::function<int (const T &o1, const T &o2)> f){
            compare = f;
        }
        ~RBTree(){ 
            delete root;
        }

        Node* getRoot(){ return root;}

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
                        ptr->left = new Node(val, ptr, COLOR::RED);
                        insertFixup(ptr->left);
                    }else{
                        ptr->right = new Node(val, ptr, COLOR::RED);
                        insertFixup(ptr->right);
                    }
                    return;
                }else if(not ptr->left and compare(val, ptr->val) < 0){
                    ptr->left = new Node(val, ptr, COLOR::RED);
                    insertFixup(ptr->left);
                    return;
                }else if(not ptr->right and compare(val, ptr->val) > 0){
                    ptr->right = new Node(val, ptr, COLOR::RED);
                    insertFixup(ptr->right);
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
                    root->color = COLOR::BLACK;
                }else if(not root->right){
                    root = root->left;
                    delete root->parent;
                    root->parent = nil;
                    root->color = COLOR::BLACK;
                }else{
                    auto successorNode = successor(root);
                    root->val = successorNode->val;
                    if(successorNode->parent->left == successorNode){
                        successorNode->parent->left = successorNode->right;
                        if(successorNode->right) 
                            successorNode->right->parent = successorNode->parent;
                    }else{
                        successorNode->parent->right = successorNode->right;
                        if(successorNode->right) 
                            successorNode->right->parent = successorNode->parent;
                    }
                    if(successorNode->color == COLOR::BLACK) 
                        removeFixup(successorNode->right);
                    delete successorNode;
                }
            }else{
                auto removeNode = [=](Node* cur, Node* next){
                    if(cur->parent->left == cur){
                        cur->parent->left = next;
                    }else{
                        cur->parent->right = next;
                    }
                    if(next) {
                        next->parent = cur->parent;
                    }
                    if(cur->color == COLOR::BLACK)
                        removeFixup(next);
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

        auto red(){
            return COLOR::RED;
        }

        int blackLength(Node* node){
            if(not node) return 0;
            if(not node->left and not node->right) 
                return node->color == COLOR::RED?0:1;

            if(node->color == COLOR::RED) 
                return std::max(blackLength(node->left), blackLength(node->right));
            else
                return std::max(blackLength(node->left), blackLength(node->right))+1;
        }
};

bool checkLength(RBTree<int> &tree){
    auto ptr = tree.getRoot();
    vector<void*> l;
    while(1){
        while(ptr){
            l.push_back(ptr);
            ptr = ptr->left;
        }
        if(l.empty()) return true;
        ptr = (decltype(ptr)) l.back();
        if(tree.blackLength(ptr->left) != tree.blackLength(ptr->right))
            return false;
        l.pop_back();
        ptr = ptr->right;
    }
    return true;
}

bool check(RBTree<int> &tree){
    auto ptr = tree.getRoot();
    vector<void*> l;
    while(1){
        while(ptr){
            l.push_back(ptr);
            ptr = ptr->left;
        }
        if(l.empty()) return true;
        ptr = (decltype(ptr)) l.back();
        if(ptr->left and ptr->val < ptr->left->val) return false;
        if(ptr->right and ptr->val > ptr->right->val) return false;
        l.pop_back();
        ptr = ptr->right;
    }
    return true;
}

void traverse_graph(RBTree<int> &tree){
    auto ptr = tree.getRoot();
    vector<void*> l;
    int n = 0;
    while(1){
       while(ptr){
            l.push_back(ptr);
            ptr = ptr->left;
        }
        if(l.empty()) return;
        ptr = (decltype(ptr)) l.back();
        l.pop_back();
        std::printf("%d [ lable=%d, color=%s]\n", ptr->val, ptr->val,
                ptr->color == tree.red() ? "red":"black");
        if(ptr->left) std::printf("%d -> %d\n", ptr->val, ptr->left->val);
        if(ptr->right) std::printf("%d -> %d\n", ptr->val, ptr->right->val);
        ptr = ptr->right;
        n += 1;
    }
}

void traverse(RBTree<int> &tree){
    auto ptr = tree.getRoot();
    vector<void*> l;
    int n = 0;
    while(1){
        if(ptr and (ptr == ptr->left or ptr == ptr->right)){
            cout<<"ptr "<<ptr->val<<" equal it's left or it's right"<<endl;
            return;
        }
        while(ptr){
            l.push_back(ptr);
            ptr = ptr->left;
        }
        if(l.empty()) return;
        ptr = (decltype(ptr)) l.back();
        l.pop_back();
        cout<<ptr->val<<endl;
        ptr = ptr->right;
        n += 1;
    }
}

void test12(){
    auto t = std::max(1,3);
}

void test13(){
    RBTree<int> tree;
    int n;
    cin >> n;
    int c = 0;
    while(c<n){
        int t = rand()%n;
        if(not tree.find(t)){
            tree.insert(t);
            c += 1;
        }
    }

    traverse_graph(tree);
    while(c>n/2){
        int t = rand()%n;
        if(tree.find(t)){
            std::printf("remove %d ===================\n", t);
            traverse_graph(tree);
            std::printf("==============================\n");
            tree.remove(t);
            if(not checkLength(tree)){
                std::printf("struct destroyed...\n");
                traverse_graph(tree);
                return;
            }
            c -= 1;
        }
    }
    std::printf("test12 finished...\n");
}

void test11(){
    RBTree<int> tree;
    int n;
    cin >> n;
    int c = 0;
    while(c<n){
        int t = rand()%n;
        if(not tree.find(t)){
            tree.insert(t);
            c += 1;
        }
    }

    traverse_graph(tree);
    while(c>n/2){
        int t = rand()%n;
        if(tree.find(t)){
            std::printf("remove %d ===================\n", t);
            tree.remove(t);
            traverse_graph(tree);
            c -= 1;
        }
    }
    std::printf("test11 finished...\n");
}

void test10(){
    RBTree<int> tree;
    int n;
    cin >> n;
    int c = 0;
    while(c<n){
        int t = rand()%n;
        if(not tree.find(t)){
            tree.insert(t);
            traverse_graph(tree);
            cout<<"======================"<<endl;
        }
        c += 1;
    }
}

void test09(){
    std::printf("hello world %d", 1024);
}

void test08(){
    int n;
    cin>>n;
    RBTree<int> tree;
    for(int i=0;i<n;i++){
        int t = rand()%n;
        tree.insert(t);
    }
    cout<<"insert finished ..."<<endl;
    traverse(tree);
    for(int i=0;i<n-1;i++){
        tree.remove(i);
    }
    cout<<"traverse tree..."<<endl;
    traverse(tree);
    cout<<"traverse finish ..."<<endl;
    test08();
}

void test07(){
    int *a = nullptr;
    delete a;
    cout<<"delete a ..."<<endl;
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
        if(not check(tree)){
            cout<<"tree struct has been destroyed..."<<endl;
            traverse(tree);
            return;
        }
        //traverse(tree);
        cout<<"============="<<endl;
        c+=1;
    }
    cout<<"insert finished..."<<endl;
    traverse(tree);
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
    test13();
    return 0;

    test11();
    return 0;

    test10();
    return 0;

    test09();
    return 0;

    test04();
    return 0;

    test00();
    return 0;

    test08();
    while(1);
    return 0;

    test07();
    return 0;

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

