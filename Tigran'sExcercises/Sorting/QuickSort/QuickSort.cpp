#include<iostream>

using namespace std;

int partition(int a[], int start, int end){
  int pivot = a[end];
  int pIndex = start;
  for(int i = start; i < end; ++i)
    if(a[i] <= pivot) swap(a[i], a[pIndex++]);
  swap(a[pIndex], a[end]);
  return pIndex;  
}

void quicksort(int a[], int start, int end){
  if(start < end){
    int pIndex  = partition(a, start, end);
    quicksort(a, start, pIndex-1);
    quicksort(a, pIndex+1, end);    
  }    
}

int main(){
  int size;
  cout << "Input array size: ";
  cin >> size;
  int arr[size];
  for(int i = 0; i < size; ++i)
    cin >> arr[i];
  quicksort(arr, 0, size-1);
  for(int i = 0; i < size; ++i)
    cout << arr[i] << " ";
  cout << endl;
  return 0;
}
