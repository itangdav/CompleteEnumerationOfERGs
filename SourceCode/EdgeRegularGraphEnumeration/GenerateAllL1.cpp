#include <algorithm>
#include <bitset>
#include <iterator>
#include <math.h>
#include <new>
#include <numeric>
#include <queue>
#include <set>
#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <map>
#include <array>
#include <stdexcept>
#include <stdio.h>
#include <chrono>
#include <fstream>
#include <sstream>

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pi;

#define F first
#define S second
#define PB push_back
#define MP make_pair

int main(int argc, char *argv[])
{
   int n = 22;
   int k = 6;
   int l = 1;
   int tt = 1044;
   for(int t=0;t<tt;t++){
      string coreString = "L1,";
      coreString.append(to_string(t));
      coreString.append("(");
      coreString.append(to_string(n));
      coreString.append(",");
      coreString.append(to_string(k));
      coreString.append(",");
      coreString.append(to_string(l));
      coreString.append(")");
      // system(("wsl ./EnumerateAllSRGs.exe \'" + coreString + "\' " + to_string(n)).c_str());
      // system(("wsl ./ExtractSolutions.exe \'./" + coreString + ".out\' " + to_string(n)).c_str());
      system(("wsl ./SolveAllSRGs.exe \'" + coreString + "\' " + to_string(n) + " " + to_string(t)).c_str());
 
   }
   return 0;

}