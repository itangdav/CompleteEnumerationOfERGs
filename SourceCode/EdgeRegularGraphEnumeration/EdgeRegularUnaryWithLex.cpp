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
vector<vector<pi>> graphs;
vector<vector<pi>> reg4;
vector<vector<pi>> reg5;

int getIndex(vector<pi> v, pi K)
{
    auto it = find(v.begin(), v.end(), K);
    if (it != v.end()) return it - v.begin();
    else return -1;
}

int getIndex2(vector<int> v, int K)
{
    auto it = find(v.begin(), v.end(), K);
    if (it != v.end()) return it - v.begin();
    else return -1;
}

//Helper to get index of B_(i,j)
int indexB(int i, int j, int n, int k, int start){
    return start + i*k + j;
}

//Unary Adder
//Also, we need room to write additional n * k variables which is indexed from start, start+1, ..., start+n*k-1, last k bits from start + (n-1)*k to end represent the final sum
//The unary bit B_(i,j), for which i encodes we are summing up to X_(Xs[i]) and the largest j with bit 1 represents the sum so far, so 1111 represents 4
//We do index start + i * k + j as the bit B_(i,j) 
void unaryAdderWithPredicate(int n, int k, vector<int> Xs, int start, string pred){
    //This writes all, for i in range (0,n), not X_(Xs[i]) or B_(i,0)
    for(int i=0;i<n;i++){
        cout << pred << "-" << Xs[i] << " "<< indexB(i,0,n,k,start) << " " << 0 << endl;
    } 

    //This ensures that we never write a 1 in the top row until column i, where X_(Xs[i]) is the first 1
    for(int i=0;i<n;i++){
        if(i==0){
            cout << pred << Xs[i] << " " << "-" << indexB(i,0,n,k,start) << " " << 0 << endl;
        }
        else{
            cout << pred << "-" << indexB(i,0,n,k,start) << " " << indexB(i-1,0,n,k,start) << " " << Xs[i] << " " << 0 << endl;
        }
    }

    //This writes that all B_(0,j), j>=1
    for(int j=1; j<k;j++){
        cout << pred << "-" << indexB(0,j,n,k,start) << " " << 0 << endl;
    }

    //This writes the propagation forwards, so if we have a 1 in a row, all future columns will have a 1 in that row
    for(int i=1;i<n;i++){
        for(int j=0;j<k;j++){
            cout << pred << "-" << indexB(i-1,j,n,k,start) << " " << indexB(i,j,n,k,start)<< " " << 0 << endl;
        }
    }

    //This ensures that we add an extra 1 to column i if X_(Xs[i]) is a 1
    for(int i=1;i<n;i++){
        for(int j=1;j<k;j++){
            cout << pred << "-" << Xs[i] << " " << "-" << indexB(i-1,j-1,n,k,start) << " " << indexB(i,j,n,k,start) << " " << 0 << endl;
        }
    }

    //This ensures that we propagate zeros forwards for rows >=1 unless we need to add
    for(int i=1;i<n;i++){
        for(int j=1;j<k;j++){
            cout << pred << "-" << indexB(i,j,n,k,start) << " " << indexB(i-1,j,n,k,start) << " " << indexB(i-1,j-1,n,k,start) << " " << 0 << endl;
            cout << pred << "-" << indexB(i,j,n,k,start) << " " << indexB(i-1,j,n,k,start) << " " << Xs[i] << " " << 0 << endl;
        }
    }

    //This checks to ensure that no overflow occurs (sum >=k)
    for(int i=1;i<n;i++){
        cout << pred << "-" << Xs[i] << " " << "-" << indexB(i-1,k-1,n,k,start) << " " << 0 << endl;
    }
}

//We want to write an encoding for =K on n variables in the vector Xs (so X_1, X_3, X_4, X_7, X_9) for example would be (1,3,4,7,9)
//Also, we need room to write additional b * (k+1) variables which is indexed from start, start+1, ..., start+(n-1)*k-1
//The unary bit B_(i,j), for which i encodes we are summing up to X_(Xs[i]) and the largest j with bit 1 represents the sum so far
//We do index start + i * k + j as the bit B_(i,j) 
//This is done using the Sinz sequential encoding for <=k in addition to ensuring that we never "add" when it's not necessary
//Adds predicate in front of each clause
void encodeEqualsKWithPredicate(int n, int k, vector<int> Xs, int start, string pred){
    //We don't do anything for n=0
    if(n==0) return;
    //This means the variables start + (n-1) * (k+1) to start + n * (k+1) - 1 are the final sum in unary
    unaryAdderWithPredicate(n, k+1, Xs, start, pred);

    //This checks if the final sum is exactly k and not k+1
    cout << pred << -1 * (start + (n-1) * (k+1) + k) << " " << 0 << endl;
    if(k!=0){
        cout << pred << start + (n-1) * (k+1) + k - 1 << " " << 0 << endl;
    }
}

void encodeEqualsKWithoutPredicate(int n, int k, vector<int> Xs, int start){
    encodeEqualsKWithPredicate(n,k,Xs,start,"");
}




//I'm going to create helper variables H_i = Xs[i] AND Ys[i]
//Then, we just need to check if the helper variables sum to l if b is true (b would usually be if an edge exists or not), else its m
//Uses n * (l+2) new variables
void encodeDotProdEqualsKOrL(int b, int n, int l, vector<int>Xs, vector<int>Ys, int start){
   
    //Creating n helper variables
    for(int i=0;i<n;i++){
        cout << -1 * (start + i) << " " << Xs[i] << " " << 0 << endl;
        cout << -1 * (start + i) << " " << Ys[i] << " " << 0 << endl;
        cout << (start + i) << " " << -1 * Xs[i] << " "  << -1 * Ys[i] << " " << 0 << endl;
    }

    vector<int> helpers;
    for(int i=0;i<n;i++){
        helpers.PB(start+i);
    }

    string pred = to_string(-1 * b).append(" ");
    //Uses another n * (l+1) variables
    encodeEqualsKWithPredicate(n,l,helpers,start+n, pred);
}


//Encodes that Xs is lexicographically before Ys
//l is the length of the array
//Uses additional variables start to start+l-2 to represent whether xi = yi
//Uses additional variables start+l-1 to start+2*l-2 to represent whether xi <= yi
//Uses additional variables start+2*l-1 to start+3*l-3 to represent whether start and ... and start+i are true
//In total, uses 3 * l - 2 additional varaibles
void writeLexico(vector<int> Xs, vector<int>Ys, int l, int start){
    //Writes the additional variables representing xi = yi
    for(int i=0;i<l-1; i++){
        cout << -1 * Xs[i] << " " << -1 * Ys[i] << " " << (start+i) << " " << 0 << endl;
        cout << -1 * Xs[i] << " " << Ys[i] << " " << -1 * (start+i) << " " << 0 << endl;
        cout << Xs[i] << " " << -1 * Ys[i] << " " << -1 * (start+i) << " " << 0 << endl;
        cout << Xs[i] << " " << Ys[i] << " " << (start+i) << " " << 0 << endl;
    }

    //Writes the additional variables representing xi <= yi
    for(int i=0;i<l;i++){
        cout << -1 * Xs[i] << " " <<  Ys[i] << " " << -1 * (start+l-1+i) << " " << 0 << endl;
        cout << Xs[i] << " " << (start+l-1+i) << " " << 0 << endl;
        cout << -1 * Ys[i] << " " << (start+l-1+i) << " " << 0 << endl;
    }

    //Writes the additional variables representing start and ... and start + i
    for(int i=0;i<l-1;i++){
        for(int j=0;j<=i;j++){
            cout << -1 * (start+2*l-1+i) << " " << start+j << " " << 0 << endl; 
        }
        cout << (start+2*l-1+i) << " ";
        for(int j=0;j<=i;j++){
            cout << -1 * (start+j) << " ";
        }
        cout << 0 << endl;
    }

    //Write that x1 <= y1
    cout << start+l-1 << " " << 0 << endl;
    
    //Write that if x1 = y1 and x2 = y2 and ... and xi = yi then xi+1 <= yi+1 
    for(int i=1;i<l;i++){
        cout << -1 * (start+2*l-1+(i-1)) << " " << start+l-1+i << " " << 0 << endl;
    }
}

int main(int argc, char *argv[])
{
    //Takes in arguments ./-.exe N K l m
    if(argc<4){
        throw 1;
    }

    int N = stoi(argv[1]);
    int K = stoi(argv[2]);
    int l = stoi(argv[3]);
    

    //Offset edges by 1
    allEdges.PB(MP(-1,-1));

    for(int i=1;i<N;i++){
        for(int j=i+1; j<=N;j++){
            allEdges.PB(MP(i,j));
        }
    }

    string outname="";
    outname.append("EdgeReg(");
    outname.append(to_string(N));
    outname.append(",");
    outname.append(to_string(K));
    outname.append(",");
    outname.append(to_string(l));
    outname.append(")");
    outname.append(".out");

    freopen(outname.c_str(), "w", stdout);
            
    int counter = ((N * (N-1))/2)+1;

    //Encode Regularity Condition
    for(int v=1;v<=N;v++){
        vector<int> vEdges;
        for(int i=1;i<allEdges.size();i++){
            pi a = allEdges[i];
            if(a.first ==v || a.second == v){
                vEdges.PB(i);
            }
        }

        encodeEqualsKWithoutPredicate(vEdges.size(),K, vEdges, counter);
        counter+= vEdges.size() * (K+1);
    }

    //Encoding Edge Regular Condition
    for(int eNum = 1; eNum<allEdges.size();eNum++){
        int a = allEdges[eNum].first;
        int b = allEdges[eNum].second;
        vector<int> AEdges;
        vector<int> BEdges;
        for(int v = 1; v<=N; v++){
            if(v!=a && v!=b){
                for(int eN = 1; eN<allEdges.size();eN++){
                    if(eN!=eNum){
                        if((allEdges[eN].first == a && allEdges[eN].second == v)|| (allEdges[eN].first == v && allEdges[eN].second == a)){
                            AEdges.PB(eN);
                        }
                        if((allEdges[eN].first == b && allEdges[eN].second == v)|| (allEdges[eN].first == v && allEdges[eN].second == b)){
                            BEdges.PB(eN);
                        }
                    }
                }
            }
        }
        //Only need to encoding stuff if the vector is non-empty
        if(AEdges.size() > 0){
            encodeDotProdEqualsKOrL(eNum, AEdges.size(),l,AEdges,BEdges,counter);
            counter += (AEdges.size()) *(l+2);

            if(AEdges.size()!=N-2){
                throw 1;
            }

            //Lexicographic ordering
            writeLexico(BEdges,AEdges,AEdges.size(),counter);
            counter += 3 * AEdges.size() - 2;
        }


    }
            

    return 0;

}