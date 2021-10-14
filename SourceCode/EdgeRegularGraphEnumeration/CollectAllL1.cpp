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
   int n = 21;
   int k = 6;
   int l = 1;
   int tt = 156;
   int count = 0;
   string outName = "All";
   outName.append("(");
   outName.append(to_string(n));
   outName.append(",");
   outName.append(to_string(k));
   outName.append(",");
   outName.append(to_string(l));
   outName.append(")Graphs.txt");
   ofstream out;
   out.open(outName.c_str());
   string output = "";

   for(int t=0;t<tt;t++){
      string iFileName = "L1,";
      iFileName.append(to_string(t));
      iFileName.append("(");
      iFileName.append(to_string(n));
      iFileName.append(",");
      iFileName.append(to_string(k));
      iFileName.append(",");
      iFileName.append(to_string(l));
      iFileName.append(")Graphs.txt");
      ifstream iFile(iFileName.c_str());
      string temp;
      getline(iFile,temp);
      int numLines = stoi(temp);
      count+=numLines;
      for (int i = 0; i < numLines; i++){
         getline(iFile, temp);
         output.append(temp);
         output.append("\n");
      }
   }
   out << count << endl;
   out << output;
   return 0;

}