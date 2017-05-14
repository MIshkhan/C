#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <list>

using namespace std;

const int size = 10;
vector< pair<int,int> > ways;
vector< vector<int> > graph;
int visited[size][size];

string PRINT_ELEMENTS (){
  string result;
  for (int i = 0; i < ways.size(); ++i) {
    std::stringstream out1, out2;
    out1 << ways[i].first + 1;
    out2 << ways[i].second + 1;
    result += "( " + out1.str() + ":" + out2.str()  + " )";
  }
  return result;
}

void findPath ( int peak ){
  // cout << "This is for vertex " << peak+1 << " which size is " << graph[peak].size() << endl;
  static string prev = "";
  for(int i = 0; i < graph[peak].size(); ++i ) {
    if( visited[peak][graph[peak][i]] == 0) {
      //cout << "For " << peak+1 << " pushed ( " << peak+1 << ", " << graph[peak][i]+1 << " ) ->" << prev << endl; 
      visited[peak][graph[peak][i]] = 1; visited[graph[peak][i]][peak] = 1; ways.push_back(make_pair(peak, graph[peak][i]));
      
      findPath(graph[peak][i]);

      visited[peak][graph[peak][i]] = 0; visited[graph[peak][i]][peak] = 0; ways.pop_back();
      //cout << "For " << peak+1 << " poped ( " << peak+1 << ", " << graph[peak][i]+1 << " )" << endl; 

    }
    else {
      prev = "";
    }
    if(i==graph[peak].size()-1) {
      if((prev.find(PRINT_ELEMENTS()) == string::npos)) {
	cout << PRINT_ELEMENTS() << endl;
	prev += PRINT_ELEMENTS();
      }

    }
  }
}

int main(){
  int n, x, i, y;

  cout << "Input array size: ";
  cin >> n;
  graph = vector< vector<int> >(n);

  for(i = 0; i < n; ++i) {
    cin >> x >> y;
    x--, y--;
    graph[x].push_back(y);
    graph[y].push_back(x);
  }

  for( i = 0; i < n; ++i) {
    findPath(i);
    cout << endl << endl;
  }
  
  return 0;
}

