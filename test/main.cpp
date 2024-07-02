#include "../src/trie.cpp"
#include <iostream>
#include <algorithm>
#include <fstream>
using namespace std;

template <typename T>
void read_trie(trie<T>& t,string file_name){
    std::ifstream in("datasets/"+file_name);
    if (!in.is_open()) {
        cerr << "Errore nell'apertura del file di input." << endl;
        return;
    }
    try{
    // Leggere i dati nel trie
        in >> t;
        in.close();
    }catch(const parser_exception& e){
        cout<<"Parser Exception: "<<e.what()<<endl;
    }
}


trie<char> test_move(){
    trie<char> t(1.3);
    return t;
}

int main(){
    try{
        trie<string> t1(1.1);
        read_trie(t1,"trie_int1.tr");
        cout<<"T1: "<<t1<<endl;
        trie<string> t2=t1;
        cout<<"T2: "<<t2<<endl;
        cout<<(t1==t2)<<endl;
        t1+=t1[{"z"}];
        cout<<"T1: "<<t1<<endl;

        trie<string> t3;
        read_trie(t3,"trie_string1.tr");
        cout<<"T3: "<<t3<<endl;

        t3=t3+t3;
        cout<<"T3+T2: "<<t3<<endl;


    }catch(const parser_exception& e){
        cout<<"Parser Exception: "<<e.what()<<endl;
    }
    // Aprire il file per la lettura
   
}