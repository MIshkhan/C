#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <cstring>
#include <algorithm>    // std::stable_sort
#include "numberGroups.hpp"

using namespace std;

void NumberGroups::printGroups(vector<int> numbers){
  /* counting average difference between numbers */
  stable_sort (numbers.begin(), numbers.end());
  int size = numbers.size();
  int difference = 0;
  map<int, int> m;
  map<int, int>::iterator pos;  
  for(int i = 1; i < size; ++i ) {
    int difference = numbers[i] - numbers[i-1] ;
    pos = m.find(difference);
    if( pos != m.end() ) pos->second++ ; 
    else m.insert(pair<int,int>( difference, 1 )) ;
  }
  int avgDif = 0;
  for( pos = m.begin(); pos != m.end(); ++pos )
    avgDif += pos->first;
  avgDif /= size;
  
  /* breaking numbers into groups */
  for(int i = 0; i < size-1; ++i ) {
    if(numbers[i+1] - numbers[i] > avgDif) cout << numbers[i] << endl;
    else cout << numbers[i] << " ";
  }
  cout << numbers[size-1] << endl;
}

void NumberGroups::printGroups(string filepath){
  fstream f;
  string data;
  vector<int> numbers;
  char * splitData;
  char  charData[250];
  f.open(filepath, ios::in);	
  getline(f, data); 
  strcpy(charData, data.c_str());
  splitData = strtok (charData , " ");
  while (splitData != NULL) {
    numbers.push_back(atoi(splitData));
    splitData = strtok (NULL, " ");
    }
  f.close();
  printGroups(numbers);
}

