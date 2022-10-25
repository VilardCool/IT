#include "table.h"
#include <iostream>
using namespace std;

Table::Table(string name)
{
    this->name = name;
}

void Table::AddColumn(string name, string type)
{
    Column c(name, type);
    columns.push_back(c);
    for (int i=0; i<rows.size(); i++) rows[i].UpdateColumns(c);
}

void Table::AddRow()
{
    Row r(rows.size());
    for (int i=0; i<columns.size(); i++)
        r.UpdateColumns(columns[i]);
    rows.push_back(r);
}

string Table::GetName()
{
    return name;
}

Column& Table::GetColumn(string name)
{
    for (int i=0; i<columns.size(); i++)
        if (columns[i].GetName() == name)
            return columns[i];
}

vector<string> Table::GetColumns()
{
    vector<string> names;
    for (int i=0; i<columns.size(); i++)
        names.push_back(columns[i].GetName());
    return names;
}

Row& Table::GetRow(int num)
{
    return rows[num];
}

int Table::GetRows()
{
    return rows.size();
}

void Table::DeleteColumn(string name)
{
    for (int i=0; i<columns.size(); i++)
        if (columns[i].GetName() == name)
        {
            for (int j=0; j<rows.size(); j++) rows[j].DeleteColumns(i);
            columns.erase(columns.begin()+i);
        }
}

void Table::DeleteRow(int num)
{
    rows.erase(rows.begin()+num);
}
