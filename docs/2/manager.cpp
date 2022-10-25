#include "manager.h"
using namespace std;

void Manager::AddDatabase(string name)
{
    Database d(name);
    databases.push_back(d);
}

Database& Manager::GetDatabase(string name)
{
    for (int i=0; i<databases.size(); i++)
        if (databases[i].GetName() == name)
            return databases[i];
}

vector<string> Manager::GetDatabases()
{
    vector<string> names;
    for (int i=0; i<databases.size(); i++) names.push_back(databases[i].GetName());
    return names;
}

void Manager::DeleteDatabase(string name)
{
    for (int i=0; i<databases.size(); i++)
        if (databases[i].GetName() == name)
            databases.erase(databases.begin()+i);
}

void Manager::DeleteDatabases()
{
    databases.clear();
}
