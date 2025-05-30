#ifndef MARKETPLACE_H
#define MARKETPLACE_H

#include "Product.h"
#include "Customer.h"
#include <vector>
#include <map>
#include <memory>

class Marketplace {
private:
    std::vector<std::unique_ptr<Product>> products;
    std::vector<Customer> customers;
    std::map<std::string, std::vector<std::pair<std::string, int>>> purchases;
    std::vector<std::string> waitingList;
    std::map<std::string, std::vector<std::pair<std::string, int>>> reservedItems;

    double discountThreshold;
    double discountPercentage;

public:
    Marketplace(double threshold, double percentage);

    void loadProducts(const std::string& filename);
    void loadCustomers(const std::string& filename);
    void loadPurchases(const std::string& filename);

    void processOrders();
    void analyzeRevenue();
    void printWaitingList();
    void printReservedItems();
    void sendReminders();
};

#endif // MARKETPLACE_H