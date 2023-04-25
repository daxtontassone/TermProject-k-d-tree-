#include "node.h"

class KDTree {
private:
    Node* root;
    int size;
    bool same(int point1[], int point2[]);
    int find_median(std::vector<std::vector<double>> list, int dimension, int &median_index);
    Node* construct(std::vector<std::vector<double>> list, int depth);
    int search_helper(Node* root, std::vector<double> point, unsigned depth);
    void insert_helper(Node* root, std::vector<double> point, int depth);
    void print_helper(Node* node, int depth);
public:
    KDTree(std::vector<std::vector<double>> list, int size);
    KDTree();
    void insert(std::vector<double> point);
    int search(std::vector<double> point);
    void print();
};
