#include <iostream>
#include <cmath>

using namespace std;

void coefficients(double& a, double& b, double& c) {
	cout << "For the equation ax^2 + bx + c = 0 write, what the coefficients a, b, c:" << endl;
	cin >> a >> b >> c;
}

void solve_linear(double b, double c) {
	if (b == 0) {
		if (c == 0) {
			cout << "Infinitely many solutions" << endl;
		}
		else {
			cout << "No solutions" << endl;
		}
	}
	else {
		cout << "Only one solution, x = " << -c / b << endl;
	}
}


int main() {
	double a, b, c;
	coefficients(a, b, c);
	cout << a << " " << b << " " << c << endl;
	solve_linear(b, c);
	return 0;
}