#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <utility>
#include <algorithm>

using namespace std;

const int size = 6;
static list<pair<int, int>> ways;

int findPath (int graph[][size], int peak, int size = 6){
  cout<<"mtav\n";
  for(int i = 0; i < size; ++i ) {
    if(i == peak) continue;
    if(graph[peak][i] == 1) {
      cout << peak << " -> " << i << endl;
      pair<int,int> way = make_pair(peak,i);
      if((find(ways.begin(), ways.end(), way) == ways.end()) && (find(ways.begin(), ways.end(), make_pair(i, peak)) == ways.end())  ){
        ways.push_back(way) ;
        findPath(graph, i, size);
      }
    }
  }
  return 0;
}


int main(){
  // cout << "Input array size: ";
  // cin >> size;
  int arr[size][size];
  for(int i = 0; i < size; ++i)
    for(int j = 0; j < size; ++j)
      cin >> arr[i][j];

  findPath(arr, 0);
  
  return 0;
}
