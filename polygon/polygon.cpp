#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

class dot {
public:
	int x, y;
	int index;

	dot* next, * prev;
	
	dot() {

	}
	dot(int index, int x, int y, dot* prev = nullptr, dot* next = nullptr) {
		this->index = index;
		this->x = x; this->y = y;
		this->next = next; this->prev = prev;
	}

	dot operator -(const dot d) {
		return dot(0, x - d.x, y - d.y);
	}
	int operator *(const dot d) {
		return x * d.x + y * d.y;
	}
	int operator ^(const dot d) {
		return x * d.y - y * d.x;
	}

};

vector <dot* > dots; bool none = false;
int n, cnt;

bool onLine(dot p, dot q, dot r) {
	if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) && q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
		return true;

	return false;
}

int ccw(dot p, dot q, dot r){
	int a = p.x * q.y + q.x * r.y + r.x * p.y;
	int b = p.y * q.x + q.y * r.x + r.y * p.x;
	int t = a - b;

	if (t < 0) return -1;
	else if (t == 0) return 0;

	return 1;
}

bool isIntersect(dot p1, dot q1, dot p2, dot q2) {
	// ref : http://flassari.is/2008/11/line-line-intersection-in-cplusplus/
	int x1 = p1.x, x2 = q1.x, x3 = p2.x, x4 = q2.x;
	int y1 = p1.y, y2 = q1.y, y3 = p2.y, y4 = q2.y;

	double den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
	if (den == 0) return false;

	double prev = (x1 * y2 - y1 * x2), post = (x3 * y4 - y3 * x4);
	double x = (prev * (x3 - x4) - (x1 - x2) * post) / den;
	float y = (prev * (y3 - y4) - (y1 - y2) * post) / den;

	if (x <= min(x1, x2) || x >= max(x1, x2) || x <= min(x3, x4) || x >= max(x3, x4)) return false;
	if (y <= min(y1, y2) || y >= max(y1, y2) || y <= min(y3, y4) || y >= max(y3, y4)) return false;

	return true;
}

int calcAngle(dot p, dot q, dot r) {
	dot ab = q - p;
	dot bc = q - r;
	double pi = 3.14;

	double s = atan2(ab ^ bc, ab * bc);
	if (s < 0) s += 2 * pi;

	double d;
	d = s * 180 / pi;
	if (d >= 180) 
		cnt++;

	return d;
}

void input() {
	ifstream inp("./polygon.inp");

	inp >> n;
	for (int i = 0; i < n; i++) {
		int x, y;
		inp >> x >> y;

		if (i == 0)
			dots.push_back(new dot(i, x, y));
		else if (i == n - 1) {
			dots.push_back(new dot(i, x, y, dots[i - 1], dots[0]));
			dots[i - 1]->next = dots[i];
			dots[0]->prev = dots[i];
		}
		else {
			dots.push_back(new dot(i, x, y, dots[i-1]));
			dots[i - 1]->next = dots[i];
		}
	}

	inp.close();
}

void output() {
	ofstream out("./polygon.out");

	if (none) out << "None";
	else if (cnt != 0) out << "Concave " << cnt;
	else out << "Convex";

	out.close();
}


int main() {
	input();
	dot a, b, c, d;

	for (int i = 0; i < n; i++) {
		a = *dots[i]; b = *dots[i]->next;

		for (int j = 0; j < n; j++) {
			if (j == i) continue;

			c = *dots[j]; d = *dots[j]->next;
			none = isIntersect(a, b, c, d);
			if (none) break;
		}
		if (none) break;
	}

	for (int i = 0; i < n; i++) {
		a = *dots[i]->prev; b = *dots[i]; c = *dots[i]->next;

		double s = calcAngle(a, b, c);

	}
	
	output();
	return 0;
}
