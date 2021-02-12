#include "RBTree.cc"
#include <iostream>

using namespace std;
bool checkLength(RBTree<int> &tree){
    auto ptr = tree.getRoot();
    auto nil = tree.getNil();
    vector<void*> l;
    while(1){
        while(ptr != nil){
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
    auto nil = tree.getNil();
    vector<void*> l;
    while(1){
        while(ptr != nil){
            l.push_back(ptr);
            ptr = ptr->left;
        }
        if(l.empty()) return true;
        ptr = (decltype(ptr)) l.back();
        if(ptr->left != nil and ptr->val < ptr->left->val) return false;
        if(ptr->right != nil and ptr->val > ptr->right->val) return false;
        l.pop_back();
        ptr = ptr->right;
    }
    return true;
}

void traverse_graph(RBTree<int> &tree){
    auto ptr = tree.getRoot();
    auto nil = tree.getNil();
    vector<void*> l;
    int n = 0;
    while(1){
       while(ptr != nil){
            l.push_back(ptr);
            ptr = ptr->left;
        }
        if(l.empty()) return;
        ptr = (decltype(ptr)) l.back();
        l.pop_back();
        std::printf("%d [ lable=%d, color=%s]\n", ptr->val, ptr->val,
                ptr->color == tree.red() ? "red":"black");
        if(ptr->left != nil) std::printf("%d -> %d\n", ptr->val, ptr->left->val);
        if(ptr->right != nil) std::printf("%d -> %d\n", ptr->val, ptr->right->val);
        ptr = ptr->right;
        n += 1;
    }
}

void traverse(RBTree<int> &tree){
    auto ptr = tree.getRoot();
    auto nil = tree.getNil();
    vector<void*> l;
    int n = 0;
    while(1){
       while(ptr != nil){
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

void test14(){
    int *a = new int(1);
    if(a) std::printf("a is %d\n", *a);
    delete a;
    if(a){
        std::printf("a check work after deleted...\n");
    }else{
        std::printf("a check doesn't work after deleted...\n");
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
            std::printf("...\n");
            if(not checkLength(tree)){
                std::printf("struct destroyed...\n");
                traverse_graph(tree);
                return;
            }
            c -= 1;
        }
    }
    std::printf("test13 finished...\n");
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
        traverse_graph(tree);
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
            traverse_graph(tree);
            return;
        }
        traverse_graph(tree);
        cout<<"============="<<endl;
        c+=1;
    }
    cout<<"insert finished..."<<endl;
    traverse_graph(tree);
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

    test05();
    return 0;

    test14();
    return 0;

    test05();
    return 0;

    test04();
    return 0;

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

