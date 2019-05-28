#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
using namespace std;

vector <string> s(500000); // pre-scaling for memory allocation speed issue
int idx = 0;

void input(){
    int n = 0;
    ifstream inp("./read.inp");
    while(!inp.eof()){
        inp >> s[n++];
    }
    inp.close();
}

void output(){
    ofstream out("./read.out");
    out << s[idx] << endl;
    out.close();
}

void count(){
    int max = 0, cnt = 0;
    
    for(auto it = s.begin(); it != s.end(); it++){
        auto it2 = next(it, 1);

		if (*it != *it2 && max < cnt) {
			max = cnt;
			idx = distance(s.begin(), it);
			cnt = 0;
		}
		else if (*it != *it2 && max >= cnt) cnt = 0;
		else cnt++;
    }
}

int main() {
    input();
    sort(s.begin(), s.end());
    count();
    output();
    return 0;
}
