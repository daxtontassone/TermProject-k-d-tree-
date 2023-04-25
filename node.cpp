#include "node.h"
#include <vector>

// Default constructor
Node::Node(){
    this->k = 0;
    Node* temp = new Node;
    for (int i=0; i<k; i++) {
        temp->data.push_back(0);
    }
    temp->left = temp->right = NULL;
}

Node::Node(std::vector<double> data, int size){
    this->k = size;
    Node* temp = new Node;
    for (int i=0; i<k; i++) {
        temp->data.push_back(data[i]);
    }
    temp->left = temp->right = NULL;
}


Node::~Node(){
    if(this->left != nullptr || this->right != nullptr){
        delete this->left;
        delete this->right;
    }
}
