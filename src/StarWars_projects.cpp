#include"StarWars_projects.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include"memtrace.h"

// Returns the name of the Star Wars project
const std::string& StarWars_projects::GetName() const {
    return name;
}

// Returns the release year of the Star Wars project
int StarWars_projects::GetReleaseYear() const {
    return release_year;
}

// Returns the publisher of the Star Wars project
const std::string& StarWars_projects::GetPublisher() const {
    return publisher;
}

// Prints the details of the Star Wars project
void StarWars_projects::Print() const {
    std::cout << "Name: " << name << ", Release Year: " << release_year << ", Publisher: " << publisher << std::endl;
}

// Prints the details of the Star Wars project to a file
void StarWars_projects::PrintToFile(std::ofstream& file) const {
    file << name << "," << release_year << "," << publisher << ",";
}

// Loads the Star Wars project details from the input stream
// Returns true if successful, false otherwise
// Reads the project name from the stream
// Reads the release year from the stream
// Reads the publisher from the stream
// Checks whether the stream was successfully read or not
// Sets the name, release year, and publisher of the Star Wars project
bool StarWars_projects::Load(std::istream& stream) {
    std::string name;
    getline(stream, name, ',');


    int release_year;
    stream >> release_year;
    stream.ignore();


    std::string publisher;
    getline(stream, publisher, ',');


    if (!stream) {
        return false;
    }


    SetName(name);
    SetReleaseYear(release_year);
    SetPublisher(publisher);

    return true;
}

// Sets the publisher of the Star Wars project
void StarWars_projects::SetPublisher(const std::string& p) {
    publisher = p;
}

// Sets the name of the Star Wars project
void StarWars_projects::SetName(const std::string& n) {
    name = n;
}

// Sets release year of the Star Wars project
void StarWars_projects::SetReleaseYear(int release_y) {
    release_year = release_y;
}

// Loads the Star Wars project details from user input
// Returns true if successful, false otherwise
// Reads and sets release year, name and publisher
bool StarWars_projects::ReadFromUserInput() {
    int releaseYear;
    std::cout << "Release year: ";
    std::cin >> releaseYear;
    std::cin.ignore();
    SetReleaseYear(releaseYear);

    std::string name;
    std::cout << "Name: ";
    std::getline(std::cin, name, '\n');
    SetName(name);


    std::string publisher;
    std::cout << "Publisher: ";
    std::getline(std::cin, publisher, '\n');
    SetPublisher(publisher);

    return true;
}

// Checks whether two objects are the same or not by comparing every attribute
bool StarWars_projects::operator==(const StarWars_projects& other) const {
    return (name == other.name && release_year == other.release_year && publisher == other.publisher);
}

