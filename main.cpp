#include <iostream>
#include <fstream>

using namespace std;

const char* MOVIE_FILE_PATH = "movies.txt";

const size_t MAX_TITLE_LENGTH = 50;
const size_t MAX_GENRE_LENGTH = 50;
const size_t MAX_DIRECTOR_LENGTH = 50;
const size_t MAX_ACTORS = 10;
const size_t MAX_ACTORS_LENGTH = 50;
const double DEFAULT_RATING = 5;

struct Movie {
    double rating = DEFAULT_RATING;
    short year = 0;
    short actorsCount = 0;
    char* title{};
    char* genre{};
    char* director{};
    char** actors{};
};

struct MovieList {
    size_t size = 0;
    size_t capacity = 8;
    Movie* movies = new Movie[capacity];
};

void initMovieStrings(Movie& movie);
void initMovieActors(Movie& movie);
void freeMovieMemory(const Movie& movie);
void resizeMovieList(MovieList& movieList);
void freeMovieListMemory(const MovieList& movieList);

void printUserTypeMenu();
bool pickUserType();

void printActionMenu();
void pickAction(bool isAdmin);

void addMovie();
void writeMovieInfoToFile(const Movie& movie, ofstream& movieFile);
void writeMovieToFile(const Movie& movie);

void getAllMovies(MovieList& movieList);
void printMovie(const Movie& movie);
void printAllMovies();

size_t myStrlen(const char* str);
bool areStringsEqual(const char* str1, const char* str2);
void searchMoviesByGenre();
void printAllMoviesByGenre(const char* genre);

bool isSubstring(const char* str, const char* substr);
void searchMoviesByTitle();
void printAllMoviesByTitle(const char* title);

void pickMovieToEdit();
void printEditMenu();
void editMovieTitle(Movie& movie);
void editMovieYear(Movie& movie);
void editMovieGenre(Movie& movie);
void editMovieDirector(Movie& movie);
void editMovieActors(Movie& movie);
void editMovieRating(Movie& movie);
void editMovie(Movie& movie);
void updateMovieFile(const MovieList& movieList);

void pickMovieToDelete();

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

void pickAction(const bool isAdmin) {
    int choice = 0;

    while (choice == 0) {
        printActionMenu();

        cout << "Enter your choice: ";
        cin >> choice;

        cout << endl;

        switch (choice) {
            case 1:
                if (isAdmin) {
                    addMovie();
                } else {
                    cout << "You don't have permission to add movies." << endl;
                }
                break;
            case 2:
                searchMoviesByTitle();
                break;
            case 3:
                searchMoviesByGenre();
                break;
            case 4:
                printAllMovies();
                break;
            case 5:
                if (isAdmin) {
                    pickMovieToEdit();
                } else {
                    cout << "You don't have permission to edit movies." << endl;
                }
                break;
            case 6:
                if (isAdmin) {
                    pickMovieToDelete();
                } else {
                    cout << "You don't have permission to delete movies." << endl;
                }
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

void initMovieStrings(Movie& movie) {
    movie.title = new char[MAX_TITLE_LENGTH];
    movie.genre = new char[MAX_GENRE_LENGTH];
    movie.director = new char[MAX_DIRECTOR_LENGTH];
}

void initMovieActors(Movie& movie) {
    movie.actors = new char*[movie.actorsCount];
    for (size_t i = 0; i < movie.actorsCount; i++) {
        movie.actors[i] = new char[MAX_ACTORS_LENGTH];
    }
}

void freeMovieMemory(const Movie &movie) {
    delete [] movie.title;
    delete [] movie.genre;
    delete [] movie.director;
    for (size_t i = 0; i < movie.actorsCount; i++) {
        delete [] movie.actors[i];
    }
    delete [] movie.actors;
}

void addMovie() {
    Movie movie{};
    initMovieStrings(movie);

    cout << "Enter movie title: ";
    cin.ignore();
    cin.getline(movie.title, MAX_TITLE_LENGTH);

    short year = 0;
    cout << "Enter movie year: ";
    if (!(cin >> year)) {
        cout << "Year must be a number. Addition of movie was unsuccessful." << endl;
        cin.clear();
        cin.ignore(10000, '\n');

        freeMovieMemory(movie);

        return;
    }
    if (year < 1800 || year > 2025) {
        cout << "Invalid year. Addition of movie was unsuccessful." << endl;

        freeMovieMemory(movie);

        return;
    }
    movie.year = year;

    cout << "Enter movie genre: ";
    cin.ignore();
    cin.getline(movie.genre, MAX_GENRE_LENGTH);

    cout << "Enter movie director: ";
    cin.getline(movie.director, MAX_DIRECTOR_LENGTH);

    cout << "Enter number of actors: ";
    if (!(cin >> movie.actorsCount)) {
        cout << "Number of actors must be a number. Addition of movie was unsuccessful." << endl;
        cin.clear();
        cin.ignore(10000, '\n');

        freeMovieMemory(movie);

        return;
    }
    if (movie.actorsCount < 1) {
        cout << "Number of actors must be positive. Addition of movie was unsuccessful." << endl;

        freeMovieMemory(movie);

        return;
    }

    initMovieActors(movie);

    cin.ignore();
    for (size_t i = 0; i < movie.actorsCount; i++) {
        cout << "Enter actor " << i + 1 << ": ";
        cin.getline(movie.actors[i], MAX_ACTORS_LENGTH);
    }

    writeMovieToFile(movie);
}

void writeMovieInfoToFile(const Movie& movie, ofstream& movieFile) {
    movieFile << movie.title << endl;
    movieFile << movie.year << endl;
    movieFile << movie.genre << endl;
    movieFile << movie.director << endl;
    movieFile << movie.actorsCount << endl;
    for (size_t i = 0; i < movie.actorsCount; i++) {
        movieFile << movie.actors[i];
        if (i != movie.actorsCount - 1) {
            movieFile << ";";
        } else {
            movieFile << endl;
        }
    }
    movieFile << movie.rating << endl;
}

void writeMovieToFile(const Movie& movie) {
    ofstream movieFile(MOVIE_FILE_PATH, ios::app);
    if (!movieFile.is_open()) {
        cout << "Failed to open file." << endl;
        freeMovieMemory(movie);
        return;
    }

    writeMovieInfoToFile(movie, movieFile);

    movieFile.close();

    freeMovieMemory(movie);
}

void resizeMovieList(MovieList& movieList) {
    Movie* movies = new Movie[movieList.capacity * 2];
    for (size_t i = 0; i < movieList.size; i++) {
        movies[i] = movieList.movies[i];
    }
    delete [] movieList.movies;
    movieList.movies = movies;
}

void freeMovieListMemory(const MovieList& movieList) {
    for (size_t i = 0; i < movieList.size; i++) {
        freeMovieMemory(movieList.movies[i]);
    }

    delete [] movieList.movies;
}

void getAllMovies(MovieList& movieList) {
    ifstream movieFile(MOVIE_FILE_PATH);
    if (!movieFile.is_open()) {
        cout << "Failed to open file." << endl;
        return;
    }

    while (movieFile.peek() != EOF) {
        if (movieList.size == movieList.capacity) {
            resizeMovieList(movieList);
        }

        Movie movie;
        initMovieStrings(movie);

        movieFile.getline(movie.title, MAX_TITLE_LENGTH);
        movieFile >> movie.year;
        movieFile.ignore();
        movieFile.getline(movie.genre, MAX_GENRE_LENGTH);
        movieFile.getline(movie.director, MAX_DIRECTOR_LENGTH);
        movieFile >> movie.actorsCount;
        movieFile.ignore();

        initMovieActors(movie);
        for (size_t i = 0; i < movie.actorsCount; i++) {
            const char separator = i == movie.actorsCount - 1 ? '\n' : ';';
            movieFile.getline(movie.actors[i], MAX_ACTORS_LENGTH, separator);
        }

        movieFile >> movie.rating;
        movieFile.ignore();

        movieList.movies[movieList.size] = movie;
        movieList.size++;
    }

    movieFile.close();
}

void printMovie(const Movie& movie) {
    cout << "Title: " << movie.title << endl;
    cout << "Year: " << movie.year << endl;
    cout << "Genre: " << movie.genre << endl;
    cout << "Director: " << movie.director << endl;
    cout << "Actors: ";
    for (size_t i = 0; i < movie.actorsCount; i++) {
        cout << movie.actors[i];
        if (i != movie.actorsCount - 1) {
            cout << ", ";
        } else {
            cout << endl;
        }
    }
    cout << "Rating: " << movie.rating << endl;
}

void printAllMovies() {
    MovieList movieList{};
    getAllMovies(movieList);

    for (size_t i = 0; i < movieList.size; i++) {
        cout << "Movie " << i + 1 << ":" << endl;
        printMovie(movieList.movies[i]);
        cout << endl;
    }

    freeMovieListMemory(movieList);
}

size_t myStrlen(const char* str) {
    if (str == nullptr) {
        return 0;
    }

    size_t length = 0;
    for (size_t i = 0; str[i] != '\0'; i++) {
        length++;
    }

    return length;
}

bool areStringsEqual(const char* str1, const char* str2) {
    if (str1 == nullptr || str2 == nullptr) {
        return false;
    }

    const size_t len1 = myStrlen(str1);
    if (len1 != myStrlen(str2)) {
        return false;
    }

    for (size_t i = 0; i < len1; i++) {
        if (str1[i] != str2[i]) {
            return false;
        }
    }

    return true;
}

void searchMoviesByGenre() {
    cout << "Enter genre: ";
    char* genre = new char[MAX_GENRE_LENGTH];
    cin.ignore();
    cin.getline(genre, MAX_GENRE_LENGTH);

    cout << endl;
    printAllMoviesByGenre(genre);

    delete [] genre;
}

void printAllMoviesByGenre(const char *genre) {
    if (genre == nullptr) {
        cout << "Invalid genre." << endl;
        return;
    }

    MovieList movieList{};
    getAllMovies(movieList);

    unsigned short foundMoviesCount = 0;

    for (size_t i = 0; i < movieList.size; i++) {
        if (areStringsEqual(movieList.movies[i].genre, genre)) {
            cout << "Result " << ++foundMoviesCount << ":" << endl;
            printMovie(movieList.movies[i]);
            cout << endl;
        }
    }

    if (foundMoviesCount == 0) {
        cout << "No movies found with genre \"" << genre << "\"." << endl;
    }
}

bool isSubstring(const char* str, const char* substr) {
    if (str == nullptr || substr == nullptr) {
        return false;
    }

    const size_t len = myStrlen(str), subLen = myStrlen(substr);
    if (subLen > len) {
        return false;
    }

    for (size_t i = 0; i <= len - subLen; i++) {
        bool isSubstring = true;
        for (size_t j = 0; j < subLen; j++) {
            if (str[i + j] != substr[j]) {
                isSubstring = false;
                break;
            }
        }

        if (isSubstring) {
            return true;
        }
    }

    return false;
}

void searchMoviesByTitle() {
    cout << "Enter title: ";
    char* title = new char[MAX_TITLE_LENGTH];
    cin.ignore();
    cin.getline(title, MAX_TITLE_LENGTH);

    cout << endl;
    printAllMoviesByTitle(title);

    delete [] title;
}


void printAllMoviesByTitle(const char* title) {
    if (title == nullptr) {
        cout << "Invalid title." << endl;
        return;
    }

    MovieList movieList{};
    getAllMovies(movieList);

    unsigned short foundMoviesCount = 0;

    for (size_t i = 0; i < movieList.size; i++) {
        if (isSubstring(movieList.movies[i].title, title)) {
            cout << "Result " << ++foundMoviesCount << ":" << endl;
            printMovie(movieList.movies[i]);
            cout << endl;
        }
    }

    if (foundMoviesCount == 0) {
        cout << "No movies found with title containing \"" << title << "\"." << endl;
    }
}

void pickMovieToEdit() {
    printAllMovies();

    MovieList movieList{};
    getAllMovies(movieList);

    cout << "Enter the number of the movie you want to edit: ";
    size_t movieNumber = 0;
    if (!(cin >> movieNumber)) {
        cout << "Movie number must be a number." << endl;
        cin.clear();
        cin.ignore(10000, '\n');

        freeMovieListMemory(movieList);

        return;
    }

    if (movieNumber < 1 || movieNumber > movieList.size) {
        cout << "Invalid movie number." << endl;

        freeMovieListMemory(movieList);

        return;
    }

    cout << endl;
    editMovie(movieList.movies[movieNumber - 1]);

    updateMovieFile(movieList);

    freeMovieListMemory(movieList);
}

void printEditMenu() {
    cout << "What do you want to edit?" << endl;
    cout << "1. Title" << endl;
    cout << "2. Year" << endl;
    cout << "3. Genre" << endl;
    cout << "4. Director" << endl;
    cout << "5. Actors" << endl;
    cout << "6. Rating" << endl;
    cout << "7. Done" << endl;
}

void editMovieTitle(Movie& movie) {
    cout << "Enter new title: ";

    delete [] movie.title;
    movie.title = new char[MAX_TITLE_LENGTH];
    cin.ignore();
    cin.getline(movie.title, MAX_TITLE_LENGTH);
}

void editMovieYear(Movie& movie) {
    int year = 0;

    cout << "Enter new year: ";
    if (!(cin >> year)) {
        cout << "Year must be a number." << endl;
        cin.clear();
        cin.ignore(10000, '\n');
        return;
    }

    if (year < 1800 || year > 2025) {
        cout << "Invalid year." << endl;
        return;
    }

    movie.year = year;
}

void editMovieGenre(Movie& movie) {
    cout << "Enter new genre: ";

    delete [] movie.genre;
    movie.genre = new char[MAX_GENRE_LENGTH];
    cin.ignore();
    cin.getline(movie.genre, MAX_GENRE_LENGTH);
}

void editMovieDirector(Movie& movie) {
    cout << "Enter new director: ";

    delete [] movie.director;
    movie.director = new char[MAX_DIRECTOR_LENGTH];
    cin.ignore();
    cin.getline(movie.director, MAX_DIRECTOR_LENGTH);
}

void editMovieActors(Movie& movie) {
    cout << "Enter new number of actors: ";
    if (!(cin >> movie.actorsCount)) {
        cout << "Number of actors must be a number." << endl;
        cin.clear();
        cin.ignore(10000, '\n');
        return;
    }

    for (size_t i = 0; i < movie.actorsCount; i++) {
        delete [] movie.actors[i];
    }
    delete [] movie.actors;

    movie.actors = new char*[movie.actorsCount];

    cin.ignore();
    for (size_t i = 0; i < movie.actorsCount; i++) {
        movie.actors[i] = new char[MAX_ACTORS_LENGTH];
        cout << "Enter actor " << i + 1 << ": ";
        cin.getline(movie.actors[i], MAX_ACTORS_LENGTH);
    }
}

void editMovieRating(Movie& movie) {
    double rating = 0;

    cout << "Enter new rating: ";
    if (!(cin >> rating)) {
        cout << "Rating must be a number." << endl;
        cin.clear();
        cin.ignore(10000, '\n');
        return;
    }

    if (rating < 0 || rating > 10) {
        cout << "Rating must be between 0 and 10." << endl;
        return;
    }

    movie.rating = rating;
}

void editMovie(Movie& movie) {
    int choice = 0;

    while (choice == 0) {
        cout << "Current movie information: " << endl;
        printMovie(movie);
        cout << endl;
        printEditMenu();

        cout << "Enter your choice: ";
        cin >> choice;

        cout << endl;

        switch (choice) {
            case 1:
                editMovieTitle(movie);
                break;
            case 2:
                editMovieYear(movie);
                break;
            case 3:
                editMovieGenre(movie);
                break;
            case 4:
                editMovieDirector(movie);
                break;
            case 5:
                editMovieActors(movie);
                break;
            case 6:
                editMovieRating(movie);
                break;
            case 7:
                break;
            default:
                cout << "Invalid choice." << endl;
        }

        if (choice != 7) {
            choice = 0;
            cout << endl;
        } else {
            cout << "Movie editing complete." << endl;
            return;
        }
    }
}

void updateMovieFile(const MovieList &movieList) {
    ofstream movieFile(MOVIE_FILE_PATH);

    if (!movieFile.is_open()) {
        cout << "Failed to open file." << endl;
        return;
    }

    for (size_t i = 0; i < movieList.size; i++) {
        writeMovieInfoToFile(movieList.movies[i], movieFile);
    }

    movieFile.close();
}

void pickMovieToDelete() {
    printAllMovies();

    MovieList movieList{};
    getAllMovies(movieList);

    cout << "Enter the number of the movie you want to delete: ";
    size_t movieNumber = 0;
    if (!(cin >> movieNumber)) {
        cout << "Movie number must be a number." << endl;
        cin.clear();
        cin.ignore(10000, '\n');

        freeMovieListMemory(movieList);

        return;
    }

    if (movieNumber < 1 || movieNumber > movieList.size) {
        cout << "Invalid movie number." << endl;

        freeMovieListMemory(movieList);

        return;
    }

    cout << endl;

    for (size_t i = movieNumber - 1; i < movieList.size - 1; i++) {
        movieList.movies[i] = movieList.movies[i + 1];
    }
    freeMovieMemory(movieList.movies[movieList.size - 1]);
    movieList.size--;

    updateMovieFile(movieList);

    freeMovieListMemory(movieList);
}
