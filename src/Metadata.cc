#include <iostream>
#include <fstream>
#include <string>

#include "ice.hpp"
#include "hashClass.hpp"

void Metadata::read_metadata(std::ifstream& icem)
{
    std::string buf;
    int i=0;

    // For name
    getline(icem, buf);
    this->name = buf;

    // For last_modified
    getline(icem, buf);
    this->last_modified = buf;

    // For size
    getline(icem, buf);
    this->size = buf;

    return;
}

void Metadata::write_metadata(std::ofstream& icem, std::string name, int size)
{
    // Update the size
    this->size = std::to_string(size);

    // Update the name
    this->name = name;

    // Update the last_modified time
    time_t current_last_modified = time(0);
    this->last_modified = ctime(&current_last_modified);

    // Writing them to file
    icem << this->name << "\n";
    icem << this->last_modified << "\n";
    icem << this->size << "\n";
}

void Metadata::display_metadata()
{
    std::cout << "Database Name: " << this->name << "\n";
    std::cout << "Last Modified: " << this->last_modified << "\n";
    std::cout << "Size of Database: " << this->size << "\n";
}