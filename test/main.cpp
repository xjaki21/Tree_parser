#include "../src/trie.cpp"
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int main(int argc, char const** argv){
    trie<string> t;
    // Aprire il file per la lettura
    std::ifstream in("datasets/trie_string1.tr");
    if (!in) {
        cerr << "Errore nell'apertura del file di input." << endl;
        return 1;
    }
    try{
    // Leggere i dati nel trie
        in >> t;
        if (!in) {
            cerr << "Errore nella lettura del file." << endl;
            return 1;
        }

        in.close();
        trie<string> t1;
        t1=t;
        cout<<t<<endl;
        cout<<(t1==t)<<endl;
        trie<string>& comp=t[{"languages","java",}];
        cout<<comp<<endl;
       // auto it=t.begin();
        cout<<"MAX LEAF= "<<t.max()<<endl;
        t.max().set_weight(10.1);
        cout<<t<<endl;

        //t.set_label(new string("root"));

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
   
    }catch(const parser_exception& e){
        cout<<"Parser Exception: "<<e.what()<<endl;
    }

    // Verifica del contenuto del trie
    // Assicurati che il tuo operatore == sia sovraccaricato correttamente
    // trie<char> another;
    // assert(t == another);

    // Per visualizzare il contenuto del trie o altre operazioni di debug
    // t.print(); // Assumendo che ci sia un metodo print() per il debug

    return 0;
}
