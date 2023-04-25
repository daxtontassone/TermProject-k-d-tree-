#include <vector>
#include "kdtree.h"

//function that finds the median value given a 2d vector based on the current dimension that is being used
int KDTree::find_median(std::vector<std::vector<double>> list, int dimension, int &median_index){
        //get the number of points
        int num_points = list.size();

        //sort points by value in the given dimension
        std::sort(list.begin(), list.end(),[dimension](std::vector<double> a, std::vector<double> b) {
            return a[dimension] < b[dimension];
        });

        //find index of median point, which is a pointer
        median_index = num_points / 2;
        //if there are an odd number of points, return value at median index
        if (num_points % 2 == 1) {
            return list[median_index][dimension];
        }
            //if there is an even number of points, return average of values at the two middle places
        else {
            double value1 = list[median_index - 1][dimension];
            double value2 = list[median_index][dimension];
            return (value1 + value2) / 2.0;
        }
}

//function that constructs the tree
Node* KDTree::construct(std::vector<std::vector<double>> list, int depth){
    //depth variable that takes the depth and mods it by size (k dimension)
    depth = depth % size;
    //make new node
    Node* data = new Node;
    //median_index is a pointer
    int median_index;
    //find median and get median_index
    int median;
    median = find_median(list, depth, median_index);
    //node data is list indexed by median_index
    data->data = list[median_index];
    //if list size is 1, return data (base case)
    if (list.size() == 1){
        return data;
    }
    //make 2 lists, for left and right side of list
    std::vector<std::vector<double>> left_list;
    std::vector<std::vector<double>> right_list;
    //loop through list and sort data to the proper list, depending on the median
    for (int i = 0 ; i < list.size() ; i++){
        //hold is the value that is being compared, based on the depth that is being used
        double hold = list[i][depth];
        if (hold <= median){
            left_list.push_back(list[i]);
        }
        if (hold >= median){
            right_list.push_back(list[i]);
        }
    }
    //left neighbor and right neighbor called recursively, with left or right list being passed and depth being incremented by 1
    data->left = construct(left_list, depth+1);
    data->right = construct(right_list, depth+1);
    return data;
}

//constructor function that has a vector and size given to it
KDTree::KDTree(std::vector<std::vector<double>> list, int size){
    this->size = size;
    //calls construct
    this->root = construct(list, 0);
}

//constructor function with nothing given
KDTree::KDTree(){
    this->root = nullptr;
    this->size = 0;
}

//insert function, calls insert_helper
void KDTree::insert(std::vector<double> point){
    insert_helper(root, point, 0);
}

//insert_helper, actually does the insert
void KDTree::insert_helper(Node *root, std::vector<double> point, int depth) {
    //mod depth by size
    depth = depth % size;
    //if no root, make new one, base case
    if (!root) {
        root = new Node(point, depth);
        return;
    }
    //get dimension
    int dimension = depth % point.size();
    //if point at dimension less than data of room at that dimension
    if (point[dimension] < root->data[dimension]) {
        //go to left leg
        insert_helper(root->left, point, depth + 1);
    }
    else {
        //else, go to the right leg
        insert_helper(root->right, point, depth + 1);
    }
}

//search function that takes in a point
int KDTree::search(std::vector<double> point){
    //calls search_helper function
    return search_helper(root, point, 0);
}

//search_helper actually does the search
int KDTree::search_helper(Node* node, std::vector<double> point, unsigned depth){
    //base cases
    if (node == nullptr) {
        return false;
    }
    //if point matches search point, return true
    bool match = true;
    for (int i = 0 ; i < size ; i++) {
        if (node->data[i] != point[i]) {
            match = false;
            break;
        }
    }
    if (match) {
        return true;
    }

    //check if search should continue in left or right subtree based on the current depth
    depth = depth % size;
    if (point[depth] < node->data[depth]) {
        //continue left
        return search_helper(node->left, point, depth + 1);
    } else {
        //continue right
        return search_helper(node->right, point, depth + 1);
    }
}

//print function
void KDTree::print(){
    //calls print_helper function
    print_helper(root, 0);
}

//print_helper function that actually does the print
void KDTree::print_helper(Node* node, int depth){
    //if no node, do nothing, base case
    if (!node) {
        return;
    }
    //loop through depth
    for (int i = 0; i < depth; i++) {
        //if 1 away from depth, print |_ (points to child from parent)
        if (i == depth - 1) {
            std::cout << "|_";
        } else {
            //else just print a space
            std::cout << "  ";
        }
    }
    //prints like: (data, data, data) [depth]
    std::cout << "(";
    for (int i = 0; i < node->data.size(); i++) {
        std::cout << ", " << node->data[i];
    }
    std::cout << ") [" << depth << "]" << "\n";
    //recursive call of left and right, and depth+1
    print_helper(node->left, depth+1);
    print_helper(node->right, depth+1);
}
