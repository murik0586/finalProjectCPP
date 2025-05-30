#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <vector>

class Product {
protected:
    std::string article;
    std::string name;
    double price;
    int stock;

public:
    Product(const std::string& article, const std::string& name, double price, int stock);
    virtual ~Product() = default;

    std::string getArticle() const;
    std::string getName() const;
    double getPrice() const;
    int getStock() const;

    void setStock(int newStock);

    virtual std::string getCategory() const = 0;
    virtual std::string getDetails() const = 0;
};

#endif // PRODUCT_H