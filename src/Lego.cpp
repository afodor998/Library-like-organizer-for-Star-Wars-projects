#include "Lego.h"
#include "StarWars_projects.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include "memtrace.h"

// Returns the number of pieces in the Lego set
int Lego::GetPieces() const { return pcs; }

// Prints Lego project details and Lego-specific data
void Lego::Print() const {
    std::cout << "Type: Lego, ";
    StarWars_projects::Print();
    std::cout << "Number of pieces: " << pcs << std::endl;
}

// Prints Lego project details and Lego-specific data to a file
void Lego::PrintToFile(std::ofstream& file) const {
    file << "LEGO;";
    StarWars_projects::PrintToFile(file);
    file << pcs;
}

// Loads Lego project details from the input stream
// Returns true if successful, false otherwise
// Load base class details using StarWars_projects::Load()
// Reads the number of pieces as a string from the stream
// Converts string to an integer using std::stringstream
// Set the number of pieces of the set using SetPieces()
bool Lego::Load(std::istream& stream) {
    if (!StarWars_projects::Load(stream)) {
        return false;
    }
    std::string pcs_str;
    getline(stream, pcs_str);
    if (!stream) {
        return false;
    }
    int pieces;
    std::stringstream(pcs_str) >> pieces;
    SetPieces(pieces);
    return true;
}

// Reads Lego project details and Lego-specific data from user input
bool Lego::ReadFromUserInput() {
    if (!StarWars_projects::ReadFromUserInput())
        return false;

    int pieceCount;
    std::cout << "Piece count: ";
    std::cin >> pieceCount;
    SetPieces(pieceCount);

    return true;
}

// Sets the number of pieces in the Lego set
void Lego::SetPieces(int pieces) {
    pcs = pieces;
}
