#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
// to run the program
// g++ -std=c++11  a.cpp
// ./a.out
int main()
{
  cout << "Hello mlkes" << endl;
  printf("Á\n");

  // sort(a.login(),a.end());
  vector<int> a;

  for (int i = 10; i > 0; i--)
  {
    a.push_back(i);
  }
  sort(a.begin(),a.end());

  for (int i : a)
    cout << i << endl;
}
