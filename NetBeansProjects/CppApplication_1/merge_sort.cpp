#include <iostream>
#include <thread>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void merge(vector<double> left, vector<double> right, vector<double> base){
  int i = 0;
  int j = 0;
  int k = 0;
  while(i < left.size() && j < r){
    if(left[i] <= right[j]) base[k++] = left[i++];
    else base[k++] = right[j++];
  }
  while(i < l) base[k++] = left[i++];
  while(j < r) base[k++] = right[j++];
}
void s(bool doMultithreaded, double a[], int y){
}
void mergesort(bool doMultithreaded, double a[], int n){
  if(n < 2) return;
  else {
    unsigned int mid = abs(n/2);
    double left[mid];
    double right[n-mid];
    for(int i = 0; i < mid; ++i) left[i] = a[i];
    for(int i = 0; i < n-mid; ++i) right[i] = a[i+mid];
    if( doMultithreaded == true ) {
         thread t1( s, true, (void *) (left) , 4);
      //  thread t2( mergesort, true, right, n-mid );
        //t1.join(); 
    //    t2.join(); 
    }
     else {
        mergesort(false, left, mid);
        mergesort(false, right, n-mid);
     }
     merge(left, mid, right, n-mid, a);
  }    
}

int main(int argc, char* argv[]) {
  if (argc != 2 ) {
    cout << "You must input a file path!\n";
    return 1;
  }
  else {
    fstream f;
    double value;
    vector<double> arr;  
    int size = 0;
    
    f.open(argv[1], ios::in);
    while(f >> value) {
        arr[size++] = value;
    }
    
    cout << "\nDo you want to do sorting in multi-threaded way ? (y/n) : ";
    char answer;
    cin >> answer;
    
    switch( answer ) {
        // Multi-threaded mergesort
        case 'y': mergesort(true, arr); break;
        // Single-threaded mergesort
        case 'n': mergesort(false, arr); break;
        default : cout << "Wrong answer !!!\n"; return -1;
    }

    for(int i = 0; i < size; ++i)
      cout << arr[i] << " ";
    cout << endl;
  }
  return 0;
}
