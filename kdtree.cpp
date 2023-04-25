#include <vector>
#include "kdtree.h"

bool KDTree::same(int point1[], int point2[]){
    // Compare values
    for (int i = 0; i < size; i++) {
        if (point1[i] != point2[i]) {
            return false;
        }
    }
    return true;
}

int KDTree::find_median(std::vector<std::vector<double>> list, int dimension, int &median_index){
        // Get the number of points
        int num_points = list.size();

        // Sort the points by their value in the given dimension
        std::sort(list.begin(), list.end(),
                  [dimension](std::vector<double> a, std::vector<double> b) {
                      return a[dimension] < b[dimension];
                  });

        // Find the index of the median point
        median_index = num_points / 2;
        // If there are an odd number of points, return the value at the median index
        if (num_points % 2 == 1) {
            return list[median_index][dimension];
        }
            // If there are an even number of points, return the average of the values at the two middle indices
        else {
            double value1 = list[median_index - 1][dimension];
            double value2 = list[median_index][dimension];
            return (value1 + value2) / 2.0;
        }
}


Node* KDTree::construct(std::vector<std::vector<double>> list, int depth){
    int axis = depth % size;
    Node* data;
    int* median_index;
    int median = find_median(list, axis, *median_index);
    data->location = median;
    data->data = list[*median_index];
    if (list.size() == 1){
        return data;
    }
    std::vector<std::vector<double>> left_list;
    std::vector<std::vector<double>> right_list;
    for (int i = 0 ; i < list.size() ; i++){
        double hold = list[i][axis];
        if (hold <= median){
            left_list.push_back(list[i]);
        }
        if (hold >= median){
            right_list.push_back(list[i]);
        }
    }

    data->left = construct(left_list, depth+1);
    data->right = construct(right_list, depth+1);
    return data;
}

KDTree::KDTree(std::vector<std::vector<double>> list, int size){
    this->size = size;
    this->root = construct(list, 0);
}

KDTree::KDTree(){
    this->root = nullptr;
    this->size = 0;
}

void KDTree::insert(std::vector<double> point){
    insert_helper(root, point, 0);
}

void KDTree::insert_helper(Node *root, std::vector<double> point, int depth) {
    depth = depth % size;
    if (!root) {
        root = new Node(point, depth);
        return;
    }
    int dimension = depth % point.size();
    if (point[dimension] < root->data[dimension]) {
        insert_helper(root->left, point, depth + 1);
    } else {
        insert_helper(root->right, point, depth + 1);
    }
}

int KDTree::search(std::vector<double> point){
    return search_helper(root, point, 0);
}

int KDTree::search_helper(Node* node, std::vector<double> point, unsigned depth){
    // Base cases
    if (node == nullptr) {
        return false;
    }
    // If the point in the current node matches the search point, return true
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

    // Check if the search should continue in the left or right subtree based on the current depth
    int axis = depth % size;
    if (point[axis] < node->data[axis]) {
        return search_helper(node->left, point, depth + 1);
    } else {
        return search_helper(node->right, point, depth + 1);
    }
}

void KDTree::print(){
    print_helper(root, 0);
}

void KDTree::print_helper(Node* node, int depth){
    if (!node) {
        return;
    }
    for (int i = 0; i < depth; i++) {
        if (i == depth - 1) {
            std::cout << "|_";
        } else {
            std::cout << "  ";
        }
    }
    std::cout << "(";
    for (int i = 0; i < node->data.size(); i++) {
        std::cout << ", " << node->data[i];
    }
    std::cout << ") [" << depth << "]" << "\n";
    print_helper(node->left, depth + 1);
    print_helper(node->right, depth + 1);
}
