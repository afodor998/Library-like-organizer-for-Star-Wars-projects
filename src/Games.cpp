#include "Games.h"
#include"StarWars_projects.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include"memtrace.h"



    // Returns the story of the game
    const std::string& Games::GetStory() const { return story; }

    // Prints game details and game-specific data
    void Games::Print() const{
        std::cout << "Type: Game, ";
        StarWars_projects::Print();
        std::cout << "Story: " << story << std::endl;
    }

    // Prints game details and game-specific data to a file
    void Games::PrintToFile(std::ofstream& file) const {
        file << "GAME;";
        StarWars_projects::PrintToFile(file);
        file << story;
    }

// Loads game details from the input stream
// Returns true if successful, false otherwise
// Sets story using SetStory()
bool Games::Load(std::istream& stream) {
    if (!StarWars_projects::Load(stream)){
        return false;
    }
    std::string story;
    getline(stream, story);
    if (!stream) {
        return false;
    }
    SetStory(story);
    return true;
}

// Reads game details and game-specific data from user input
// Sets story using SetStory()
bool Games::ReadFromUserInput() {
    if (!StarWars_projects::ReadFromUserInput())
        return false;

    std::string story;
    std::cout << "Story: ";
    std::getline(std::cin, story);
    SetStory(story);

    return true;
}
// Sets the story of the game
void Games::SetStory(const std::string& s) {
    story = s;
}


