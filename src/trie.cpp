#include "trie.hpp"  // It is forbidden to include other libraries!

/* Here below, your implementation of trie. */


/* node iterators */
template <typename T>
trie<T>::node_iterator::node_iterator(trie<T>* t){
    m_ptr=t;
}

template <typename T>
typename trie<T>::node_iterator::reference trie<T>::node_iterator::operator*() const{
    return *(m_ptr->get_label());
}

template <typename T>
typename trie<T>::node_iterator::pointer trie<T>::node_iterator::operator->() const{
    return m_ptr->get_label();
}

template <typename T>
typename trie<T>::node_iterator& trie<T>::node_iterator::operator++(){
    m_ptr=m_ptr->get_parent();
    return *this;
}

/* constructors */
template <typename T>
trie<T>::trie(){
    m_p=*this;
    m_l=nullptr;
    m_c();
    m_w=0.0;
}
template <typename T>
trie<T>::trie(double w){
    m_p=*this;
    m_l=nullptr;
    m_c{default};
    m_w=w;
}


/* destructor */
template <typename T>
trie<T>::~trie()=default;

/* setters*/
template <typename T>
void trie<T>::set_weight(double w){
    m_w=w;
}
template <typename T>
void trie<T>::set_label(T* l){
    m_l=l;
}
template <typename T>
void trie<T>::set_parent(trie<T>* p){
    m_p=p;
}
template <typename T>
void add_child(trie<T> const& c){

}