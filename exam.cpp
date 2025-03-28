#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <string>
#include <cmath>

double discriminant(double a, double b, double c) {
    return b * b - 4.0 * a * c;
}

void solve_linear(double b, double c, std::string& out) {
    if (std::fabs(b) < 1e-15) {
        if (std::fabs(c) < 1e-15) {
            out = "Infinitely many";
        }
        else {
            out = "No solutions";
        }
    }
    else {
        double x = -c / b;
        out = "x=" + std::to_string(x);
    }
}

void real_solve(double a, double b, double D, std::string& out) {
    double x1 = (-b + std::sqrt(D)) / (2.0 * a);
    double x2 = (-b - std::sqrt(D)) / (2.0 * a);
    out = "x1=" + std::to_string(x1) + " x2=" + std::to_string(x2);
}

void single_solve(double a, double b, std::string& out) {
    double x = -b / (2.0 * a);
    out = "x=" + std::to_string(x);
}

void complex_solve(double a, double b, double D, std::string& out) {
    double realPart = -b / (2.0 * a);
    double imagPart = std::sqrt(-D) / (2.0 * a);

    out = "x1=" + std::to_string(realPart) + "+" + std::to_string(imagPart) + "i "
        "x2=" + std::to_string(realPart) + "-" + std::to_string(imagPart) + "i";
}

void solve_equation(double a, double b, double c, std::string& out) {
    if (std::fabs(a) < 1e-15) {
        solve_linear(b, c, out);
        return;
    }

    double D = discriminant(a, b, c);

    if (std::fabs(D) < 1e-15) {
        single_solve(a, b, out);
    }
    else if (D > 0) {
        real_solve(a, b, D, out);
    }
    else {
        complex_solve(a, b, D, out);
    }
}

int main() {
    std::ifstream eqFile("equations.txt");
    if (!eqFile.is_open()) {
        std::cout << "Cannot open file\n";
        return 1;
    }

    std::vector< std::array<double, 3> > equations;
    double A, B, C;

    while (eqFile >> A >> B >> C) {
        equations.push_back({ A, B, C });
    }
    eqFile.close();

    std::cout << equations.size() << "\n";

    for (std::size_t i = 0; i < equations.size(); ++i) {
        double a = equations[i][0];
        double b = equations[i][1];
        double c = equations[i][2];

        std::string out;
        solve_equation(a, b, c, out);

        std::cout << a << "x^2 + " << b << "x + " << c << " = 0\n" << out << "\n\n";
    }

    return 0;
}
