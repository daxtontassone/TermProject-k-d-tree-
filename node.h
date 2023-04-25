#include <iostream>
#include <vector>

class Node {
private:
    std::vector<double> data;
    int location;
    Node* parent;
    Node* left;
    Node* right;
    friend class KDTree;
    int k;
public:
    Node();
    Node(std::vector<int> data, int size);
    ~Node();
};




