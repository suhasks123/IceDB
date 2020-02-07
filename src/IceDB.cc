#include<iostream>
#include<fstream>

#include "IceDB.hpp"

using namespace std;

void IceDB::Open(string path, uint32_t open_opt)
{
    ios_base::openmode opt;
    
    if ((open_opt & CREATE) > 0) {
        opt |= ios::trunc;
    }
    else {
        opt |= ios::ate;
    }

    if ((open_opt & WRITE) > 0) {
        opt |= ios::out;
        cout << "write\n";
    }

    if ((open_opt & READ) > 0) {
        opt |= ios::in;
    }

    if ((open_opt & TRUNC) > 0) {
        opt |= ios::trunc;
    }

    this->db_file.open(path, opt);
}

void IceDB::Close()
{
    if(this->db_file.is_open())
        this->db_file.close();
}