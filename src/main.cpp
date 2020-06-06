
#include<iostream>
#include<cstdlib>
#include<string>

#include "../include/hashClass.hpp"

using namespace std;

int main(int argc, char** argv){


// For testing:

    hashClass hashObj;
    hashObj.SetValue("Sai", "Gym");
    hashObj.SetValue("Pachi", "Chips");
    hashObj.SetValue("Saji", "Mallu");
    hashObj.SetValue("Krithik", "Goan");
    hashObj.SetValue("Hema", "Swami");
    hashObj.SetValue("Dhanwin", "Stalker");
    hashObj.SetValue("Arnav", "Marketer");
    hashObj.SetValue("Sanjana", "Hairy");
    hashObj.SetValue("Anand", "LMAO");
    hashObj.SetValue("Suhas", "OS God");
    
    // cout << hashObj.NumberOfItems(5) << endl;

    hashObj.PrintTable();
    hashObj.UpdateValue("Sai", "Mast");
    // hashObj.DeleteValue("Saji");
    // cout << "\n\n\n";
    // hashObj.PrintTable();

    return 0;
}
