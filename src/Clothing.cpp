#include "../include/Clothing.h"

Clothing::Clothing(const std::string& article, const std::string& name, const std::string& size,
                   const std::string& color, double price, int stock)
        : Product(article, name, price, stock), size(size), color(color) {}

std::string Clothing::getCategory() const { return "Clothing"; }

std::string Clothing::getDetails() const {
    return "Size: " + size + ", Color: " + color;
}