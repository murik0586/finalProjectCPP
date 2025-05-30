#include "../include/Electronics.h"

Electronics::Electronics(const std::string& article, const std::string& name, const std::string& model,
                         const std::string& manufacturer, double price, int stock)
        : Product(article, name, price, stock), model(model), manufacturer(manufacturer) {}

std::string Electronics::getCategory() const { return "Electronics"; }

std::string Electronics::getDetails() const {
    return "Model: " + model + ", Manufacturer: " + manufacturer;
}
