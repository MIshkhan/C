#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <fstream>
#include <sstream>
#include <regex>

using namespace std;

vector< vector<int> > graph;
vector< int > visited;

void dfs(int s,  bool visited[]) {
  list<int> tmp;
  visited[s] = true; 
  tmp.push_back(s);
  
  while (!tmp.empty()) {
    s = tmp.front();
    tmp.pop_front();
    for (vector<int>::iterator i = graph[s].begin(); i != graph[s].end(); ++i) {
      if (!visited[*i]) {
	visited[*i] = true;
	tmp.push_back(*i);
      }
    }
  }
}

bool isConnected() {
  bool *visited = new bool(graph.size());
  for(int i = 0; i < graph.size(); ++i)
    visited[i] = false;
  dfs(0, visited);
  for(int i = 0; i < graph.size(); ++i)
    if(visited[i] == false)
      return false;
  return true;
}

struct Path {
  pair<int, vector<string> > max_paths = pair<int, vector<string> > (0, vector<string>());
  string direction;
  size_t length;
  
  void addEdge( int peak, int i ) {
    length++;
    direction += "( " + to_string( peak + 1 ) + ":" + to_string( i + 1 ) + " )";
    if( max_paths.first < length )
      max_paths = pair<int, vector<string> >(length, vector<string>(1, direction));
    else if ( max_paths.first == length )
      max_paths.second.push_back(direction);
  }

  void removeLastEdge() {
    length--;
    direction = direction.substr(0, direction.find_last_of("("));
  }

  string getMaxPaths() {
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
      path.addEdge(peak, graph[peak][i]);
      
      findPath(graph[peak][i]);

      visited[graph[peak][i]] = 0; 
      path.removeLastEdge();

    }
  }
  visited[peak] = 0; 
}

void graphInit(string filepath) {
  fstream file;
  string line;
  file.open(filepath, ios::in);
  getline(file, line);
  if(regex_match(line, regex("^vertex_number:([0-9]+)(\\s+)?") )) {
    int first = line.find(":");
    int size = stoi(line.substr(first+1, line.find(" ")-first-1));
    graph = vector< vector<int> >(size);
    visited = vector<int>(size);
    
    getline(file, line);
    while(line != "") {
      if (regex_match (line, regex("^([0-9]+)\\](\\s([0-9]+))+(\\s+)?") )) {
    	int x = stoi(line.substr(0, line.find("]")));
	stringstream ss(line.substr(line.find("]")+2, line.size()-line.find("]")));
	string var;
	
	while ( getline(ss, var, ' ') ) {
	  if (var.length() > 0) 
	    graph[x-1].push_back(stoi(var)-1);	    
	}
	getline(file, line);
      }
      else {
    	cerr << "\nIncorrect input \"" + line << "\""<< endl;
    	cerr << "Example: \"5] 1 2 4\"\n" << endl;
    	exit(1);
      }
    }
  }
  else {
    cerr << "\nIncorrect info \"" + line << "\""<< endl;
    cerr << "Example: \"vertex_numbern:10\"\n" << endl;
    exit(1);
  }
}

int main(int argc, char* argv[]) {
  if (argc != 2 ) {
    cout << "You must input a file path!\n";
    return 1;
  }
  else 
    graphInit(argv[1]);
  
  for(int i = 0; i < graph.size(); ++i) {
    findPath(i);
  }
  
  cout << "Is graph connected: " << (isConnected() == 1? "true" : "false") << endl;
  cout << "Max paths :\n" << path.getMaxPaths();
  return 0;
}

// int main(){
//   int n, x, i, y, size;

//   cout << "Input number of vertexis in graph: ";
//   cin >> size; 
//   cout << "Input number of edges: ";
//   cin >> n;
//   cout << "Input edges: " << endl;
 
//   graph = vector< vector<int> >(size);
//   visited = vector<int>(size);
  
//   for(i = 0; i < n; ++i) {
//       cin >> x >> y;
//       x--, y--;
//       graph[x].push_back(y);
//       graph[y].push_back(x);
//   }

//   for( i = 0; i < size; ++i) {
//     findPath(i);
//   }

//   cout << "Is graph connected: " << (isConnected() == 1? "true" : "false") << endl;
//   cout << "Max paths :\n" << path.getMaxPaths();
//   cout << t << endl;
//   return 0;
// }
