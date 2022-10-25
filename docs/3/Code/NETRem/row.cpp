#include "pch.h"
#include "row.h"

Row::Row(int num)
{
    this->num = num;
}

void Row::ChangeData(String^ value, int columnIndex)
{
    Console::WriteLine("Changing data");
    if (columns[columnIndex]->GetType() == "int") values[columnIndex] = Int32::Parse(value);
    if (columns[columnIndex]->GetType() == "double") values[columnIndex] = Double::Parse(value);
    if (columns[columnIndex]->GetType() == "char") values[columnIndex] = value[0];
    if (columns[columnIndex]->GetType() == "string") values[columnIndex] = value;
    if (columns[columnIndex]->GetType() == "hex") values[columnIndex] = value;
    if (columns[columnIndex]->GetType() == "hexInvl") values[columnIndex] = value;
}

void Row::UpdateColumns(Column^ c)
{
    columns->Add(c);
    values->Add(0);
}

void Row::DeleteColumns(int i)
{
    columns->Remove(columns[i]);
    values->Remove(values[i]);
}

String^ Row::GetData(int columnIndex)
{
    return values[columnIndex]->ToString();
}

int Row::GetNum()
{
    return num;
}