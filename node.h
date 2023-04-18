#include <iostream>

class Node {
private:
    int data;
    Node* left;
    Node* right;
public:
    Node();
    // Overloading
    Node(int data);
    Node(int data, Node* next);
    ~Node();
};



