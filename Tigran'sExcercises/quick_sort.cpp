#include <iostream>
#include <thread>
#include <fstream>
#include <string>

using namespace std;

int partition(double a[], int start, int end){
  int pivot = a[end];
  int pIndex = start;
  for(int i = start; i < end; ++i)
    if(a[i] <= pivot) swap(a[i], a[pIndex++]);
  swap(a[pIndex], a[end]);
  return pIndex;  
}

void quicksort(bool doMultithreaded, double a[], int start, int end) {
  if(start < end){
    int pIndex  = partition(a, start, end);
    if( doMultithreaded == true ) {
        thread t1(quicksort, true, a, start, pIndex-1);
        thread t2(quicksort, true, a, pIndex+1, end);
        t1.join(); 
        t2.join(); 
    }
    else {
        quicksort(false, a, start, pIndex-1);
        quicksort(false, a, pIndex+1, end);
    }
  }    
}

int main(int argc, char* argv[]){
  if (argc != 2 ) {
    cout << "You must input a file path!\n";
    return 1;
  }
  else {
    fstream f;
    string data;
    double value;
    double arr[100];  
    int size = 0;
    
    f.open(argv[1], ios::in);
    while(f >> value) {
        arr[size++] = value;
    }
    
    cout << "\Do you want to do sorting in multi-threaded way ? (y/n) : ";
    char answer;
    cin >> answer;
    
    switch( answer ) {
        // Multi-threaded quickSort
        case 'y': quicksort(true, arr, 0, size-1); break;
        // Single-threaded quickSort
        case 'n': quicksort(true, arr, 0, size-1); break;
        default : cout << "Wrong answer !!!\n"; return -1;
    }

    for(int i = 0; i < size; ++i)
      cout << arr[i] << " ";
    cout << endl;
  }
  return 0;
}
