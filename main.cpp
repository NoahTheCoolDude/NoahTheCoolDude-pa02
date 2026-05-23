// Winter'24
// Instructor: Diba Mirza
// Student name: Noah Rudemran
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include <cstring>
#include <algorithm>
#include <limits.h>
#include <iomanip>
#include <set>
#include <queue>
#include <sstream>
using namespace std;

#include "utilities.h"
#include "movies.h"

bool parseLine(string &line, string &movieName, double &movieRating);

int main(int argc, char** argv){
    if (argc < 2){
        cerr << "Not enough arguments provided (need at least 1 argument)." << endl;
        cerr << "Usage: " << argv[ 0 ] << " moviesFilename prefixFilename " << endl;
        exit(1);
    }

    ifstream movieFile (argv[1]);
 
    if (movieFile.fail()){
        cerr << "Could not open file " << argv[1];
        exit(1);
    }
  
    // Create an object of a STL data-structure to store all the movies
    //using vector because that just makes sense, a vector of Movies! then we can sort later
    vector<Movie> movies;

    string line, movieName;
    double movieRating;
    // Read each file and store the name and rating
    while (getline (movieFile, line) && parseLine(line, movieName, movieRating)){
            // Use std::string movieName and double movieRating
            // to construct your Movie objects
            // cout << movieName << " has rating " << movieRating << endl;
            // insert elements into your data structure

            // cout << movieName << " has rating " << movieRating << endl;

            //insert into vector of movies
            Movie currMovie(movieName, movieRating);
            movies.push_back(currMovie); //add to end of the datatype
    }

    movieFile.close();

    if (argc == 2){
            //print all the movies in ascending alphabetical order of movie names
            
            //the plan here is to order the vector alphabetically.... hmm....
            //.sort(v.begin, v.end()) works on a vector by using the < operator to compare
            // which i just defined in the movies.h struct, so let's try sorting and printing

            sort(movies.begin(), movies.end());

            //claude said this is the way to fix the decimal places correctly using <iomanip>
            cout << fixed << setprecision(1);

            for (auto v : movies) {
                cout << v.name << ", " << v.rating << endl;
            }

            return 0;
    }

    ifstream prefixFile (argv[2]);

    if (prefixFile.fail()) {
        cerr << "Could not open file " << argv[2];
        exit(1);
    }

    vector<string> prefixes;
    while (getline (prefixFile, line)) {
        if (!line.empty()) {
            prefixes.push_back(line);
        }
    }

    //  For each prefix,
    //  Find all movies that have that prefix and store them in an appropriate data structure
    //  If no movie with that prefix exists print the following message
    // cout << "No movies found with prefix "<<"<replace with prefix>" << endl;

    vector<string> bestPrefixes;
    vector<Movie> bests; //to store the top ranking lines by prefix

    //do iterators by reference as to not make a new copy everytime, faster for longer csvs 
    for (auto& prefix : prefixes) {
        vector<Movie> matches;
        for (auto& m : movies) {
            if (m.name.substr(0, prefix.size()) == prefix) { //if the start matches the prefix we are on...
                matches.push_back(m);
            }
        }

        if (matches.empty()) {
            cout << "No movies found with prefix "<< prefix << endl;
        } else {
            // asked claude if I can use a custom comparator with sort, said yes and define as 3rd argument in .sort()
            //so sorting by rating now, tiebreaker alphabet:

            sort(matches.begin(), matches.end(), [](const Movie& a, const Movie& b) {
                if (a.rating != b.rating) { //if different ratings, return the one with a greater rating
                    return a.rating > b.rating;
                } else { //otherwise go alphabetically
                    return a.name < b.name;
                }

            });

            //now print all matches

            for (auto& m : matches) {
                cout << m.name << ", " << m.rating << endl;
            }

            //saving the best for part 2b
            bestPrefixes.push_back(prefix);
            bests.push_back(matches[0]);
        }

    }

    //  For each prefix,
    //  Print the highest rated movie with that prefix if it exists.

    for (int i = 0; i < bests.size(); i++) { 
        cout << "Best movie with prefix " << bestPrefixes[i] << " is: " 
        << bests[i].name << " with rating " << std::fixed << std::setprecision(1) << bests[i].rating << endl;
    }
    return 0;
}

/* Add your run time analysis for part 3 of the assignment here as commented block*/
// thank goodness part 3 is optional!
bool parseLine(string &line, string &movieName, double &movieRating) {
    int commaIndex = line.find_last_of(",");
    movieName = line.substr(0, commaIndex);
    movieRating = stod(line.substr(commaIndex+1));
    if (movieName[0] == '\"') {
        movieName = movieName.substr(1, movieName.length() - 2);
    }
    return true;
}