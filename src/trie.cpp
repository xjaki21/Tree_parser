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
    template <typename T>
    bool trie<T>::node_iterator::operator==(node_iterator const& n) const{
        return m_ptr==n.m_ptr;
    }
    template <typename T>
    bool trie<T>::node_iterator::operator!=(node_iterator const& n) const{
        return m_ptr!=n.m_ptr;
    }
/* leaf iterators */
    template <typename T>
    trie<T>::leaf_iterator::leaf_iterator(trie<T>* t){
        m_ptr=t;
    }
    template <typename T>
    typename trie<T>::leaf_iterator::reference trie<T>::leaf_iterator::operator*() const{
        return *m_ptr->get_label();
    }
    template <typename T>
    typename trie<T>::leaf_iterator::pointer trie<T>::leaf_iterator::operator->() const{
        return m_ptr->get_label();
    }
    template <typename T>
    typename trie<T>::leaf_iterator& trie<T>::leaf_iterator::operator++(){
        if(m_ptr->get_parent()!=nullptr){
            trie<T>& parent=*m_ptr->get_parent();
            trie<T>& next=parent.get_children().next_to(get_leaf());
            if(next==*m_ptr){
                //devo scorrere sul padre e vedere se ci sono altri rami con foglie
                leaf_iterator lf=leaf_iterator(&parent);
                ++lf;
                m_ptr=lf.m_ptr;
            }else{
                auto next_leaf=next.begin();
                m_ptr=next_leaf.m_ptr;
            }
        }else{
            m_ptr=nullptr;    
        }
        return *this;
    }
    template <typename T>
    typename trie<T>::leaf_iterator trie<T>::leaf_iterator::operator++(int){
        if(m_ptr->get_parent()!=nullptr){
            trie<T>& parent=*m_ptr->get_parent();
            trie<T>& next=parent.get_children().next_to(get_leaf());
            if(next==*m_ptr){
                //devo scorrere sul padre e vedere se ci sono altri rami con foglie
                leaf_iterator lf=leaf_iterator(&parent);
                lf++;
                m_ptr=lf.m_ptr;
            }else{
                auto next_leaf=next.begin();
                m_ptr=next_leaf.m_ptr;
            }
        }else{
            m_ptr=nullptr;    
        }
        return *this;
    }
    template <typename T>
    bool trie<T>::leaf_iterator::operator==(trie<T>::leaf_iterator const& l) const{
        return m_ptr==l.m_ptr;
    }
    template <typename T>
    bool trie<T>::leaf_iterator::operator!=(trie<T>::leaf_iterator const& l) const{
        return m_ptr!=l.m_ptr;
    }
    template <typename T>
    trie<T>::leaf_iterator::operator trie<T>::node_iterator() const{
        return node_iterator(m_ptr);
    }
    template <typename T>
    trie<T>& trie<T>::leaf_iterator::get_leaf() const{
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
        /*
        restituisce ultima foglia
        if(m_c.empty()){
            return const_leaf_iterator(this);
        }else{
            return m_c.get_tail().end();
        }
        */
       return leaf_iterator(nullptr);
    }
    
    template <typename T>
    typename trie<T>::node_iterator trie<T>::root(){
        if(m_p==nullptr){
            return node_iterator(this);
        }else{
            return m_p->root();
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
        m_p=nullptr;
        m_l=nullptr;
        m_w=t.m_w;
        for(auto it=t.m_c.begin();it!=t.m_c.end();++it){
            trie<T>& child=m_c.append(*it);
            child.set_label(it->m_l);
            child.set_parent(this);
        }
    }
    template <typename T>
    trie<T>::trie(trie<T>&& t){
        //m_p=t.m_p;
        //t.m_p=nullptr;
        //m_l=t.m_l;
        //t.m_l=nullptr;
        m_w=t.m_w;
        m_c=std::move(t.m_c);
    }


/* destructor */
    template <typename T>
    trie<T>::~trie(){
        if(m_l!=nullptr){
            //std::cout<<*m_l;
            delete m_l;
            m_l=nullptr;
            m_p=nullptr;
        }
    }
/* assignment operators */
    template <typename T>
    trie<T>& trie<T>::operator=(trie<T> const& t){
        if(this!=&t){
            m_w=t.m_w;
            m_c.clean();
            for(auto it=t.m_c.begin();it!=t.m_c.end();++it){
                trie<T> child=*it;
                child.set_label(it->m_l);
                child.set_parent(this);
                m_c.append(child);
            }
        }
        return *this;
    }
    template <typename T>
    trie<T>& trie<T>::operator=(trie<T>&& t){
        if(this!=&t){
            m_w=t.m_w;
            m_c=std::move(t.m_c);
        }
        return *this;

    }




/* setters*/
    template <typename T>
    void trie<T>::set_weight(double w){
        if(m_c.empty()){
            m_w=w;
        }else
            throw parser_exception("Cannot set weight: Node is not a leaf!");
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
        
        if(!m_c.empty()){
            auto it=m_c.begin();
            bool inserted=false;
            while(it!=m_c.end() && !inserted){ 
                if(*c.get_label()==*it->get_label()){
                    throw parser_exception("FORMAT ERROR: LABELS ARE REPEATED");
                }else if(*c.get_label()<*it->get_label()){
                    inserted=true;
                    trie<T>& child=m_c.insert(it,c);
                    child.set_label(c.m_l);
                    child.set_parent(this);
                }

                ++it;

            }
            
            if(!inserted){
                trie<T>& child=m_c.append(c);
                child.set_label(c.m_l);
                child.set_parent(this);
            }
            
        }else{
            trie<T>& child=m_c.append(c);
            child.set_label(c.m_l);
            child.set_parent(this);
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
        //DA SISTEMARE
        if(get_label()!=nullptr && t.get_label()!=nullptr)
            return *m_l==*t.m_l && m_w==t.m_w && m_c==t.m_c;
        else
            return m_l==t.m_l && m_w==t.m_w && m_c==t.m_c;
    }
    template <typename T>
    bool trie<T>::operator!=(trie<T> const& t) const{
        return  m_w!=t.m_w || m_c!=t.m_c;
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
/*
CONTEXT FREE GRAMMAR

*/
static void skip_blank_spaces(std::istream& is) {
    char c = 0;
    is >> c;
    is.putback(c);
}

static bool check_character(std::istream& is,char chr){
    skip_blank_spaces(is);
    char c=0;
    c=is.peek();
    if(c!=chr) return false;
    else return true;

}
static bool is_children(std::istream& is){
    skip_blank_spaces(is);
    std::string str_children="children";
    char c=0;
    bool s=true;
    int i=0;
    while(i<str_children.length() && s){
        c=is.peek();
        if(c!=str_children.at(i)){
            s=false;
        }else{
            is>>c;            
        }
        i++;
    }
    return s;
}
template <typename T>
trie<T> TRIE(std::istream& is);

    template <typename T>
    trie<T> CHILD(std::istream& is){
       // skip_blank_spaces(is);ù
        char c=0;
        trie<T> t;

        T label;
        is>>label;
        std::cout<<"label: "<<label<<std::endl;
        t.set_label(&label);
        if(is_children(is)){
            t=TRIE<T>(is);
        }else{
            //foglia
            double weight=0.0;
            is>>weight;
            std::cout<<"weight: "<<weight<<std::endl;
            if(!is_children(is)) throw parser_exception("LEAF DOESNT END WITH children={}");
            if(!check_character(is,'=')) throw parser_exception("LEAF DOESNT END WITH children={}");
            is>>c;
            if(!check_character(is,'{')) throw parser_exception("LEAF DOESNT END WITH children={}");
            is>>c;
            if(!check_character(is,'}')) throw parser_exception("LEAF DOESNT END WITH children={}");
            is>>c;
            t.set_weight(weight);
        }
        return t;
    }
    template <typename T>
    trie<T> TRIE(std::istream& is){
        char c=0;

        if(!check_character(is,'=')) throw parser_exception("FILE IS NOT VALID");
        is>>c;

        if(!check_character(is,'{')) throw parser_exception("FILE IS NOT VALID");
        is>>c;
        trie<T> t(0.0);

       // skip_blank_spaces(is);
       while(true){
            trie<T> child=CHILD<T>(is);
            t.add_child(child);
            if(!check_character(is,',')){
                c=is.peek();
                //std::cout<<"virgola: "<<c<<std::endl;

                break;
            }else{
                is>>c;
                std::cout<<"virgola: "<<c<<std::endl;
            }
       }
        if(!check_character(is,'}')) throw parser_exception("FILE IS NOT VALID: NOT ENDS WITH '}'");
        if(is>>c){
            return t;
        }else{
            throw parser_exception("FILE IS NOT VALID: NOT ENDS WITH '}'");
        }
    } 

    template <typename T>
    std::istream& operator>>(std::istream& is,trie<T>& t){
        if(!is_children(is)) throw parser_exception("FILE IS NOT A TRIE");
        t=TRIE<T>(is);
        //skip_blank_spaces(is);
        // Prova a leggere un altro carattere per verificare se lo stream è finito
        char c=0;
        while (is.peek()!=EOF && is.get(c)) {
            if (!std::isspace(c)) {
                throw parser_exception("FILE IS NOT VALID: EXTRA CHARACTERS AFTER '}'");
            }
        }
        return is;
    }