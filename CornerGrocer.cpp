/*
* Jasmine Harris
* June 12, 2026
* Corner Grocer
* CS-210
*/

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

class CornerGrocer {
private:
    map<string, int> itemFrequency;

public:
    // Reads item names from the input file and counts each item
    void LoadItemsFromFile(const string& fileName) {
        ifstream inputFile(fileName);
        string itemName;

        if (!inputFile.is_open()) {
            cout << "Error: Could not open " << fileName << endl;
            return;
        }

        while (inputFile >> itemName) {
            itemFrequency[itemName]++;
        }

        inputFile.close();
    }

    // Creates the required backup file named frequency.dat
    void CreateBackupFile(const string& fileName) {
        ofstream outputFile(fileName);

        if (!outputFile.is_open()) {
            cout << "Error: Could not create " << fileName << endl;
            return;
        }

        for (const auto& item : itemFrequency) {
            outputFile << item.first << " " << item.second << endl;
        }

        outputFile.close();
    }

    // Returns the number of times one item appears
    int GetItemFrequency(const string& itemName) const {
        auto item = itemFrequency.find(itemName);

        if (item != itemFrequency.end()) {
            return item->second;
        }

        return 0;
    }

    // Prints every item and its frequency
    void PrintAllFrequencies() const {
        for (const auto& item : itemFrequency) {
            cout << left << setw(15) << item.first << item.second << endl;
        }
    }

    // Prints every item as a histogram using asterisks
    void PrintHistogram() const {
        for (const auto& item : itemFrequency) {
            cout << left << setw(15) << item.first;

            for (int i = 0; i < item.second; ++i) {
                cout << "*";
            }

            cout << endl;
        }
    }
};

int main() {
    CornerGrocer grocer;
    int menuChoice = 0;
    string searchItem;

    grocer.LoadItemsFromFile("CS210_Project_Three_Input_File.txt");
    grocer.CreateBackupFile("frequency.dat");

    while (menuChoice != 4) {
        cout << "\n========== Corner Grocer Menu ==========" << endl;
        cout << "1. Search for an item" << endl;
        cout << "2. Display all item frequencies" << endl;
        cout << "3. Display histogram" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";

        cin >> menuChoice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number from 1 to 4." << endl;
            continue;
        }

        switch (menuChoice) {
        case 1:
            cout << "Enter the item name: ";
            cin >> searchItem;

            cout << searchItem << " was purchased "
                << grocer.GetItemFrequency(searchItem)
                << " time(s)." << endl;
            break;

        case 2:
            cout << "\nItem Frequency List" << endl;
            cout << "-------------------" << endl;
            grocer.PrintAllFrequencies();
            break;

        case 3:
            cout << "\nItem Frequency Histogram" << endl;
            cout << "------------------------" << endl;
            grocer.PrintHistogram();
            break;

        case 4:
            cout << "Thank you for using the Corner Grocer program." << endl;
            break;

        default:
            cout << "Invalid choice. Please enter a number from 1 to 4." << endl;
            break;
        }
    }

    return 0;
}
