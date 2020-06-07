#include<iostream>
#include<fstream>

// Defining Macros

#define CREATE 1
#define WRITE 2
#define READ 4
#define TRUNC 8

class IceDB
{

private:
    std::fstream db_file;

public:
    void Open(std::string, uint32_t = CREATE | WRITE);
    void Close();
    void Set(string key, string data);
    void Get(string key);
    void Delete(string key);
    void Update(string key, string data);
};