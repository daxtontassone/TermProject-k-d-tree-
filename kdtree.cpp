#include "kdtree.h"

bool same(int point1[], int point2[]){
    // Compare individual values
    for (int i = 0; i < k; ++i) {
        if (point1[i] != point2[i]) {
            return false;
        }
    }
    return true;
}


Node* KDTree::insert(Node *root, int point[], unsigned depth) {
    // if tree is empty
    if (root == NULL) {
        //return Node(point);
    }
    // Calculate current dimension of comparison
    unsigned currentDim = depth % k;

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
    if (same(root->data, point)) {
        return true;
    }

    // Current dimension is computed using current depth and total
    // dimensions (k)
    unsigned currentDim = depth % k;

    // Compare point with root with respect to cd (Current dimension)
    if (point[currentDim] < root->data[currentDim]) {
        return search(root->left, point, depth + 1);
    }
    return search(root->right, point, depth + 1);
}

void KDTree::print(){

}
