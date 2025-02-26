#include "TV_series.h"
#include "StarWars_projects.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include "memtrace.h"

// Returns the number of episodes in the TV series
int TV_series::GetEpisodeNum() const { return episode_num; }

// Prints TV series project details and TV series-specific data
void TV_series::Print() const {
    std::cout << "Type: TV series, ";
    StarWars_projects::Print();
    std::cout << "Number of episodes: " << episode_num << std::endl;
}

// Prints TV series project details and TV series-specific data to a file
void TV_series::PrintToFile(std::ofstream& file) const {
    file << "SERIES;";
    StarWars_projects::PrintToFile(file);
    file << episode_num;
}

// Loads TV series project details from the input stream
// Returns true if successful, false otherwise
// Load base class details using StarWars_projects::Load()
// Reads the number of episodes as a string from the stream
// Converts string to an integer using std::stringstream
// Set the number of episodes using SetEpisodeNum()
bool TV_series::Load(std::istream& stream) {
    if (!StarWars_projects::Load(stream)) {
        return false;
    }
    std::string ep_str;
    getline(stream, ep_str);
    if (!stream) {
        return false;
    }
    int episode;
    std::stringstream(ep_str) >> episode;
    SetEpisodeNum(episode);
    return true;
}

// Reads TV series project details and TV series-specific data from user input
// True if successful, false otherwise
// Set the number of episodes using SetEpisodeNum()
bool TV_series::ReadFromUserInput() {
    if (!StarWars_projects::ReadFromUserInput())
        return false;

    int episodeCount;
    std::cout << "Episode count: ";
    std::cin >> episodeCount;
    SetEpisodeNum(episodeCount);

    return true;
}

// Sets the number of episodes in the TV series
void TV_series::SetEpisodeNum(int episodes) {
    episode_num = episodes;
}
