#include <string.h>

template<typename T>
class PriorityQueue{

    private:
        int len = 0;
        int capability = 1024;
        T* arr;

        void exchagne(int i, int j){
            auto t = arr[i];
            arr[i] = arr[j];
            arr[j] = t;
        }

        void maintainHeap(){
            int index = len-1;
            while(index>0){
                int parent = (index -1)/2;
                if(arr[parent] < arr[index]){
                    exchagne(index, parent);
                    index = parent;
                }else break;
            }
        }

        void maxHeap(){
            int index = 0;
            while(index < len){
                int largest = index;
                int left = index*2+1;
                int right = index*2+2;
                if(left<len and arr[largest]<arr[left]) largest = left;
                if(right<len and arr[largest]<arr[right]) largest = right;

                if(largest!=index) exchagne(index, largest);
                else break;

                index = largest;
            }
        }

    public:

        PriorityQueue(){
            arr = (T*) malloc(sizeof(T)*capability);
        }

        PriorityQueue(int capability_){
            capability = capability_;
            arr = (T*) malloc(sizeof(T)*capability);
        }

        ~PriorityQueue(){
            delete arr;
            cout<<"delete arr..."<<endl;
        }

        T top(){
            if(len == 0) throw "priority queue is empty!";
            auto result = arr[0];
            arr[0] = arr[--len];
            maxHeap();
            return result;
        }

        bool empty(){ return len == 0;}

        void insert(T o){
            if(len == capability){
                capability = capability * 2;
                T *t = (T*) malloc(sizeof(T) * capability);
                memcpy(t, arr, capability/2);
                delete arr;
                arr = t;
            }
            arr[len++] = o;
            maintainHeap();
        }

};

