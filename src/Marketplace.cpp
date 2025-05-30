#include "../include/Marketplace.h"
#include "../include/Clothing.h"
#include "../include/Book.h"
#include "../include/Electronics.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>

Marketplace::Marketplace(double threshold, double percentage)
        : discountThreshold(threshold), discountPercentage(percentage) {}

void Marketplace::loadProducts(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening products file!" << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string category, article, name;
        std::string detail1, detail2;
        std::string priceStr, stockStr;

        // Сначала читаем первые три поля
        std::getline(iss, category, ',');
        std::getline(iss, article, ',');
        std::getline(iss, name, ',');

        if (category == "Clothing" || category == "Electronics") {
            // Для одежды и электроники - читаем detail1, detail2, price и stock как строки
            std::getline(iss, detail1, ',');
            std::getline(iss, detail2, ',');
            std::getline(iss, priceStr, ',');
            std::getline(iss, stockStr, ',');

            double price = std::stod(priceStr);
            int stock = std::stoi(stockStr);

            if (category == "Clothing") {
                products.push_back(std::make_unique<Clothing>(article, name, detail1, detail2, price, stock));
            } else { // Electronics
                products.push_back(std::make_unique<Electronics>(article, name, detail1, detail2, price, stock));
            }

        } else if (category == "Book") {
            // Для книги читаем author, price, publisher, stock
            std::string author, publisher;
            std::getline(iss, author, ',');
            std::getline(iss, priceStr, ',');
            std::getline(iss, publisher, ',');
            std::getline(iss, stockStr, ',');

            double price = std::stod(priceStr);
            int stock = std::stoi(stockStr);

            products.push_back(std::make_unique<Book>(article, author, name, price, publisher, stock));
        }
    }
}


void Marketplace::loadCustomers(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening customers file!" << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string fullName, cardNumber;
        double balance;

        std::getline(iss, fullName, ',');
        std::getline(iss, cardNumber, ',');
        iss >> balance;

        customers.emplace_back(fullName, cardNumber, balance);
    }
}

void Marketplace::loadPurchases(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening purchases file!" << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string orderId, cardNumber, article;
        int quantity;

        std::getline(iss, orderId, ',');
        std::getline(iss, cardNumber, ',');
        std::getline(iss, article, ',');
        iss >> quantity;

        purchases[cardNumber].emplace_back(article, quantity);
    }
}

void Marketplace::processOrders() {
    for (auto& customer : customers) {
        auto it = purchases.find(customer.getCardNumber());
        if (it == purchases.end()) continue;

        double total = 0;
        std::vector<std::pair<std::string, int>> validItems;

        for (auto& item : it->second) {
            auto productIt = std::find_if(products.begin(), products.end(),
                                          [&item](const std::unique_ptr<Product>& p) { return p->getArticle() == item.first; });

            if (productIt != products.end() && (*productIt)->getStock() >= item.second) {
                total += (*productIt)->getPrice() * item.second;
                validItems.push_back(item);
            }
        }

        if (total > discountThreshold) {
            total *= (1 - discountPercentage / 100);
        }

        if (total <= customer.getBalance()) {
            for (auto& item : validItems) {
                auto productIt = std::find_if(products.begin(), products.end(),
                                              [&item](const std::unique_ptr<Product>& p) { return p->getArticle() == item.first; });

                (*productIt)->setStock((*productIt)->getStock() - item.second);
            }
            customer.setBalance(customer.getBalance() - total);
        } else {
            waitingList.push_back(customer.getCardNumber());
            for (auto& item : validItems) {
                reservedItems[customer.getCardNumber()].push_back(item);
            }
        }
    }
}

void Marketplace::analyzeRevenue() {
    std::map<std::string, double> revenueByCategory;
    for (const auto& product : products) {
        revenueByCategory[product->getCategory()] += product->getPrice() * (product->getStock());
    }

    for (const auto& entry : revenueByCategory) {
        std::cout << entry.first << ": " << entry.second << std::endl;
    }
}

void Marketplace::printWaitingList() {
    for (const auto& cardNumber : waitingList) {
        auto customerIt = std::find_if(customers.begin(), customers.end(),
                                       [&cardNumber](const Customer& c) { return c.getCardNumber() == cardNumber; });

        if (customerIt != customers.end()) {
            std::cout << customerIt->getFullName() << " (" << cardNumber << ")" << std::endl;
        }
    }
}

void Marketplace::printReservedItems() {
    for (const auto& entry : reservedItems) {
        std::cout << "Customer: " << entry.first << std::endl;
        for (const auto& item : entry.second) {
            std::cout << "  Article: " << item.first << ", Quantity: " << item.second << std::endl;
        }
    }
}

void Marketplace::sendReminders() {
    for (const auto& cardNumber : waitingList) {
        auto customerIt = std::find_if(customers.begin(), customers.end(),
                                       [&cardNumber](const Customer& c) { return c.getCardNumber() == cardNumber; });

        if (customerIt != customers.end()) {
            std::cout << "Reminder for " << customerIt->getFullName() << ":" << std::endl;
            std::cout << "  Your order is still pending. Please complete the payment." << std::endl;
        }
    }
}