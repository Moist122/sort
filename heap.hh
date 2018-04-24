#pragma once
#include <vector>
#include <cmath>
//complete binary tree
template <typename Value>
class CompleteTree {
public:
    CompleteTree(Value* array, int n)
        :A(new Value[n+1]), _size(n) {
            for(int i=0;i<n;i++) A[i+1]=array[i];
        }
    ~CompleteTree() {delete[] A;}
    int size() const //number of elements
        {return _size;}
    Value& value(const int i) {return A[i];} //value on position i in array

    int left(const int i) //index of left child of ith element
        {return 2*i;}
    int right(const int i) //index of right child of ith element
        {return 2*i+1;}
    int parent(const int i) //index of parent of ith element
        {return i/2;}

    bool hasLeft(const int i) const //does ith element have left child
        {return i*2<=size();}
    bool hasRight(const int i) const //does ith element have right child
        {return i*2+1<=size();}
    bool isRoot(const int i) const //is ith element root
        {return i==1;}
    bool isEmpty() const //is tree empty
        {return size()==0;}

    int root() //index of root
        {return 1;}
    int last() //index of last element
        {return size();}
    
    void removeLast() //remove last element from tree
        {_size--;}
    void swapPositions(const int i, const int j) //swap positions on 2 indices
        {Value v=A[i]; A[i]=A[j]; A[j]=v;}
    
private:
    Value* A;
    int _size;
};

//Heap data structure
template <typename Value, typename Comparator>
class Heap:public CompleteTree<Value> {
public:
    Heap(const Comparator& c, Value* array, int size);
    void insert(Value v) //insert value to heap
        {this->addLast(v); goUp(CompleteTree<Value>::last());}
    Value removeMin(); //remove minimal element and return it
protected:
    void upHeap(int i); //restor heap property to ith element and ancestors
    void downHeap(int i); //restor heap property to ith element and offspring
private:
    Comparator comp;
};