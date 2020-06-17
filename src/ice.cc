#include <bits/stdc++.h> 
#include <iostream> 
#include <sys/stat.h> 
#include <sys/types.h>
#include <fstream>
#include <string>

#include "ice.hpp"
#include "hashClass.hpp"

// Initialize the main path of the created databases to the default value
IceDB::IceDB()
{
    int status = mkdir("/var/lib/icedb", 0777);
    this->path = "/var/lib/icedb/";
}

void IceDB::Open(std::string name)
{
    std::ifstream iced, icem;
    std::string iced_path, icem_path;

    // Prepare the path for the .iced file and send it to hashClass
    iced_path.append(this->path);
    iced_path.append(name);
    iced_path.append(".iced");
    iced.open(iced_path.c_str(), std::fstream::in);
    this->db.hash.ReadDB(iced);

    // Prepare the path for the .icem file and send it to Metadata class
    icem_path.append(this->path);
    icem_path.append(name);
    icem_path.append(".icem");
    icem.open(icem_path.c_str(), std::fstream::in);
    this->db.meta.read_metadata(icem);
}

void IceDB::Close(std::string name)
{
    std::ofstream iced, icem;
    std::string iced_path, icem_path;

    // Prepare the path for the .iced file and send it to hashClass
    iced_path.append(this->path);
    iced_path.append(name);
    iced_path.append(".iced");
    iced.open(iced_path, std::fstream::out | std::fstream::trunc);
    this->db.hash.WriteDB(iced);

    // Prepare the path for the .icem file and send it to Metadata class
    icem_path.append(this->path);
    icem_path.append(name);
    icem_path.append(".icem");
    icem.open(icem_path, std::fstream::out | std::fstream::trunc);
    int size = this->db.hash.findTableSize();
    this->db.meta.write_metadata(icem, name, size);
}

void IceDB::Set(std::string key, std::string data)
{
    this->db.hash.SetValue(key, data);
}

void IceDB::Get(std::string key)
{
    this->db.hash.GetValue(key);
}

void IceDB::Delete(std::string key)
{
    this->db.hash.DeleteValue(key);
}

void IceDB::Update(std::string key, std::string data)
{
    this->db.hash.UpdateValue(key, data);
}

void IceDB::PrintAll()
{
    this->db.hash.PrintTable();
}

void IceDB::PrintKeyBucket(std::string key)
{
    bool ok = this->db.hash.PrintBucket(key);
    if(!ok)
        std::cout << "Given key not present in table" << std::endl;
}

void IceDB::Drop(std::string name)
{
    std::string iced_path, icem_path;

    // Prepare the path for the .iced file and send it to hashClass
    iced_path.append(this->path);
    iced_path.append(name);
    iced_path.append(".iced");
    const char *iced = iced_path.c_str();
    if(std::remove(iced) != 0)
        std::cout << "Couldn't delete the database files\n";

    // Prepare the path for the .icem file and send it to Metadata class
    icem_path.append(this->path);
    icem_path.append(name);
    icem_path.append(".icem");
    const char *icem = icem_path.c_str();
    if(std::remove(icem) != 0)
        std::cout << "Couldn't delete the database files\n";
}