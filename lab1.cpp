#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
using namespace std;

void write_to_file(const string& name, const string& res) {
	ofstream file(name);
	file << res;
	file.close();
}

void coefficients(double& a, double& b, double& c) {
	cout << "For the equation ax^2 + bx + c = 0 write, what the coefficients a, b, c:" << endl;
	cin >> a >> b >> c;
}

void solve_linear(double b, double c, string& out) {
	if (b == 0) {
		if (c == 0) {
			out = "Infinitely many solutions\n";
		}
		else {
			out = "No solutions\n";
		}
	}
	else {
		out = "Only one solution, x = " + to_string(-c / b) + "\n";
	}
}

double discriminant(double a, double b, double c) {
	return b * b - 4 * a * c;
}

void real_solve(double a, double b, double D, string& out) {
	double x1 = (-b + sqrt(D)) / (2 * a);
	double x2 = (-b - sqrt(D)) / (2 * a);
	out = "Two real solutions: \n x1 = " + to_string(x1) + "\n x2 = " + to_string(x2);
}

void single_solve(double a, double b, string& out) {
	out = "One real solution, x = " + to_string((-b) / (2 * a));
}

void complex_solve(double a, double b, double D, string& out) {
	double real_s = (-b) / (2 * a);
	double imaginary_s = sqrt(-D) / (2 * a);
	out = "Complex solves: \n x1 = " + to_string(real_s) + " + " + to_string(imaginary_s) + "i" + "\n x2 = " + to_string(real_s) + " - " + to_string(imaginary_s) + "i";
}

void solve(double a, double b, double c, string& out) {
	if (a == 0) {
		solve_linear(b, c, out);
	}
	else {
		double D = discriminant(a, b, c);
		if (D > 0) {
			real_solve(a, b, D, out);
		}
		else if (D == 0) {
			single_solve(a, b, out);
		}
		else {
			complex_solve(a, b, D, out);
		}
	}

}

int main() {
	double a, b, c;
	string output_file = "solves.txt";
	string res;
	coefficients(a, b, c);
	solve(a, b, c, res);
	write_to_file(output_file, res);
	return 0;
}