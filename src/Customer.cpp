#include "../include/Customer.h"

Customer::Customer(const std::string& fullName, const std::string& cardNumber, double balance)
        : fullName(fullName), cardNumber(cardNumber), balance(balance) {}

std::string Customer::getFullName() const { return fullName; }
std::string Customer::getCardNumber() const { return cardNumber; }
double Customer::getBalance() const { return balance; }
void Customer::setBalance(double newBalance) { balance = newBalance; }