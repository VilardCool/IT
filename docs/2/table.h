#ifndef TABLE_H_INCLUDED
#define TABLE_H_INCLUDED
#include <string>
#include <vector>
#include "column.h"
#include "row.h"

using namespace std;

class Table{
    string name;
    vector<Column> columns;
    vector<Row> rows;

public:
    Table(string name);
    void AddColumn(string name, string type);
    void AddRow();
    string GetName();
    Column& GetColumn(string name);
    Row& GetRow(int num);
    vector<string> GetColumns();
    int GetRows();
    void DeleteColumn(string name);
    void DeleteRow(int num);
    ~Table(){};
};

#endif // TABLE_H_INCLUDED
