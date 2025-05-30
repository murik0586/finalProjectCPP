#ifndef ELECTRONICS_H
#define ELECTRONICS_H

#include "Product.h"

class Electronics : public Product {
private:
    std::string model;
    std::string manufacturer;

public:
    Electronics(const std::string& article, const std::string& name, const std::string& model,
                const std::string& manufacturer, double price, int stock);

    [[nodiscard]] std::string getCategory() const override;
    [[nodiscard]] std::string getDetails() const override;
};

#endif // ELECTRONICS_H