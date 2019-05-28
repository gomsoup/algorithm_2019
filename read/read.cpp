#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <algorithm>
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
    out << s[idx];
    out.close();
}

void count(){
    int max = 0, cnt = 0;

	sort(s.begin(), s.end());
	auto it = s.begin();

	while (it != s.end()) {
		auto it2 = next(it, 1);

		if (*it == *it2) cnt++;
		else if (max >= cnt) cnt = 0;
		else {
			max = cnt;
			idx = distance(s.begin(), it);
			cnt = 0;
		}
		
		it++;
	}
}

int main() {
    input();
    count();
    output();
    return 0;
}
