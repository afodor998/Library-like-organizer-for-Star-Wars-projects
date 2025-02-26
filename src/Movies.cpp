#include"Movies.h"
#include "StarWars_projects.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include"memtrace.h"

    // Returns the length of the movie
    int Movies::GetLength() const { return length; }

    //Prints project (project = movie) details and movie specific data
    void Movies::Print() const {
        std::cout << "Type: Movie, ";
        StarWars_projects::Print();
        std::cout << "Movie length (min): " << length << std::endl;
    }

    // Prints project (project = movie) details and movie specific data to a file
    void Movies::PrintToFile(std::ofstream& file) const {
    file << "MOVIE;";
    StarWars_projects::PrintToFile(file);
    file << length;
}
// Loads movie details from the input stream
// Returns true if successful, false otherwise
// Load base class details using StarWars_projects::Load()
// Read the movie length as a string from the stream
// Converts string to an integer using std::stringstream
// Set the length of the movie using SetLength()
bool Movies::Load(std::istream& stream) {
    if (!StarWars_projects::Load(stream)){
        return false;
    }
    std::string length_str;
    getline(stream, length_str);
    if (!stream) {
        return false;
    }
    int length;
    std::stringstream(length_str) >> length;
    SetLength(length);
    //std::cout << 6;
    return true;
}
// Reads project details and movie specific data from user input
// Set the length of the movie using SetLength()
bool Movies::ReadFromUserInput() {
    if (!StarWars_projects::ReadFromUserInput())
        return false;

    int length;
    std::cout << "Length: ";
    std::cin >> length;
    SetLength(length);

    return true;
}
    // Sets the length of the movie
    void Movies::SetLength(int len) {
    length = len;
}

