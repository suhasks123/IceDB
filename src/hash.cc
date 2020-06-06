#include <cstdlib>
#include <iostream>
#include <string>
#include <bits/stdc++.h>

#include "../include/hashClass.hpp"

using namespace std;

hashClass::hashClass()
{
  for (int i = 0;i<TableSize;i++)
  {
      store[i] = new Key_Value;
      store[i]->value = "NULL"; 
      store[i]->secret = "NULL";  
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

void hashClass::SetValue(string value, string secret)
{
    int index = Hash(value);

    if(store[index]->value=="NULL")
    {
        store[index]->value = value;
        store[index]->secret = secret;
    }

    else
    {
        Key_Value* x = store[index];
        Key_Value* new_value = new Key_Value;
        new_value->value = value;
        new_value->secret = secret;
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
        Key_Value* ptr = store[i];

        if(ptr->value == "NULL")
            continue;
        n = NumberOfItems(i);
        cout << "Number of values at index " << i << " are: " << n<<endl;
        while(ptr->next!=NULL)
        {
            cout << "--------------------\n";
            cout << "Index = " << i << endl;
            cout << ptr->value << endl;
            cout << ptr->secret << endl;
            ptr = ptr->next;
        }   
        cout << "--------------------\n";
        cout << "Index = " << i << endl;
        cout << ptr->value << endl;
        cout << ptr->secret << endl;
        cout << "\n";
    }
}

void hashClass::PrintBucket(int index)
{
    if(index < 0 || index >= TableSize)
    {
        cout << "Invalid index" << endl;
        return;
    }
    else if(store[index]->value == "NULL")
    {
        cout << "Bucket is empty" << endl;
        return;
    }
    cout << "Bucket " << index << " info : " << endl;
    Key_Value* ptr = store[index];
    while(ptr != NULL)
    {
        cout << "-------------------\n";
        cout << ptr->value << endl;
        cout << "-------------------\n";
        cout << ptr->secret << endl;
        cout << "-------------------\n";
        ptr = ptr->next;
    }
}

void hashClass::GetValue(string key)
{
    int index = Hash(key);
    bool found = false;

    Key_Value* ptr = store[index];
    while(ptr != NULL)
    {
        if(ptr->value == key)
        {
            found = true;
            break;
        }
        ptr = ptr->next;
    }
    if(found)
    {
        cout << "Value " << key << " present in table at index " << index << "." << endl;
        cout << "Data : " << ptr->secret << endl;
    }
    else
    {
        cout << key << " was not found in table." << endl;
    }
}

void hashClass::DeleteValue(string key)
{
    int index = Hash(key);
    Key_Value* p1;
    Key_Value* p2;
    Key_Value* del;

    if(store[index]->value == "NULL")                                               //Empty bucket
        cout << "Record to be deleted not present in the table." << endl;

    else if(store[index]->value == key && store[index]->next == NULL)               //Single element bucket and match
    {
        store[index]->value = "NULL";
        cout << "Record " << key << " deleted successfully." << endl;
    } 

    else if(store[index]->value == key && store[index]->next != NULL)               //Multi element bucket and match on 1st value
    {
        del = store[index];
        store[index] = store[index]->next;
        delete del; 
        cout << "Record " << key << " deleted successfully." << endl;
    }   
    else                                                                            //Multi element bucket and no match on 1st value
    {
        p2 = store[index];
        p1 = store[index]->next;

        while(p1 != NULL && p1->value != key)
        {
            p2 = p1;
            p1 = p1->next;
        }
        if(p1 == NULL)                                                              //No match in bucket
            cout << "Record to be deleted not present in the table." << endl;
        
        else
        {
            del = p1;
            p1 = p1->next;
            p2->next = p1;
            delete del;
            cout << "Record " << key << " deleted successfully." << endl;
        }
    }
}

void hashClass::UpdateValue(string key, string secret)
{
    int index = Hash(key);
    bool found = false;

    Key_Value* ptr = store[index];
    while(ptr != NULL)
    {
        if(ptr->value == key)
        {
            found = true;
            break;
        }
        ptr = ptr->next;
    }
    if(found)
    {
        ptr->secret = secret;
        cout << "Value was succesfully updated" << endl;
    }
    else
    {
        SetValue(key, secret);
        cout << "New object was created." << endl;
    }
}

int hashClass::Hash(string key)
{
    int hash = 0;
    int index, i;

    for (i = 0; i< key.length(); i++)
    {
        hash += (int)key[i];
    }

    index = hash % TableSize;

    return index;
}
