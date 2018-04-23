#include <algorithm>
#include<cmath>
#include<list>
#include<vector>
#include"comparators.hh"
#include"heap.t.hpp"

#include<ctime>
#include<iostream>

using std::swap;
using std::list;
using std::vector;

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
void mergeSort1(V array[], int size, const C& comp) {
    if(size<=1) return;
    int size1 = ceil(size/2.);
    int size2 = size/2;
    //divide
    V* array1 = new V[size1];
    V* array2 = new V[size2];
    V* element = array;
    for(int i=0;i<size1;i++) array1[i]=*element++;
    for(int i=0;i<size2;i++) array2[i]=*element++;
    mergeSort1(array1, size1, comp);
    mergeSort1(array2, size2, comp);
    merge1(array,array1,size1,array2,size2,comp);
    delete[] array1;
    delete[] array2;
}

template <typename V, typename C>
void merge1(V array[], V array1[], int size1, V array2[], int size2, const C& comp) {
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
        hybridSort(array, left, comp, m-1);
    if(pivot!=&array[size-1])
        hybridSort(pivot+1, right, comp, m-1);
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