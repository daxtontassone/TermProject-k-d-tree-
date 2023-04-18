#include "node.h"

class KDTree {
private:
    bool same(int point1[], int point2[]);

public:
    Node* insert(Node *root, int point[], unsigned depth);
    int search(Node* root, int point[], unsigned depth);
    void print();
};


