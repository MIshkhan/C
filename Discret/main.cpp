#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <utility>
#include <algorithm>


#include <stdlib.h>     /* srand, rand */
#include <time.h>

using namespace std;

const int size = 6;
static list<pair<int, int>> ways;

string PRINT_ELEMENTS (){
  string result;
  for (list<pair<int,int>>::iterator it=ways.begin(); it != ways.end(); ++it) {
    result += "( " + to_string(it->first+1) + ":" + to_string(it->second+1) + " )";
  }
  return result;
}

void findPath (int graph[][size], int peak, int size = size){
static string prev = "";
  for(int i = 0; i < size; ++i ) {
    if(i == peak) continue;
    if(graph[peak][i] == 1) {
      pair<int,int> way = make_pair(peak,i);
      if((find(ways.begin(), ways.end(), way) == ways.end()) && (find(ways.begin(), ways.end(), make_pair(i, peak)) == ways.end())){
        ways.push_back(way);
        findPath(graph, i, size);
        ways.pop_back();
      }
    }
    if(i==size-1) {
       if((prev.find(PRINT_ELEMENTS()) == string::npos)) {
        cout << PRINT_ELEMENTS() << endl;
        prev += PRINT_ELEMENTS();
       }
    }
  }
}

int main(){
  cout << "Input array size: ";
  int t ;
  cin >> t;
  int arr[size][size];
  for(int i = 0; i < size; ++i)
    for(int j = 0; j < size; ++j)
      cin >> arr[i][j];

  findPath(arr, 0);
  cout << endl << endl;
  findPath(arr, 1);
  cout << endl << endl;
  findPath(arr, 2);
  cout << endl << endl;
  findPath(arr, 3);
  cout << endl << endl;
  findPath(arr, 4);
  cout << endl << endl;
  findPath(arr, 5);
  cout << endl << endl;
  return 0;
}
