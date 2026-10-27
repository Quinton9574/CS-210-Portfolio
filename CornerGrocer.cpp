// Corner Grocer - CS 210 Project Three
#include "GroceryTracker.h"

#include <exception>
#include <iostream>
#include <sstream>
#include <string>

int main() {
    GroceryTracker tracker;

    try {
        tracker.LoadPurchases("CS210_Project_Three_Input_File.txt");

        // Automatically back up the counts before displaying the menu.
        tracker.SaveBackup("frequency.dat");
    }
    catch (const std::exception& error) {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }

    std::string line;

    while (true) {
        std::cout << "\nCORNER GROCER\n"
            << "1. Find an item\n"
            << "2. Display all frequencies\n"
            << "3. Display histogram\n"
            << "4. Exit\n"
            << "Choose 1-4: ";

        if (!std::getline(std::cin, line)) {
            break;
        }

        // Reject invalid numbers and extra characters.
        std::istringstream menuInput(line);
        int choice = 0;
        std::string extra;

        if (!(menuInput >> choice) || (menuInput >> extra)
            || choice < 1 || choice > 4) {
            std::cout << "Invalid choice. Enter a whole number from 1 to 4.\n";
            continue;
        }

        switch (choice) {
        case 1: {
            std::cout << "Enter item (match spelling and capitalization): ";

            if (!std::getline(std::cin, line)) {
                return 0;
            }

            std::istringstream itemInput(line);
            std::string item;

            if (!(itemInput >> item) || (itemInput >> extra)) {
                std::cout << "Enter one item name.\n";
                break;
            }

            std::cout << item << ": "
                << tracker.GetFrequency(item) << '\n';
            break;
        }
        case 2:
            tracker.PrintFrequencies();
            break;

        case 3:
            tracker.PrintHistogram();
            break;

        case 4:
            std::cout << "Goodbye!\n";
            return 0;
        }
    }

    return 0;
}