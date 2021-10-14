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

int adj[21][21];
ifstream inFile;

vector<string> split(const string &text, char sep) {
    vector<string> tokens;
    size_t start = 0, end = 0;
    while ((end = text.find(sep, start)) != string::npos) {
        if (end != start) {
          tokens.push_back(text.substr(start, end - start));
        }
        start = end + 1;
    }
    if (end != start) {
       tokens.push_back(text.substr(start));
    }
    return tokens;
}

void readGraph(int n){
   for(int i=0;i<n;i++){
      string currLine;
      getline(inFile, currLine);
      vector<string> tokens = split(currLine, ' ');
      for(int j=0;j<n;j++){
          adj[i][j] = stoi(tokens[j]);
      }
   }
}

int numDistinctMu(int n){
   set<int> ans;
   for(int i=0;i<n;i++){
      for(int j=i+1;j<n;j++){
         if(!adj[i][j]){
            int cnt = 0;
            for(int ii=0;ii<n;ii++){
               cnt += adj[i][ii] * adj[ii][j];
            }
            ans.insert(cnt);
         }
      }
   }
   return ans.size();
}

int maximumIndependentSetSize (int n) {
   int mx = 0;
   for(int i=0;i<pow(2,n);i++){
      bool bad = false;
      for(int x=0;x<n && !bad;x++){
         for(int y=x+1;y<n && !bad;y++){
            if(adj[x][y] && (i>>x & 1) && (i>>y & 1)){
               bad = true;
            }
         }
      }
      if(!bad){
         mx = max(mx, __builtin_popcount(i));
      }
   }
   return mx;
}

int main(int argc, char *argv[])
{
   int maxN = 21;
   int minN = 21;

   freopen("statsDistinctMu.txt","w",stdout);

   int numSRG = 0;
   int totNum = 0;

   for(int n=minN;n<=maxN;n++){
      for(int k=1;k<n;k++){
         for(int l=max(1,2*k-n);l<=k-1;l++){
            if (l==1) {
               map<int,int> distinctMu;
               map<int,int> distinctMaxIS;
               int numGraphs = 0;
               string inString = "EdgeReg(";
               inString.append(to_string(n));
               inString.append(",");
               inString.append(to_string(k));
               inString.append(",");
               inString.append(to_string(l));
               inString.append(")NoIsoGraphs.txt");
               inFile.open(inString.c_str());
               string currLine;
               if(inFile){
                  while (getline(inFile, currLine)) 
                  {
                     if (currLine.find("Graph ") != string::npos) {
                        readGraph(n);
                        // int mxIS = maximumIndependentSetSize(n);
                        // if (distinctMaxIS.find(mxIS) == distinctMaxIS.end() ) {
                        //    distinctMaxIS.insert(pi(mxIS,1));
                        // } else {
                        //    distinctMaxIS[mxIS]++;
                        // }
                        // int distMu = numDistinctMu(n);
                        // if (distinctMu.find(distMu) == distinctMu.end() ) {
                        //    distinctMu.insert(pi(distMu,1));
                        // } else {
                        //    distinctMu[distMu]++;
                        // }
                        numGraphs++;                        
                     }
                  }
                  string outString = "|";
                  outString.append(to_string(n));
                  outString.append("|");
                  outString.append(to_string(k));
                  outString.append("|");
                  outString.append(to_string(l));
                  outString.append("|");
                  outString.append(to_string(numGraphs));
                  outString.append("|");
                  int count = 0;
                  for (auto const& x : distinctMu)
                  {
                     // if(count++ != 0){
                     //    outString.append(", ");
                     // }
                     // outString.append(to_string(x.first));
                     // outString.append(": ");
                     // outString.append(to_string(x.second));
                  }
                  outString.append(" <a href=\"FinalGraphs/EdgeReg(");
                  outString.append(to_string(n)+","+to_string(k)+","+to_string(l)+")NoIsoGraphs.txt\" download> Download </a>||");
                  count = 0;
                  for (auto const& x : distinctMaxIS)
                  {
                     // if(count++ != 0){
                     //    outString.append(", ");
                     // }
                     // outString.append(to_string(x.first));
                     // outString.append(": ");
                     // outString.append(to_string(x.second));
                  }
                  // outString.append("\\\\");
                  // cout << outString << endl;
                  // string outString = "";
                  // outString.append(to_string(n));
                  // outString.append("&");
                  // outString.append(to_string(k));
                  // outString.append("&");
                  // outString.append(to_string(l));
                  // outString.append("&");
                  // outString.append(to_string(numGraphs));
                  // outString.append("&");
                  // int count = 0;
                  // for (auto const& x : distinctMu)
                  // {
                  //    if(count++ != 0){
                  //       outString.append(", ");
                  //    }
                  //    outString.append(to_string(x.first));
                  //    outString.append(": ");
                  //    outString.append(to_string(x.second));
                  // }
                  // outString.append("&");
                  // count = 0;
                  // for (auto const& x : distinctMaxIS)
                  // {
                  //    if(count++ != 0){
                  //       outString.append(", ");
                  //    }
                  //    outString.append(to_string(x.first));
                  //    outString.append(": ");
                  //    outString.append(to_string(x.second));
                  // }
                  // outString.append("\\\\");
                  cout << outString << endl;
               }
               inFile.close();
            }
         }
      }
   }

   return 0;

}