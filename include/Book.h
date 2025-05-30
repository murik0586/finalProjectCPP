#ifndef BOOK_H
#define BOOK_H

#include "Product.h"

class Book : public Product {
private:
    std::string author;
    std::string publisher;

public:
    Book(const std::string& article, const std::string& author, const std::string& title,
         double price, const std::string& publisher, int stock);

    [[nodiscard]] std::string getCategory() const override;
    [[nodiscard]] std::string getDetails() const override;
};

#endif // BOOK_H