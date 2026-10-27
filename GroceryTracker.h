#ifndef GROCERY_TRACKER_H
#define GROCERY_TRACKER_H

#include <map>
#include <string>

// Stores purchase counts and provides item-tracking operations.
class GroceryTracker {
public:
    void LoadPurchases(const std::string& filename);
    void SaveBackup(const std::string& filename) const;
    int GetFrequency(const std::string& item) const;
    void PrintFrequencies() const;
    void PrintHistogram() const;

private:
    std::map<std::string, int> itemFrequencies;
};

#endif