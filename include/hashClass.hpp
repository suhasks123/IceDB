#include <cstdlib>
#include <iostream>
#include <string>
#include <bits/stdc++.h>

using namespace std;

#ifndef ICE_HPP
#define ICE_HPP
//#define HASH_H

class hashClass{

    private:
        static const int TableSize = 10;

        struct Key_Value{
            string key;
            std::unordered_map<string, string> mp;
            Key_Value* next;
        };

        Key_Value* store[TableSize];
 
    public:

        hashClass();
        int Hash(string key);
        void SetValue(string key, string data);
        int NumberOfItems(int index);
        void PrintTable();
        void PrintBucket(int index);
        void GetValue(string key);
        void DeleteValue(string key);
        void UpdateValue(string key, string data);
};
