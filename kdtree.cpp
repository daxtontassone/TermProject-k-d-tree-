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

int KDTree::find_median(std::vector<std::vector<double>> list, int dimension){
        // Get the number of points
        int num_points = list.size();

        // Sort the points by their value in the given dimension
        std::sort(list.begin(), list.end(),
                  [dimension](std::vector<double> a, std::vector<double> b) {
                      return a[dimension] < b[dimension];
                  });

        // Find the index of the median point
        int median_index = num_points / 2;

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


Node* KDTree::construct(std::vector<std::vector<double>> list, int depth, int i){
    int axis = depth % size;
    Node* data;
    int median = find_median(list, axis);
    data->location = median;
    data->data = list[i];
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

    data->left = construct(left_list, depth+1, i+1);
    data->right = construct(right_list, depth+1, i+1);
    return data;
}

KDTree::KDTree(std::vector<std::vector<double>> list, int size){
    this->size = size;
    construct(list, 0, 0);
}

Node* KDTree::insert(Node *root, int point[], unsigned depth) {
    // if tree is empty
    if (root == NULL) {
        //return Node(point);
    }
    // Calculate current dimension of comparison
    unsigned currentDim = depth % size;

    // Compare the new point with root on current dimension 'cd'
    // and decide the left or right subtree
    if (point[currentDim] < (root->data[currentDim])) {
        root->left = insert(root->left, point, depth + 1);
    }
    else {
        root->right = insert(root->right, point, depth + 1);
    }

    return root;
}

int KDTree::search(Node* root, int point[], unsigned depth){
    // Base cases
    if (root == NULL) {
        return false;
    }
//    if (same(root->data, point)) {
//        return true;
//    }

    // Current dimension is computed using current depth and total
    // dimensions (k)
    unsigned currentDim = depth % size;

    // Compare point with root with respect to cd (Current dimension)
    if (point[currentDim] < root->data[currentDim]) {
        return search(root->left, point, depth + 1);
    }
    return search(root->right, point, depth + 1);
}

void KDTree::print(){

}
