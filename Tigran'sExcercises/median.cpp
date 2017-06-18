#include <iostream>
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

void mergesort(vector<double>& a) {
  int n = a.size();
  if(n < 2) return;
  else {
    vector<double> left, right;
    int i = 0;
    for(i = 0; i < n/2; ++i) left.push_back(a[i]);
    for( ; i < n; ++i) right.push_back(a[i]);
    mergesort(left);
    mergesort(right);
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

    int size = arr.size();
    mergesort(arr);
    if(size % 2 == 0)
      cout << "Median Value:" << (arr[size/2-1] + arr[size/2]) / 2  << endl;
    else
      cout << "Median Value:" << arr[size/2]  << endl;
  }
  return 0;
}
