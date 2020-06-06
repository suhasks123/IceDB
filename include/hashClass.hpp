#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

//#define HASH_H

class hashClass{

    private:
        static const int TableSize = 10;

        struct Key_Value{
            string value;
            string secret;
            Key_Value* next;
        };

        Key_Value* store[TableSize];
 
    public:

        hashClass();
        int Hash(string key);
        void SetValue(string value, string secret);
        int NumberOfItems(int index);
        void PrintTable();
        void PrintBucket(int index);
        void GetValue(string key);
        void DeleteValue(string key);
        void UpdateValue(string key, string secret);
};
