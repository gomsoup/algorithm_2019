#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include <vector>
#include <regex>
using namespace std;

wstring q;
vector <int> lcs;
vector <double> result;
vector <wstring> s;

void replaceAll(wstring &str){
    wregex reg1(L"[을|를]");
    wregex reg2(L"[은|는]");
   	wregex reg(L"[\\s]+");
    
    str = regex_replace(str, reg, L" ");
    str = regex_replace(str, reg1, L"을");
    str = regex_replace(str, reg2, L"은");
}


int getMax(){
    double n = 0; int p = 0;
    
    for(int i=0; i<result.size(); i++){
        if(result[i] > n){
            n = result[i];
            p = i;
        }
    }
    
    return p;
}

void sim(){
    for(int i=0; i<lcs.size(); i++){
        double sim = (double)(2* lcs[i]) / (double)(q.size() + s[i].size());
        result.push_back(sim);
    }
}

int LCS(wstring &a){
    int cache[100][100];
    memset(cache, 0, sizeof(cache));
    for(int i= 1; i<=a.length(); i++){
        for(int j = 1; j<= q.length(); j++){
            if(a[i-1] == q[j-1]){
                cache[i][j] = cache[i-1][j-1] + 1;
            }
            else{
                cache[i][j] = max(cache[i-1][j], cache[i][j-1]);
            }
        }
    }
    
    return cache[a.length()][q.length()];
}


void sort(){
    replaceAll(q);
    
    for(int i=0; i<s.size(); i++){
        replaceAll(s[i]);
    }
}

void input(){
    wstring cnt;
    wfstream inp("copy.inp");
    
    getline(inp, cnt);
    getline(inp, q);
    q.pop_back();
    
    while(!inp.eof()){
        wstring tmp;
        getline(inp, tmp);
        tmp.pop_back();
        s.push_back(tmp);
    }
}

void output(int max){
    wofstream out("copy.out");
    
    out << max+2 << endl;
    
    out.close();
}

int main(){
    locale::global(std::locale("ko_KR.UTF-8"));
    
    input();
    sort();
    
    for(auto it : s){
        lcs.push_back(LCS(it));
    }
    sim();
    int max = getMax();
    
    output(max);
    
    
    return 0;
}


