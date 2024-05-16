#include "../src/trie.cpp"


int main(){
    trie<int> t;
    trie<int> c(10);
    //std::cout<<t.get_weight()<<std::endl;
    t.add_child(c);
    std::cout<<t<<std::endl;
    //t.get_children().print();
    return 0;
}