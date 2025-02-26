#include <iostream>
#include "StarWars_projects.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include "Projects.h"
#include "memtrace.h"

void test1(Projects& projects){
    // Add projects manually
    Games* game = new Games("Star Wars: Jedi Fallen Order", 2019, "Electronic Arts", "Play as Jedi Cal Kestis and take on the Empire");
    projects.Add(game);
    Movies* movie = new Movies("Star Wars: The Rise of Skywalker", 2019, "Lucasfilm", 124);
    projects.Add(movie);

    // Search for projects by year
    StarWars_projects** foundProjects = projects.FindByYear(2019);
    if (foundProjects != nullptr) {
        std::cout << std::endl << "Found projects (2019):" << std::endl;
        int idx = 0;
        while (foundProjects[idx] != nullptr) {
            foundProjects[idx]->Print();
            idx++;
        }
        delete[] foundProjects;
    } else {
        std::cout << "No elements found." << std::endl;
    }

    // Search for projects by publisher
    StarWars_projects** foundProjects2 = projects.FindByPublisher("LEGO");
    if (foundProjects != nullptr) {
        std::cout << std::endl << "Found projects (Publisher: LEGO):" << std::endl;
        int idx = 0;
        while (foundProjects2[idx] != nullptr) {
            foundProjects2[idx]->Print();
            idx++;
        }
        delete[] foundProjects2;
    } else {
        std::cout << "No elements found." << std::endl;
    }

    // Search for projects by name and remove them
    StarWars_projects** foundProjects3 = projects.FindByName("Star Wars: Jedi Fallen Order");
    if (foundProjects3 != nullptr) {
        std::cout << std::endl << "Found projects (Star Wars Jedi: Fallen Order):" << std::endl;
        int idx = 0;
        while (foundProjects3[idx] != nullptr) {
            foundProjects3[idx]->Print();
            idx++;
        }
        projects.Remove(foundProjects3);
        std::cout << "Project(s) successfully removed."<<std::endl;
    } else {
        std::cout << std::endl << "No elements found with the name: Star Wars Jedi: Fallen Order. No data was deleted." << std::endl;
    }
    delete[] foundProjects3;
        return;
}

void test2(Projects& projects){
// Add projects based on user input
    char addChoice;
    do {
        std::cout << "Do you want to add a project? (y/n): ";
        std::cin >> addChoice;
        std::cin.ignore();
        if (std::cin.fail() || std::cin.eof()) {
            break;
        }

        if (addChoice == 'y') {
            std::cout << "Enter new project data:" << std::endl;
            StarWars_projects* newProject = projects.CreateProjectFromUserInput();
            if (newProject != nullptr) {
                projects.Add(newProject);
            }
        }
    } while (addChoice != 'n');

    // Search for projects based on user input
    char searchChoice;
    do {
        std::cout << "Do you want to search for projects? (y/n): ";
        std::cin >> searchChoice;

        if (std::cin.fail() || std::cin.eof()) {
            break;
        }

        if (searchChoice == 'y') {
            std::string searchCriteria;
            std::cout << "Please enter the search criteria (year/publisher/name): ";
            std::cin >> searchCriteria;
            std::cin.ignore();

            if (searchCriteria == "year") {
                int year;
                std::cout << "Please enter the year to search for: ";
                std::cin >> year;

                StarWars_projects** foundProjects = projects.FindByYear(year);
                if (foundProjects != nullptr) {
                    std::cout << "Found projects (" << year << "):" << std::endl;
                    int index = 0;
                    while (foundProjects[index] != nullptr) {
                        foundProjects[index]->Print();
                        index++;
                    }
                    delete[] foundProjects;
                }
            } else if (searchCriteria == "publisher") {
                std::string publisher;
                std::cout << "Please enter the publisher to search for: ";
                std::getline(std::cin, publisher, '\n');

                StarWars_projects** foundProjects = projects.FindByPublisher(publisher);
                if (foundProjects != nullptr) {
                    std::cout << "Found projects by publisher (" << publisher << "):" << std::endl;
                    int index = 0;
                    while (foundProjects[index] != nullptr) {
                        foundProjects[index]->Print();
                        index++;
                    }
                    delete[] foundProjects;
                }
            } else if (searchCriteria == "name") {
                std::string name;
                std::cout << "Please enter the name to search for: ";
                std::getline(std::cin, name, '\n');

                StarWars_projects** foundProjects = projects.FindByName(name);
                if (foundProjects != nullptr) {
                    std::cout << "Found projects by name (" << name << "):" << std::endl;
                    int index = 0;
                    while (foundProjects[index] != nullptr) {
                        foundProjects[index]->Print();
                        index++;
                    }
                    delete[] foundProjects;
                }
            }
        }
    } while (searchChoice != 'n');

    // Delete projects based on user input
    char deleteChoice;
    do {
        std::cout << "Do you want to delete projects? (y/n): ";
        std::cin >> deleteChoice;
        if (std::cin.fail() || std::cin.eof()) {
            break;
        }

        if (deleteChoice == 'y') {
            std::string deleteCriteria;
            std::cout << "Please enter the criteria for deletion (year/publisher/name): ";
            std::cin >> deleteCriteria;
            std::cin.ignore();

            if (deleteCriteria == "year") {
                int year;
                std::cout << "Please enter the year from which you want to delete projects: ";
                std::cin >> year;

                StarWars_projects** foundProjects = projects.FindByYear(year);
                if (foundProjects != nullptr) {
                    projects.Remove(foundProjects);
                    delete[] foundProjects;
                }
            } else if (deleteCriteria == "publisher") {
                std::string publisher;
                std::cout << "Please enter the publisher whose projects you wish to delete: ";
                std::getline(std::cin, publisher, '\n');

                StarWars_projects** foundProjects = projects.FindByPublisher(publisher);
                if (foundProjects != nullptr) {
                    projects.Remove(foundProjects);
                    delete[] foundProjects;
                }
            } else if (deleteCriteria == "name") {
                std::string name;
                std::cout << "Please enter the name of the project you wish to delete: ";
                std::getline(std::cin, name, '\n');

                StarWars_projects** foundProjects = projects.FindByName(name);
                if (foundProjects != nullptr) {
                    projects.Remove(foundProjects);
                    delete[] foundProjects;
                }
            }
        }
    } while (deleteChoice != 'n');
    return;
}


int main()
{
    Projects projects;

    // Load projects from file
    try {
        projects.LoadFile("StarWars.txt");
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    // Print original content
    std::cout << "Original content:" << std::endl;
    projects.PrintAll();
    std::cout << std::endl;
    test1(projects);
    test2(projects);


    // Print modified content
    std::cout << std::endl << "Modified content:" << std::endl;
    projects.PrintAll();
    std::cout << std::endl;

    // Save modified content to file, displays error if needed
    try {
        projects.PrintAllToFile();
        std::cout << "Modified content saved to file." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}





