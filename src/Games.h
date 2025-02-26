#ifndef GAMES_H_INCLUDED
#define GAMES_H_INCLUDED
#include "StarWars_projects.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include"memtrace.h"


class Games : public StarWars_projects {
private:
    std::string story;

public:
    Games(const std::string& name="", int release_year=0, const std::string& publisher="", const std::string& story="")
        : StarWars_projects(name, release_year, publisher), story(story) {}

    ~Games() {}

    const std::string& GetStory() const;

    void Print() const override;

    void PrintToFile(std::ofstream& file) const override;

    bool Load(std::istream& stream);

    void SetStory(const std::string& s);

    bool ReadFromUserInput();

};


#endif // GAMES_H_INCLUDED
