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

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pi;
 
#define F first
#define S second
#define PB push_back
#define MP make_pair

vector<pi> allEdges;

int main(int argc, char *argv[])
{
    //Takes in arguments ./-.exe n
    if(argc<2){
        throw 1;
    }

    int N = stoi(argv[1]);

    string outname = argv[1];
    outname.append("Graphs.txt");
    //outname.append(argv[1]);

    freopen(outname.c_str(),"w",stdout);

    int adj[7][7];

    for(int i=0;i<N;i++){
        for(int j=i+1; j<N;j++){
            allEdges.PB(MP(i,j));
        }
    }

    cout << (1<<allEdges.size()) << endl;

    for(long i = 0; i < (1<<allEdges.size());i++){
        for(int j=0;j<allEdges.size();j++){
            if((i>>j)&1){
                cout << j+1 << " ";
            }
            else {
                cout << -1 * (j+1) << " ";
            }
        }
        cout << 0 << endl;
    }

    return 0;
}