#include <cstdlib>
#include <iostream>
#include <string>
#include <bits/stdc++.h>

#include "../include/hashClass.hpp"

using namespace std;

hashClass::hashClass()
{
  for (int i = 0;i < TableSize;i++)
  {
      store[i] = new Key_Value;
      store[i]->key = "NULL"; 
      store[i]->next = NULL;
  }
}

int hashClass::NumberOfItems(int index)
{
    int count = 0;
    if(store[index]->key == "NULL")
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

void hashClass::SetValue(string key, string data)
{
    int index = Hash(key);
    vector<string> tokens;
    stringstream check1(data);
    string intermediate;

    while(getline(check1, intermediate, ',')) 
        tokens.push_back(intermediate); 

    if(store[index]->key == "NULL")
    {
        store[index]->key = key;
        for(int i = 0;i < tokens.size(); i++)
        {
            string token = tokens[i];
            stringstream check2(token);
            string inter;
            getline(check2, inter, ':');
            string a = inter;
            getline(check2, inter, ':');
            string t = inter;
            store[index]->mp[a] = t;
            // cout << a << " is set for : " << key << endl;
        }
    }

    else
    {
        Key_Value* x = store[index];
        Key_Value* new_value = new Key_Value;
        new_value->key = key;
        for(int i = 0;i < tokens.size(); i++)
        {
            string token = tokens[i];
            stringstream check2(token);
            string inter;
            getline(check2, inter, ':');
            string a = inter;
            getline(check2, inter, ':');
            string t = inter;
            new_value->mp[a] = t;
            // cout << a << " is set for : " << key << endl;
        }
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

        if(ptr->key == "NULL")
            continue;
        n = NumberOfItems(i);
        cout << "Number of values at index " << i << " are: " << n <<endl;
        while(ptr->next!=NULL)
        {
            cout << "--------------------\n";
            cout << "Index = " << i << endl;
            cout << ptr->key << endl;
            for(auto j: ptr->mp){
                cout << j.first << " : " << j.second << endl;
            }
            ptr = ptr->next;
        }   
        cout << "--------------------\n";
        cout << "Index = " << i << endl;
        cout << ptr->key << endl;
        for(auto j: ptr->mp)
            cout << j.first << " : " << j.second << endl;
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
    else if(store[index]->key == "NULL")
    {
        cout << "Bucket is empty" << endl;
        return;
    }
    cout << "Bucket " << index << " info : " << endl;
    Key_Value* ptr = store[index];
    while(ptr != NULL)
    {
        cout << "-------------------\n";
        cout << ptr->key << endl;
        cout << "-------------------\n";
        for(auto i : ptr->mp)
        {
            cout << i.first << " : " << i.second << endl;
            cout << "-------------------\n";
        }
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
        if(ptr->key == key)
        {
            found = true;
            break;
        }
        ptr = ptr->next;
    }
    if(found)
    {
        cout << "Value " << key << " present in table at index " << index << "." << endl;
        // cout << "Data : \n";
        for(auto i : ptr->mp)
            cout << i.first << " : " << i.second << endl;
        cout << "-------------------\n";
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

    if(store[index]->key == "NULL")                                               //Empty bucket
        cout << "Record to be deleted not present in the table." << endl;

    else if(store[index]->key == key && store[index]->next == NULL)               //Single element bucket and match
    {
        store[index]->key = "NULL";
        cout << "Record " << key << " deleted successfully." << endl;
    } 

    else if(store[index]->key == key && store[index]->next != NULL)               //Multi element bucket and match on 1st value
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

        while(p1 != NULL && p1->key != key)
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

void hashClass::UpdateValue(string key, string changeData)
{
    int index = Hash(key);
    bool found = false;

    vector<string> tokens;
    stringstream check1(changeData);
    string intermediate;

    while(getline(check1, intermediate, ',')) 
        tokens.push_back(intermediate); 

    Key_Value* ptr = store[index];
    while(ptr != NULL)
    {
        if(ptr->key == key)
        {
            found = true;
            break;
        }
        ptr = ptr->next;
    }
    if(found)
    {
        for(int i = 0;i < tokens.size(); i++)
        {
            string token = tokens[i];
            stringstream check2(token);
            string inter;
            getline(check2, inter, ':');
            string a = inter;
            getline(check2, inter, ':');
            string t = inter;
            store[index]->mp[a] = t;
        }
        cout << "Value was succesfully updated" << endl;
    }
    else
    {
        SetValue(key, changeData);
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
