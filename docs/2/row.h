#ifndef ROW_H_INCLUDED
#define ROW_H_INCLUDED
#include <string>
#include <vector>
#include "column.h"

using namespace std;

struct Value
{
    int vInt = 0;
    double vDouble = 0;
    char vChar = NULL;
    string vString = "-";
    string vHex = "#000000";
    string vHexInvl[2] = {"#000000", "#000000"};
};

class Row{
    int num;
    vector<Value> values;
    vector<Column> columns;

public:
    Row(int num);
    void ChangeData(string value, int columnIndex);
    void UpdateColumns(Column c);
    void DeleteColumns(int i);
    string GetData(int columnIndex);
    int GetNum();
    ~Row(){};
};

#endif // ROW_H_INCLUDED
