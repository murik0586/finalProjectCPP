#include "../include/Product.h"

Product::Product(const std::string& article, const std::string& name, double price, int stock)
        : article(article), name(name), price(price), stock(stock) {}

std::string Product::getArticle() const { return article; }
std::string Product::getName() const { return name; }
double Product::getPrice() const { return price; }
int Product::getStock() const { return stock; }
void Product::setStock(int newStock) { stock = newStock; }