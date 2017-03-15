#include<iostream>

using namespace std;

void merge(int left[], int l, int right[], int r, int base[]){
  int i = 0;
  int j = 0;
  int k = 0;
  while(i < l && j < r){
    if(left[i] <= right[j]) base[k++] = left[i++];
    else base[k++] = right[j++];
  }
  while(i < l) base[k++] = left[i++];
  while(j < r) base[k++] = right[j++];
}

void mergesort(int a[], int n){
  if(n < 2) return;
  else {
    int mid = n/2;
    int left[mid];
    int right[n-mid];
    for(int i = 0; i < mid; ++i) left[i] = a[i];
    for(int i = 0; i < n-mid; ++i) right[i] = a[i+mid];
    mergesort(left, mid);
    mergesort(right, n-mid);
    merge(left, mid, right, n-mid, a);
  }    
}

int main(){
  int size;
  cout << "Input array size: ";
  cin >> size;
  int arr[size];
  for(int i = 0; i < size; ++i)
    cin >> arr[i];
  mergesort(arr, size);
  for(int i = 0; i < size; ++i)
    cout << arr[i] << " ";
  cout << endl;
  return 0;
}
