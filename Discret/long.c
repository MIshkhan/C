#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int size = 4;
vector< vector<int> > graph;
int visited[size][size];

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
    cout << endl;
    for(int i = 0; i < max_paths.second.size(); ++i) {
      cout <<  max_paths.second[i] << endl;
    }
  }
  
};

static Path path; 

void findPath ( int peak ){
  // cout << "This is for vertex " << peak+1 << " which size is " << graph[peak].size() << endl;
  static string prev = "";
  for(int i = 0; i < graph[peak].size(); ++i ) {
    if( visited[peak][graph[peak][i]] == 0) {
      //cout << "For " << peak+1 << " pushed ( " << peak+1 << ", " << graph[peak][i]+1 << " ) ->" << prev << endl; 
      visited[peak][graph[peak][i]] = 1; visited[graph[peak][i]][peak] = 1;
      path.addEdge(peak, i);
      
      findPath(graph[peak][i]);

      visited[peak][graph[peak][i]] = 0; visited[graph[peak][i]][peak] = 0;
      path.removeLastEdge();
      //cout << "For " << peak+1 << " poped ( " << peak+1 << ", " << graph[peak][i]+1 << " )" << endl; 

    }
    else {
      prev = "";
    }
    if(i==graph[peak].size()-1) {
      if( prev.find( path.direction ) == string::npos ) {
        prev += path.direction;
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

  path.getMaxPath();

  return 0;
}

