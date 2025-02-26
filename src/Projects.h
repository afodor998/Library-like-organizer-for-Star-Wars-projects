#ifndef PROJECTS_H_INCLUDED
#define PROJECTS_H_INCLUDED
#include "StarWars_projects.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include"memtrace.h"
#include "Games.h"
#include "Movies.h"
#include "TV_series.h"
#include "Lego.h"

class Projects {
private:
    int size;
    int capacity;
    StarWars_projects** data;


public:
    Projects() : size(0), capacity(0), data(NULL) {}
    ~Projects();

    StarWars_projects* CreateProjectFromUserInput();

    StarWars_projects*& operator[](int index);

    const StarWars_projects* operator[](int index) const;

    void Add(StarWars_projects* project);

    void PrintAll() const;

    void PrintAllToFile() const;

    void LoadFile(const std::string& filename);

    StarWars_projects** FindByName(const std::string& name) const ;

    StarWars_projects** FindByYear(int year) const ;

    StarWars_projects** FindByPublisher(const std::string& pub) const;

    void Remove(StarWars_projects** projectsToRemove);


};


#endif // PROJECTS_H_INCLUDED
