#include <iostream>
#include <cmath>

using namespace std;

void coefficients(double& a, double& b, double& c) {
	cout << "For the equation ax^2 + bx + c = 0 write, what the coefficients a, b, c:" << endl;
	cin >> a >> b >> c;
}

int main() {
	double a, b, c;
	coefficients(a, b, c);
	cout << a << " " << b << " "  << c;
	return 0;
}