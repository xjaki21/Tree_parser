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
template <typename T>
typename trie<T>::node_iterator trie<T>::node_iterator::operator++(int){
    m_ptr=m_ptr->get_parent();
    return *this;
}



/* constructors */
template <typename T>
trie<T>::trie(){
    m_p=nullptr;
    m_l=nullptr;
    m_c{default};
    m_w=0.0;
}
template <typename T>
trie<T>::trie(double w){
    m_p=nullptr;
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
    if(m_c.empty()){
        m_w=w;
    }
}
template <typename T>
void trie<T>::set_label(T* l){
    if(m_l==nullptr && m_p!=nullptr){
        m_l=l;
    }
}
template <typename T>
void trie<T>::set_parent(trie<T>* p){
    m_p=p;
}
template <typename T>
void trie<T>::add_child(trie<T> const& c){

    m_c.add(c);
}

 /* getters */
template <typename T>
double trie<T>::get_weight() const{
    return m_w;
}
template <typename T>
T const* trie<T>::get_label() const{
    return m_l;
}
template <typename T>
trie<T> const* trie<T>::get_parent() const{
    return m_p;
}
template <typename T>
bag<trie<T>> const& trie<T>::get_children() const{
    return m_c;
}

 /* comparison */
template <typename T>
bool trie<T>::operator==(trie<T> const& t) const{
    return this->m_c==t.m_c;
}
template <typename T>
bool trie<T>::operator!=(trie<T> const&) const{
    return this->m_c!=t.m_c;
}

