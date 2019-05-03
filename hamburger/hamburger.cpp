#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

typedef pair<int, int> pii;
vector <string> table;
int k, result = 0;

void canEat() {
	for (int i = 0; i < table.size(); i++) {
		if (table[i] == "P") {
			pii range;

			if (i - k < 0) range.first = 0;
			else range.first = i - k;

			if (i + k > (table.size() - 1)) range.second = table.size() - 1;
			else range.second = i + k;

			for (int i = range.first; i <= range.second; i++) {
				if (table[i] == "H") {
					result++;
					table[i] = "X";
					break;
				}
			}
		}
	}
}



void input() {
	int n;
	fstream inp("hamburg.inp");

	inp >> k >> n;

	for (int i = 0; i < n; i++) {
		string tmp; inp >> tmp;
		table.push_back(tmp);
	}

	inp.close();
}



void output() {
	ofstream out("hamburg.out");

	out << result << endl;

	out.close();
}



int main() {
	input();
	canEat();
	output();

	return 0;
}