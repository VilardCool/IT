#include "column.h"
using namespace std;

Column::Column(string name, string type)
{
    this->name = name;
    this->type = type;
}

string Column::GetType()
{
    return type;
}

string Column::GetName()
{
    return name;
}
