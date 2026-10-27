#include "GroceryTracker.h"

#include <fstream>
#include <iostream>
#include <stdexcept>

// Read each purchase and count how often each item appears.
void GroceryTracker::LoadPurchases(const std::string& filename) {
    std::ifstream inputFile(filename);

    if (!inputFile) {
        throw std::runtime_error("Cannot open input file: " + filename);
    }

    std::map<std::string, int> newFrequencies;
    std::string item;

    while (inputFile >> item) {
        ++newFrequencies[item];
    }

    if (inputFile.bad() || (inputFile.fail() && !inputFile.eof())) {
        throw std::runtime_error("Failed while reading input file.");
    }

    itemFrequencies.swap(newFrequencies);
}

// Save all counts automatically for backup purposes.
void GroceryTracker::SaveBackup(const std::string& filename) const {
    std::ofstream outputFile(filename);

    if (!outputFile) {
        throw std::runtime_error("Cannot create backup file: " + filename);
    }

    for (const auto& entry : itemFrequencies) {
        outputFile << entry.first << ' ' << entry.second << '\n';
    }

    outputFile.close();

    if (!outputFile) {
        throw std::runtime_error("Failed while writing backup file.");
    }
}

// Return zero when the requested item is not in the map.
int GroceryTracker::GetFrequency(const std::string& item) const {
    const auto found = itemFrequencies.find(item);

    return found == itemFrequencies.end() ? 0 : found->second;
}

// Display each item with its numeric purchase count.
void GroceryTracker::PrintFrequencies() const {
    std::cout << "\nItem frequencies\n";

    for (const auto& entry : itemFrequencies) {
        std::cout << entry.first << ' ' << entry.second << '\n';
    }
}

// Display one asterisk for each purchase.
void GroceryTracker::PrintHistogram() const {
    std::cout << "\nPurchase histogram\n";

    for (const auto& entry : itemFrequencies) {
        std::cout << entry.first << ' '
            << std::string(entry.second, '*') << '\n';
    }
}