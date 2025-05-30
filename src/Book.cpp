#include "../include/Book.h"

Book::Book(const std::string& article, const std::string& author, const std::string& title,
           double price, const std::string& publisher, int stock)
        : Product(article, title, price, stock), author(author), publisher(publisher) {}

std::string Book::getCategory() const { return "Book"; }

std::string Book::getDetails() const {
    return "Author: " + author + ", Publisher: " + publisher;
}