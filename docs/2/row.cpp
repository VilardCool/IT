#include "row.h"
#include <iostream>
using namespace std;

Row::Row(int num)
{
    this->num = num;
}

void Row::ChangeData(string value, int columnIndex)
{
    if (columns[columnIndex].GetType() == "int") values[columnIndex].vInt = stoi(value);
    if (columns[columnIndex].GetType() == "double") values[columnIndex].vDouble = stod(value);
    if (columns[columnIndex].GetType() == "char") values[columnIndex].vChar = value[0];
    if (columns[columnIndex].GetType() == "string") values[columnIndex].vString = value;
    if (columns[columnIndex].GetType() == "hex") values[columnIndex].vHex = value;
    if (columns[columnIndex].GetType() == "hexInvl") {
        values[columnIndex].vHexInvl[0] = value.substr(0, 7);
        values[columnIndex].vHexInvl[1] = value.substr(7);
    }
}

void Row::UpdateColumns(Column c)
{
    columns.push_back(c);
    Value v;
    values.push_back(v);
}

void Row::DeleteColumns(int i)
{
    columns.erase(columns.begin()+i);
    values.erase(values.begin()+i);
}

string Row::GetData(int columnIndex)
{
    if (columns[columnIndex].GetType() == "int") return to_string(values[columnIndex].vInt);
    if (columns[columnIndex].GetType() == "double") return to_string(values[columnIndex].vDouble);
    if (columns[columnIndex].GetType() == "char") { string s{values[columnIndex].vChar}; return s;}
    if (columns[columnIndex].GetType() == "string") return values[columnIndex].vString;
    if (columns[columnIndex].GetType() == "hex") return values[columnIndex].vHex;
    if (columns[columnIndex].GetType() == "hexInvl") return values[columnIndex].vHexInvl[0]+values[columnIndex].vHexInvl[1];
}

int Row::GetNum()
{
    return num;
}
