#ifndef TV_SERIES_H_INCLUDED
#define TV_SERIES_H_INCLUDED
#include "StarWars_projects.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include"memtrace.h"
class TV_series : public StarWars_projects {
public:
    TV_series(const std::string& name="", int release_year=0, const std::string& publisher="", int episode_num=0)
        : StarWars_projects(name, release_year, publisher), episode_num(episode_num) {}

    ~TV_series() {}

    int GetEpisodeNum() const;

    void Print() const override;

    void PrintToFile(std::ofstream& file) const override;

    bool Load(std::istream& stream);

    void SetEpisodeNum(int episodes);
    bool ReadFromUserInput();

private:
    int episode_num;
};

#endif // TV_SERIES_H_INCLUDED
