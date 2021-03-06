#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;


int isPalin(string a) {
	string b = a; 
	reverse(b.begin(), b.end());

	if (a == b)
		return 0;
	else
		return 1;
}

int isPseudo(string a) {
	while(a.front() == a.back()){
		a.pop_back();
		a.erase(0,1);
	} // 다른 부분이 나올 때 까지 앞뒤로 pop

	string tmp = a;

	// case 1. 앞에서 빼기
	tmp.erase(0,1);
	if(isPalin(tmp) == 0)
		return 0;
	
	// case2. 뒤에서 빼기
	tmp = a;
	tmp.pop_back();
	if(isPalin(tmp) == 0)
		return 0;
	
	return 1;
}

int main() {
	int len = 0;
	vector <string> lists;
	vector <int> results;

	ifstream inp("palin.inp");
	string tmp;
	inp >> len;

	for (int i = 0; i < len; i++) {
		inp >> tmp;
		lists.push_back(tmp);
	}

	inp.close();

	for (int i = 0; i < len; i++) {
		if (isPalin(lists[i]) == 1)
			if (isPseudo(lists[i]) == 1)
				results.push_back(3);
			else
				results.push_back(2);
		else
			results.push_back(1);
	}

	ofstream out("palin.out");
	for (int i = 0; i < results.size(); i++) {
		out << results[i] << endl;
	}
	out.close();

	return 0;
}
