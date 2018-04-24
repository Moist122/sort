#include<algorithm>
#include<fstream>
//#include<string>

//check if array is sorted
template <typename V, typename C>
bool checkArray(V array[], int size, const C& comp) {
    for(int i=1; i<size;i++)
        if(!comp(array[i-1],array[i])) return false;
    return true;
}
//reverse order of array elements
template <typename V>
void reverseArray(V array[], int size) {
    int p=0, q=size-1;
    while(p<q) swap(array[p++],array[q--]);
}
//load array from file with given name
template <typename V>
void load_array_from_file(std::string filename, V array[], int size) {
    std::ifstream file (filename);
    std::string num;
    for(int i=0;i<size;++i) {
        getline(file, num, ' ') ;
        array[i] = std::stoi(num);
    }
    file.close();
}
//copy elements of array1 to array 2
template <typename V>
void copy_array(V array1[], V array2[], int size) {
    for(int i=0;i<size;++i) array2[i]=array1[i];
}