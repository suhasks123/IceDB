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
            Key_Value* next;
        };

        Key_Value* store[TableSize];
 
    public:

        hashClass();
        int Hash(string key);
        void AddValue(string value);
        int NumberOfItems(int index);
        void PrintTable();
    

};