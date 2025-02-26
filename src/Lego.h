#ifndef LEGO_H_INCLUDED
#define LEGO_H_INCLUDED
#include "StarWars_projects.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include"memtrace.h"

class Lego : public StarWars_projects {
public:
    Lego(const std::string& name="", int release_year=0, const std::string& publisher="", int pcs=0)
        : StarWars_projects(name, release_year, publisher), pcs(pcs) {}

    ~Lego() {}

    int GetPieces() const;

    void Print() const override;

    void PrintToFile(std::ofstream& file) const override;

    bool Load(std::istream& stream);

    void SetPieces(int pieces);
    bool ReadFromUserInput();

private:
    int pcs;
};


#endif // LEGO_H_INCLUDED
