#include<iostream>
#include<fstream>

#include "IceDB.hpp"

using namespace std;

int main()
{
    string path = "/home/xenon/hello.txt";
    
    IceDB db;
    db.Open(path);
    system("ls /home/xenon/hello.txt");
    //db.db_file << "Hello .\n";
    db.Close();
    return 0;
}