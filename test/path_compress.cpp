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

template <typename T>
void extract_sequences(const trie<T>& t){

}

int main(){
    trie<int> t1;
    read_trie(t1,"trie_int1.tr");
    cout<<"T1: "<<t1<<endl;
    t1.path_compress();
    cout<<"T1 COMPRESSED = "<<t1<<endl;

    trie<string> t2;
    read_trie(t2,"trie_string2.tr");
    trie<string> empty(0.0);
    t2+=empty;
    t2+=t2;
    cout<<"T2: "<<t2<<endl;
    t2.path_compress();
    cout<<"T2 COMPRESSED = "<<t2<<endl;



    const trie<int> t=t1;
    for (auto leaf_it = t.begin(); leaf_it != t.end(); ++leaf_it) {
        trie<int>::const_node_iterator node_it = leaf_it; // we convert leaf_it into node_it to navigate from leaf to root
        std::vector<int> s;
        while (node_it != t.root()) {
            s.push_back(*node_it);
            ++node_it;
        }
        std::reverse(s.begin(), s.end());
        for (auto const& x: s) std::cout << x << ' ';
        std::cout << '\n';
    }

    for (auto leaf_it = t2.begin(); leaf_it != t2.end(); ++leaf_it) {
        trie<string>::node_iterator node_it = leaf_it; // we convert leaf_it into node_it to navigate from leaf to root
        std::vector<string> s;
        while (node_it != t2.root()) {
            s.push_back(*node_it);
            ++node_it;
        }
        std::reverse(s.begin(), s.end());
        for (auto const& x: s) std::cout << x << ' ';
        std::cout << '\n';
    }
    cout<<t1.max()<<endl;
    
    trie<char> tt;
    read_trie(tt,"trie_char1.tr");
    std::vector<char> prefix{'b'};
    auto tpr = tt[prefix];
    for (auto it2 = tpr.begin(); it2 != tpr.end(); ++it2) {
        std::cout << *it2 << ' ';
    }


}