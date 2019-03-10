#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

class Vector {
private:
	float x = 0, y = 0, z = 0;

public:
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
	Vector operator*(Vector v) { // cross product
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
	Vector AB = b - a;
	Vector AP = p - a;
	Vector square = AB * AP;
	return  square.size() / AB.size();
	
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
