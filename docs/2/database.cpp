#include "database.h"
using namespace std;

Database::Database(string name)
{
    this->name = name;
}

void Database::AddTable(string name)
{
    Table t(name);
    tables.push_back(t);
}

void Database::DeleteTable(string name)
{
    for (int i=0; i<tables.size(); i++)
        if (tables[i].GetName() == name)
            tables.erase(tables.begin()+i);
}

Table& Database::GetTable(string name)
{
    for (int i=0; i<tables.size(); i++)
        if (tables[i].GetName() == name)
            return tables[i];
}

string Database::GetName()
{
    return name;
}

vector<string> Database::GetTables()
{
    vector<string> names;
    for (int i=0; i<tables.size(); i++) names.push_back(tables[i].GetName());
    return names;
}

Table Database::JoinTables(string fTable, string sTable, string fColumn, string sColumn)
{
    Table joinTable("join"), fTab(fTable), sTab(sTable);
    for (int i=0; i<tables.size(); i++)
    {
        if (tables[i].GetName() == fTable)
            fTab = tables[i];
        if (tables[i].GetName() == sTable)
            sTab = tables[i];
    }
    vector<string> fColumns = fTab.GetColumns();
    vector<string> sColumns = sTab.GetColumns();
    int fCol, sCol;
    for (int i=0; i<fColumns.size(); i++)
    {
        if (fColumns[i] == fColumn) fCol = i;
        joinTable.AddColumn(fColumns[i], fTab.GetColumn(fColumns[i]).GetType());
    }
    for (int i=0; i<sColumns.size(); i++)
    {
        if (sColumns[i] == sColumn) sCol = i;
        joinTable.AddColumn(sColumns[i], sTab.GetColumn(sColumns[i]).GetType());
    }

    for (int i=0; i<fTab.GetRows(); i++)
    {
        for (int j=0; j<sTab.GetRows(); j++)
        {
            if (fTab.GetRow(i).GetData(fCol) == sTab.GetRow(j).GetData(sCol))
            {
                joinTable.AddRow();
                for (int k=0; k<fColumns.size(); k++)
                    joinTable.GetRow(joinTable.GetRows()-1).ChangeData(fTab.GetRow(i).GetData(k), k);
                for (int k=0; k<sColumns.size(); k++)
                {
                    joinTable.GetRow(joinTable.GetRows()-1).ChangeData(sTab.GetRow(j).GetData(k), k+fColumns.size());
                }
            }
        }
    }

    return joinTable;
}
