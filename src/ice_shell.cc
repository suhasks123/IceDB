#include <iostream>
#include <fstream>
#include <string>
#include<readline/readline.h>

#include "ice.hpp"

std::string read_instr(){
    
    std::string inp;
    // std::cin >> inp; 
    inp = readline(">>");
    return inp;
}

std::vector<std::string> tokenize(std::string command){

    std::vector<std::string> tokens;
    int i, j;

    i = 0;
    while(command[i] == ' ')                                              //Truncate spaces from the beginning
        i++;     
    while(i < command.length() && command[i] != ' '){
        i++;
    }

    std::string func = command.substr(0, i);
    if(func != "open" || func != "close" || func != "set" || func != "get" || func != "update" || func != "delete" || func != "display")
        tokens.push_back(func);

    if(func == "open" || func == "close")                                  // open <database_name> or close <database_name>
    {
        while(i < command.length() && command[i] == ' ')
            i++;
        std::string name = command.substr(i);
        tokens.push_back(name);
        return tokens;
    }

    else if(func == "delete" || func == "get")                               // get <key> or delete <key> 
    {
        while(i < command.length() && command[i] == ' ')
            i++;
        std::string key = command.substr(i);
        tokens.push_back(key);
        return tokens;
    }

    else if(func == "display")                                               // Print entire database
        return tokens;

    else if(func == "update" || func == "set")                               // update / set <key>, <key-value pair 1>, <key-value pair 2>....
    {
        std::vector<std::string> kv;
        while(command[i] == ' ')
            i++;
        std::string remaining = command.substr(i);
        j = 0;
        while(j < remaining.length() && remaining[j] != ',')
            j++;
        std::string key = remaining.substr(0, j);                       // Get the key
        tokens.push_back(key);

        for(i = j + 1; i < remaining.length(); i++)                     // Get the key value pairs
        {
            while(i < remaining.length() && remaining[i] == ' ')
                i++;
            int k = i;
            while(i < remaining.length() && remaining[i] != ',')
                i++;
            std::string pair = remaining.substr(k, i - k);
            kv.push_back(pair);
        }
        std::string pairs = "";

        for(i = 0;i < kv.size(); i++)
        {
            std::string pair = kv[i];
            j = 0;
            while(j < pair.length() && pair[j] == ' ')
                j++;
            int ks = j;                                                 // Key start index
            while(j < pair.length() && pair[j] != ':')
                j++;
            std::string key = pair.substr(ks, j - ks);                  // From start index to length of the substr

            int l = key.length();
            while(key[l - 1] == ' ')
                l--;
            key = key.substr(0, l);

            while(j < pair.length() && pair[j] == ' ')
                j++;
            std::string value = pair.substr(j + 1);
            pairs += key + ":" + value + ",";
        }
        pairs = pairs.substr(0, pairs.length() - 1);
        tokens.push_back(pairs);
        return tokens;
    }

    else 
        return {};
}

int main()
{
    while(true)
    {
        // The instruction read

        std::string command = read_instr();
        if(command.length() < 3)
            continue;

        // The instruction parse - Tokenisation

        int i;
        std::vector<std::string> tokens = tokenize(command);
        if(!tokens.size())
        {
            std::cout << "Invalid command" << std::endl;
            continue;
        }

        /* Uncomment for testing the tokenization */

        // for(auto i : tokens)                                                 
        //     std::cout << i << std::endl;

        fflush(stdin);

        // The instruction processing - Call the library

        
    }
    return 0;
}