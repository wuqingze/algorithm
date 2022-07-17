template<typename T>
void f1(T o){
    f2(o, 1);
}

template<typename T>
void f2(T o, int i){
    int j = i+1;
}

int main(int argc, char* argv[]){

    return 0;
}
