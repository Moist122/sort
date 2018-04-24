#include<iostream> //c++11
#include <iomanip>
#include<fstream>
#include<ctime>
#include "sortings.t.hpp"

#include<windows.h> //for windows only

using std::ifstream;
using std::ofstream;
using std::string;
using std::stoi;
using std::cout;
using std::endl;
using std::to_string;

template <typename V>
void load_array_from_file(string filename, V array[], int size) {
    ifstream file (filename);
    string num;
    for(int i=0;i<size;++i) {
        getline(file, num, ' ') ;
        array[i] = stoi(num);
    }
    file.close();
}

template <typename V>
void copy_array(V array1[], V array2[], int size) {
    for(int i=0;i<size;++i) array2[i]=array1[i];
}

template <typename V, typename C>
void testSortFromFile(string filename, int size, C comp, float sortedPart=0, bool reversed=false){
    time_t t;
    V* array0 = new int[size];
    V* array = new int[size];
    load_array_from_file<int>(filename,array0,size);
    quickSort(array0,size*sortedPart,comp);
    if(reversed) reverseArray(array0,size);
    
    copy_array(array0, array, size);
    t=clock();
    mergeSort1(array, size, comp);
    t=clock()-t;
    if(checkArray(array,size,comp))
        cout<<"Sorted with mergesort in: "<<(double)t/CLOCKS_PER_SEC<<" s"<<endl;
    else
        cout<<"Mergesort failed"<<endl;

    copy_array(array0, array, size);
    t=clock();
    quickSort(array, size, comp);
    t=clock()-t;
    if(checkArray(array,size,comp))
        cout<<"Sorted with quicksort in: "<<(double)t/CLOCKS_PER_SEC<<" s"<<endl;
    else
        cout<<"Quicksort failed"<<endl;

    copy_array(array0, array, size);
    t=clock();
    introSort(array, size, comp);
    t=clock()-t;
    if(checkArray(array,size,comp))
        cout<<"Sorted with introsort in: "<<(double)t/CLOCKS_PER_SEC<<" s"<<endl;
    else
        cout<<"Introsort failed"<<endl;
    delete[] array0;
    delete[] array;
}

template <typename V, typename C>
void testSortTime(string filename, int size, ofstream& mergeSortFile,\
ofstream& quickSortFile, ofstream& introSortFile, C comp, float sortedPart=0, bool reversed=false){
    time_t t;
    V* array0 = new int[size];
    V* array = new int[size];
    load_array_from_file<int>(filename,array0,size);
    quickSort(array0,size*sortedPart,comp);
    if(reversed) reverseArray(array0,size);
    
    copy_array(array0, array, size);
    t=clock();
    //mergeSort1(array, size, comp);
    t=clock()-t;
    if(checkArray(array,size,comp))
        mergeSortFile<<(double)t/CLOCKS_PER_SEC<<',';
    else
        mergeSortFile<<0<<',';

    copy_array(array0, array, size);
    t=clock();
    quickSort(array, size, comp);
    t=clock()-t;
    if(checkArray(array,size,comp))
        quickSortFile<<(double)t/CLOCKS_PER_SEC<<',';
    else
        quickSortFile<<0<<',';

    copy_array(array0, array, size);
    t=clock();
    //introSort(array, size, comp);
    t=clock()-t;
    if(checkArray(array,size,comp))
        introSortFile<<(double)t/CLOCKS_PER_SEC<<',';
    else
        introSortFile<<0<<',';
    delete[] array0;
    delete[] array;
}

int main() {
    ascending<int> comp;
    testSortFromFile<int>("50000/1.txt",50000,comp,1,1);
    
    int arraysSizes=4;
    int sizes[]={10000, 50000, 100000, 500000/*, 1000000*/};
    int arraysNumber=100;
    int nMethods=1;//8;
    float sortedMethods[]={/*0,.25,.5,.75,.95,.99,.997,*/1};
    bool reversedMethods[]={/*0,0, 0, 0, 0, 0, 0, */1};
    for(int n=0;n<nMethods;n++){
        //ofstream mergeSortFile ("times/mergeSortTimes"+to_string(sortedMethods[n])+".csv");
        ofstream mergeSortFile ("placeholder");
        ofstream quickSortFile ("times/quickSortTimes"+to_string(sortedMethods[n])+".csv");
        //ofstream introSortFile ("times/introSortTimes"+to_string(sortedMethods[n])+".csv");
        ofstream introSortFile ("placeholder2");
        float sortedPart=sortedMethods[n];
        bool reversed=reversedMethods[n];
        for(int i=0;i<arraysSizes;i++) {
            int size=sizes[i];
            mergeSortFile<<size<<'\n';
            quickSortFile<<size<<'\n';
            introSortFile<<size<<'\n';
            for(int j=0;j<arraysNumber;j++) {
                string filename=to_string(size)+"/"+to_string(j)+".txt";
                testSortTime<int>(filename,size,mergeSortFile,quickSortFile,introSortFile,comp,\
                sortedPart,reversed);
            }
            mergeSortFile<<size<<'\n';
            quickSortFile<<size<<'\n';
            introSortFile<<size<<'\n';
        }
        mergeSortFile.close();
        quickSortFile.close();
        introSortFile.close();
    }
}