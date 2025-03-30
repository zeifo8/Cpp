#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <string>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm>

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

std::vector<double> readRealSolutions(const std::string& sol) {
    if (sol.find("No solutions") != std::string::npos) return {};
    if (sol.find("Infinitely many") != std::string::npos) return {};
    if (sol.find("i") != std::string::npos)  return {};

    std::vector<double> roots;
    std::vector<std::string> tokens;

    std::size_t start = 0;
    while (true) {
        std::size_t pos = sol.find(' ', start);
        if (pos == std::string::npos) {
            tokens.push_back(sol.substr(start));
            break;
        }
        tokens.push_back(sol.substr(start, pos - start));
        start = pos + 1;
    }

    for (std::size_t i = 0; i < tokens.size(); ++i) {
        std::size_t eqPos = tokens[i].find('=');
        if (eqPos != std::string::npos) {
            std::string numStr = tokens[i].substr(eqPos + 1);
            double val = std::atof(numStr.c_str());
            roots.push_back(val);
        }
    }
    return roots;
}

bool isCorrect(const std::string& teacherSol, const std::string& studentSol) {
    if (teacherSol == "No solutions" && studentSol == "No solutions") {
        return true;
    }
    if (teacherSol == "Infinitely many" && studentSol == "Infinitely many") {
        return true;
    }

    bool teacherHasComplex = (teacherSol.find('i') != std::string::npos);
    bool studentHasComplex = (studentSol.find('i') != std::string::npos);

    if (teacherHasComplex && studentHasComplex) {
        return true;
    }
    if (teacherHasComplex != studentHasComplex) {
        return false;
    }

    std::vector<double> tRoots = readRealSolutions(teacherSol);
    std::vector<double> sRoots = readRealSolutions(studentSol);

    if (tRoots.size() != sRoots.size()) {
        return false;
    }

    std::sort(tRoots.begin(), tRoots.end());
    std::sort(sRoots.begin(), sRoots.end());

    const double EPS = 1e-5;
    for (std::size_t i = 0; i < tRoots.size(); ++i) {
        if (std::fabs(tRoots[i] - sRoots[i]) > EPS) {
            return false;
        }
    }
    return true;
}

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

    int totalEquations = static_cast<int>(equations.size());
    if (totalEquations == 0) {
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

    if (students.empty()) {
        std::cout << "No students\n";
        return 1;
    }

    Teacher teacher;

    std::vector<std::string> teacherSolutions;
    teacherSolutions.reserve(equations.size());

    for (std::size_t iEq = 0; iEq < equations.size(); ++iEq) {
        double a = equations[iEq][0];
        double b = equations[iEq][1];
        double c = equations[iEq][2];

        std::string sol = teacher.solve(a, b, c);
        teacherSolutions.push_back(sol);
    }

    std::ofstream answFile("answers.txt");

    std::vector<int> correctCount(students.size(), 0);

    for (std::size_t iStu = 0; iStu < students.size(); ++iStu) {
        const Student& st = students[iStu];

        for (std::size_t iEq = 0; iEq < equations.size(); ++iEq) {
            double a = equations[iEq][0];
            double b = equations[iEq][1];
            double c = equations[iEq][2];

            std::string stuSol = st.solveEquation(a, b, c, teacher);

            answFile << a << " " << b << " " << c << " | " << stuSol << " | " << st.getName() << "\n";

            if (isCorrect(teacherSolutions[iEq], stuSol)) {
                correctCount[iStu]++;
            }
        }
    }
    answFile.close();

    std::ofstream resFile("results.txt");

    resFile << "Name" << " True/Total\n";

    for (std::size_t iStu = 0; iStu < students.size(); ++iStu) {
        resFile << students[iStu].getName() << " " << correctCount[iStu] << "/" << totalEquations << "\n";
    }
    resFile.close();

    std::cout << "Files are saved\n";

    return 0;
}
