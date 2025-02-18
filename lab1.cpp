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

double discriminant(double a, double b, double c) {
	return b * b - 4 * a * c;
}

void real_solve(double a, double b, double D) {
	double x1 = (-b + sqrt(D)) / (2 * a);
	double x2 = (-b - sqrt(D)) / (2 * a);
	cout << "Two real solutions: \n x1 = " << x1 << "\n x2 = " << x2 << endl;
}

void single_solve(double a, double b) {
	cout << "One real solution, x = " << (-b) / (2 * a) << endl;
}

void complex_solve(double a, double b, double D) {
	double real_s = (-b) / (2 * a);
	double imaginary_s = sqrt(-D) / (2 * a);
	cout << "Complex solves: \n x1 = " << real_s << " + " << imaginary_s << "i" << "\n x2 = " << real_s << " - " << imaginary_s << "i" << endl;
}

int main() {
	double a, b, c;
	coefficients(a, b, c);
	cout << "\n" << discriminant(a, b, c) << endl;
	complex_solve(a, b, discriminant(a, b, c));
	return 0;
}