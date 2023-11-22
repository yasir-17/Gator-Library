#include <iostream>
#include "GatorLibrary.h"
#include "RedBlackTree.h"
#include "ReservationHeap.h"
#include "BookNode.h"

using namespace std;

RedBlackTree redBlackTree;

// PrintBookNode function to print information about a book node
void GatorLibrary::PrintBookNode(BookNode& bookNode) {
    cout << "BookID = " << bookNode.BookID << "\n";
    cout << "Title = \"" << bookNode.BookName << "\"\n";
    cout << "Author = \"" << bookNode.AuthorName << "\"\n";
    cout << "Availability = \"" << bookNode.AvailabilityStatus << "\"\n";
    cout << "BorrowedBy = " << (bookNode.BorrowedBy != -1 ? to_string(bookNode.BorrowedBy) : "None") << "\n";

    // Print reservations
    vector<ReservationNode> reservations = bookNode.ReservationHeap.getReservations();
    cout << "Reservations = [";
    for (size_t i = 0; i < reservations.size(); ++i) {
        cout << reservations[i].patronID;
        if (i != reservations.size() - 1) {
            cout << ", ";
        }
    }
    cout << "]\n\n";
}

// PrintReservationNode function to print information about a reservation node
void GatorLibrary::PrintReservationNode(const ReservationNode& reservationNode) {
    cout << "(" << reservationNode.patronID << "," << reservationNode.priorityNumber << ","
         << reservationNode.timeOfReservation << ")";
}

// Function to print details of the Book
void GatorLibrary::PrintBook(int bookID) {
    BookNode* foundBook = searchBookByID(bookID);

    // If the book is found, print its information
    if (foundBook != nullptr) {
        PrintBookNode(*foundBook);
    } else {
        // If not found, print an error message
        cout << "Book " << bookID << " not found in the Library\n\n";
    }
}

// Function to search for a book in Red Black Tree
BookNode* GatorLibrary::searchBookByID(int bookID) {
    // Use the Red-Black Tree's search function to find the book by ID
    return redBlackTree.searchNode(bookID);
}

// Function to print details of the Book with the ID lies between given two IDs
void GatorLibrary::PrintBooks(int bookID1, int bookID2) {
    for (int bookID = bookID1; bookID <= bookID2; ++bookID) {
        if (BookNode* bookNode = searchBookByID(bookID)) {
            PrintBookNode(*bookNode);
        } 
    }
}

// Function to insert book into library (RBT)
void GatorLibrary::InsertBook(int bookID, const string& bookName, const string& authorName, string availability) {
    // Check if the book already exists in the library
    BookNode* existingBook = searchBookByID(bookID);

    if (existingBook) {
        // Book with the same ID already exists
        cout << "Book with ID " << bookID << " already exists in the Library\n";
    } else {
        // Insert the new book into the Red-Black Tree
        redBlackTree.insert(bookID, bookName, authorName, availability);;
    }
}

// Function to implement mechanism of Borrow Book
void GatorLibrary::BorrowBook(int patronID, int bookID, int patronPriority) {
    // Search for the book in the Red-Black Tree
    BookNode* bookToBorrow = searchBookByID(bookID);

    if (bookToBorrow) {
        // Book found in the library, borrow or reserve it
        if (bookToBorrow->AvailabilityStatus == "Yes") {
            // Book is available, update status
            bookToBorrow->AvailabilityStatus = "No";
            bookToBorrow->BorrowedBy = patronID;
            cout << "Book " << bookToBorrow->BookID << " Borrowed by Patron " << patronID << "\n\n";
        } else {
            // Book is not available, create a reservation
            bookToBorrow->ReservationHeap.insertReservation(patronID, patronPriority);
            cout << "Book " << bookToBorrow->BookID << " Reserved by Patron " << patronID << "\n\n";
        }
    } else {
        // Book not found in the library
        cout << "Book " << bookID << " not found in the Library\n\n";
    }
}

// Return Book Function
void GatorLibrary::ReturnBook(int patronID, int bookID) {
    BookNode* bookNode = searchBookByID(bookID); // Search for Book

    if (bookNode) {
        // Book is found
        if (bookNode->BorrowedBy == patronID) {
            // Book is returned by the correct patron
            cout << "Book " << bookID << " Returned by Patron " << patronID << "\n\n";

            // Check if there are reservations
            if (!bookNode->ReservationHeap.isEmpty()) {
                // Get the top priority patron from the reservation heap
                ReservationNode topPriorityReservation = bookNode->ReservationHeap.getTopPriority();

                // Assign the book to the top priority patron
                bookNode->BorrowedBy = topPriorityReservation.patronID;

                // Remove the top priority reservation from the heap
                bookNode->ReservationHeap.removeTopPriority();

                cout << "Book " << bookID << " Allotted to Patron " << topPriorityReservation.patronID << "\n\n";
            } else {
                // No reservations, mark the book as available
                bookNode->AvailabilityStatus = "Yes";
            }
        } else {
            // Book is not borrowed by the specified patron
            cout << "Book " << bookID << " is not currently borrowed by Patron " << patronID << "\n\n";
        }
    } else {
        // Book not found
        cout << "Book " << bookID << " not found in the Library\n\n";
    }
}

// Function to remove book from library
void GatorLibrary::DeleteBook(int bookID) {
    // Search for the book
    BookNode* bookToDelete = searchBookByID(bookID);

    if (bookToDelete == nullptr) {
        // Book not found, print a message
        cout << "Book " << bookID << " not found in the Library\n\n";
        return;
    }

    // Check if the book has reservations
    if (!bookToDelete->ReservationHeap.isEmpty()) {
        // Book has reservations, cancel them
        vector<ReservationNode>& reservations = bookToDelete->ReservationHeap.getReservations();
        
        cout << "Book " << bookID << " is no longer available. Reservation made by Patrons ";
        for (size_t i = 0; i < reservations.size(); ++i) {
            cout << reservations[i].patronID;
            if (i != reservations.size() - 1) {
                cout << ", ";
            }
        }
        cout << " has been cancelled!\n\n";

        // Clear reservations
        bookToDelete->ReservationHeap.getReservations().clear();
        redBlackTree.deleteNode(bookID);

    } else {
        // No reservations found. Simply delete the book
        redBlackTree.deleteNode(bookID);
        cout << "Book " << bookID << " is no longer available\n\n";
    }
}

// Function to print closest book of the given ID
void GatorLibrary::FindClosestBook(int targetID) {

    // Search for book in the library
    if (BookNode* bookNode = searchBookByID(targetID)) {
        PrintBook(targetID);
        return;
    }
    
    int i = 1;
    bool flag = false;

    while (true) {

        int forward = targetID + i;   // to search in forward direction
        int backward = targetID - i;   // to search in backward direction

        if (searchBookByID(backward)) {
            PrintBook(backward);
            flag = true;
        }
        if (searchBookByID(forward)) {
            PrintBook(forward);
            flag = true;
        }

        if (flag) return;
        i += 1;
    }

    return;
}

// Returns the color flip count
int GatorLibrary::ColorFlipCount() {
    
    cout << "Color Flip Count:" << redBlackTree.colorFlipCount <<"\n\n"; 
    return 0;
}
