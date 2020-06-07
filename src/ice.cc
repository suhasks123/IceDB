#include <iostream>
#include <fstream>
#include <string>

#include "ice.hpp"
#include "hashClass.hpp"

// Initialize the main path of the created databases to the default value
IceDB::IceDB()
{
    this.path = "/var/lib/icedb/";
}

void IceDB::Open(std::string name)
{
    std::fstream iced, icem;
    std::string iced_path, icem_path;

    // Prepare the path for the .iced file and send it to hashClass
    iced_path.append(this.path);
    iced_path.append(name);
    iced_path.append(".iced");
    iced.open(iced_path, std::fstream::in);
    this.db.hash.ReadDB(iced);

    // Prepare the path for the .icem file and send it to Metadata class
    icem_path.append(this.path);
    icem_path.append(name);
    icem_path.append(".icem");
    icem.open(icem_path, std::fstream::in);
    this.db.meta.read_metadata(icem);

}

void IceDB::Close(std::string name)
{
    std::fstream iced, icem;
    std::string iced_path, icem_path;

    // Prepare the path for the .iced file and send it to hashClass
    iced_path.append(this.path);
    iced_path.append(name);
    iced_path.append(".iced");
    iced.open(iced_path, std::fstream::out | std::fstream::trunc);
    this.db.hash.WriteDB(iced);

    // Prepare the path for the .icem file and send it to Metadata class
    icem_path.append(this.path);
    icem_path.append(name);
    icem_path.append(".iced");
    icem.open(icem_path, std::fstream::out | std::fstream::trunc);
    this.db.meta.write_metadata(icem);
}

void IceDB::Set(string key, string data)
{
    this.db.hash.SetValue(key, data);
}

void IceDB::Get(string key)
{
    this.db.hash.GetValue(key);
}

void IceDB::Delete(string key)
{
    this.db.hash.DeleteValue(key);
}

void IceDB::Update(string key, string data)
{
    this.db.hash.UpdateValue(key, data);
}