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
/* leaf iterators */
    template <typename T>
    trie<T>::leaf_iterator::leaf_iterator(trie<T>* t){
        m_ptr=t;
    }
    template <typename T>
    typename trie<T>::leaf_iterator::reference trie<T>::leaf_iterator::operator*() const{
        return (*m_ptr->get_label());
    }
    template <typename T>
    typename trie<T>::leaf_iterator::pointer trie<T>::leaf_iterator::operator->() const{
        return m_ptr->get_label();
    }
    template <typename T>
    typename trie<T>::leaf_iterator& trie<T>::leaf_iterator::operator++(){
        return m_ptr;
    }
    template <typename T>
    trie<T>& trie<T>::leaf_iterator::get_leaf() const{
        return *m_ptr;
    }

    template <typename T>
    trie<T>::const_leaf_iterator::const_leaf_iterator(trie<T> const* t){
        m_ptr=t;
    }
    template <typename T>
    typename trie<T>::const_leaf_iterator::reference trie<T>::const_leaf_iterator::operator*() const{
        return (*m_ptr->get_label());
    }
    template <typename T>
    typename trie<T>::const_leaf_iterator::pointer trie<T>::const_leaf_iterator::operator->() const{
        return m_ptr->get_label();
    }
    template <typename T>
    typename trie<T>::const_leaf_iterator& trie<T>::const_leaf_iterator::operator++(){
        return m_ptr;
    }
    template <typename T>
    trie<T> const& trie<T>::const_leaf_iterator::get_leaf() const{
        return *m_ptr;
    }

    /* methods to return iterators */
    template <typename T>
    typename trie<T>::leaf_iterator trie<T>::begin(){
        if(m_c.empty()){
            return leaf_iterator(this);
        }else{
            //std::cout<<"ok"<<std::endl;
            return m_c.get_head().begin();
        }
    }
    template <typename T>
    typename trie<T>::leaf_iterator trie<T>::end(){
        if(m_c.empty()){
            return leaf_iterator(this);
        }else{
            //std::cout<<"ok"<<std::endl;
            return m_c.get_tail().end();
        }
    }
    
    template <typename T>
    typename trie<T>::node_iterator trie<T>::root(){
        if(m_p==nullptr){
            //node_iterator* node_it=new node_iterator(this);
            //return *node_it;
            return node_iterator(this);
        }else{
            return m_p->root();
        }
    }

    template <typename T>
    typename trie<T>::const_leaf_iterator trie<T>::begin() const{
        if(m_c.empty()){
            return const_leaf_iterator(this);
        }else{
            //std::cout<<"ok"<<std::endl;
            return m_c.get_head().begin();
        }
    }

    template <typename T>
    typename trie<T>::const_leaf_iterator trie<T>::end() const{
        if(m_c.empty()){
            return const_leaf_iterator(this);
        }else{
            //std::cout<<"ok"<<std::endl;
            return m_c.get_tail().end();
        }
    }


/* constructors */
    template <typename T>
    trie<T>::trie(){
        m_p=nullptr;
        m_l=nullptr;
        //m_c();
        m_w=0.0;
    }
    template <typename T>
    trie<T>::trie(double w){
        m_p=nullptr;
        m_l=nullptr;
        //m_c();
        m_w=w;
    }
    template <typename T>
    trie<T>::trie(trie<T> const& t){
        m_p=t.m_p;
        m_l=new T(*t.get_label());
        m_w=t.m_w;
        m_c=t.m_c;
    }
    template <typename T>
    trie<T>::trie(trie<T>&& t){
        std::cout<<"move trie"<<std::endl;
        m_p=t.m_p;
        t.m_p=nullptr;
        m_l=t.m_l;
        t.m_l=nullptr;
        m_w=t.m_w;
        m_c=std::move(t.m_c);
    }


/* destructor */
    template <typename T>
    trie<T>::~trie(){
        if(m_l!=nullptr){
            std::cout<<*m_l;
            delete m_l;
            m_l=nullptr;
        }
    }
/* assignment operators */
    template <typename T>
    trie<T>& trie<T>::operator=(trie<T> const& t){
        if(this!=&t){
            m_w=t.get_weight();
            m_c=t.get_children();
        }
        return *this;
    }


/* setters*/
    template <typename T>
    void trie<T>::set_weight(double w){
        if(m_c.empty()){
            m_w=w;
        }
    }
    template <typename T>
    void trie<T>::set_label(T* l){
        /*
        if(m_l==nullptr && m_p!=nullptr){
            m_l=l;
        }else if(m_p==nullptr){
            throw parser_exception("root cant have parent");
        }
        */
       //m_l=l;
        if(m_l==nullptr && m_p==nullptr){
            m_l=new T(*l);
        }else{
            throw parser_exception("Trie is root or has already a father");
        }

    }
    template <typename T>
    void trie<T>::set_parent(trie<T>* p){
        m_p=p;
    }
    template <typename T>
    void trie<T>::add_child(trie<T> const& c){
        m_w=0.0;
        
        //m_c.add(c);
        //m_c.add_at(c,10);
        //c.set_parent(this);
        //uso iteratore di bag per inserire il child in ordine;
        //m_c.prepend(c);
        
        if(!m_c.empty()){
            auto it=m_c.begin();
            bool inserted=false;
            while(it!=m_c.end() && !inserted){ 
                if(*c.get_label()<*it->get_label()){
                    
                    inserted=true;
                    m_c.insert(it,c);
                }
                
                ++it;
            }
            
            if(!inserted){
                m_c.append(c);
            }
            
        }else{
            m_c.append(c);
        }
        
    
    }

 /* getters */
    template <typename T>
    double trie<T>::get_weight() const{
        return m_w;
    }
    template <typename T>
    T const* trie<T>::get_label() const{
        //if(m_l==nullptr) throw parser_exception("label is nullptr");
        //else return m_l;
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
    
    template <typename T>
    T* trie<T>::get_label(){
        //if(m_l==nullptr) throw parser_exception("label is nullptr");
        //else return m_l;
        return m_l;
    }
    template <typename T>
    trie<T>* trie<T>::get_parent(){
        return m_p;
    }
    template <typename T>
    bag<trie<T>>& trie<T>::get_children(){
        return m_c;
    }

 /* comparison */
    template <typename T>
    bool trie<T>::operator==(trie<T> const& t) const{
        return this->m_l==t.m_l && this->m_p==t.m_p && this->m_w==t.m_w && this- this->m_c==t.m_c;
    }
    template <typename T>
    bool trie<T>::operator!=(trie<T> const& t) const{
        return this->m_l!=t.m_l && this->m_p!=t.m_p && this->m_w!=t.m_w && this- this->m_c!=t.m_c;
    }


/* prefix-search */
    template <typename T>
    trie<T>& trie<T>::operator[](std::vector<T> const& v){
        
    }

/*streams*/
    template <typename T>
    std::ostream& operator<<(std::ostream& os, trie<T> const& t){
        if(t.get_label()!=nullptr){
            os<<*t.get_label()<<" ";
        }
        //os<<t.get_label()<<" ";
        if(t.get_children().empty()){
            os<<t.get_weight()<<" ";
        }
        os<<"childern={";
        //os<<t.get_weight()<<" ";
        t.get_children().print();
        os<<"}";
        return os;

    }