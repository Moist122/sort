#pragma once
#include <vector>
#include <cmath>
template <typename Value>
class CompleteTree {
public:
    CompleteTree(Value* array, int n)
        :A(new Value[n+1]), _size(n) {
            for(int i=0;i<n;i++) A[i+1]=array[i];
        }
    ~CompleteTree() {delete[] A;}
    int size() const
        {return _size;}
    Value& value(const int i) {return A[i];}

    int left(const int i)
        {return 2*i;}
    int right(const int i)
        {return 2*i+1;}
    int parent(const int i)
        {return i/2;}

    bool hasLeft(const int i) const
        {return i*2<=size();}
    bool hasRight(const int i) const
        {return i*2+1<=size();}
    bool isRoot(const int i) const
        {return i==1;}
    bool isEmpty() const
        {return size()==0;}

    int root()
        {return 1;}
    int last()
        {return size();}
    
    /*void addLast(const Value& v)
        {vec.push_back(v);}*/
    void removeLast()
        {_size--;}
    void swapPositions(const int i, const int j)
        {Value v=A[i]; A[i]=A[j]; A[j]=v;}
    
private:
    Value* A;
    int _size;
};

template <typename Value, typename Comparator>
class Heap:public CompleteTree<Value> {
public:
    Heap(const Comparator& c, Value* array, int size);
    void insert(Value v)
        {this->addLast(v); goUp(CompleteTree<Value>::last());}
    Value removeMin();
protected:
    void upHeap(int i);
    void downHeap(int i);
private:
    Comparator comp;
};