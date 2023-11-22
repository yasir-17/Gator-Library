#ifndef RedBlackTree_H
#define RedBlackTree_H

#include <unordered_map>
#include "BookNode.h"

// RedBlack Tree class definition
class RedBlackTree {
private:
    
    BookNode* root;

    // Hashmap to store color
    unordered_map<int, int> nodeColorsOld;
    unordered_map<int, int> nodeColorNew;

    // Helper functions for rotation and fixing violations
    void leftRotate(BookNode* x);
    void rightRotate(BookNode* x);
    void fixInsertion(BookNode* x);
    void fixDeletion(BookNode* x);
    void transplant(BookNode* u, BookNode* v);

    // To find minimum in a tree
    BookNode* treeMinimum(BookNode* x);

    // Helper function to get color flip count
    void storeNodeColor(BookNode *); 
    void compareAndCountColorChanges();

public:
    int colorFlipCount;
    RedBlackTree() : root(nullptr), colorFlipCount(0) {}

    // Insert function for Red-Black Tree
    void insert(int bookId, string bookName, string authorName, string availabilityStatus);

    void deleteNode(int key);

    // Search function for Red-Black Tree
    BookNode* searchNode(int key);
};

#endif