#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include "GatorLibrary.h"

using namespace std;

int main(int argc, char* argv[]) {
    GatorLibrary library;  // instance of Library class

    // Open the input file
    const char* inputFileName = argv[1];
    ifstream inputFile(inputFileName);

    // Check if the file is open
    if (!inputFile.is_open()) {
        cout << "Error opening input file." << endl;
        return 1;
    }

    // Create an output file stream with the desired output file name
    string outputFileName = string(inputFileName).substr(0, string(inputFileName).length() - 4) + "_output_file.txt";
    ofstream outputFile(outputFileName);

    // Redirect cout to the output file
    streambuf* coutBuffer = cout.rdbuf();
    cout.rdbuf(outputFile.rdbuf());

    string line;

    // while there is input
    while (getline(inputFile, line)) {

        istringstream iss(line);
        
        string command;
        getline(iss, command, '(');

        if (command == "InsertBook") {
            int id;
            string title, author, available;
            char discard; 

            iss >> id >> discard >> quoted(title) >> discard >> quoted(author) >> discard >> quoted(available) >> discard;

            library.InsertBook(id, title, author, available);  // Insert book into library

        } else if (command == "PrintBook") {
            int id;
            char discard;

            iss >> id >> discard;

            library.PrintBook(id);  // print book
            
        } else if (command == "PrintBooks") {
            int id1, id2;
            char discard;

            iss >> id1 >> discard >> id2 >> discard;

            library.PrintBooks(id1, id2); // Print books

        } else if (command == "BorrowBook") {
            int patronId, bookId, patronPriority;
            char discard;

            iss >> patronId >> discard >> bookId >> discard >> patronPriority >> discard;

            library.BorrowBook(patronId, bookId, patronPriority); //  Borrow Book

        } else if (command == "ReturnBook") {
            int patronId, bookID;
            char discard;

            iss >> patronId >> discard >> bookID >> discard;

            library.ReturnBook(patronId, bookID); // Return Book

        } else if (command == "FindClosestBook") {
            int targetId;
            char discard;

            iss >> targetId >> discard;

            library.FindClosestBook(targetId); // Find closest book to target

        } else if (command == "DeleteBook") {
            int bookId;
            char discard;

            iss >> bookId >> discard;

            library.DeleteBook(bookId); // Delete book

        } else if (command == "ColorFlipCount") {

            library.ColorFlipCount(); // get color flip count

        } else if (command == "Quit") {

            cout << "Program Terminated!!" << endl;
            break;
            
        } else {
            cout << "Unknown Command!!";
        }
    }
        
    //Restore cout to the original buffer
    cout.rdbuf(coutBuffer);

    inputFile.close();
    outputFile.close();

    return 0;
}