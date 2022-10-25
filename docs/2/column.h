#ifndef COLUMN_H_INCLUDED
#define COLUMN_H_INCLUDED
#include <string>

using namespace std;

class Column{
    string name;
    string type;

public:
    Column (string name, string type);
    string GetType();
    string GetName();
    ~Column(){};
};

#endif // COLUMN_H_INCLUDED
