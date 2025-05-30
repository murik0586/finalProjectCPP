#ifndef CLOTHING_H
#define CLOTHING_H

#include "Product.h"

class Clothing : public Product {
private:
    std::string size;
    std::string color;

public:
    Clothing(const std::string& article, const std::string& name, const std::string& size,
             const std::string& color, double price, int stock);

    [[nodiscard]] std::string getCategory() const override;
    [[nodiscard]] std::string getDetails() const override;
};

#endif // CLOTHING_H