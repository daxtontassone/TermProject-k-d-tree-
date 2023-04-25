#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "kdtree.h"

int main(int argc, char*argv[]) {
    int size = std::stoi(argv[2]);
    std::string filename(argv[1]);
    std::ifstream input_file(filename);

    std::vector<std::vector<double>> points;
    std::string line, coordinate_str;
    while (std::getline(input_file, line)) {
        std::vector<double> point;
        std::stringstream line_stream(line);
        while (std::getline(line_stream, coordinate_str, ']')) {
            if (coordinate_str.empty()) {
                continue;
            }
            coordinate_str.erase(std::remove(coordinate_str.begin(), coordinate_str.end(), '['), coordinate_str.end());
            double coordinate;
            std::stringstream coordinate_stream(coordinate_str);
            while (std::getline(coordinate_stream, coordinate_str, ',')) {
                coordinate = std::stod(coordinate_str);
                point.push_back(coordinate);
            }
        }
        points.push_back(point);
    }

    input_file.close();

    KDTree tree(points, size);

//    // Print out the points
//    for (const auto& point : points) {
//        std::cout << "[";
//        for (size_t i = 0; i < point.size(); ++i) {
//            std::cout << point[i];
//            if (i != point.size() - 1) {
//                std::cout << ", ";
//            }
//        }
//        std::cout << "]" << std::endl;
//    }
//
    return 0;
}
