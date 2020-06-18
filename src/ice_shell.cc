#include <iostream>
#include <fstream>
#include <string>
#include<readline/readline.h>

#include "ice.hpp"

IceDB *ice;
//IceDB *global_metadata;
bool openflag = 0;
std::string open_db = "";

// Functions
std::string read_instr();
std::vector<std::string> tokenize(std::string command);
void processing(std::vector<std::string> tokens);
void display_help();

int main()
{
    //global_metadata = new IceDB();
    //global_metadata->Open("global_metadata");
    std::cout << "IceDB version 0.1\n";
    std::cout << "Run 'help' for the list of shell commands\n";
    std::cout << "Make sure that the shell is run as root. If not, exit the shell and run as root\n";
    while(true)
    {
        // The instruction read
        std::string command = read_instr();
        if(command.length() < 3)
            continue;

        // The instruction parse - Tokenisation
        int i;
        std::vector<std::string> tokens = tokenize(command);
        /*if(!tokens.size() && (tokens[0] != "exit" && tokens[0] !=
            "quit" && tokens[0] != "help" && tokens[0] != "list"))*/
        if(tokens.size() <= 0)
        {
            std::cout << "Invalid command" << std::endl;
            continue;
        }

        fflush(stdin);

        // The instruction processing - Call the library
        processing(tokens);        
    }
    return 0;
}

std::string read_instr()
{
    std::string current_db = open_db;
    if (current_db == "")
        current_db = ":>> ";
    else
        current_db += " :>> ";
    std::string inp;
    const char *prompt = current_db.c_str();
    inp = readline(prompt);
    return inp;
}

std::vector<std::string> tokenize(std::string command)
{
    std::vector<std::string> tokens;
    int i, j;

    i = 0;

    //Truncate spaces from the beginning
    while(command[i] == ' ')
        i++;     
    while(i < command.length() && command[i] != ' '){
        i++;
    }

    std::string func = command.substr(0, i);
    if(func != "open" || func != "close" || func != "set" || func != "get" ||
       func != "update" || func != "delete" || func != "display" || func != "drop" ||
       func != "exit" || func != "quit" || func != "help" || func != "list")
        tokens.push_back(func);

    if((func != "open" && !openflag) && (func != "exit" && func != "quit" && func != "help" && func != "list"))
    {
        std::cout << "No database is open. Open first" << std::endl;
        return {};
    }

    if(func == "open" && openflag)
    {
        std::cout << "Close current database first." << std::endl;
        return {};
    }

    // open <database_name> or close <database_name>
    if(func == "open" || func == "close" || func == "drop")
    {
        while(i < command.length() && command[i] == ' ')
            i++;
        std::string name = command.substr(i);
        tokens.push_back(name);
        return tokens;
    }

    // get <key> or delete <key>
    else if(func == "delete" || func == "get")
    {
        while(i < command.length() && command[i] == ' ')
            i++;
        std::string key = command.substr(i);
        tokens.push_back(key);
        return tokens;
    }

    // Print entire database
    else if(func == "display"){
        while(i < command.length() && command[i] == ' ')
            i++;
        
        //Print All
        if(i == command.length())
            return tokens;
        std::string key = command.substr(i);
        tokens.push_back(key);

        //Print bucket
        return tokens;
    }

    // update / set <key>, <key-value pair 1>, <key-value pair 2>....
    else if(func == "update" || func == "set")
    {
        std::vector<std::string> kv;
        while(command[i] == ' ')
            i++;
        std::string remaining = command.substr(i);
        j = 0;
        while(j < remaining.length() && remaining[j] != ',')
            j++;

        // Get the key
        std::string key = remaining.substr(0, j);
        tokens.push_back(key);

        // Get the key value pairs
        for(i = j + 1; i < remaining.length(); i++)
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

            // Key start index
            int ks = j;
            while(j < pair.length() && pair[j] != ':')
                j++;

            // From start index to length of the substr
            std::string key = pair.substr(ks, j - ks);

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

    else if (func == "exit" || func == "quit" || func == "help" || func == "list")
    {
        tokens.push_back(func);
        return tokens;
    }

    else 
        return {};
}

void processing(std::vector<std::string> tokens)
{
    if(tokens[0] == "open")
    {
        openflag = true;
        open_db = tokens[1];
        ice = new IceDB();
        ice->Open(tokens[1]);
        std::string database_name = tokens[1];
        std::string database_pair = "name:" + database_name;
        //global_metadata->Set(database_name,database_pair);
    }
    else if(tokens[0] == "close")
    {
        if(tokens[1] != open_db)
        {
            std::cout << "Invalid database name to close" << std::endl;
            return;
        }
        else
        {
            openflag = false;
            open_db = "";
        }
        ice->Close(tokens[1]);
        open_db = "";
        delete ice;
        //global_metadata->Close("global_metadata");
    }
    else if(tokens[0] == "display")
    {
        if(tokens.size() == 1)
            ice->PrintAll();
        else
            ice->PrintKeyBucket(tokens[1]);
    }
    else if(tokens[0] == "set")
        ice->Set(tokens[1], tokens[2]);
    else if(tokens[0] == "get")
    {
        std::map<std::string, std::string> *data = ice->Get(tokens[1]);
        std::cout << "Value " << tokens[1] << " present in table\n";
        for(auto i : *data)
            std::cout << i.first << " : " << i.second << std::endl;
        std::cout << "-------------------\n";
    }
    else if(tokens[0] == "update")
        ice->Update(tokens[1], tokens[2]);
    else if(tokens[0] == "delete")
        ice->Delete(tokens[1]);
    else if(tokens[0] == "drop")
    {
        ice->Drop(tokens[1]);
        //global_metadata->Delete(tokens[1]);
        ice->Close(tokens[1]);
    }
    else if(tokens[0] == "help")
        display_help();
    //else if(tokens[0] == "list")
        //global_metadata->PrintAll();
    else if(tokens[0] == "exit" || tokens[0] == "quit")
    {
        //global_metadata->Close("global_metadata");
        exit(0);
    }
}

void display_help()
{
    std::cout << "\nList of commands in the current shell:\n";
    std::cout << "1. open <database-name> : Open a database\n";
    std::cout << "2. close <database-name> : Close a database\n";
    std::cout << "3. get <master-key> : Get an entry based on the master key\n";
    std::cout << "4. set <master-key>, <key>:<value>, <key>:<value>.... : Insert an entry\n";
    std::cout << "5. update <master-key>, <key>:<value>, <key>:<value>.... : Update an entry\n";
    std::cout << "6. delete <master-key> : Delete an entry based in the master key\n";
    std::cout << "7. drop <database-name> : Drop, i.e, delete a database\n";
    std::cout << "8. list : List all the existing databases on the current machine\n";
    std::cout << "9. exit / quit : Exit the shell\n";
    std::cout << "10. help : Display help\n";
    std::cout << "Note: Changes to the database will not be saved unless the database is closed.\n\n";
}