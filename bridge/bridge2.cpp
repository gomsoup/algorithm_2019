#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>

using namespace std;

class Vector {
public:
	float x = 0, y = 0, z = 0;

	Vector() {
		x = 0; y = 0; z = 0;
	}
	Vector(const float x, const float y, const float z) {
		this->x = x; this->y = y; this->z = z;
	}
	Vector operator+(Vector v) {
		float x, y, z;
		x = this->x + v.x;
		y = this->y + v.y;
		z = this->z + v.z;
		return Vector(x, y, z);
	}	
	Vector operator-(Vector v) {
		float x, y, z;
		x = this->x - v.x;
		y = this->y - v.y;
		z = this->z - v.z;
		return Vector(x, y, z);
	}
	Vector operator^(float t) {
		float x, y, z;
		x = this->x * t;
		y = this->y * t;
		z = this->z * t;
		return Vector(x, y, z);
	}
	Vector operator*(Vector v) { // cross
		float x, y, z;
		x = this->y * v.z - this->z * v.y;
		y = this->z * v.x - this->x * v.z;
		z = this->x * v.y - this->y * v.x;
		return Vector(x, y, z);
	}
	void getXYZ(const float x, const float y, const float z) {
		this->x = x; this->y = y; this->z = z;
	}
	float size() {
		return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
	}
};

float getShortDistance(Vector a, Vector b, Vector p) {
	Vector x;
	float t=0;
	
	vector <Vector> v;
	vector <float> result;

	for (int i = 0; i < 100; i++) {
		x = (b ^ t) + (a ^ (1 - t));
		v.push_back(x);
		t += 0.01;
	}
	
	for (int i = 0; i < 100; i++) {
		float d = sqrt(pow(v[i].x - p.x, 2) + pow(v[i].y - p.y, 2) + pow(v[i].z - p.z, 2));
		result.push_back(d);
	}

	return *min_element(result.begin(), result.end());
}

int getSolution(float f) {
	float fraction = f - (int)f;

	if (fraction > 0) {
		return (int)f + 1;
	}

	return (int)f;
}

void input(Vector &a, Vector &b, Vector& p) {
	ifstream inp("bridge.inp");
	float x, y, z;

	inp >> x >> y >> z;
	a.getXYZ(x, y, z);
	inp >> x >> y >> z;
	b.getXYZ(x, y, z);
	inp >> x >> y >> z;
	p.getXYZ(x, y, z);

	inp.close();
}

void output(int sol) {
	ofstream out("bridge.out");

	out << sol << endl;

	out.close();
}

int main() {
	Vector a, b, p;
	
	input(a, b, p);
	float sol = getShortDistance(a, b, p);
	output(getSolution(sol));

	return 0;
}
