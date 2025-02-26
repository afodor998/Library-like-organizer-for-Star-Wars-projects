#ifndef MOVIES_H_INCLUDED
#define MOVIES_H_INCLUDED
#include "StarWars_projects.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include"memtrace.h"

class Movies : public StarWars_projects {
public:
    Movies(const std::string& name="", int release_year=0, const std::string& publisher="", int length=0)
        : StarWars_projects(name, release_year, publisher), length(length) {}

    ~Movies() {}

    int GetLength() const;

    void Print() const override;

    void PrintToFile(std::ofstream& file) const override;

    bool Load(std::istream& stream);

    void SetLength(int len);
    bool ReadFromUserInput();


private:
    int length;
};

#endif // MOVIES_H_INCLUDED
