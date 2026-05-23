#include <string> //wasn't working with std::string, probabaly cuz i have to do this?

struct Movie {
    //must store the name and the rating, string and double respectively
    std::string name;
    double rating;

    //constructor
    Movie(std::string n, double r) : name(n), rating(r) {}

    //compare movies alphabetically with < operator
    bool operator<(const Movie& m) const { 
        return (*this).name < m.name;
    }

} ;