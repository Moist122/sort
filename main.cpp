#include<iostream> //c++11
#include<fstream>
#include<ctime>
#include "sortings.t.hpp"
#include "array_utility.t.hpp"

using std::ifstream;
using std::ofstream;
using std::string;
using std::stoi;
using std::cout;
using std::endl;
using std::to_string;

//test sorting arrays from files, show times using cout
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
    mergeSort(array, size, comp);
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

//test sorting algorithms, save times of sorting to file, arrays can be partialy sorted or reversed
//algorithms use comparator comp
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
    mergeSort(array, size, comp);
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
    introSort(array, size, comp);
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
    
    int arraysSizes=4; //number of array sizes tested
    int sizes[]={10000, 50000, 100000, 500000, 1000000};
    int arraysNumber=100; //number of arrays of each type
    int nMethods=8; //number of initial conditions for testing
    float sortedMethods[]={0,.25,.5,.75,.95,.99,.997,1};
    bool reversedMethods[]={0,0, 0, 0, 0, 0, 0, 1};
    for(int n=0;n<nMethods;n++){
        //files to save results
        ofstream mergeSortFile ("times/mergeSortTimes"+to_string(sortedMethods[n])+".csv");
        ofstream quickSortFile ("times/quickSortTimes"+to_string(sortedMethods[n])+".csv");
        ofstream introSortFile ("times/introSortTimes"+to_string(sortedMethods[n])+".csv");
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