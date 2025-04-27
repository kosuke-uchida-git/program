#include"functions.h"

int sign(double& number){
    if(number>0.0)
        return 1;
    else if(number<0.0)
        return -1;
    else
        return 0;
}

void shuffle(double* array, int size, int seed){
    srand(seed);
    double* remain=new double[size];
    for(int i=0;i<size;i++)
        remain[i]=array[i];
    for(int i=0;i<size;i++){
        int index=rand()%(size-i);
        array[i]=remain[index];
        remain[index]=remain[size-i-1];
    }
    delete[] remain;
}

void shuffle(int* array, int size, int seed){
    srand(seed);
    int* remain=new int[size];
    for(int i=0;i<size;i++)
        remain[i]=array[i];
    for(int i=0;i<size;i++){
        int index=rand()%(size-i);
        array[i]=remain[index];
        remain[index]=remain[size-i-1];
    }
    delete[] remain;
}