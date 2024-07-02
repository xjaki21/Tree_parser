#include "trie.hpp"  // It is forbidden to include other libraries!

/* Here below, your implementation of trie. */


/* node iterators */
    template <typename T>
    trie<T>::node_iterator::node_iterator(trie<T>* t){
        m_ptr=t;
    }

    template <typename T>
    typename trie<T>::node_iterator::reference trie<T>::node_iterator::operator*() const{
        if(m_ptr!=nullptr && m_ptr->get_parent()!=nullptr && m_ptr->get_label()!=nullptr)
            return *(m_ptr->get_label());
        else
            throw parser_exception("LABEL IS NULL");
    }

    template <typename T>
    typename trie<T>::node_iterator::pointer trie<T>::node_iterator::operator->() const{
        if(m_ptr!=nullptr && m_ptr->get_parent()!=nullptr && m_ptr->get_label()!=nullptr)
            return m_ptr->get_label();
        else
            throw parser_exception("LABEL IS NULL");
    }

    template <typename T>
    typename trie<T>::node_iterator& trie<T>::node_iterator::operator++(){
        if(m_ptr!=nullptr)
            m_ptr=m_ptr->get_parent();
        else
            throw parser_exception("M_PTR IS NULL");
        return *this;
    }
    template <typename T>
    typename trie<T>::node_iterator trie<T>::node_iterator::operator++(int){
        if(m_ptr!=nullptr)
            m_ptr=m_ptr->get_parent();
        else
            throw parser_exception("M_PTR IS NULL");
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

/* const node iterator */
    template <typename T>
    trie<T>::const_node_iterator::const_node_iterator(trie<T> const* ptr){
        m_ptr=ptr;
    }

    template <typename T>
    typename trie<T>::const_node_iterator::reference trie<T>::const_node_iterator::operator*() const{
        if(m_ptr!=nullptr && m_ptr->get_parent()!=nullptr && m_ptr->get_label()!=nullptr)
            return *m_ptr->get_label();
        else
            throw parser_exception("LABEL IS NULL");    
    }

    template <typename T>
    typename trie<T>::const_node_iterator::pointer trie<T>::const_node_iterator::operator->() const{
        if(m_ptr!=nullptr && m_ptr->get_parent()!=nullptr && m_ptr->get_label()!=nullptr)
            return m_ptr->get_label();
        else
            throw parser_exception("LABEL IS NULL");    
    }

    template <typename T>
    typename trie<T>::const_node_iterator& trie<T>::const_node_iterator::operator++(){
        if(m_ptr!=nullptr)
            m_ptr=m_ptr->get_parent();
        else
            throw parser_exception("M_PTR IS NULL");
        return *this;
    }
    template <typename T>
    typename trie<T>::const_node_iterator trie<T>::const_node_iterator::operator++(int){
        if(m_ptr!=nullptr)
            m_ptr=m_ptr->get_parent();
        else
            throw parser_exception("M_PTR IS NULL");
        return *this;
    }  
    template <typename T>
    bool trie<T>::const_node_iterator::operator==(const_node_iterator const& n) const{
        return m_ptr==n.m_ptr;
    }
    template <typename T>
    bool trie<T>::const_node_iterator::operator!=(const_node_iterator const& n) const{
        return m_ptr!=n.m_ptr;
    }    
/* leaf iterators */
    template <typename T>
    trie<T>::leaf_iterator::leaf_iterator(trie<T>* t){
        m_ptr=t;
    }
    template <typename T>
    typename trie<T>::leaf_iterator::reference trie<T>::leaf_iterator::operator*() const{
        if(m_ptr!=nullptr && m_ptr->get_parent()!=nullptr && m_ptr->get_label()!=nullptr)
            return *m_ptr->get_label();
        else
            throw parser_exception("LABEL IS NULL");  
    }
    template <typename T>
    typename trie<T>::leaf_iterator::pointer trie<T>::leaf_iterator::operator->() const{
        if(m_ptr!=nullptr && m_ptr->get_parent()!=nullptr && m_ptr->get_label()!=nullptr)
            return m_ptr->get_label();
        else
            throw parser_exception("LABEL IS NULL");  
    }
    template <typename T>
    typename trie<T>::leaf_iterator& trie<T>::leaf_iterator::operator++(){
        if(m_ptr!=nullptr){
            if(m_ptr->get_parent()!=nullptr){
                trie<T>& parent=*m_ptr->get_parent();
                trie<T>& next=parent.get_children().next_to(get_leaf());
                if(next==*m_ptr && next.get_parent()==m_ptr->get_parent() && *next.get_label()==*m_ptr->get_label()){
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
        }else{
            throw parser_exception("ITERATOR IS NULL");
        }
        return *this;
    }
    template <typename T>
    typename trie<T>::leaf_iterator trie<T>::leaf_iterator::operator++(int){
        if(m_ptr!=nullptr){
            if(m_ptr->get_parent()!=nullptr){
                trie<T>& parent=*m_ptr->get_parent();
                trie<T>& next=parent.get_children().next_to(get_leaf());
                if(next==*m_ptr && next.get_parent()==m_ptr->get_parent() && *next.get_label()==*m_ptr->get_label()){
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
        }else{
            throw parser_exception("ITERATOR IS NULL");
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
        if(m_ptr!=nullptr)
            return *m_ptr;
        else
            throw parser_exception("LEAF IS NULL");
    }
/* const leaf iteartor*/
    template <typename T>
    trie<T>::const_leaf_iterator::const_leaf_iterator(trie<T> const* ptr){
        m_ptr=ptr;
    }
    template <typename T>
    typename trie<T>::const_leaf_iterator::reference trie<T>::const_leaf_iterator::operator*() const{
        if(m_ptr!=nullptr && m_ptr->get_parent()!=nullptr && m_ptr->get_label()!=nullptr)
            return *m_ptr->get_label();
        else
            throw parser_exception("LABEL IS NULL");
    }
    template <typename T>
    typename trie<T>::const_leaf_iterator::pointer trie<T>::const_leaf_iterator::operator->() const{
        if(m_ptr!=nullptr && m_ptr->get_parent()!=nullptr && m_ptr->get_label()!=nullptr)
            return m_ptr->get_label();
        else
            throw parser_exception("LABEL IS NULL");
    }
    template <typename T>
    typename trie<T>::const_leaf_iterator& trie<T>::const_leaf_iterator::operator++(){
        if(m_ptr!=nullptr){
            if(m_ptr->get_parent()!=nullptr){
                const trie<T>& parent=*m_ptr->get_parent();
                const trie<T>& next=parent.get_children().next_to(get_leaf());
                if(next==*m_ptr && next.get_parent()==m_ptr->get_parent() && *next.get_label()==*m_ptr->get_label()){
                    const_leaf_iterator lf=const_leaf_iterator(&parent);
                    ++lf;
                    m_ptr=lf.m_ptr;
                }else{
                    auto next_leaf=next.begin();
                    m_ptr=next_leaf.m_ptr;
                }
            }else{
                m_ptr=nullptr;    
            }
        }else{
            throw parser_exception("ITERATOR IS NULL");
        }
        return *this;
    }
    template <typename T>
    typename trie<T>::const_leaf_iterator trie<T>::const_leaf_iterator::operator++(int){
        if(m_ptr!=nullptr){
            if(m_ptr->get_parent()!=nullptr){
                const trie<T>& parent=*m_ptr->get_parent();
                const trie<T>& next=parent.get_children().next_to(get_leaf());
                if(next==*m_ptr && next.get_parent()==m_ptr->get_parent() && *next.get_label()==*m_ptr->get_label()){
                    const_leaf_iterator lf=const_leaf_iterator(&parent);
                    lf++;
                    m_ptr=lf.m_ptr;
                }else{
                    auto next_leaf=next.begin();
                    m_ptr=next_leaf.m_ptr;
                }
            }else{
                m_ptr=nullptr;    
            }
        }else{
            throw parser_exception("ITERATOR IS NULL");
        }
        return *this;
    }
    template <typename T>
    bool trie<T>::const_leaf_iterator::operator==(trie<T>::const_leaf_iterator const& l) const{
        return m_ptr==l.m_ptr;
    }
    template <typename T>
    bool trie<T>::const_leaf_iterator::operator!=(trie<T>::const_leaf_iterator const& l) const{
        return m_ptr!=l.m_ptr;
    }
    template <typename T>
    trie<T>::const_leaf_iterator::operator trie<T>::const_node_iterator() const{
        return const_node_iterator(m_ptr);
    }
    template <typename T>
    trie<T> const& trie<T>::const_leaf_iterator::get_leaf() const{
        if(m_ptr!=nullptr)
            return *m_ptr;
        else
            throw parser_exception("LEAF IS NULL");
    }

/* methods to return iterators */
    template <typename T>
    typename trie<T>::leaf_iterator trie<T>::begin(){
        if(m_c.empty() && m_p==nullptr){
            return leaf_iterator(this);
        }else if(m_c.empty()){
            return leaf_iterator(this);
        }else{
            return m_c.get_head().begin();
        }
    }
    template <typename T>
    typename trie<T>::leaf_iterator trie<T>::end(){
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

   template <typename T>
    typename trie<T>::const_leaf_iterator trie<T>::begin() const{
        if(m_c.empty() && m_p==nullptr){
            return const_leaf_iterator(this);
        }else if(m_c.empty()){
            return const_leaf_iterator(this);
        }else{
            return m_c.get_head().begin();
        }
    }
    template <typename T>
    typename trie<T>::const_leaf_iterator trie<T>::end() const{
       return const_leaf_iterator(nullptr);
    }
    
    template <typename T>
    typename trie<T>::const_node_iterator trie<T>::root() const{
        if(get_parent()==nullptr){
            return const_node_iterator(this);
        }else{
            return get_parent()->root();
        }
    }

/* constructors */
    template <typename T>
    trie<T>::trie(){
        m_p=nullptr;
        m_l=nullptr;
        m_w=0.0;
    }
    template <typename T>
    trie<T>::trie(double w){
        m_p=nullptr;
        m_l=nullptr;
        m_w=w;
    }
    template <typename T>
    trie<T>::trie(trie<T> const& t){
        m_p=nullptr;
        m_l=nullptr;
        m_w=t.m_w;
        for(auto it=t.m_c.begin();it!=t.m_c.end();++it){
            add_child(*it);
        }
    }
    template <typename T>
    trie<T>::trie(trie<T>&& t){
/*
        m_p=nullptr;
        m_l=t.m_l;
        t.m_l=nullptr;
        m_w=t.m_w;
        t.m_w=0.0;
        for(auto it=t.m_c.begin();it!=t.m_c.end();++it){
            add_child(*it);
        }
        t.m_c.clean();
        */
        m_p=nullptr;
        m_l=nullptr;
        m_w=t.m_w;
        //t.m_w=0.0;
        for(auto it=t.m_c.begin();it!=t.m_c.end();++it){
            add_child(*it);
        }
        t.m_c.clean();        

        if(t.m_p!=nullptr){
            t.m_p->m_c.remove(t);
        }
    }


/* destructor */
    template <typename T>
    trie<T>::~trie(){
        if(m_l!=nullptr){
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
            bool child_param=m_c.clean_except(t);; //controllo se il parametro è un figlio dell'albero

            for(auto it1=t.m_c.begin();it1!=t.m_c.end();++it1){
                add_child(*it1);
            }
            if(child_param){
                m_c.remove(t);
            }
        }
        return *this;
    }
    template <typename T>
    trie<T>& trie<T>::operator=(trie<T>&& t){
        /*
        if(this!=&t){
            m_w=t.m_w;
            m_c.clean();
            for(auto it=t.m_c.begin();it!=t.m_c.end();++it){
                add_child(*it);
            }
            t.m_c.clean();
        }
        return *this;
        */
       
        if(this!=&t){
            m_w=t.m_w;
            bool child_param=m_c.clean_except(t);; //controllo se il parametro è un figlio dell'albero
            for(auto it1=t.m_c.begin();it1!=t.m_c.end();++it1){
                add_child(*it1);
            }
            if(child_param){
                m_c.remove(t);
            }else{
                if(t.m_p!=nullptr){
                    t.m_p->m_c.remove(t);
                }
            }
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
        if(c.get_label()==nullptr){
            throw parser_exception("CHILD HAS NOT A LABEL");
        }
        else{
            m_w=0.0;
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
    
    template <typename T>
    T* trie<T>::get_label(){
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
        //controllo tutti i figli con bag iterator
        auto it1=m_c.begin();
        auto it2=t.m_c.begin();
        bool equal=true;
        do{
            if(it1==m_c.end() && it2==t.m_c.end()){
                equal=get_weight()==t.get_weight();
                it1=m_c.end();
                it2=t.m_c.end();
            }else if(it1==m_c.end() || it2==t.m_c.end()){
                equal=false;
            }else if(it1->get_weight()!=it2->get_weight() || *it1->get_label()!=*it2->get_label() || it1->get_children()!=it2->get_children()){
                equal=false;
            }else{
                ++it1;
                ++it2;
            }
        }while(it1!=m_c.end() && it2!=t.m_c.end() && equal);

        return equal;
    }
    template <typename T>
    bool trie<T>::operator!=(trie<T> const& t) const{
        auto it1=m_c.begin();
        auto it2=t.m_c.begin();
        bool not_equal=false;
        do{
            if(it1==m_c.end() && it2==t.m_c.end()){
                not_equal=get_weight()!=t.get_weight();
                it1=m_c.end();
                it2=t.m_c.end();
            }else if(it1==m_c.end() || it2==t.m_c.end()){
                not_equal=true;
            }else if(it1->get_weight()!=it2->get_weight() || *it1->get_label()!=*it2->get_label() || it1->get_children()!=it2->get_children()){
                not_equal=true;
            }else{
                ++it1;
                ++it2;
            }
        }while(it1!=m_c.end() && it2!=t.m_c.end() && !not_equal);
        
        return not_equal;
    }

/* max-weight leaf */
    template <typename T>
    trie<T>& trie<T>::max(){
        leaf_iterator it=begin();
        double max_weight=it.get_leaf().get_weight();
        ++it;
        while(it!=end()){
            if(it.get_leaf().get_weight()>max_weight){
                max_weight=it.get_leaf().get_weight();
            }
            ++it;
        }
        bool found=false;
        it=begin();
        while(it!=end() && !found){
            if(it.get_leaf().get_weight()==max_weight){
                found=true;
            }else{
                ++it;
            }
        }
        return it.get_leaf();
    }

    template <typename T>
    trie<T> const& trie<T>::max() const{
        const_leaf_iterator it=begin();
        double max_weight=it.get_leaf().get_weight();
        ++it;
        while(it!=end()){
            if(it.get_leaf().get_weight()>max_weight){
                max_weight=it.get_leaf().get_weight();
            }
            ++it;
        }
        bool found=false;
        it=begin();
        while(it!=end() && !found){
            if(it.get_leaf().get_weight()==max_weight){
                found=true;
            }else{
                ++it;
            }
        }
        return it.get_leaf();
    }
/* prefix-search */
    template <typename T>
    trie<T>& trie<T>::operator[](std::vector<T> const& v){
        auto it=m_c.begin();
        bool found=false;
        while(it!=m_c.end() && v.size()>0 && !found){
            if(*it->get_label()==v.at(0)){
                found=true;
            }else{
                ++it;
            }
        }
        if(found){
            std::vector<T> v1=v;
            v1.erase(v1.begin());
            trie<T>& t=*it;
            return t[v1];
        }else
            return *this;
    }

    template <typename T>
    trie<T> const& trie<T>::operator[](std::vector<T> const& v) const{
        auto it=m_c.begin();
        bool found=false;
        while(it!=m_c.end() && v.size()>0 && !found){
            if(*it->get_label()==v.at(0)){
                found=true;
            }else{
                ++it;
            }
        }
        if(found){
            std::vector<T> v1=v;
            v1.erase(v1.begin());
            const trie<T>& t=*it;
            return t[v1];
        }else
            return *this;
    }

/* facultative: union */
    template <typename T>
    trie<T> trie<T>::operator+(trie<T> const& t) const{
        trie<T> sum=*this;
        auto& bag1=get_children();
        auto& bag2=t.get_children();
        if(bag1.empty() && bag2.empty()){
            sum.m_w+=t.get_weight();
        }else{
            for(auto it2=bag2.begin();it2!=bag2.end();++it2){
                bool found=false;
                for(auto it1=bag1.begin();it1!=bag1.end();++it1){
                    if(*it2->get_label()==*it1->get_label()){
                        found=true;
                        trie<T> t=*it1+*it2;
                        t.m_w=it1->get_weight()+it2->get_weight();
                        sum[{*it1->get_label()}]=t;
                    }
                }
                if(!found){
                    sum.add_child(*it2);
                }
            }
        }
        return sum;
    }
    template <typename T>
    trie<T>& trie<T>::operator+=(trie<T> const& t){
        auto& bag1=get_children();
        auto& bag2=t.get_children();
        if(bag1.empty() && bag2.empty()){
            m_w+=t.get_weight();
        }else{
            for(auto it2=bag2.begin();it2!=bag2.end();++it2){
                bool found=false;
                for(auto it1=bag1.begin();it1!=bag1.end();++it1){
                    if(*it2->get_label()==*it1->get_label()){
                        found=true;
                        trie<T> t=*it1+*it2;
                        t.m_w=it1->get_weight()+it2->get_weight();
                        this->operator[]({*it1->get_label()})=t;
                    }
                }
                if(!found){
                    std::cout<<"add"<<std::endl;
                    add_child(*it2);
                }
            }
        }
        return *this;
    }


/* facultative: path compression */
    template <typename T>
    void trie<T>::path_compress(){
        if(!m_c.empty()){
            auto it=m_c.begin();
            if(get_label()!=nullptr && m_c.next_to(*it)==*it){
                //compress
                //*m_l=*m_l+*it->get_label();
                trie<T> t=*it;
                t.set_label(it->get_label());
                t.path_compress();
                *this=t;
                *m_l+=*t.m_l;
            }else{
                while(it!=m_c.end()){
                    it->path_compress();
                    ++it;
                }
            }
            bool sort=false;
            auto end= m_c.tail_it();
            while(end!=m_c.begin() && !sort){
                sort=true;
                auto start=m_c.begin();
                if(start!=end){
                    auto next=start;
                    ++next;
                    if(*start->get_label()>*next->get_label()){
                        sort=false;
                        auto temp=*start;
                        auto temp_ml=start->m_l;
                        *start=*next;
                        start->m_l=next->m_l;
                        *next=temp;
                        next->m_l=temp_ml;
                    }
                    ++start;
                }

                --end;
            }
        }
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
        os<<"children={";
        //os<<t.get_weight()<<" ";
        auto it=t.get_children().begin();
        while(it!=t.get_children().end()){
            os<<*it;
            if(++it!=t.get_children().end())
                os<<", ";
        }
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
    unsigned int i=0;
    while(i<str_children.length() && s){
        c=is.peek();
        if(c!=str_children.at(i)){
            s=false;
        }else{
            is>>c;
            i++;
        }
    }
    if(!s && i>0){
        for(unsigned int j=0;j<=i-1;j++){
            is.putback(str_children.at(i-j-1));
        }
    }
    return s;
}
template <typename T>
trie<T> TRIE_PARSER(std::istream& is);

template <typename T>
trie<T> ONE_LEAF(std::istream& is){
    trie<T> t;
    skip_blank_spaces(is);
    char c=0;
    bool empty=true;
    c=is.peek();
    while (c!=EOF && empty){
        c=is.peek();
        if (!std::isspace(c)) {
            empty=false;
        }
    }
    if(!empty){
        double weight=0.0;
        is>>weight;
        c=is.get();
        if(c!=' ') throw parser_exception("CHILDREN FORMAT ERROR");
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
    trie<T> CHILD_PARSER(std::istream& is){
        skip_blank_spaces(is);
        char c=0;
        trie<T> t;

        T label;
        is>>label;
        t.set_label(&label);
        c=is.get();
        if(c!=' ') throw parser_exception("CHILDREN FORMAT ERROR");
        
        if(is_children(is)){
            t=TRIE_PARSER<T>(is);
        }else{
            //foglia
            double weight=0.0;
            is>>weight;
            c=is.get();
            if(c!=' ') throw parser_exception("CHILDREN FORMAT ERROR");
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
    trie<T> TRIE_PARSER(std::istream& is){
        char c=0;

        if(!check_character(is,'=')) throw parser_exception("FILE IS NOT VALID");
        is>>c;

        if(!check_character(is,'{')) throw parser_exception("FILE IS NOT VALID");
        is>>c;
        trie<T> t(0.0);

       // skip_blank_spaces(is);
       while(true){
            trie<T> child=CHILD_PARSER<T>(is);
            t.add_child(child);
            if(!check_character(is,',')){
                c=is.peek();
                break;
            }else{
                is>>c;
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
        if(is_children(is)){
            t=TRIE_PARSER<T>(is);
        }else{
            t=ONE_LEAF<T>(is);
        }
        // Prova a leggere un altro carattere per verificare se lo stream è finito
        char c=0;
        while (is.peek()!=EOF && is.get(c)) {
            if (!std::isspace(c)) {
                throw parser_exception("FILE IS NOT VALID: EXTRA CHARACTERS AFTER '}'");
            }
        }
        return is;
    }