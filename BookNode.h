#ifndef BookNode_H
#define BookNode_H

#include <string>
#include <vector>
#include "ReservationNode.h"
#include "ReservationHeap.h"

using namespace std;

enum Color { RED, BLACK };

// BookNode structure which includes BookId, BookName, etc.
struct BookNode
{
    int BookID;
    string BookName;
    string AuthorName;
    string AvailabilityStatus;
    int BorrowedBy;

    ReservationHeap ReservationHeap;   // to store the reservations made for the book

    Color color;
    BookNode* parent;
    BookNode* left;
    BookNode* right;

    // Constructor for BookNode
    BookNode(int id, const string& name, const string& author, string availability, int borrowedBy)
        : BookID(id), BookName(name), AuthorName(author), AvailabilityStatus(availability), BorrowedBy(borrowedBy) {}


    BookNode(int id, const string& name, const string& author, string availability)
        : BookID(id), BookName(name), AuthorName(author), AvailabilityStatus(availability), BorrowedBy(-1), color(RED), parent(nullptr), left(nullptr), right(nullptr) {}
        
};

#endif


