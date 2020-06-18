#include <iostream>
#include <fstream>
#include <ctime>

#include "hashClass.hpp"

// Defining Macros
#ifndef ICE_HPP
#define ICE_HPP

#define CREATE 1
#define WRITE 2
#define READ 4
#define TRUNC 8

class Metadata
{
private:
    std::string name;
    std::string last_modified;
    std::string size;
public:
    void write_metadata(std::ofstream&, std::string, int);
    void read_metadata(std::ifstream&);
    void display_metadata();
};

class Database
{
public:
    hashClass hash;
    Metadata meta;
    Database();
};

class IceDB
{

private:
    std::string path;

public:
    Database db;
    IceDB();
    void Open(std::string name);
    void Close(std::string name);
    void Set(std::string key, std::string data);
    std::map<std::string, std::string> Get(std::string key);
    void Delete(std::string key);
    void Update(std::string key, std::string data);
    void PrintAll();
    void PrintKeyBucket(std::string key);
    void Drop(std::string name);
};

#endif