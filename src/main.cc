#include<iostream>
#include<fstream>

#include "ice.hpp"

using namespace std;

int main()
{
    IceDB* ice = new IceDB();
    IceDB* ice1 = new IceDB();
    ice->Open("Test1");

    ice->Set("Harry", "Age:20,Interest:Gym,Food:Pasta");
    ice->Set("Dick", "Age:30,Interest:Cry,Food:Pizza");
    ice->Set("Alice", "Age:40,Interest:Laugh,Food:Dosa");
    ice->Set("Bob", "Age:50,Interest:Work,Food:Idli");
    ice->Set("Natasha", "Age:26,Interest:Cook,Food:Tofu");
    ice->Set("Julia", "Age:22,Interest:Write,Food:Burger");
    ice->Set("Audi", "Age:34,Interest:Read,Food:Upma");
    ice->Set("Mercedes", "Age:55,Interest:Run,Food:Milk");

    ice->PrintAll();
    ice->Close("Test1");

    ice1->Open("Test1");

    ice1->PrintAll();

    ice1->Get("Harry");

    return 0;
}