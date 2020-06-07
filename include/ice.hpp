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
    int size;
public:
    void write_metadata(std::fstream *, std::string);
    void read_metadata(std::fstream *);
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
    void Open(std::string);
    void Close(std::string name);
    void Set(string key, string data);
    void Get(string key);
    void Delete(string key);
    void Update(string key, string data);
};

#endif