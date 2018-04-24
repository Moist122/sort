#include<fstream> //c++11
#include<ctime>

const int elem_num=1000000; //specify array size
//create 100 arrays and save to file
int main() {
    srand (time(NULL));
    for(int i=0;i<100;++i) {
        int* array = new int[elem_num];
        for(int j=0;j<elem_num;++j)
            array[j] = rand();
        std::ofstream myfile (std::to_string(elem_num)+"/"+std::to_string(i)+".txt");
        if (myfile.is_open())
            for(int j=0;j<elem_num;++j)
                myfile<<array[j]<<' ';
        myfile.close();
        delete[] array;
    }
}