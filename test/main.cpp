#include "../src/trie.cpp"
#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char const** argv){
    trie<char> t;
    // Aprire il file per la lettura
    std::ifstream in("datasets/trie_char1.tr");
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
    
        cout<<t<<endl;

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
