#ifndef DATABASE_H_INCLUDED
#define DATABASE_H_INCLUDED
#include <string>
#include <vector>
#include "table.h"

using namespace std;

class Database{
    string name;
    vector<Table> tables;

public:
    Database(string name);
    void AddTable(string name);
    void DeleteTable(string name);
    Table JoinTables(string fTable,
                    string sTable,
                    string fColumn,
                    string sColumn);
    Table& GetTable(string name);
    string GetName();
    vector<string> GetTables();
    ~Database(){};
};

#endif // DATABASE_H_INCLUDED
