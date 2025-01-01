#include <iostream>

using namespace std;

void printUserTypeMenu();
bool pickUserType();

int main() {
    const bool isAdmin = pickUserType();

    return 0;
}

void printUserTypeMenu() {
    cout << "What type of user are you?" << endl;
    cout << "1. User" << endl;
    cout << "2. Admin" << endl;
}

bool pickUserType() {
    int choice = 0;

    while (choice == 0) {
        printUserTypeMenu();

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                choice = 1;
                break;
            case 2:
                choice = 2;
                break;
            default:
                cout << "Invalid choice." << endl;
                choice = 0;
                break;
        }

        cout << endl;
    }

    return choice == 2;
}