#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>
#include <vector>

using namespace std;
typedef pair<string, pair<int, string> > myType;

int main(int argc, char* argv[]) {
  if (argc != 2 ) {
    cout << "You must input a file path!\n";
    return 1;
  }
  else {
    fstream f;
    string value;
    list<string> s;  
    int index = 0;
    
    f.open(argv[1], ios::in);
    while(f >> value) {
      s.push_front(value);
    }
    
    map<string, pair<int, string> > words;
    map<string, pair<int, string> >::iterator it;

    for(list<string>::iterator i = s.begin(); i != s.end(); ++i) {
      it = words.find(*i);
      if( it != words.end() ) {
        it->second.first++;
        it->second.second += " " + to_string(index++);
      }
      else 
        words.insert( myType (*i, pair<int, string>( 1, to_string(index++) )) );
    }

    for( it = words.begin(); it != words.end(); ++it ) 
      cout << " (\"" << it->first << "\" : " << it->second.first << " : [ " << it->second.second << " ])\n";                                  
                                                                                                    
    return 0;
  }
}
