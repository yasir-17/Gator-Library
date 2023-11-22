#include "RedBlackTree.h"
#include "BookNode.h"

// GatorLibrary Class
class GatorLibrary {
private:
    RedBlackTree redBlackTree;

    // Helper function to search for a book by ID
    BookNode* searchBookByID(int bookID);

    // Function to print information about a book node
    void PrintBookNode(BookNode& bookNode);

    // Function to print information about a reservation node
    void PrintReservationNode(const ReservationNode& reservationNode);


public:

    // Function to print information about a specific book
    void PrintBook(int bookID);

    // Function to print information about books in a range
    void PrintBooks(int bookID1, int bookID2);

    // Function to insert a new book to the library
    void InsertBook(int bookID, const string& bookName, const string& authorName, string availability);

    // Function to borrow a book
    void BorrowBook(int patronID, int bookID, int patronPriority);

    // Function to return a borrowed book
    void ReturnBook(int patronID, int bookID);

    // Function to delete a book from the library
    void DeleteBook(int bookID);

    // Function to find the book with ID closest to the given target ID
    void FindClosestBook(int targetID);

    // Function to track color flip count in the Red-Black tree
    int ColorFlipCount();

};