# Gator-Library
GatorLibrary is a fictional library that needs a software system to efficiently manage its books, patrons, and borrowing operations.

The system should utilize a Red-Black tree data structure to ensure efficient management of the books. Implement a priority-queue mechanism using Binary Min-heaps as a data structure for managing book reservations in case a book is not currently available to be borrowed. Each book will have its own min-heap to keep track of book reservations made by the patrons.

Each node in the Red-Black tree will represent a book and will have the following structure:
● BookId // Integer ID
● BookName //Name of the book
● AuthorName //Name of the Author
● AvailabilityStatus //To indicate whether it is currently borrowed
● BorrowedBy //ID of the Patron who borrowed the book
● ReservationHeap: Implement Binary Min-heap for managing book reservations and waitlists for the book ordered by the patron’s priority which is an integer. (Priority 1 has precedence over Priority 2 and so on). Ties need be broken by considering the timestamp at which the reservation was made (first come first serve basis). Every node of the Min-heap should contain (patronID, priorityNumber, timeOfReservation)

The system should support the following operations:
1. PrintBook(bookID): Print information about a specific book identified by its unique bookID (e.g., title, author, availability status).
Note*: If not found, Print “Book <BookID> not found in the Library”
2. PrintBooks(bookID1, bookID2): Print information about all books with bookIDs in the range [bookID1, bookID2].
3. InsertBook(bookID, bookName, authorName, availabilityStatus, borrowedBy, reservationHeap): Add a new book to the library. BookID should be unique, and availability indicates whether the book is available for borrowing.
4. BorrowBook(patronID, bookID, patronPriority): Allow a patron to borrow a book that is available and update the status of the book. If a book is currently unavailable, create a reservation node in the heap as per the patron’s priority (patronPriority).
5. ReturnBook(patronID, bookID): Allow a patron to return a borrowed book. Update the book's status and assign the book to the patron with highest priority in the Reservation Heap. (if there’s a reservation).
6. DeleteBook(bookID): Delete the book from the library and notify the patrons in the reservation list that the book is no longer available to borrow.
7. FindClosestBook(targetID) : Find the book with an ID closest to the given ID (checking on both sides of the ID). Print all the details about the book. In case of ties, print both the books ordered by bookIDs.
8. ColorFlipCount(): GatorLibrary's Red-Black tree structure requires an analytics tool to monitor and analyze the frequency of color flips in the Red-Black tree. Track the occurrence of color changes in the Red-Black tree nodes during tree operations, such as insertion, deletion, and rotations.
