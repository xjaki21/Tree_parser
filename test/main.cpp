#include "../src/trie.cpp"
#include <iostream>
#include <utility>
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
    //trie<string>* a=new_child("gatto",t,1.2);
    string s="gatto";
    trie<string> a=std::move(new_child(s,t,2.1));
    trie<string> b=std::move(new_child("cane",a,1.1));
    a.add_child(b);

    trie<string> c=std::move(new_child("criceto",t,2.3));
    string c_s="criceto";
    
    t.add_child(a);
    t.add_child(c);
/*
    auto f_leaf=t.begin();
    cout<<"prima foglia: "<<f_leaf.get_leaf()<<endl;
    auto e_leaf=t.end();
    cout<<"ultima foglia: "<<e_leaf.get_leaf()<<endl;
   */
    
    //t.add_child(b);
    //a.add_child(b);
    //t.add_child(c);
   // t.add_child(a);

 


    //t.add_child(c);
    std::cout<<t<<std::endl;
    //t.get_children().print();
    return 0;
}