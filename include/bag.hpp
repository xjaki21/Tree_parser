/*
 * Your implementation of the container bag<Val>.
 * Write both the declaration and definition of the
 * container in this file.
 */

template <typename Val>
class bag{
    public:
        bag();
        bag(const bag& b);
        ~bag();
        void add(Val v);
        void remove();
        bool operator==(const bag<Val>& b) const;
        bool operator!=(const bag<Val>& b) const;
    private:
        struct Cell{
            Val val;
            Cell* next;
        };
        typedef Cell* pCell;
        pCell head;
};

template <typename Val>
bag<Val>::bag(){
    head=nullptr;
}
template <typename Val>
bag<Val>::bag(const bag& b){
    pCell pc=b.head;
    while(pc!=nullptr){
        add(pc->val);
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
}

template <typename Val>
void bag<Val>::add(Val val){ 
    pCell pn=new Cell{val,head};
    head=pn;
}

template <typename Val>
void bag<Val>::remove(){
    if(head!=nullptr){
        pCell pc=head;
        head=head->next;
        delete pc;
    }
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