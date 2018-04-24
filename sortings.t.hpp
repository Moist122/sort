#include<cmath>
#include"comparators.hh"
#include"heap.t.hpp"

using std::swap;

//sort array using recursive mergesort algorithm and comparator comp
template <typename V, typename C>
void mergeSort(V array[], int size, const C& comp) {
    if(size<=1) return;
    int size1 = ceil(size/2.);
    int size2 = size/2;
    //divide
    V* array1 = new V[size1];
    V* array2 = new V[size2];
    V* element = array;
    for(int i=0;i<size1;i++) array1[i]=*element++;
    for(int i=0;i<size2;i++) array2[i]=*element++;
    mergeSort(array1, size1, comp);
    mergeSort(array2, size2, comp);
    merge(array,array1,size1,array2,size2,comp);
    delete[] array1;
    delete[] array2;
}
//merge arrays for mergeSort
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

//quicksort of array, using comparator comp, first element is a pivot
template <typename V, typename C>
void quickSort(V array[], int size, const C& comp) {
    if(size<=1) return;
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
//heapsort of array using comparator comp
template <typename V, typename C>
void heapSort(V array[], int size, const C& comp) {
    Heap<V,C> h(comp,array,size);
    for(int i=0;i<size;i++) array[i]=h.removeMin();
}
//introspective sort of array with comparator comp
template <typename V, typename C>
void introSort(V array[], int size, const C& comp) {
    float m=2*log2(size);
    hybridSort(array,size,comp,m);
}
//utility of introSort called recursively
template <typename V, typename C>
void hybridSort(V array[], int size, const C& comp, float m) {
    if(m<=0) {
        heapSort(array,size, comp);
        return;
    }
    //quicksort
    if(size<=1) return;
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