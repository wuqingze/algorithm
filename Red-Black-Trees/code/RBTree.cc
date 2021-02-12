#include <functional>
#include <vector>

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
            
           Node(T val_, COLOR clr, Node* parent_, Node* nil):
                val(val_), color(clr), 
                parent(parent_), left(nil),
                right(nil){}
            Node(T val_, COLOR clr, Node* nil):
                val(val_), color(clr),
                parent(nil), left(nil),
                right(nil){}

            Node(COLOR clr): color(clr){}
        };

        Node *nil = new Node(COLOR::BLACK);
        Node *root = nil;

        std::function<int (const T &o1,const T &o2)> compare = 
            [](T o1, T o2){ return o1-o2;};

        Node* findNode(T val){
            if(root == nil) return nil;
            auto ptr = root;
            while(ptr != nil){
                if(compare(val, ptr->val) == 0) return ptr;
                else if(compare(val, ptr->val) > 0) ptr=ptr->right;
                else ptr = ptr->left;
            }
            return nil;
        }

        Node* successor(Node* node){
            auto ptr = node->right;
            while(ptr->left != nil) ptr = ptr->left;
            return ptr;
        }

        bool check(){
            if(root == nil) return true;
            auto ptr = root;
            std::vector<Node*> l;
            while(1){
                while(ptr != nil){
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

        void leftRotion(Node* node){
            if(node == nil or node->right == nil) 
                return;
            auto A = node;
            auto B = node->right;
            if(A->parent == nil){
                A->right = B->left;
                if(A->right != nil) A->right->parent = A;
                B->left = A;
                if(B->left != nil) B->left->parent = B;
                B->parent = nil;
                root = B;
            }else{
                auto parent = A->parent;
                A->right = B->left;
                if(A->right != nil) A->right->parent = A;
                B->left = A;
                if(B->left != nil) B->left->parent = B;
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
            if(node == nil or node->left == nil)
                return;
            auto A = node;
            auto B = A->left;
            if(A->parent == nil){
                A->left = B->right;
                if(A->left != nil) A->left->parent = A;
                B->right = A;
                if(B->right != nil) B->right->parent = B;
                B->parent = nil;
                root = B;
            }else{
                auto parent = A->parent;
                A->left = B->right;
                if(A->left != nil) A->left->parent = A;
                B->right = A;
                if(B->right != nil) B->right->parent = B;
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
            while(x->parent != nil and x->parent->color == COLOR::RED){
                if(x->parent == x->parent->parent->left){
                    auto uncle = x->parent->parent->right;
                    if(uncle->color==COLOR::RED){
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
                    if(uncle->color==COLOR::RED){
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
                    if(sibling->color == COLOR::RED){
                        x->parent->color = COLOR::RED;
                        sibling->color = COLOR::BLACK;
                        leftRotion(x->parent);
                        sibling = x->parent->right;
                    }

                    if(sibling->left->color == COLOR::BLACK and 
                            sibling->right->color == COLOR::BLACK){
                        sibling->color = COLOR::RED;
                        x = x->parent;
                    }else{
                        if(sibling->right->color == COLOR::BLACK){
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
                    if(sibling->color == COLOR::RED){
                        sibling->color = COLOR::BLACK;
                        x->parent->color = COLOR::RED;
                        rightRotation(x->parent);
                        sibling = x->parent->left;
                    }

                    if(sibling->left->color == COLOR::BLACK and 
                            sibling->right->color == COLOR::BLACK){
                        sibling->color = COLOR::RED;
                        x = x->parent;
                    }else{
                        if(sibling->left->color == COLOR::BLACK){
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
            if(root == nil) delete nil;
            else {
                delete root;
                delete nil;
            }
        }

        Node* getRoot(){ return root;}
        Node* getNil() { return nil;}

        void insert(T val){
            if(root == nil){
                root = new Node(val, COLOR::BLACK, nil);
                return;
            }

            auto ptr = root;
            while(ptr != nil){
                if(compare(val, ptr->val) == 0) return;
                if(ptr->left == nil and ptr->right == nil){
                    if(compare(val, ptr->val) < 0){
                        ptr->left = new Node(val, COLOR::RED, ptr, nil);
                        insertFixup(ptr->left);
                    }else{
                        ptr->right = new Node(val, COLOR::RED, ptr, nil);
                        insertFixup(ptr->right);
                    }
                    return;
                }else if(ptr->left == nil and compare(val, ptr->val) < 0){
                    ptr->left = new Node(val, COLOR::RED, ptr, nil);
                    insertFixup(ptr->left);
                    return;
                }else if(ptr->right == nil and compare(val, ptr->val) > 0){
                    ptr->right = new Node(val, COLOR::RED, ptr, nil);
                    insertFixup(ptr->right);
                    return;
                }
                ptr = compare(val, ptr->val) > 0 ? ptr->right : ptr->left;
            }
        }

        void remove(T val){
            auto node = findNode(val);
            if(node == nil) return;

            if(node == root){
                if(root->left == nil and root->right == nil) {
                    delete root;
                    root = nil;
                }else if(root->left == nil){
                    root = root->right;
                    delete root->parent;
                    root->parent = nil;
                    root->color = COLOR::BLACK;
                }else if(root->right == nil){
                    root = root->left;
                    delete root->parent;
                    root->parent = nil;
                    root->color = COLOR::BLACK;
                }else{
                    auto successorNode = successor(root);
                    root->val = successorNode->val;
                    if(successorNode->parent->left == successorNode){
                        successorNode->parent->left = successorNode->right;
                        if(successorNode->right != nil) 
                            successorNode->right->parent = successorNode->parent;
                    }else{
                        successorNode->parent->right = successorNode->right;
                        if(successorNode->right != nil) 
                            successorNode->right->parent = successorNode->parent;
                    }
                    if(successorNode->color == COLOR::BLACK) {
                        if(successorNode->right == nil) nil->parent = successorNode->parent;
                        removeFixup(successorNode->right);
                        if(successorNode->right == nil) nil->parent = nullptr;
                    }
                    delete successorNode;
                }
            }else{
                auto removeNode = [=](Node* cur, Node* next){
                    if(cur->parent->left == cur){
                        cur->parent->left = next;
                    }else{
                        cur->parent->right = next;
                    }
                    if(next != nil) {
                        next->parent = cur->parent;
                    }
                    if(cur->color == COLOR::BLACK){
                        if(next == nil) nil->parent = cur->parent;
                        removeFixup(next);
                        if(next == nil) nil->parent = nullptr;
                    }
                    delete cur;
                };

                if(node->left == nil and node->right == nil){
                    removeNode(node, nil);
                }else if(node->right == nil){
                    removeNode(node, node->left);
                }else if(node->left == nil){
                    removeNode(node, node->right);
                }else {
                    auto successorNode = successor(node);
                    node->val = successorNode->val;
                    removeNode(successorNode, successorNode->right);
                }
            }
        }

        bool find(T val){
            if(root == nil) return false;
            auto ptr = root;
            while(ptr != nil){
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
            if(node == nil) return 0;
            if(node->left == nil and node->right == nil) 
                return node->color == COLOR::RED?0:1;

            if(node->color == COLOR::RED) 
                return std::max(blackLength(node->left), blackLength(node->right));
            else
                return std::max(blackLength(node->left), blackLength(node->right))+1;
        }
};
