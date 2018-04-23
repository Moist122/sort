#include"heap.hh"
#include<iostream> /////////////////
template <typename Value, typename Comparator>
Heap<Value,Comparator>::Heap(const Comparator& c, Value* array, int n)
    :CompleteTree<Value>(array,n), comp(c) {
        int depth=floor(std::log2(this->size()));
        for(int i=pow(2,depth)-1;i>0;i--)
            downHeap(i);
        //for(int i=1;i<=this->size();i++) std::cout<<this->value(i)<<std::endl;
    }

template <typename Value, typename Comparator>
void Heap<Value,Comparator>::upHeap(int i) {
    if(this->isRoot(i)) return;
    int par=this->parent(i);
    if(comp(this->value(par),this->value(i))) return;
    this->swapPositions(i, par);
    upHeap(par);
}

template <typename Value, typename Comparator>
Value Heap<Value,Comparator>::removeMin() {
    Value v = this->value(this->root());
    this->value(this->root()) = this->value(this->last());
    //std::cout<<std::endl;
    //for(int i=1;i<=this->size();i++) std::cout<<this->value(i)<<std::endl;
    this->removeLast();
    downHeap(this->root());
    //std::cout<<std::endl;
    //for(int i=1;i<=this->size();i++) std::cout<<this->value(i)<<std::endl;
    return v;
}

template <typename Value, typename Comparator>
void Heap<Value,Comparator>::downHeap(int i) {
    if(!this->hasLeft(i)) return;
    if(!this->hasRight(i)) {
        if(!comp(this->value(i),this->value(this->left(i)))) 
            this->swapPositions(i,this->left(i));
        return;
    }
    int next;
    if(comp(this->value(i),this->value(this->left(i)))&&comp(this->value(i),this->value(this->right(i)))) return;
    else if(comp(this->value(this->left(i)),this->value(this->right(i)))) next=this->left(i);
    else next=this->right(i);
    this->swapPositions(i, next);
    downHeap(next);
}