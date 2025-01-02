#include <iostream>

using namespace std;

void printUserTypeMenu();
bool pickUserType();

void printActionMenu();
void pickAction(bool isAdmin);

int main() {
    const bool isAdmin = pickUserType();

    pickAction(isAdmin);

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
        }

        cout << endl;
    }

    return choice == 2;
}

void printActionMenu() {
    cout << "1. Add movie" << endl;
    cout << "2. Search movie by title" << endl;
    cout << "3. Search movie by genre" << endl;
    cout << "4. View all movies" << endl;
    cout << "5. Redact movie" << endl;
    cout << "6. Delete movie" << endl;
    cout << "7. Rate movie" << endl;
    cout << "8. Sort/Filter movie by rating" << endl;
    cout << "9. Exit" << endl;
}

void pickAction(bool isAdmin) {
    int choice = 0;

    while (choice == 0) {
        printActionMenu();

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                //TODO: Add movie function
                break;
            case 2:
                //TODO: Search movie by title function
                break;
            case 3:
                //TODO: Search movie by genre function
                break;
            case 4:
                //TODO: View all movies function
                break;
            case 5:
                //TODO: Redact movie function
                break;
            case 6:
                //TODO: Delete movie function
                break;
            case 7:
                //TODO: Rate movie function
                break;
            case 8:
                //TODO: Sort/Filter movie by rating function
                break;
            case 9:
                break;
            default:
                cout << "Invalid choice." << endl;
        }

        cout << endl;

        if (choice != 9) {
            choice = 0;
        } else {
            cout << "Goodbye!" << endl;
            return;
        }
    }
}
