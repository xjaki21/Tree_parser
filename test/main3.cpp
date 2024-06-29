#include "../src/trie.cpp"
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int main(int argc, char const** argv){
    trie<string> t;

    // Aprire il file per la lettura
    std::ifstream in("datasets/trie_string2.tr");
    if (!in) {
        cerr << "Errore nell'apertura del file di input." << endl;
        return 1;
    }
    try{
    // Leggere i dati nel trie
        in >> t;

        /*
        if (!in) {
            cerr << "Errore nella lettura del file." << endl;
            return 1;
        }
        */
   

    in.close();
    cout<<t<<endl;
    trie<string> empty;
    trie<string> e1;
    cout<<(e1==empty);
    cout<<"EMPTY: "<<empty<<endl;
    const trie<string> t2=empty[{"bello"}];
    cout<<"MAX LEAF OF T: "<<t.max()<<endl;
    //t=empty;
    
    for (auto it2 = t.begin(); it2 != t.end(); ++it2) {
        std::cout << it2.get_leaf() << ' ';
    }
    

    cout<<endl;

    for (auto leaf_it = t.begin(); leaf_it != t.end(); ++leaf_it) {
        trie<string>::node_iterator node_it = leaf_it; // we convert leaf_it into node_it to navigate from leaf to root
        std::vector<string> s;
        while (node_it != t.root()) {
            s.push_back(*node_it);
            ++node_it;
        }
        std::reverse(s.begin(), s.end());
        for (auto const& x: s) std::cout << x << ' ';
        std::cout << '\n';
    }
    cout<<endl;
  
    }catch(const parser_exception& e){
        cout<<"Parser Exception: "<<e.what()<<endl;
    }

    return 0;
}
