#include<list>
#include<iostream>
#include<cmath>
#include<ctime>
#include <algorithm>

#include"comparators.hh"
#include"heap.t.hpp"


using std::cout;
using std::cin;
using std::endl;
using std::list;
using std::swap;

template <typename V, typename C>
void mergeSort(V array[], int size, const C& comp) {
    typedef typename list<V>::iterator iter;
    list<V> l;
    for(int i=0;i<size;++i) l.push_back(array[i]);
    mergeSort(l,comp);
    iter p=l.begin();
    for(int i=0;i<size;++i) array[i]=*p++;
}
template <typename V, typename C>
void mergeSort(list<V>& l, const C& comp) {
    typedef typename list<V>::iterator iter;
    int size=l.size();
    if(size<=1) return;
    //divide
    list<V> l1, l2;
    iter p = l.begin();
    for(int i=0;i<size/2;i++) l1.push_back(*p++);
    for(int i=size/2;i<size;i++) l2.push_back(*p++);
    l.clear();
    mergeSort(l1, comp);
    mergeSort(l2, comp);
    merge(l,l1,l2,comp);
}
template <typename V, typename C>
void merge(list<V>& l, list<V>& l1, list<V>& l2, const C& comp) {
    typedef typename list<V>::iterator iter;
    iter p=l1.begin();
    iter q=l2.begin();
    while(p!=l1.end()&&q!=l2.end()) {
        if(comp(*p,*q)) l.push_back(*p++);
        else l.push_back(*q++);
    }
    while(p!=l1.end()) l.push_back(*p++);
    while(q!=l2.end()) l.push_back(*q++);
}

template <typename V, typename C>
void merge(V array[], V array1[], int size1, V array2[], int size2, const C& comp) {
    int p=0; //iterate array1
    int q=0; //iterate array2
    int i=0; //iterate array
    while(p<size1&&q<size2) {
        if(comp(array1[p],array2[q])) array[i++]=array1[p++];
        else array[i++]=array2[q++];
    }
    if(p<size1) while(p<size1) array[i++] = array1[p++];
    else        while(q<size2) array[i++] = array2[q++];
}

template <typename V, typename C>
void quickSort(V array[], int size, const C& comp) {
    if(size<=1) return;
    //divide
    V* pivot = array;
    V* p = &(array[size-1]);
    bool from_left=false;
    int left=0, right=0;
    while(p!=pivot) {
        if(from_left) {
            if(comp(*pivot,*p)) {
                swap(*p,*pivot);
                V* old_pivot=pivot;
                pivot=p;
                p=old_pivot-1;
                from_left=false;
                right++;
            }
            else {
                left++;
                p++;
            }
        }
        else {
            if(comp(*p,*pivot)) {
                swap(*p,*pivot);
                V* old_pivot=pivot;
                pivot=p;
                p=old_pivot+1;
                from_left=true;
                left++;
            }
            else {
                right++;
                p--;
            }
        }
    }
    if(pivot!=array)
        quickSort(array, left, comp);
    if(pivot!=&array[size-1])
        quickSort(pivot+1, right, comp);
}
/*
template <typename V>
list<V> merge(list<V>& l1, V pivot, list<V>& l2) {
    typedef typename list<V>::iterator iter;
    list<V> sortedList;
    iter i = l1.begin();
    while(i!=l1.end()) sortedList.push_back(*i++);
    sortedList.push_back(pivot);
    i = l2.begin();
    while(i!=l2.end()) sortedList.push_back(*i++);
    return sortedList;
}*/

template <typename V, typename C>
void heapSort(V array[], int size, const C& comp) {
    Heap<V,C> h(comp,array,size);
    for(int i=0;i<size;i++) array[i]=h.removeMin();
}

template <typename V, typename C>
void introSort(V array[], int size, const C& comp) {
    float m=2*log2(size);
    hybridSort(array,size,comp,m);
}

template <typename V, typename C>
void hybridSort(V array[], int size, const C& comp, float m) {
    if(m<=0) {
        heapSort(array,size, comp);
        return;
    }
    //quicksort
    if(size<=1) return;
    //divide
    V* pivot = array;
    V* p = &(array[size-1]);
    bool from_left=false;
    int left=0, right=0;
    while(p!=pivot) {
        if(from_left) {
            if(comp(*pivot,*p)) {
                swap(*p,*pivot);
                V* old_pivot=pivot;
                pivot=p;
                p=old_pivot-1;
                from_left=false;
                right++;
            }
            else {
                left++;
                p++;
            }
        }
        else {
            if(comp(*p,*pivot)) {
                swap(*p,*pivot);
                V* old_pivot=pivot;
                pivot=p;
                p=old_pivot+1;
                from_left=true;
                left++;
            }
            else {
                right++;
                p--;
            }
        }
    }
    if(pivot!=array)
        hybridSort(array, left, comp, m);
    if(pivot!=&array[size-1])
        hybridSort(pivot+1, right, comp, m);
}

template <typename V>
void printList(list<V>& l) {
    typedef typename list<V>::iterator iter;
    iter i=l.begin();
    while(i!=l.end()) cout<<*i++<<" ";
    cout<<endl;
}
template <typename V>
void printArray(V array[], int size) {
    for(int i=0;i<size;i++) {
        if(array[i]<10) cout<<" ";
        cout<<array[i]<<" ";
    }
    cout<<endl;
}
template <typename V, typename C>
bool checkArray(V array[], int size, const C& comp) {
    for(int i=1; i<size;i++)
        if(!comp(array[i-1],array[i])) return false;
    return true;
}
template <typename V>
void reverseArray(V array[], int size) {
    int p=0, q=size-1;
    while(p<q) swap(array[p++],array[q--]);
}

int main() {
    typedef typename list<int>::iterator iter;
    int size=10;
    int array[size];
    ascending<int> comp;
    descending<int> comp2;
    /* initialize random seed: */
    srand (time(NULL));
    time_t t;

    for(int i=0;i<10;++i)
        array[i]=rand()%100;
    quickSort(array,size*.5,comp);
    printArray<int>(array, size);

    t=clock();
    mergeSort(array, size, comp);
    t=clock()-t;

    if(checkArray(array,size,comp)) cout<<"ok"<<endl;
    //reverseArray(array,size);
    printArray<int>(array, size);
    cout<<"Merge sort: "<<(double)t/CLOCKS_PER_SEC<<endl;

    for(int i=0;i<10;++i)
        array[i]=rand()%100;

    t=clock();
    quickSort(array,size,comp);
    t=clock()-t;

    if(checkArray(array,size,comp)) cout<<"ok"<<endl;
    printArray<int>(array, size);
    cout<<"Quick sort: "<<(double)t/CLOCKS_PER_SEC<<endl;

    for(int i=0;i<10;++i)
        array[i]=rand()%100;

    t=clock();
    heapSort(array, size,comp);
    t=clock()-t;

    if(checkArray(array,size,comp)) cout<<"ok"<<endl;
    printArray<int>(array, size);
    cout<<"Heap sort: "<<(double)t/CLOCKS_PER_SEC<<endl;

    for(int i=0;i<10;++i)
        array[i]=rand()%100;
    
    t=clock();
    introSort(array,size,comp);
    t=clock()-t;

    if(checkArray(array,size,comp)) cout<<"ok"<<endl;
    printArray<int>(array, size);
    cout<<"Intro sort: "<<(double)t/CLOCKS_PER_SEC<<endl;
    return 0;

}