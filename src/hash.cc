#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <bits/stdc++.h>

#include "hashClass.hpp"
#include "encrypt.h"

hashClass::hashClass()
{
  for (int i = 0;i < TableSize;i++)
  {
      this->store[i] = new Key_Value;
      this->store[i]->key = "NULL"; 
      this->store[i]->next = NULL;
  }
}

void hashClass::ReadDB(std::ifstream& fptr)  
{
    int i;
    std::string str, key, data, enc;
    while(getline(fptr, enc))
    {
        i = 0;
        // enc = enc.substr(0, enc.length() - 1);
        str = decrypt(enc, priv_key);
        // str = enc;
        while(str[i] != ',')
            i++;
        key = str.substr(0, i);                          //When writing, we store the key first, a comma, followed by the key value pairs to be inserted in the map, each separated by a comma.
        data = str.substr(i + 1);                        //This is the data part, the key value pairs to be stored in the map.
        // std::cout << key << " : " << data;
        this->SetValue(key, data);
    }
    fptr.close();
}

void hashClass::WriteDB(std::ofstream& fptr)
{
    int i;
    for(i = 0;i < TableSize; i++)
    {
        Key_Value* ptr = this->store[i];
        if(ptr->key == "NULL")
            continue;
        while(ptr->next != NULL)                                     // For every item
        {
            std::string s = ptr->key;                                // Write "key,key1:value1,key2:value2....."
            for(auto j: ptr->mp)
            {
                std::string key = j.first;
                std::string value = j.second;
                s += ',' + key + ':' + value;
            }
            std::string en = encrypt(s, priv_key); 
            en += "\n";
            fptr << en;                                               // std::cout << key << " : " << data;
            ptr = ptr->next;                                         // Write to file.
        }
        std::string s = ptr->key;                                    // For last item.
        for(auto j: ptr->mp)
        {
            std::string key = j.first;
            std::string value = j.second;
            s += ',' + key + ':' + value;
        }
        std::string en = encrypt(s, priv_key); 
        en += "\n";
        fptr << en;
    }
    fptr.close();
}

int hashClass::findTableSize()                                      //Total number of items in the table.
{
    int i;
    int ans = 0;
    for(i = 0;i < TableSize; i++)
        ans += NumberOfItems(i);
    return ans;
}

int hashClass::NumberOfItems(int index)                             //Calculates number of items in a given bucket 
{
    int count = 0;
    if(this->store[index]->key == "NULL")
        return count;
    else
    {
        count++;
        Key_Value* ptr = this->store[index];
        while(ptr->next != NULL)
        {
            count++;
            ptr = ptr->next;
        }
    }
    return count; 
}

void hashClass::SetValue(std::string key, std::string data)                 //Add item to Database.
{
    int index = Hash(key);                                                  //Find bucket number
    std::vector<std::string> tokens;
    std::stringstream check1(data);
    std::string intermediate;

    while(getline(check1, intermediate, ','))                           
        tokens.push_back(intermediate); 

    if(this->store[index]->key == "NULL")                                   //If bucket empty
    {
        this->store[index]->key = key;                                      
        for(int i = 0;i < tokens.size(); i++)
        {
            std::string token = tokens[i];                                  //Add all the key value pairs to the map
            std::stringstream check2(token);
            std::string inter;
            getline(check2, inter, ':');
            std::string a = inter;
            getline(check2, inter, ':');
            std::string t = inter;
            this->store[index]->mp[a] = t;
            // std::cout << a << " is set for : " << key << std::endl;
        }
    }

    else
    {
        if(this->store[index]->key == key)
        {
            std::cout << "Given key present in table. Select new key." << std::endl;
            return; 
        }
        Key_Value* x = this->store[index];                          
        Key_Value* new_value = new Key_Value;
        new_value->key = key;
        for(int i = 0;i < tokens.size(); i++)
        {
            std::string token = tokens[i];
            std::stringstream check2(token);
            std::string inter;
            getline(check2, inter, ':');
            std::string a = inter;
            getline(check2, inter, ':');
            std::string t = inter;
            new_value->mp[a] = t;
            // std::cout << a << " is set for : " << key << endl;
        }
        new_value->next = NULL;
        while (x->next != NULL)                                                 //Go to last item of bucket to add onto this item
        {
            if(x->key == key)
            {
                std::cout << "Given key present in table. Select new key." << std::endl;
                return;
            }
            x = x->next;
        }
        x->next = new_value;
    }
}

void hashClass::PrintTable()                                                    //Print all items.
{
    int n;
    for(int i = 0; i < TableSize; i++)
    {
        Key_Value* ptr = this->store[i];

        if(ptr->key == "NULL")                                                  //No need to print if bucket is empty.
            continue;

        n = NumberOfItems(i);
        std::cout << "Number of values in bucket " << i << " are: " << n << std::endl;
        while(ptr->next!=NULL)
        {
            std::cout << "--------------------\n";
            //std::cout << "Index = " << i << std::endl;
            std::cout << ptr->key << std::endl;
            for(auto j: ptr->mp){
                std::cout << j.first << " : " << j.second << std::endl;
            }
            ptr = ptr->next;
        }   
        std::cout << "--------------------\n";                                              //Last item of bucket
        //std::cout << "Index = " << i << std::endl;
        std::cout << ptr->key << std::endl;
        for(auto j: ptr->mp)
            std::cout << j.first << " : " << j.second << std::endl;
        std::cout << "\n";
    }
}

bool hashClass::PrintBucket(std::string key)                                          //Print all items of a given bucket.
{
    int index = Hash(key);
    if(this->store[index]->key == "NULL")
    {
        std::cout << "Bucket is empty" << std::endl;
        return false;
    }
    Key_Value* p = this->store[index];
    while(p != NULL){
        if(p->key == key)
            break;
        p = p->next;
    }
    if(!p)                                                                          //Bucket has elements but key not there.
        return false;
        
    std::cout << "Bucket " << index << " info : " << std::endl;
    Key_Value* ptr = this->store[index];
    while(ptr != NULL)
    {
        std::cout << "-------------------\n";
        std::cout << ptr->key << std::endl;
        std::cout << "-------------------\n";
        for(auto i : ptr->mp)
        {
            std::cout << i.first << " : " << i.second << std::endl;
            std::cout << "-------------------\n";
        }
        ptr = ptr->next;
    }
    return true;
}

std::map<std::string, std::string> *hashClass::GetValue(std::string key)
{
    int index = Hash(key);                                          //Finding bucket
    bool found = false;

    Key_Value* ptr = this->store[index];
    while(ptr != NULL)
    {
        if(ptr->key == key)                                         //Searching in bucket
        {
            found = true;
            break;
        }
        ptr = ptr->next;
    }
    if(found)                                                       //Item found
    {
        /*std::cout << "Value " << key << " present in table at index " << index << "." << std::endl;
        // std::cout << "Data : \n";
        for(auto i : ptr->mp)
            std::cout << i.first << " : " << i.second << std::endl;
        std::cout << "-------------------\n";*/
        return &(ptr->mp);
    }
    else                                                            //Item not found
    {
        std::cout << key << " was not found in table.\n";
        return NULL;
    }
}

void hashClass::DeleteValue(std::string key)
{
    int index = Hash(key);
    Key_Value* p1;
    Key_Value* p2;
    Key_Value* del;

    if(this->store[index]->key == "NULL")                                               //Empty bucket
        std::cout << "Record to be deleted not present in the table." << std::endl;

    else if(this->store[index]->key == key && this->store[index]->next == NULL)               //Single element bucket and match
    {
        this->store[index]->key = "NULL";
        std::cout << "Record " << key << " deleted successfully." << std::endl;
    } 

    else if(this->store[index]->key == key && this->store[index]->next != NULL)               //Multi element bucket and match on 1st value
    {
        del = this->store[index];
        this->store[index] = this->store[index]->next;
        delete del; 
        std::cout << "Record " << key << " deleted successfully." << std::endl;
    }   
    else                                                                            //Multi element bucket and no match on 1st value
    {
        p2 = this->store[index];
        p1 = this->store[index]->next;

        while(p1 != NULL && p1->key != key)
        {
            p2 = p1;
            p1 = p1->next;
        }
        if(p1 == NULL)                                                              //No match in bucket
            std::cout << "Record to be deleted not present in the table." << std::endl;
        
        else
        {
            del = p1;
            p1 = p1->next;
            p2->next = p1;
            delete del;
            std::cout << "Record " << key << " deleted successfully." << std::endl;
        }
    }
}

void hashClass::UpdateValue(std::string key, std::string changeData)
{   
    int index = Hash(key);                                                  //Find bucket
    bool found = false;

    std::vector<std::string> tokens;
    std::stringstream check1(changeData);
    std::string intermediate;

    while(getline(check1, intermediate, ',')) 
        tokens.push_back(intermediate); 

    Key_Value* ptr = this->store[index];
    while(ptr != NULL)                                                      //Search in bucket
    {       
        if(ptr->key == key)
        {
            found = true;
            break;
        }
        ptr = ptr->next;
    }
    if(found)                                                               //Effect the changes as per the changeData string in the item
    {
        for(int i = 0;i < tokens.size(); i++)
        {
            std::string token = tokens[i];
            std::stringstream check2(token);
            std::string inter;
            getline(check2, inter, ':');
            std::string a = inter;
            getline(check2, inter, ':');
            std::string t = inter;
            this->store[index]->mp[a] = t;
        }
        std::cout << "Value was succesfully updated" << std::endl;
    }
    else                                                                     //If not found, create an item with those key value pairs
    {
        SetValue(key, changeData);
        std::cout << "New object was created." << std::endl;
    }
}

int hashClass::Hash(std::string key)
{
    int hash = 0;
    int index, i;

    for (i = 0; i< key.length(); i++)
        hash += (int)key[i];

    index = hash % TableSize;

    return index;
}
