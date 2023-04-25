#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "kdtree.h"

//main function of KDTree
int main(int argc, char*argv[]) {
    //get size (k variable) from CLA
    int size = std::stoi(argv[2]);
    //get file name from CLA
    std::string filename(argv[1]);
    //open file
    std::ifstream input_file(filename);
    //make a 2d vector to fill with points
    std::vector<std::vector<double>> points;
    std::string line, coordinate_str;
    //while loop that loops through in_file
    while (std::getline(input_file, line)) {
        std::vector<double> point;
        std::stringstream line_stream(line);
        //get line, continue until ']'
        while (std::getline(line_stream, coordinate_str, ']')) {
            //if empty, continue
            if (coordinate_str.empty()) {
                continue;
            }
            //remove '[' from string
            coordinate_str.erase(std::remove(coordinate_str.begin(), coordinate_str.end(), '['), coordinate_str.end());
            double coordinate;
            std::stringstream coordinate_stream(coordinate_str);
            //get each value and push it into point vector, separated by ,
            while (std::getline(coordinate_stream, coordinate_str, ',')) {
                coordinate = std::stod(coordinate_str);
                //push to point
                point.push_back(coordinate);
            }
        }
        //push point vector to points 2d vector
        points.push_back(point);
    }
    //close file
    input_file.close();

    //make the tree, giving it the points 2d vector and the size (k dimensions)
    KDTree tree(points, size);

    std::string input;
    //while loop that runs
    while (input != "end"){
        //possible input options
        std::cout<<"Commands: Insert, Search, Print, End";
        //cin input
        std::cin>>input;
        //make it all lowercase
        for (int i = 0 ; i < input.size() ; i++){
            input[i] = tolower(input[i]);
        }
        //if input is insert
        if (input == "insert"){
            //get point, convert it from string to vector
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
            //insert it into the tree
            tree.insert(point);
        }
        //if input is search
        else if (input == "search"){
            //get point, convert it from string to vector
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
            bool check;
            //check if the point is in the tree or not
            check = tree.search(point);
            //print either true or false
            if (check == 1) {
                std::cout<<"True\n";
            }
            else if (check == 0){
                std::cout<<"False\n";
            }
        }
        //if input is print
        else if(input == "print"){
            //print tree
            tree.print();
        }
        //if input is anything else, tell user they input something wrong, ask them to input again
        else {
            std::cout<<"Looks like you input something besides one of the allowed commands. Please try again.\n";
        }
    }

    return 0;
}
