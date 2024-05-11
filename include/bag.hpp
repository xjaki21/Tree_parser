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