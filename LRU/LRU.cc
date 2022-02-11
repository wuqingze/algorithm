#include <iostream>
#include <vector>
#include <map>

using namespace std;

struct Node{
    int k;
    int v;
    int c;
    Node* pre;
    Node* next;
    Node(){
        pre = NULL;
        next = NULL;
    }
    
    Node(int k_, int v_, int c_){
        k = k_;
        v = v_;
        c = c_;
        Node();
    }
};

class LFUCache {
public:
    Node* head;
    Node* tail;
    int capacity;
    map<int, Node*> hmap;
    map<int, Node*> nmap;
    int len;
    
    LFUCache(int capacity_) {
        capacity = capacity_;
        head = new Node();
        tail = new Node();
        head->next = tail;
        tail->pre = head;
        len =0;
    }
    
    void move(Node* n1, Node* n2){
        n1->pre->next = n1->next;
        n1->next->pre = n1->pre;
        
        n2->next->pre = n1;
        n1->next = n2->next;
        n2->next = n1;
        n1->pre = n2;
    }
    
    void update(int key){
        auto node = hmap[key];
        if(nmap.count(node->c+1)){
            auto tnode = nmap[node->c+1];
            if(nmap.count(node->c) and nmap[node->c]==node){
                if(node->pre != head and node->pre->c == node->c){
                    nmap[node->c] = node->pre;
                }else{
                    nmap.erase(nmap.find(node->c));
                }
            }
            move(node, tnode);
        }else{
            auto it = nmap.find(node->c);
            if(it != nmap.end()){
                auto tnode = it->second;
                if(tnode == node){
                    if(node->pre != head and node->pre->c == node->c){
                        nmap[node->c] = node->pre;
                    }else{
                        nmap.erase(nmap.find(node->c));
                    }
                }
                if(tnode != node){
                    move(node, tnode);
                }    
            }
        }
        node->c += 1;
        nmap[node->c] = node;
    }
    
    int get(int key) {
        if(capacity==0 or hmap.count(key)==0){
            return -1;
        }
        update(key);
        return hmap[key]->v;
    }
    
    void put(int key, int value) {
        if(capacity == 0) return;
        if(hmap.count(key)==0){
            if(len == capacity){
                auto node = head->next;
                hmap.erase(hmap.find(node->k));
                if(nmap[node->c] == node) nmap.erase(nmap.find(node->c));
                node->k = key;
                node->v = value;
                node->c = 0;
                hmap[key] = node;
                update(key);
            }else{
                auto node = new Node(key, value, 0);
                hmap[key] = node;
                len += 1;
                head->next->pre = node;
                node->next = head->next;
                head->next = node;
                node->pre = head;
                update(key);
            }
        }else{
            auto node = hmap[key];
            node->v = value;
            update(key);
        }
    }
};

int main(){
    LFUCache obj = LFUCache(3);
    obj.put(2,2);
    obj.put(1,1);
    obj.get(2);
    obj.get(1);
    obj.get(2);
    obj.put(3,3);
    obj.put(4,4);
    obj.get(3);
    obj.get(2);
    obj.get(1);
    obj.get(4);
	return 0;
}
/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
