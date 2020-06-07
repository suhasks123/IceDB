
#include<iostream>
#include<cstdlib>
#include<string>

#include "../include/hashClass.hpp"

using namespace std;

int main(int argc, char** argv){


// For testing:

    hashClass hashObj;
    hashObj.SetValue("Sai", "Interest:Gym,Age:20");
    hashObj.SetValue("Pachi", "Interest:Chips,Age:20");
    hashObj.SetValue("Saji", "Language:Mallu,Age:20");
    hashObj.SetValue("Krithik", "From:Goan,Age:20");
    hashObj.SetValue("Dhanwin", "Interest:CP God,Age:20");
    hashObj.SetValue("Arnav", "Interest:Marketer,Age:20");
    hashObj.SetValue("Anand", "Lol:LMAO,Age:45");
    hashObj.SetValue("Suhas", "Interest:OS God,Age:55");
    
    // cout << hashObj.NumberOfItems(5) << endl;
    // hashObj.PrintBucket(5);
    // hashObj.UpdateValue("Sai", "Age:25");
    // hashObj.DeleteValue("Saji");
    hashObj.GetValue("Saji");
    // cout << "\n\n\n";
    hashObj.PrintTable();

    return 0;
}
