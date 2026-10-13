#include <sstream>
#include <algorithm>

#include "book.h"

using namespace std;

// Default constructor
Book::Book() : title(""), author(""), isbn(""), isAvailable(true), borrowerId("") {}

// Parameterized constructor
Book::Book(const string& title, const string& author, const string& isbn)
    : title(title), author(author), isbn(isbn), isAvailable(true), borrowerId("") {}

// Getters
string Book::getTitle() const { return title; }
string Book::getAuthor() const { return author; }
string Book::getISBN() const { return isbn; }
bool Book::getAvailability() const { return isAvailable; }
string Book::getBorrowerId() const { return borrowerId; }

// Setters
void Book::setTitle(const string& title) { this->title = title; }
void Book::setAuthor(const string& author) { this->author = author; }
void Book::setISBN(const string& isbn) { this->isbn = isbn; }
void Book::setAvailability(bool available) { isAvailable = available; }
void Book::setBorrowerId(const string& id) { borrowerId = id; }

// Return a book
void Book::returnBook() {
    isAvailable = true;
    borrowerId = "";
}

// Display book information
string Book::toString() const {
    string result = "Titre : " + title +
                    "\nAuteur : " + author +
                    "\nISBN : " + isbn +
                    "\nStatut : ";

    if (isAvailable) {
        result += "Disponible";
    } else {
        result += "Emprunté par " + borrowerId;
    }
    return result;
}

// Check out the book to a user
void Book::checkOut(const string& borrowerId) {
    isAvailable = false;
    this->borrowerId = borrowerId;
}

// Format for file storage
string Book::toFileFormat() const {
    string result = title + "|" + author + "|" + isbn + "|";
    result += (isAvailable ? "1" : "0");
    result += "|" + borrowerId;
    return result;
}

// Parse from file format
void Book::fromFileFormat(const string& line) {
    string cleanLine = line;
    if (!cleanLine.empty() && cleanLine.back() == '\r') {
        cleanLine.pop_back();
    }

    stringstream ss(cleanLine);

    getline(ss, title, '|');
    getline(ss, author, '|');
    getline(ss, isbn, '|');

    string availableStr;
    getline(ss, availableStr, '|');
    isAvailable = (availableStr == "1");

    getline(ss, borrowerId, '|');
}