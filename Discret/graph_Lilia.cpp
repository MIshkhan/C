#include<iostream>

//stl
#include<vector>
#include<list>
#include<queue>

using namespace std;

int V;
vector<list<int> > List;

void bfs(int v, bool visited[]);

bool is_connected() {
  bool visited[List.size()];
  for (int i = 0; i < V; i++) {
    visited[i] = false;
  }
  bfs(0, visited);
  for (int i = 0; i < V; i++) {
    if (visited[i] == false) {
      return false;
    }
  }
  return true;
}

void bfs(int v, bool visited[]) {
  visited[v] = true;
  queue<int> q;
  q.push(v);

  while (!q.empty()) {
    v = q.front();
    q.pop();
    for (list<int>::iterator i = List[v].begin(); i != List[v].end(); i++) {
      if (visited[*i] == false) {
        visited[*i] = true;
        q.push(*i);
      }
    }
  }
}

int main()
{
  return 0;
}
