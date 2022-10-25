#include "pch.h"
#include "column.h"

Column::Column(String^ name, String^ type)
{
    this->name = name;
    this->type = type;
}

String^ Column::GetType()
{
    return type;
}

String^ Column::GetName()
{
    return name;
}