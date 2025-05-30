#include "Marketplace.h"
#include <iostream>
#include <filesystem>

int main() {

    std::cout << "Current path: " << std::filesystem::current_path() << std::endl;

    double threshold, percentage;
    std::cout << "Enter discount threshold: ";
    std::cin >> threshold;
    std::cout << "Enter discount percentage: ";
    std::cin >> percentage;

    Marketplace marketplace(threshold, percentage);

    marketplace.loadProducts("data/Products.csv");
    marketplace.loadCustomers("data/Customers.csv");
    marketplace.loadPurchases("data/Purchases.csv");

    marketplace.processOrders();
    marketplace.analyzeRevenue();

    std::cout << "\nWaiting List:" << std::endl;
    marketplace.printWaitingList();

    std::cout << "\nReserved Items:" << std::endl;
    marketplace.printReservedItems();

    std::cout << "\nSending Reminders:" << std::endl;
    marketplace.sendReminders();

    return 0;
}