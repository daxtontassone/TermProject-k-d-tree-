#include "node.h"

class KDTree {
private:
    //root of tree
    Node* root;
    //size, which is the k dimensions
    int size;
    //function that returns the median of a 2d vector
    int find_median(std::vector<std::vector<double>> list, int dimension, int &median_index);
    //construct fuction
    Node* construct(std::vector<std::vector<double>> list, int depth);
    //function that performs search
    int search_helper(Node* root, std::vector<double> point, unsigned depth);
    //function that performs insert
    void insert_helper(Node* root, std::vector<double> point, int depth);
    //function that performs print
    void print_helper(Node* node, int depth);
public:
    //constructors
    KDTree(std::vector<std::vector<double>> list, int size);
    KDTree();
    //public insert function
    void insert(std::vector<double> point);
    //public search function
    int search(std::vector<double> point);
    //public print function
    void print();
};


