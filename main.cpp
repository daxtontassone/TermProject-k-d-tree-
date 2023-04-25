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

    std::string input;
    while (input != "end"){
        std::cout<<"Commands: Insert, Search, Print";
        std::cin>>input;
        for (int i = 0 ; i < input.size() ; i++){
            input[i] = tolower(input[i]);
        }
        if (input == "insert"){
            std::cout<<"Enter the point you want to insert (ex: [340, 2] or [98, 320, 789]):";
            std::vector<double> point;
            std::string pointString;
            std::cin>>pointString;
            pointString.erase(remove(pointString.begin(), pointString.end(), '['), pointString.end());
            pointString.erase(remove(pointString.begin(), pointString.end(), ']'), pointString.end());
            for (int i = 0 ; i < size ; i++) {
                std::stringstream pointStream(pointString);
                std::getline(pointStream, pointString, ',');
                double coordinate = std::stod(coordinate_str);
                point.push_back(coordinate);
            }
            tree.insert(point);
        }
        else if (input == "search"){
            std::cout<<"Enter what you want to search for (ex: [1, 2] or [23, 55, 789]):";
            std::vector<double> point;
            std::string pointString;
            std::cin>>pointString;
            pointString.erase(remove(pointString.begin(), pointString.end(), '['), pointString.end());
            pointString.erase(remove(pointString.begin(), pointString.end(), ']'), pointString.end());
            for (int i = 0 ; i < size ; i++) {
                std::stringstream pointStream(pointString);
                std::getline(pointStream, pointString, ',');
                double coordinate = std::stod(coordinate_str);
                point.push_back(coordinate);
            }
            tree.search(point);
        }
        else if(input == "print"){
            tree.print();
        }
        else {
            std::cout<<"Looks like you input something besides one of the allowed commands. Please try again." << std::endl;
        }
    }

    return 0;
}
