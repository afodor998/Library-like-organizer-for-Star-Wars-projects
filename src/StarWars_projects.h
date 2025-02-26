#ifndef STARWARS_PROJECTS_H_INCLUDED
#define STARWARS_PROJECTS_H_INCLUDED
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include"memtrace.h"

class StarWars_projects {
public:
    StarWars_projects(const std::string& name="", int release_year=0, const std::string& publisher="")
        : name(name), release_year(release_year), publisher(publisher) {}

    virtual ~StarWars_projects() {}

    const std::string& GetName() const;
    int GetReleaseYear() const;
    const std::string& GetPublisher() const;

    virtual void Print() const;

    virtual void PrintToFile(std::ofstream& file) const;

    virtual bool Load(std::istream& stream);

    virtual void SetPublisher(const std::string& p);

    virtual void SetName(const std::string& n);

    virtual void SetReleaseYear(int release_y);
    virtual bool ReadFromUserInput();

    bool operator==(const StarWars_projects& other) const;

private:
    std::string name;
    int release_year;
    std::string publisher;
};


#endif // STARWARS_PROJECTS_H_INCLUDED
