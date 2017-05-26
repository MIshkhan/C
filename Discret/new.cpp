#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector< vector<int> > graph;
vector< int > visited;

struct Path {
  pair<int, vector<string> > max_paths = pair<int, vector<string> > (0, vector<string>());
  string direction;
  size_t length;
  
  void addEdge( int peak, int i ) {
    length++;
    direction += "( " + to_string( peak + 1 ) + ":" + to_string( graph[peak][i] + 1 ) + " )";
    if( max_paths.first < length )
      max_paths = pair<int, vector<string> >(length, vector<string>(1, direction));
    else if ( max_paths.first == length )
      max_paths.second.push_back(direction);
  }

  void removeLastEdge() {
    length--;
    direction = direction.substr(0, direction.find_last_of("("));
  }

  string getMaxPath() {
    string result = "";
    for(int i = 0; i < max_paths.second.size(); ++i) {
      result += max_paths.second[i] + "\n";
    }
    return result;
  }
  
};

static Path path; 

void findPath ( int peak ) {
  visited[peak] = 1; 
  for(int i = 0; i < graph[peak].size(); ++i ) {
    if(visited[graph[peak][i]] == 0) {
      
      visited[graph[peak][i]] = 1; 
      path.addEdge(peak, i);
      
      findPath(graph[peak][i]);

      visited[graph[peak][i]] = 0; 
      path.removeLastEdge();

    }
  }
  visited[peak] = 0; 
}

int main(){
  int n, x, i, y, size;

  cout << "Input number of vertexis in graph: ";
  cin >> size; 
  cout << "Input number of edges: ";
  cin >> n;
  cout << "Input edges: " << endl;
 
  graph = vector< vector<int> >(size);
  visited = vector<int>(size);
  
  for(i = 0; i < n; ++i) {
      cin >> x >> y;
      x--, y--;
      graph[x].push_back(y);
      graph[y].push_back(x);
  }

  for( i = 0; i < n; ++i) {
      findPath(i);
  }
  cout << path.getMaxPath();

  return 0;
}

