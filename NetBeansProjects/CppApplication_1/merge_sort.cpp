#include <iostream>
#include <thread>
#include <fstream>
#include <string>
#include <list>

using namespace std;

void merge(list<double> left, list<double> right, list<double> base) {
  list<double>:: iterator i, j; 
  while(i != left.end() && j != right.end()){
    if(*i <= *j) {base.push_front(*i); i++;}
    else {base.push_front(*j); ++j;}
  }
  while( i != left.end() ) { base.push_front(*i); i++; }
  while( j != right.end() ) { base.push_front(*j); j++; }
}

void mergesort(bool doMultithreaded, list<double> a) {
  int n = a.size();
  if(n < 2) return;
  else {
    unsigned int mid = abs(n/2);
    list<double> left, right;
    list<double>:: iterator i;
    int n = 0;
    for(i = a.begin(); n < a.size()/2; ++i, ++n) { left.push_front(*i);
      for( ;i != a.end(); ++i) right.push_front(*i);
      if( doMultithreaded == true ) {
        thread t1( mergesort, true, left);
        thread t2( mergesort, true, right);
        t1.join(); 
        t2.join(); 
      }
      else {
        mergesort(false, left);
        mergesort(false, right);
      }
      merge(left, right, a);
    }    
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
    list<double> arr;  
    
    f.open(argv[1], ios::in);
    while(f >> value) {
      arr.push_front(value);
    }
    
    cout << "\nDo you want to do sorting in multi-threaded way ? (y/n) : ";
    char answer;
    cin >> answer;
    
    switch( answer ) {
        // Multi-threaded mergesort
        case 'y': mergesort(true, arr); break;
        // Single-threaded mergesort
        case 'n':  mergesort(false, arr); break;
        default : cout << "Wrong answer !!!\n"; return -1;
    }

    for(list<double>:: iterator i; i != arr.end(); ++i)
      cout << *i << " ";
    cout << endl;
  }
  return 0;
}
