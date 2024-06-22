/*
 * Your implementation of the container bag<Val>.
 * Write both the declaration and definition of the
 * container in this file.
 */

template <typename Val>
class bag{
    private:
        struct Cell{
            Val val;
            Cell* next;
            Cell* prev;

        };
        typedef Cell* pCell;
        pCell head;
        pCell tail;
    public:
        bag();
        bag(const bag& b);
        bag(bag&& b);
        ~bag();
        void clean();
        Val& get_head();
        Val& get_tail();
        const Val& get_head() const;
        const Val& get_tail() const;
        Val& at(int pos);
        Val& prepend(const Val& v);
        Val& append(const Val& v);
        bool empty() const;
        void print() const;
        Val& next_to(Val& v);
        const Val& at(int pos) const;

        bag<Val>& operator=(const bag<Val>& b);
        bag<Val>& operator=(bag<Val>&& b);

        bool operator==(const bag<Val>& b) const;
        bool operator!=(const bag<Val>& b) const;

        struct bag_iterator {
            public:
                using iterator_category = std::forward_iterator_tag;
                using value_type = Val;
                using pointer = Val*;
                using reference = Val&;

                bag_iterator(Cell* ptr);
                reference operator*() const;
                pointer operator->() const;
                bag_iterator& operator++();
                bag_iterator operator++(int);
                Cell* get_ptr();
                bool operator==(bag_iterator const&) const;
                bool operator!=(bag_iterator const&) const;

            private:
                Cell* m_ptr;
        };
        Val& insert(bag_iterator it,const Val& v);
        bag_iterator begin();
        bag_iterator end();

        struct const_bag_iterator {
            public:
                using iterator_category = std::forward_iterator_tag;
                using value_type = const Val;
                using pointer = const Val*;
                using reference = const Val&;

                const_bag_iterator(const Cell* ptr);
                reference operator*() const;
                pointer operator->() const;
                const_bag_iterator& operator++();
                const_bag_iterator operator++(int);
                const Cell* get_ptr() const;
                bool operator==(const_bag_iterator const&) const;
                bool operator!=(const_bag_iterator const&) const;

            private:
                const Cell* m_ptr;
        };
        const_bag_iterator begin() const;
        const_bag_iterator end() const;
};

template <typename Val>
bag<Val>::bag(){
    head=nullptr;
    tail=nullptr;
}
template <typename Val>
bag<Val>::bag(const bag& b){
    head=nullptr;
    tail=nullptr;
    pCell pc=b.head;
    while(pc!=nullptr){
        append(pc->val);
        pc=pc->next;
    }
}

template <typename Val>
bag<Val>::bag(bag&& b){
    head=b.head;
    tail=b.tail;
    b.head=b.tail=nullptr;
}

template <typename Val>
bag<Val>::~bag(){
    while(head!=nullptr){
        pCell pc=head;
        head=head->next;
        delete pc;
    }
}
template <typename Val>
void bag<Val>::clean(){
    while(head!=nullptr){
        pCell pc=head;
        head=head->next;
        delete pc;
    }
    head=tail=nullptr;
}

template <typename Val>
Val& bag<Val>::prepend(const Val& val){ 
    pCell pn=new Cell{val,head,nullptr};
    if(head!=nullptr){
        head->prev=pn;
        head=pn;
    }else{
        head=tail=pn;
    }
    return pn->val;
}
template <typename Val>
Val& bag<Val>::append(const Val& val){ 
    pCell pn=new Cell{val,nullptr,tail};
    if(tail!=nullptr){
        tail->next=pn;
        tail=pn;
    }else{
        head=tail=pn;
    }
    return pn->val;
}

template <typename Val>
Val& bag<Val>::get_head(){
    if(head!=nullptr)
        return head->val;
    /*
    else{
        //eccezione
    }
    */
}
template <typename Val>
Val& bag<Val>::get_tail(){
    if(tail!=nullptr)
        return tail->val;
    /*
    else{
        //eccezione
    }
    */
}

template <typename Val>
const Val& bag<Val>::get_head() const{
    if(head!=nullptr)
        return head->val;

}
template <typename Val>
const Val& bag<Val>::get_tail() const{
    if(tail!=nullptr)
        return tail->val;
    /*
    else{
        //eccezione
    }
    */
}
template <typename Val>
Val& bag<Val>::next_to(Val& v){
    pCell pc=head;
    bool found=false;
    while(pc!=nullptr && !found){
        if(pc->val==v){
            found=true;
            pc=pc->next;
        }else{
            pc=pc->next;
        }
    }

    if(!found || pc==nullptr){
        return v;
    }
    else
        return pc->val;
}

template<typename Val>
bool bag<Val>::empty() const{
    return head==nullptr;
}


template<typename Val>
void bag<Val>::print() const{
    pCell pc=head;
    while(pc!=nullptr){
        std::cout<<pc->val;
        if(pc->next!=nullptr){
            std::cout<<",";
        }
        pc=pc->next;
    }
}

template <typename Val>
bag<Val>& bag<Val>::operator=(const bag<Val>& b){
    if(this!=&b){
        while(head!=nullptr){
            pCell pc=head;
            head=head->next;
            delete pc;
        }
        head=tail=nullptr;
        pCell pc=b.head;
        while(pc!=nullptr){
            append(pc->val);
            pc=pc->next;
        }
    }
    return *this;
}

template <typename Val>
bag<Val>& bag<Val>::operator=(bag<Val>&& b){
    clean();
    head=b.head;
    tail=b.tail;
    b.head=b.tail=nullptr;
    return *this;
}

template <typename Val>
bool bag<Val>::operator==(const bag<Val>& b) const{
    pCell pc=head;
    pCell pb=b.head;
    while(pc!=nullptr && pb!=nullptr){
        if(pc->val!=pb->val){
            pc=nullptr;
        }else{
            pc=pc->next;
            pb=pb->next;
        }
    }
    return pc==pb;
}

template <typename Val>
bool bag<Val>::operator!=(const bag<Val>& b) const{
    pCell pc=head;
    pCell pb=b.head;
    while(pc!=nullptr && pb!=nullptr){
        if(pc->val!=pb->val){
            pc=nullptr;
        }else{
            pc=pc->next;
            pb=pb->next;
        }
    }
    return pc!=pb;

}



/*
bag iterator
*/
template <typename Val>
bag<Val>::bag_iterator::bag_iterator(Cell* ptr){
    m_ptr=ptr;
}

template <typename Val>
typename bag<Val>::bag_iterator::reference bag<Val>::bag_iterator::operator*() const{
    return m_ptr->val;
}

template <typename Val>
typename bag<Val>::bag_iterator::pointer bag<Val>::bag_iterator::operator->() const{
    return &(m_ptr->val);

}

template <typename Val>
typename bag<Val>::bag_iterator& bag<Val>::bag_iterator::operator++(){
    m_ptr=m_ptr->next;
    return *this;
}
template <typename Val>
typename bag<Val>::bag_iterator bag<Val>::bag_iterator::operator++(int){
    m_ptr=m_ptr->next;
    return *this;
}

template <typename Val>
bool bag<Val>::bag_iterator::operator==(const bag<Val>::bag_iterator& b) const{
    return m_ptr==b.m_ptr;
}
template <typename Val>
bool bag<Val>::bag_iterator::operator!=(const bag<Val>::bag_iterator& b) const{
    return m_ptr!=b.m_ptr;
}

template <typename Val>
typename bag<Val>::Cell* bag<Val>::bag_iterator::get_ptr(){
    return m_ptr;
}


template <typename Val>
Val& bag<Val>::insert(bag<Val>::bag_iterator it,const Val& v){
    Cell* ptr=it.get_ptr();
    if(false){
        pCell pn=new Cell{v,ptr,ptr->prev};
        if(ptr->prev!=nullptr){
            ptr->prev->next=pn;
            ptr->prev=pn;
        }else{
            head=pn;
            ptr->prev=pn;

        }
        return pn->val;
    }else{
        Val& pn=prepend(v);
        return pn;
    }
}

template <typename Val>
typename bag<Val>::bag_iterator bag<Val>::begin(){
    return {head};
}

template <typename Val>
typename bag<Val>::bag_iterator bag<Val>::end(){
    return {nullptr};
}


/*
const bag iterator
*/
template <typename Val>
bag<Val>::const_bag_iterator::const_bag_iterator(const Cell* ptr){
    m_ptr=ptr;
}

template <typename Val>
typename bag<Val>::const_bag_iterator::reference bag<Val>::const_bag_iterator::operator*() const{
    return m_ptr->val;
}

template <typename Val>
typename bag<Val>::const_bag_iterator::pointer bag<Val>::const_bag_iterator::operator->() const{
    return &(m_ptr->val);

}

template <typename Val>
typename bag<Val>::const_bag_iterator& bag<Val>::const_bag_iterator::operator++(){
    m_ptr=m_ptr->next;
    return *this;
}
template <typename Val>
typename bag<Val>::const_bag_iterator bag<Val>::const_bag_iterator::operator++(int){
    m_ptr=m_ptr->next;
    return *this;
}

template <typename Val>
bool bag<Val>::const_bag_iterator::operator==(const bag<Val>::const_bag_iterator& b) const{
    return m_ptr==b.m_ptr;
}
template <typename Val>
bool bag<Val>::const_bag_iterator::operator!=(const bag<Val>::const_bag_iterator& b) const{
    return m_ptr!=b.m_ptr;
}

template <typename Val>
const typename bag<Val>::Cell* bag<Val>::const_bag_iterator::get_ptr() const{
    return m_ptr;
}



template <typename Val>
typename bag<Val>::const_bag_iterator bag<Val>::begin() const{
    return {head};
}

template <typename Val>
typename bag<Val>::const_bag_iterator bag<Val>::end() const{
    return {nullptr};
}