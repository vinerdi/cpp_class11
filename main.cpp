#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

const int MAX_RECORDS = 20;
const int NAME_LENGTH = 10;
const int SURNAME_LENGTH = 20;
const int PHONE_LENGTH = 12;

struct Record {
    char name[NAME_LENGTH + 1];
    char surname[SURNAME_LENGTH + 1];
    char phone[PHONE_LENGTH + 1];
};

Record phoneBook[MAX_RECORDS];
int recordCount = 0;

void addRecord() {
    if (recordCount >= MAX_RECORDS) {
        cout << "Phone book is full." << endl;
        return;
    }

    Record newRecord;
    cout << "Enter name: ";
    cin >> newRecord.name;
    cout << "Enter surname: ";
    cin >> newRecord.surname;
    cout << "Enter phone number: ";
    cin >> newRecord.phone;

    for (int i = 0; i < recordCount; ++i) {
        if (strcmp(phoneBook[i].phone, newRecord.phone) == 0) {
            cout << "Record with this phone number already exists." << endl;
            return;
        }
    }

    phoneBook[recordCount++] = newRecord;
    cout << "Record added successfully." << endl;
}

void deleteRecord() {
    char phone[PHONE_LENGTH + 1];
    cout << "Enter phone number to delete: ";
    cin >> phone;

    for (int i = 0; i < recordCount; ++i) {
        if (strcmp(phoneBook[i].phone, phone) == 0) {
            for (int j = i; j < recordCount - 1; ++j) {
                phoneBook[j] = phoneBook[j + 1];
            }
            --recordCount;
            cout << "Record deleted successfully." << endl;
            return;
        }
    }
    cout << "Record not found." << endl;
}

void findRecord() {
    char surname[SURNAME_LENGTH + 1];
    cout << "Enter surname to find: ";
    cin >> surname;

    for (int i = 0; i < recordCount; ++i) {
        if (strcmp(phoneBook[i].surname, surname) == 0) {
            cout << "Name: " << phoneBook[i].name << ", Surname: " << phoneBook[i].surname << ", Phone: " << phoneBook[i].phone << endl;
            return;
        }
    }
    cout << "Record not found." << endl;
}

void showAllRecords() {
    if (recordCount == 0) {
        cout << "Phone book is empty." << endl;
        return;
    }

    for (int i = 0; i < recordCount; ++i) {
        cout << "Name: " << phoneBook[i].name << ", Surname: " << phoneBook[i].surname << ", Phone: " << phoneBook[i].phone << endl;
    }
}

void saveToFile() {
    ofstream outFile("phone.dat", ios::binary);
    if (!outFile) {
        cout << "Error opening file for writing." << endl;
        return;
    }
    outFile.write(reinterpret_cast<char*>(phoneBook), sizeof(phoneBook));
    outFile.write(reinterpret_cast<char*>(&recordCount), sizeof(recordCount));
    outFile.close();
    cout << "Records saved successfully." << endl;
}

void loadFromFile() {
    ifstream inFile("phone.dat", ios::binary);
    if (!inFile) {
        cout << "Error opening file for reading." << endl;
        return;
    }
    inFile.read(reinterpret_cast<char*>(phoneBook), sizeof(phoneBook));
    inFile.read(reinterpret_cast<char*>(&recordCount), sizeof(recordCount));
    inFile.close();
    cout << "Records loaded successfully." << endl;
}

int main() {
    int choice;
    do {
        cout << "1. Add record" << endl;
        cout << "2. Delete record" << endl;
        cout << "3. Find record" << endl;
        cout << "4. Show all records" << endl;
        cout << "5. Save records to file" << endl;
        cout << "6. Load records from file" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addRecord();
                break;
            case 2:
                deleteRecord();
                break;
            case 3:
                findRecord();
                break;
            case 4:
                showAllRecords();
                break;
            case 5:
                saveToFile();
                break;
            case 6:
                loadFromFile();
                break;
            case 7:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
        if (choice != 7) {
            cout << "Press any key to continue..." << endl;
            cin.ignore();
            cin.get();
        }
    } while (choice != 7);

    return 0;
}
