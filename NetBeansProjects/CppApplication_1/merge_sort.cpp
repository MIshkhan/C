#include <iostream>
#include <thread>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void merge(vector<double> left, vector<double> right, vector<double>& base) {
  int i = 0, j = 0, k = 0;
  while(i < left.size() && j < right.size()) {
    if(left[i] <= right[j]) base[k++] = left[i++];
    else base[k++] = right[j++];
  }
  while( i < left.size() ) base[k++] = left[i++];
  while( j < right.size() ) base[k++] = right[j++];  
}

void mergesort(bool doMultithreaded,  vector<double>& a) {
  int n = a.size();
  if(n < 2) return;
  else {
    vector<double> left, right;
    int i = 0;
    for(i = 0; i < n/2; ++i) left.push_back(a[i]);
    for( ; i < n; ++i) right.push_back(a[i]);
    if( doMultithreaded == true ) {
      thread t1( mergesort, true, ref(left) );
      thread t2( mergesort, true, ref(right) );
      t1.join(); 
      t2.join(); 
    }
    else {
      mergesort(false, left);
      mergesort(false, right);
    }
    merge(left, right, a);
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
    
    f.open(argv[1], ios::in);
    while(f >> value) {
      arr.push_back(value);
    }
    
    cout << "\nDo you want to do sorting in multi-threaded way ? (y/n) : ";
    char answer;
    cin >> answer;
    
    switch( answer ) {
        // Multi-threaded mergesort
        case 'y': mergesort(true, arr); break;
        // Single-threaded mergesort
        case 'n':  mergesort(false, arr); break;
        default : cout << "Wrong answer !!!\n"; return -1;
    }

    for(int i = 0; i < arr.size(); ++i)
      cout << arr[i] << " ";
    cout << endl;
  }
  return 0;
}
