#include <iostream>
#include <vector>

class Node {
private:
    //every node has a vector for its data, a left and right node, and k dimensions
    std::vector<double> data;
    Node* left;
    Node* right;
    friend class KDTree;
    int k;
public:
    Node();
    Node(std::vector<double> data, int size);
    ~Node();
};
