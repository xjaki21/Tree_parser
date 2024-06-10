/*
 * Your implementation of the container bag<Val>.
 * Write both the declaration and definition of the
 * container in this file.
 */

template <typename Val>
class bag{
    private:
        struct Cell{
            const Val& val;
            Cell* next;
            Cell* prev;
        };
        typedef Cell* pCell;
        pCell head;
        pCell tail;
    public:
        bag();
        bag(const bag& b);
        ~bag();
        const Val& first_leaf() const;
        const Val& get_tail() const;
        Val& at(int pos);
        void prepend(const Val& v);
        void append(const Val& v);
        void add_at(Val v,int pos);
        void remove();
        bool empty() const;
        void print() const;

        const Val& at(int pos) const;

        bag<Val>& operator=(const bag<Val>& b);
        bool operator==(const bag<Val>& b) const;
        bool operator!=(const bag<Val>& b) const;

        struct bag_iterator {
            public:
                using iterator_category = std::forward_iterator_tag;
                using value_type = Val;
                using pointer =  Val*;
                using reference = Val&;

                bag_iterator(Cell* ptr);
                reference operator*();
                pointer operator->();
                bag_iterator& operator++();
                bag_iterator operator++(int);
                Cell* get_ptr();
                bool operator==(bag_iterator const&);
                bool operator!=(bag_iterator const&);

            private:
                Cell* m_ptr;
        };
        void insert(bag_iterator it,const Val& v);
        bag_iterator begin();
        bag_iterator end();


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
bag<Val>::~bag(){
    while(head!=nullptr){
        pCell pc=head;
        head=head->next;
        delete pc;
    }
    head=nullptr;

}

template <typename Val>
const Val& bag<Val>::first_leaf() const{
    if(head!=nullptr && head->val.get_children().g)
        return head->val->get_children()->first_leaf();
}

template <typename Val>
void bag<Val>::prepend(const Val& val){ 
    pCell pn=new Cell{val,head,nullptr};
    if(head!=nullptr){
        head->prev=pn;
        head=pn;
    }else{
        head=tail=pn;
    }
}
template <typename Val>
void bag<Val>::append(const Val& val){ 
    pCell pn=new Cell{val,nullptr,tail};
    if(tail!=nullptr){
        tail->next=pn;
        tail=pn;
    }else{
        head=tail=pn;
    }
}
template <typename Val>
void bag<Val>::add_at(Val v,int pos){
    pCell pn=new Cell{v,nullptr,nullptr};
    int i=0;
    pCell pc=head;
    while(pc!=nullptr && i<pos){
        i++;
        pc=pc->next;
    }
    if(pc!=nullptr && head!=nullptr){
        pn->next=pc;
        pn->prev=pc->prev;
        pc->prev=pn;
    }else if(head==nullptr){
        head=tail=pn;
    }else{
        tail->next=pn;
        pn->prev=tail;
        tail=pn;
    }

}

template <typename Val>
void bag<Val>::remove(){
    if(head!=nullptr){
        pCell pc=head;
        head=head->next;
        delete pc;
    }
}

template<typename Val>
bool bag<Val>::empty() const{
    return head==nullptr;
}
template <typename Val>
Val& bag<Val>::at(int pos){
    int i=0;
    pCell pc=head;
    while(pc!=nullptr && i<pos){
        i++;
        pc=pc->next;
    }
    if(pc==nullptr){
        return head->val;
    }else{
        return pc->val;
    }
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
bool bag<Val>::operator==(const bag<Val>& b) const{
    pCell ph=head;
    pCell pb=b.head;
    bool equal=true;
    while(ph->val==pb->val){
        ph=ph->next;
        pb=pb->next;
    }
    return ph==pb;
}
template <typename Val>
bool bag<Val>::operator!=(const bag<Val>& b) const{
    pCell ph=head;
    pCell pb=b.head;
    while(ph->val==pb->val){
        ph=ph->next;
        pb=pb->next;
    }
    return ph!=pb;

}


/*
bag iterator
*/
template <typename Val>
bag<Val>::bag_iterator::bag_iterator(Cell* ptr){
    m_ptr=ptr;
}

template <typename Val>
typename bag<Val>::bag_iterator::reference bag<Val>::bag_iterator::operator*(){
    return m_ptr->val;
}

template <typename Val>
typename bag<Val>::bag_iterator::pointer bag<Val>::bag_iterator::operator->(){
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
bool bag<Val>::bag_iterator::operator==(const bag<Val>::bag_iterator& b){
    return m_ptr==b.m_ptr;
}
template <typename Val>
bool bag<Val>::bag_iterator::operator!=(const bag<Val>::bag_iterator& b){
    return m_ptr!=b.m_ptr;
}

template <typename Val>
typename bag<Val>::Cell* bag<Val>::bag_iterator::get_ptr(){
    return m_ptr;
}

template <typename Val>
void bag<Val>::insert(bag<Val>::bag_iterator it,const Val& v){
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

    }else{
        prepend(v);
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

