#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

typedef pair<int, int> pii;

int getDistance(int x1, int y1, int x2, int y2){
    return ceil(sqrt( pow( (x2-x1), 2) + pow( (y2-y1), 2)));
}

void input(vector <pii> &p, int &n, int &z){
    fstream inp("battery.inp");
    
    inp >> n >> z;
    p.resize(n);
    for(int i=0; i<n; i++){
        int x, y;
        inp >> x >> y;
        p[i] = pii(x, y);
    }
    
}

void output(int ans){
    ofstream out("battery.out");
    out << ans << endl;
}

bool search(vector <pii> &p, vector<bool> &visit, int z, int w){
    queue <pii> q;
    
    q.push({0, 0});
    
    while(!q.empty()){
        int x = q.front().first, y = q.front().second;
        q.pop();
        
        if(getDistance(x, y, z, z) <= w)
            return true;
        
        
        for(int i=0; i<p.size(); i++){
            
            if(visit[i])
                continue;
            
            int nx = p[i].first;
            int ny = p[i].second;
            
            if(getDistance(x, y, nx, ny) <= w){
                q.push({nx, ny});
                visit[i] = true;
            }
        }
        
    }
    
    return false;
}




int main(){
    vector <pii> p;
    
    int n ,z, left, right, mid, ans;
    
    input(p, n, z);
    
    left = 0; right = getDistance(0, 0, z, z);
    
    while( left <= right ){
        vector <bool> visit(n, false);
        mid = (left + right) / 2;
        
        if(search(p, visit, z, mid)){
            right = mid - 1;
            ans = mid;
        }
        else
            left = mid +1;
    }
    
    output(ans);
    return 0;
}
