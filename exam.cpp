#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <string>

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

    std::cout << equations.size();

    return 0;
}
