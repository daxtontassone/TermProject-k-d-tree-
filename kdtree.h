#include "node.h"

class KDTree {
private:
    bool same(int point1[], int point2[]);
    int find_median(std::vector<std::vector<double>> list, int dimension);
    Node* construct(std::vector<std::vector<double>> list, int depth, int i);
    int size;
public:
    KDTree(std::vector<std::vector<double>> list, int size);
    Node* insert(Node *root, int point[], unsigned depth);
    int search(Node* root, int point[], unsigned depth);
    void print();
};


