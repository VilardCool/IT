#ifndef MANAGER_H_INCLUDED
#define MANAGER_H_INCLUDED
#include <string>
#include <vector>
#include "database.h"

using namespace std;

class Manager{
    vector<Database> databases;

public:
    void AddDatabase(string name);
    Database& GetDatabase(string name);
    vector<string> GetDatabases();
    void DeleteDatabase(string name);
    void DeleteDatabases();
    ~Manager(){};
};

#endif // MANAGER_H_INCLUDED
