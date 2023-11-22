#include <iostream>
#include <vector>
#include "RedBlackTree.h"


using namespace std;

//  Populate the color hash map
void RedBlackTree :: storeNodeColor(BookNode* x) {
    if (x != nullptr) {
        nodeColorNew[x->BookID] = x->color;
        storeNodeColor(x->left);
        storeNodeColor(x->right);
    }
}

// compare two hashmap and count color changes
void RedBlackTree :: compareAndCountColorChanges() {

    for (auto it : nodeColorNew) {
        if (nodeColorsOld.find(it.first) != nodeColorsOld.end()) {
            if (it.second != nodeColorsOld[it.first]) colorFlipCount += 1;
        }
    }
}

// Function to left rotate
void RedBlackTree::leftRotate(BookNode* x) {
    BookNode* y = x->right;
    x->right = y->left;
    if (y->left != nullptr) {
            y->left->parent = x;
        }
    y->parent = x->parent;
    if (x->parent == nullptr) {
        root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

// Function to right rotate
void RedBlackTree::rightRotate(BookNode* y) {
    BookNode* x = y->left;
    y->left = x->right;
    if (x->right != nullptr) {
        x->right->parent = y;
    }
    x->parent = y->parent;
    if (y->parent == nullptr) {
        root = x;
    } else if (y == y->parent->left) {
        y->parent->left = x;
    } else {
        y->parent->right = x;
    }
    x->right = y;
    y->parent = x;

}

// Function to fix the red black tree structure after insertion
void RedBlackTree::fixInsertion(BookNode* z) {
    while (z != root && z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            BookNode* y = z->parent->parent->right;
            if (y != nullptr && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(z->parent->parent);
            }
        } else {
            BookNode* y = z->parent->parent->left;
            if (y != nullptr && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(z->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

// Function to insert node in RBT
void RedBlackTree::insert(int bookId, string bookName, string authorName, string availabilityStatus) {
    BookNode* z = new BookNode(bookId, bookName, authorName, availabilityStatus);
    BookNode* y = nullptr;
    BookNode* x = root;

    while (x != nullptr) {
        y = x;
        if (z->BookID < x->BookID) {
            x = x->left;
        } else {
            x = x->right;
        }
    }

    z->parent = y;
    if (y == nullptr) {
        root = z;
    } else if (z->BookID < y->BookID) {
        y->left = z;
    } else {
        y->right = z;
    }

    fixInsertion(z);
    storeNodeColor(root);
    compareAndCountColorChanges();
    nodeColorsOld = nodeColorNew;
    nodeColorNew.clear();
}

// Function to delete node from RBT
void RedBlackTree::deleteNode(int key) {
    BookNode* z = searchNode(key);
    BookNode* y = z;
    BookNode* x;
    Color yOriginalColor = y->color;

    if (z->left == nullptr) {
        x = z->right;
        transplant(z, z->right);
    } else if (z->right == nullptr) {
        x = z->left;
        transplant(z, z->left);
    } else {
        y = treeMinimum(z->right);
        yOriginalColor = y->color;
        x = y->right;
        if (y->parent == z) {
            if (x != nullptr) {
                x->parent = y;
            }
        } else {
            transplant(y, y->right);
            y->right = z->right;
            if (y->right != nullptr) {
                y->right->parent = y;
            }
        }
        transplant(z, y);
        y->left = z->left;
        if (y->left != nullptr) {
            y->left->parent = y;
        }
        y->color = z->color;
    }

    delete z;

    if (yOriginalColor == BLACK) {
        if (x != nullptr) {
            fixDeletion(x);
        }
    }
    
    storeNodeColor(root);
    compareAndCountColorChanges();
    nodeColorsOld = nodeColorNew;
    nodeColorNew.clear();
}

// Function to swap one subtree with another
void RedBlackTree::transplant(BookNode* u, BookNode* v) {
    if (u->parent == nullptr) {
        root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    if (v != nullptr) {
        v->parent = u->parent;
    }
}

// Function to fix the red black tree structure after deletion
void RedBlackTree::fixDeletion(BookNode* x) {
    while (x != root && (x == nullptr || x->color == BLACK)) {
        if (x == x->parent->left) {
            BookNode* w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(x->parent);
                w = x->parent->right;
                        
            }
            if ((w->left == nullptr || w->left->color == BLACK) &&
                (w->right == nullptr || w->right->color == BLACK)) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right == nullptr || w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(w);
                    w = x->parent->right;
                            
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                leftRotate(x->parent);
                x = root;
            }
        } else {
            BookNode* w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rightRotate(x->parent);
                w = x->parent->left;
                        
            }
            if ((w->right == nullptr || w->right->color == BLACK) &&
                (w->left == nullptr || w->left->color == BLACK)) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left == nullptr || w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(w);
                    w = x->parent->left;
                            
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rightRotate(x->parent);
                x = root;
            }
        }
    }
    if (x != nullptr) {
        x->color = BLACK;
    }
}

// Function to find minimum in tree
BookNode* RedBlackTree::treeMinimum(BookNode* x) {
    while (x->left != nullptr) {
            x = x->left;
        }
    return x;
}

// Function to search node in a tree.
BookNode* RedBlackTree::searchNode(int key) {
    BookNode* current = root;

    while (current != nullptr) {
        if (key == current->BookID) {
            return current;
        } else if (key < current->BookID) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    return nullptr;
}