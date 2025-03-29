#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <string>
#include <cmath>
#include <cstdlib>
#include <ctime>

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

enum class StudentType {
    Excellent,
    Bad,
    Middle
};

StudentType readStudentType(const std::string& str) {
    if (str == "Excellent") {
        return StudentType::Excellent;
    }
    if (str == "Bad") {
        return StudentType::Bad;
    }
    if (str == "Middle") {
        return StudentType::Middle;
    }
}

class Teacher {
public:
    std::string solve(double a, double b, double c) const {
        std::string out;
        solve_equation(a, b, c, out);
        return out;
    }
};

class Student {
private:
    std::string name;
    StudentType type;

public:
    Student(const std::string& n, StudentType t)
        : name(n), type(t) {}

    std::string getName() const {
        return name;
    }

    StudentType getType() const {
        return type;
    }

    std::string solveEquation(double a, double b, double c, const Teacher& teacher) const
    {
        if (type == StudentType::Excellent) {
            return teacher.solve(a, b, c);
        }
        else if (type == StudentType::Bad) {
            return "x=0";
        }
        else {
            double r = static_cast<double>(rand()) / RAND_MAX;
            if (r < 0.6) {
                return teacher.solve(a, b, c);
            } else {
                return "x=0";
            }
        }
    }
};

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

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

    std::cout << equations.size() << " equations\n";

    if (equations.empty()) {
        std::cout << "No equations\n";
        return 1;
    }

    std::ifstream stFile("students.txt");
    if (!stFile.is_open()) {
        std::cout << "Cannot open file\n";
        return 1;
    }

    std::vector<Student> students;
    std::string sName, sTypeStr;

    while (stFile >> sName >> sTypeStr) {
        StudentType stType = readStudentType(sTypeStr);
        Student st(sName, stType);
        students.push_back(st);
    }
    stFile.close();

    std::cout << students.size() << " students\n";

    if (students.empty()) {
        std::cout << "No students\n";
        return 1;
    }

    Teacher teacher;

    std::array<double, 3> firstEq = equations[0];
    double a = firstEq[0];
    double b = firstEq[1];
    double c = firstEq[2];

    std::cout << "\n1 equation: " << a << "x^2 + " << b << "x + " << c << " = 0\n";

    for (std::size_t iStu = 0; iStu < students.size(); ++iStu) {
        const Student& st = students[iStu];
        std::string stuSol = st.solveEquation(a, b, c, teacher);

        std::cout << st.getName() << ": " << stuSol << "\n";
    }

    return 0;
}
