#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <bits/stdc++.h>


#ifndef HASHCLASS_HPP
#define HASHCLASS_HPP
//#define HASH_H

class hashClass{

    private:
        static const int TableSize = 10;

        struct Key_Value{
            std::string key;
            std::map<std::string, std::string> mp;
            Key_Value* next;
        };

        Key_Value* store[TableSize];
 
    public:

        hashClass();
        void ReadDB(std::fstream fptr);
        void WriteDB(std::fstream fptr);
        int Hash(std::string key);
        void SetValue(std::string key, std::string data);
        int findTableSize();
        int NumberOfItems(int index);
        void PrintTable();
        void PrintBucket(int index);
        void GetValue(std::string key);
        void DeleteValue(std::string key);
        void UpdateValue(std::string key, std::string data);
};

#endif