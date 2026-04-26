#include <iostream>
#include <fstream>
#include <map>
#include <string>
using namespace std;

// Class to track grocery item frequencies
class GroceryTracker {
private:
    map<string, int> itemFrequency;

public:
    void loadData(const string& filename) {
        ifstream inFile(filename);
        string item;

        if (!inFile.is_open()) {
            cout << "Error: Could not open file " << filename << endl;
            return;
        }

        while (inFile >> item) {
            itemFrequency[item]++;
        }

        inFile.close();
    }

    void createBackupFile() {
        ofstream outFile("frequency.dat");

        for (const auto& pair : itemFrequency) {
            outFile << pair.first << " " << pair.second << endl;
        }

        outFile.close();
    }

    void searchItem() {
        string itemName;
        cout << "Enter item to search: ";
        cin >> itemName;

        if (itemFrequency.count(itemName) > 0) {
            cout << itemName << " was purchased " << itemFrequency[itemName] << " time(s)." << endl;
        }
        else {
            cout << itemName << " was not found." << endl;
        }
    }

    void printAllFrequencies() {
        for (const auto& pair : itemFrequency) {
            cout << pair.first << " " << pair.second << endl;
        }
    }

    void printHistogram() {
        for (const auto& pair : itemFrequency) {
            cout << pair.first << " ";
            for (int i = 0; i < pair.second; i++) {
                cout << "*";
            }
            cout << endl;
        }
    }
};

void displayMenu() {
    cout << "\nCorner Grocer Menu" << endl;
    cout << "1. Search for a specific item" << endl;
    cout << "2. Display all item frequencies" << endl;
    cout << "3. Display histogram" << endl;
    cout << "4. Exit" << endl;
    cout << "Enter your choice: ";
}

int main() {
    GroceryTracker tracker;
    int choice;

    tracker.loadData("CS210_Project_Three_Input_File.txt");
    tracker.createBackupFile();

    do {
        displayMenu();
        cin >> choice;

        while (cin.fail() || choice < 1 || choice > 4) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Enter 1?4: ";
            cin >> choice;
        }

        switch (choice) {
        case 1:
            tracker.searchItem();
            break;
        case 2:
            tracker.printAllFrequencies();
            break;
        case 3:
            tracker.printHistogram();
            break;
        case 4:
            cout << "Exiting program." << endl;
            break;
        }
    } while (choice != 4);

    return 0;
}