#include<iostream>
#include<fstream>

#include "IceDB.hpp"

using namespace std;

/*class IceDB
{
    // Attributes:
    // ifstream db_file_read;
    // ofstream db_file_write;
    fstream db_file;

    // Methods
    void open(const string path, uint32_t open_opt = CREATE | WRITE)
    {
        ios_base::openmode opt;
        if (!((open_opt & CREATE) > 0)) {
            opt |= ios::ate;
        }

        if ((open_opt & WRITE) > 0) {
            opt |= ios::out;
        }

        if ((open_opt & READ) > 0) {
            opt |= ios::in;
        }

        if ((open_opt & TRUNC) > 0) {
            opt |= ios::trunc;
        }

        db_file.open(path, opt);
    }
};*/

void IceDB::Open(string path, uint32_t open_opt = CREATE | WRITE)
{
    ios_base::openmode opt;
    if (!((open_opt & CREATE) > 0)) {
        opt |= ios::ate;
    }

    if ((open_opt & WRITE) > 0) {
        opt |= ios::out;
    }

    if ((open_opt & READ) > 0) {
        opt |= ios::in;
    }

    if ((open_opt & TRUNC) > 0) {
        opt |= ios::trunc;
    }

    this->db_file.open(path, opt);
}

void IceDB::Open(string path)
{
    /*ios_base::openmode opt;
    if (!((open_opt & CREATE) > 0)) {
        opt |= ios::ate;
    }

    if ((open_opt & WRITE) > 0) {
        opt |= ios::out;
    }

    if ((open_opt & READ) > 0) {
        opt |= ios::in;
    }

    if ((open_opt & TRUNC) > 0) {
        opt |= ios::trunc;
    }*/

    this->db_file.open(path, ios::out | ios::in);
    //this->db_file.open(path);
    cout << "Hello";
}