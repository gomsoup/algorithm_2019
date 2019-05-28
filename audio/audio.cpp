#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <thread>
#include <ctime>
using namespace std;

int n;
vector <vector <int>> g;
vector <int> result;
int ** arr;
int minDist = 999999;
thread *t;


class asdf{
public:
    int pos;
    vector <int> idx;

    int allDist(){
        int dist = 0;
        for(auto it : idx) dist += abs(pos - it);
        
        return dist;
    }
};

int calc(vector <int> array){
    int dist = 0; vector<vector <int>> gg = g;
    vector <asdf> a; a.resize(n);
    
    for(int i = 0 ; i < n; i++){
        // find pos
        for(int j = 0; j < n; j++){
            if(array[j] == i){
                a[i].pos = j;
                break;
            }
        }
        
        // find connected nodes
        for(int j = 0; j< n; j++){
            if(gg[i][j] == 1){
                for(int k=0; k<n; k++){
                    if(array[k] == j){
                        a[i].idx.push_back(k);
                        gg[i][j] = 0; gg[j][i] = 0;
                        break;
                    }
                }
                
            }
        }
    }
    
    for(auto it : a){
        dist += it.allDist();
    }
    
    return dist;
}


void input(){
    ifstream inp("/Users/gomsoup/Documents/algorithm_2019/audio/3.inp");
//    ifstream inp("audio.inp");
    inp >> n;
    g.resize(n); for(int i=0; i<n; i++) g[i].resize(n);
    
    for(int i=0; i<n; i++){
        int flag = true;
        for(int j=0; j<n; j++){
            int tmp; inp >> tmp;
            if(flag){
                flag = false;
                continue;
            }
            if(tmp == 0) break;
            
            g[i][tmp-1] = 1;
        }
    }
}

void output(){
    ofstream out("audio.out");
    cout << minDist << endl;
    for(auto it : result) cout << it+1 << " ";
    cout << endl;
}

void forThread(int idx){
    vector <int> v(n);
    int cnt = 1;
    for (int i = 0; i<n; i++){
        if(i == idx) continue;
        v[cnt] = i; cnt++;
    }
    v[0] = idx;
    
    cnt = 0;
    do{
        if(v[0] != idx) break;
        int dist = calc(v);
        if (minDist > dist) {
            result = v;
            minDist = dist;
        }
        cnt++;
    }while(next_permutation(v.begin(), v.end()));
    
}

int main() __attribute__((optimize("-O2")));

int main(){
    clock_t start = clock();
    input();
    
    
    t = new thread[n];
    
    for(int i=0; i<n; i++){
        t[i] = thread(forThread, i);
    }
    
    for(int i=0; i<n; i++) t[i].join();
    
/*
    vector <int> v(n);
    for(int i =0; i<n; i++) v[i] = i;
    int cnt = 0;
    do{
        int dist = calc(v);
        if (minDist > dist) {
            result = v;
            minDist = dist;
        }
        cnt++;
    }while(next_permutation(v.begin(), v.end()));
*/
    /*
    cout << minDist << endl;
    if(!result.empty())
        for(int i =0; i<n; i++) cout << result[i] + 1<< " ";
    cout << endl;
    */
    
    cout << (float)( (clock() - start) / CLOCKS_PER_SEC) << endl;
    
    output();
     return 0;
}

