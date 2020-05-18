#include <cstdlib>
#include <iostream>
#include <string>

#include "/home/sai/Projects/IceDB/IceDB/include/hashClass.hpp"

using namespace std;

hashClass::hashClass()
{
  for (int i = 0;i<TableSize;i++)
  {
      store[i] = new Key_Value;
      store[i]->value = "NULL";   
      store[i]->next = NULL;
  }
}

int hashClass::NumberOfItems(int index)
{
    int count = 0;
    if(store[index]->value == "NULL")
    {
        return count;
    }

    else
    {
        count++;
        Key_Value* ptr = store[index];
        while(ptr->next != NULL)
        {
            count++;
            ptr = ptr->next;
        }
    }
    return count;
    
}

void hashClass::AddValue(string value)
{
    int index = Hash(value);

    if(store[index]->value=="NULL")
    {
        store[index]->value = value;
    }

    else
    {
        Key_Value* x = store[index];
        Key_Value* new_value = new Key_Value;
        new_value->value = value;
        new_value->next = NULL;
        while (x->next != NULL)
        {
            x = x->next;
        }
        x->next = new_value;
    }
}

void hashClass::PrintTable()
{
    int n;
    for(int i = 0; i < TableSize; i++)
    {
        n = NumberOfItems(i);
        cout<<"Number of values at index " << i << " are: " << n<<endl;
        Key_Value* ptr = store[i];
        while(ptr->next!=NULL)
        {
            cout<<"--------------------\n";
            cout<<"Index = "<<i<<endl;
            cout<<ptr->value<<endl;
            ptr = ptr->next;
        }   
        cout<<"--------------------\n";
        cout<<"Index = "<<i<<endl;
        cout<<ptr->value<<endl;
        cout<<"\n";
    }
}

int hashClass::Hash(string key)
{
    int hash = 0;
    int index;

    for (int i = 0; i< key.length(); i++)
    {
        hash += (int)key[i];
    }

    index = hash % TableSize;

    return index;
}