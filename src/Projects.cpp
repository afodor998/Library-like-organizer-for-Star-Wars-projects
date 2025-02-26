#include "Projects.h"
#include "StarWars_projects.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include "memtrace.h"

// Destructor for the Projects class
// Deletes all dynamically allocated StarWars_projects objects and frees the memory
Projects::~Projects() {
    for (int i = 0; i < size; i++) {
        delete data[i];
    }
    delete[] data;
    size = 0;
}

// Overloaded operator[] to access and modify StarWars_projects objects at the specified index
// Throws an exception if the index is out of range
StarWars_projects*& Projects::operator[](int index) {

    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}
// Overloaded const operator[] to access StarWars_projects objects at the specified index
// Throws an exception if the index is out of range
const StarWars_projects* Projects::operator[](int index) const {

    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

// Create a new StarWars_projects object based on user input
// Creates uppercase word from input then compares
StarWars_projects* Projects::CreateProjectFromUserInput() {

    std::string type;
    bool validType = false;
    while (!validType) {
        std::cout << "Enter project type (GAME, MOVIE, SERIES, LEGO): ";
        if (!(std::cin >> type)) {
            std::cout << "Invalid input. Please enter a valid project type." << std::endl;
            std::cin.clear();
        } else {
            validType = true;
        }
    }

    StarWars_projects* project = nullptr;
    for (char& c : type) {
        c = std::toupper(c);
    }

    if (type == "GAME") {
        // Create a Games object and read its data from user input
        Games* game = new Games();
        if (game->ReadFromUserInput()) {
            project = game;
        } else {
        // ReadFromUserInput() was unsuccessful, deletes dynamically allocated object
            delete game;
        }

    } else if (type == "MOVIE") {
        // Create a Movies object and read its data from user input
        Movies* movie = new Movies();
        if (movie->ReadFromUserInput()) {
            project = movie;
        } else {
        // ReadFromUserInput() was unsuccessful, deletes dynamically allocated object
            delete movie;
        }

    } else if (type == "SERIES") {
        // Create a TV_series object and read its data from user input
        TV_series* series = new TV_series();
        if (series->ReadFromUserInput()) {
            project = series;
        } else {
        // ReadFromUserInput() was unsuccessful, deletes dynamically allocated object
            delete series;
        }

    } else if (type == "LEGO") {
        // Create a Lego object and read its data from user input
        Lego* lego = new Lego();
        if (lego->ReadFromUserInput()) {
            project = lego;
        } else {
        // ReadFromUserInput() was unsuccessful, deletes dynamically allocated object
            delete lego;
        }

    }
    // Returns pointer to project, nullptr if  ReadFromUserInput() was unsuccessful
    return project;
}

// Add a new StarWars_projects object to the Projects database
// Check if the project already exists in the database based on its name, release year, and publisher
// If it exists, displays an error message and deletes the project
// If it does not exist, adds the project to the database (heterogenous collection)
void Projects::Add(StarWars_projects* project) {

    for (int i = 0; i < size; i++) {
        if (*data[i] == *project) {
            std::cout << "Project '" << project->GetName() << "' already exists in the database." << std::endl;
            delete project;
            return;
        }
    }

    // Increase the capacity of the data array by 8 if it's full, copies the data of the old array to the new and bigger one
    // Deletes old array
    // Changes data pointer so that it now points to new_data array
    if (size == capacity) {
        capacity += 8;
        StarWars_projects** new_data = new StarWars_projects*[capacity];
        for (int i = 0; i < size; i++) {
            new_data[i] = data[i];
        }
        delete[] data;
        data = new_data;
    }

    // Add the project to the database
    data[size++] = project;
}
// Print information about all StarWars_projects in the database
void Projects::PrintAll() const {

    for (int i = 0; i < size; i++) {
        std::cout << "Project " << i+1 << ":" << std::endl;
        data[i]->Print();
        std::cout << std::endl;
    }
}

// Prints all projects to file named 'StarWars.txt'
// Opens file in std::ofstream::trunc mode (output mode and if file's not empty deletes its contents)
// Displays error if file could not be opened and returns
// Prints all data and closes the file
void Projects::PrintAllToFile() const {
    std::ofstream file("StarWars.txt", std::ofstream::trunc);
    if (!file) {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }
    data[0]->PrintToFile(file);
    for (int i = 1; i < size; i++) {
        file<<std::endl;
        data[i]->PrintToFile(file);
    }
    file.close();
}

// Load StarWars_projects data from a file and populate the Projects database
// Displays error if file could not be opened
// Converts file to ifstream
// Steps into while loop (until it can read lines)
// Converts one line line in each iteration to istringstream
// Gets type, if line is empty skips that line, if unknown project type was read displays it and the number of its line and skips that line
// Creates object based on type and loads it using Load()
// Deletes object if Load() was not successful
void Projects::LoadFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        throw std::runtime_error("Could not open file: " + filename);
    }

    int lineNum=0;
    std::string line;
    while (std::getline(file, line)) {
        lineNum++;
        //following method was found on StackOverflow
        std::istringstream iss(line);
        std::string type;
        getline(iss, type,';');

    if (line.empty()) {
        continue;
    }

    if (type == "GAME") {
        Games* game = new Games();
        if (game->Load(iss)) {
                Add(game);
        }
        else {
            delete game;
            }
    }
    else if (type == "MOVIE") {
        Movies* movie = new Movies();
        if (movie->Load(iss)) {
            Add(movie);
        }
        else {
                delete movie;
            }

    } else if (type == "SERIES") {
        TV_series* series= new TV_series();
        if (series->Load(iss)) {
            Add(series);
        }
        else {
                delete series;
            }

    } else if (type == "LEGO") {
        Lego* lego = new Lego();
        if (lego->Load(iss)) {
            Add(lego);
        }
        else {
                delete lego;
            }

    } else {

        std::cout << "Unknown project type in line " << lineNum << ": " << "/"<<type<<"/" << std::endl;
        continue;
        }
    }
}

// Create an array of pointers to StarWars_projects objects with 'size' size
// Initialize all elements of the array to nullptr
// Keeps track of the number of matching projects found
// Iterates over each project in the data array
// Check if the project's name matches the provided name
// If there is a match, add the project to the foundProjects array
// If no matching projects were found, deallocate the memory and set the pointer to nullptr
// Return the array of matching projects (or nullptr if no matches were found)
StarWars_projects** Projects::FindByName(const std::string& name) const {

    StarWars_projects** foundProjects = new StarWars_projects*[size];
    for (int i = 0; i < size; i++) {
        foundProjects[i] = nullptr;
    }
    int count = 0;

    for (int i = 0; i < size; i++) {

        if (data[i]->GetName() == name) {
            foundProjects[count] = data[i];
            count++;
        }
    }

    if (count == 0) {
        delete[] foundProjects;
        foundProjects = nullptr;
    }

    return foundProjects;
}
// Create an array of pointers to StarWars_projects objects with 'size' size
// Initialize all elements of the array to nullptr
// Keeps track of the number of matching projects found
// Iterates over each project in the data array
// Check if the project's release year matches the provided year
// If there is a match, add the project to the foundProjects array
// If no matching projects were found, deallocate the memory and set the pointer to nullptr
// Return the array of matching projects (or nullptr if no matches were found)
StarWars_projects** Projects::FindByYear(int year) const {
    StarWars_projects** foundProjects = new StarWars_projects*[size];
    for (int i = 0; i < size; i++) {
    foundProjects[i] = nullptr;
}
    int count = 0;

    for (int i = 0; i < size; i++) {
        if (data[i]->GetReleaseYear() == year) {
            foundProjects[count] = data[i];
            count++;
            ;
        }

    }

    if (count == 0) {
        delete[] foundProjects;
        foundProjects = nullptr;
    }

    return foundProjects;
}
// Create an array of pointers to StarWars_projects objects with 'size' size
// Initialize all elements of the array to nullptr
// Keeps track of the number of matching projects found
// Iterates over each project in the data array
// Check if the project's publisher matches the provided publisher
// If there is a match, add the project to the foundProjects array
// If no matching projects were found, deallocate the memory and set the pointer to nullptr
// Return the array of matching projects (or nullptr if no matches were found)
StarWars_projects** Projects::FindByPublisher(const std::string& pub) const {
    StarWars_projects** foundProjects = new StarWars_projects*[size];
    for (int i = 0; i < size; i++) {
    foundProjects[i] = nullptr;
}
    int count = 0;

    for (int i = 0; i < size; i++) {
        if (data[i]->GetPublisher() == pub) {
            foundProjects[count] = data[i];
            count++;
        }
    }

    if (count == 0) {
        delete[] foundProjects;
        foundProjects = nullptr;
    }

    return foundProjects;
}

// Counts the number of projects to remove by iterating until a nullptr is encountered
// Iterates over each project to be removed in outer for loop
// Iterates over each project in the data array in inner for loop
// If a project in the data array matches a project to be removed then deletes the project object and sets the pointer in the data array to nullptr
// Iterates over the data array again to compact it by removing nullptr entries
// If a non-null project is encountered moves the project to the next available index in the data array
// Updates the size of the data array to reflect the exact number of remaining projects
void Projects::Remove(StarWars_projects** projectsToRemove) {
    int count = 0;

    while (projectsToRemove[count] != nullptr) {
        count++;
    }
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < size; j++) {
            if (data[j] == projectsToRemove[i]) {
                delete data[j];
                data[j] = nullptr;
            }
        }
    }

    int index = 0;
    for (int i = 0; i < size; i++) {
        if (data[i] != nullptr) {
            data[index] = data[i];
            index++;
        }
    }
    size = index;
}






