#include "node.h"

// Default constructor
Node::Node(){
    this->data = 0;
    this->left = nullptr;
    this->right = nullptr;
}

Node::Node(int data){
    this->data = data;
    this->left = nullptr;
    this->right = nullptr;
}

Node::Node(int data, Node* next){
    this->data = data;
    this->left = next;
}

Node::~Node(){
    if(this->left != nullptr){
        delete this->left;
    }
}
