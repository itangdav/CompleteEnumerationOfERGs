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
   int maxN = 21;
   int minN = 21;

   for(int n=minN;n<=maxN;n++){
      for(int k=1;k<n;k++){
         // for(int l=max(1,2*k-n);l<=k-1;l++){
         for(int l=1;l<=1;l++){
            string coreString = "EdgeReg(";
            coreString.append(to_string(n));
            coreString.append(",");
            coreString.append(to_string(k));
            coreString.append(",");
            coreString.append(to_string(l));
            coreString.append(")");
            system(("wsl ./EdgeRegularUnaryWithLex.exe "+ to_string(n) + " " + to_string(k) + " " + to_string(l)).c_str());
            system(("wsl ./EnumerateAllSRGs.exe \'" + coreString +"\' " + to_string(n)).c_str());
            system(("wsl ./ExtractSolutions.exe \'./" + coreString + ".out\' " + to_string(n)).c_str());
         }
      }
   }


   return 0;

}