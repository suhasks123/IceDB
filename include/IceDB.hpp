#include<iostream>
#include<fstream>

// Defining Macros

#define CREATE 1
#define WRITE 2
#define READ 4
#define TRUNC 8

class IceDB
{
public:
    void Open(std::string, uint32_t);
    void Open(std::string);
    std::fstream db_file;

};