#include <iostream>
#include <vector>
#include "oil.h"

using namespace std;
typedef pair<int, int> pii;

int search(int left, int right, int flag) {
	// need no more search
	if (left == right && flag == 0) return left; 
	else if (left == right && flag == 1) return right;

	//get search range
	pii range[2];
	int mid = (left + right) / 2;
	range[0] = make_pair(left, mid); range[1] = make_pair(mid + 1, right);

	int result;
	
	if (flag == 0)
		result = observe(range[0].first, range[0].second);
	else
		result = observe(range[1].first, range[1].second);


	if (result == 2 && flag == 0) // left
		search(range[0].first, range[0].second, flag);
	else if (result == 2 && flag == 1) //right
		search(range[1].first, range[1].second, flag);

	else if (result == 1 && flag == 0)
		return left;
	else if (result == 1 && flag == 1)
		return right;

	else if (flag == 0) 
		search(range[1].first, range[1].second, flag);
	else
		search(range[0].first, range[0].second, flag);
}


int main() {
	initial();
	int n = oil_size();
	pii ans;

	ans.first = search(0, n-1, 0);
	ans.second = search(0, n-1, 1);

	oil_report(ans.first, ans.second);

	return 0;
}
