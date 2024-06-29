#include "../src/trie.cpp"
#include <iostream>
#include <algorithm>
#include <fstream>
using namespace std;

void read_trie(trie<char>& t,string file_name){
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

int main(){
    try{
        trie<char> t1(1.1);
        read_trie(t1,"trie_char2.tr");
        read_trie(t1,"trie_char2.tr");

        cout<<"T1: "<<t1<<endl;

        trie<char> t2(2.3);
        read_trie(t2,"trie_char3.tr");
        cout<<"T2: "<<t2<<endl;

        trie<char> t3=t1+t2;
        cout<<"T1+T2 = "<<t3<<endl;
        t1+=t1;
        cout<<"T1+T2 = "<<t1<<endl;
        
    }catch(const parser_exception& e){
        cout<<"Parser Exception: "<<e.what()<<endl;
    }
    // Aprire il file per la lettura
   
}