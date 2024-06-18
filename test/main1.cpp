#include "../src/trie.cpp"
#include <iostream>
#include <algorithm>
using namespace std;
trie<string> new_child(string l,trie<string>& p,double w){
    trie<string> t(w);
    string* s=new string(l);
    t.set_label(s);
    t.set_parent(&p);
    delete s;
    return t;
}

int main(){
    trie<string> t;
    //t.set_label(new string("root"));
    //trie<string>* a=new_child("gatto",t,1.2);
    trie<string> compilers=new_child("compilers",t,5.1);
    trie<string> gpp=new_child("g++",compilers,2.8);
    trie<string> javac=new_child("javac",compilers,3.1);

    trie<string> languages=new_child("languages",t,3.0);
    trie<string> cpp=new_child("c++",languages,1.1);
    trie<string> java=new_child("java",languages,0.5);
    compilers.add_child(gpp);
    compilers.add_child(javac);

    languages.add_child(java);
    languages.add_child(cpp);

    //compilers=languages;


    t.add_child(languages);
    t.add_child(compilers);

    trie<string> t1=t;
    //t.add_child(c);
    std::cout<<t<<std::endl;
    std::cout<<t1<<std::endl;

    //auto root=t.root();
    //cout<<"root: "<<*root<<endl;
    //cout<<compilers<<endl;
    //t.get_children().print();


    /*
    while(it!=t.end()){
        cout<<it.get_leaf()<<endl;
        ++it;
    }
    */
    


for (auto leaf_it = t.begin(); leaf_it != t.end(); leaf_it++) {
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



    
    return 0;
}