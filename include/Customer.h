#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <vector>

class Customer {
private:
    std::string fullName;
    std::string cardNumber;
    double balance;

public:
    Customer(const std::string& fullName, const std::string& cardNumber, double balance);

    [[nodiscard]] std::string getFullName() const;
    [[nodiscard]] std::string getCardNumber() const;
    double getBalance() const;

    void setBalance(double newBalance);
};

#endif // CUSTOMER_H