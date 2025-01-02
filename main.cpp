#include <iostream>

using namespace std;

const char* MOVIE_FILE_PATH = "movies.txt";
const char* MOVIE_RATING_FILE_PATH = "ratings.txt";

const size_t MAX_TITLE_LENGTH = 50;
const size_t MAX_GENRE_LENGTH = 50;
const size_t MAX_DIRECTOR_LENGTH = 50;
const size_t MAX_ACTORS = 10;
const size_t MAX_ACTORS_LENGTH = 50;
const double DEFAULT_RATING = 5;

struct Movie {
    double rating = DEFAULT_RATING;
    short id = 0;
    short year{};
    char title[MAX_TITLE_LENGTH]{};
    char genre[MAX_GENRE_LENGTH]{};
    char director[MAX_DIRECTOR_LENGTH]{};
    char actors[MAX_ACTORS][MAX_ACTORS_LENGTH]{};
};

void printUserTypeMenu();
bool pickUserType();

void printActionMenu();
void pickAction(bool isAdmin);

void addMovie();
void writeMovieToFile(const Movie& movie);

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
                if (isAdmin) {
                    addMovie();
                } else {
                    cout << "You don't have permission to add movies." << endl;
                }
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

void addMovie() {
    Movie movie{};

    cout << "Enter movie title: ";
    cin.ignore();
    cin.getline(movie.title, MAX_TITLE_LENGTH);

    short year;
    cout << "Enter movie year: ";
    if (!(cin >> year)) {
        cout << "Year must be a number. Addition of movie was unsuccessful." << endl;
        cin.clear();
        cin.ignore(10000, '\n');
        return;
    }
    if (year < 1800 || year > 2025) {
        cout << "Invalid year. Addition of movie was unsuccessful." << endl;
        return;
    }
    movie.year = year;

    cout << "Enter movie genre: ";
    cin.ignore();
    cin.getline(movie.genre, MAX_GENRE_LENGTH);

    cout << "Enter movie director: ";
    cin.getline(movie.director, MAX_DIRECTOR_LENGTH);

    short actorsCount;
    cout << "Enter number of actors: ";
    if (!(cin >> actorsCount)) {
        cout << "Number of actors must be a number. Addition of movie was unsuccessful." << endl;
        cin.clear();
        cin.ignore(10000, '\n');
        return;
    }
    if (actorsCount < 1 || actorsCount > MAX_ACTORS) {
        cout << "Invalid number of actors. Addition of movie was unsuccessful." << endl;
        return;
    }

    cin.ignore();
    for (size_t i = 0; i < actorsCount; i++) {
        cout << "Enter actor " << i + 1 << ": ";
        cin.getline(movie.actors[i], MAX_ACTORS_LENGTH);
    }

    writeMovieToFile(movie);
}

void writeMovieToFile(const Movie& movie) {
    //TODO: Write movie to file
}
