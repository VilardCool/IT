#include "pch.h"
#include "table.h"

Table::Table(String^ name)
{
    this->name = name;
}

void Table::AddColumn(String^ name, String^ type)
{
    Console::WriteLine("Adding column {0}", name);
    Column^ c = gcnew Column(name, type);
    columns->Add(c);
    for (int i = 0; i < rows->Count; i++) rows[i]->UpdateColumns(c);
}

void Table::AddRow()
{
    Console::WriteLine("Adding row");
    Row^ r = gcnew Row(rows->Count);
    for (int i = 0; i < columns->Count; i++)
        r->UpdateColumns(columns[i]);
    rows->Add(r);
}

String^ Table::GetName()
{
    Console::WriteLine("Returning table name");
    return name;
}

Column^ Table::GetColumn(String^ name)
{
    Console::WriteLine("Returning column {0}", name);
    for (int i = 0; i < columns->Count; i++)
        if (columns[i]->GetName() == name)
            return columns[i];
}

List<String^>^ Table::GetColumns()
{
    Console::WriteLine("Returning all columns");
    List<String^>^ names = gcnew List<String^>();
    for (int i = 0; i < columns->Count; i++)
        names->Add(columns[i]->GetName());
    return names;
}

Row^ Table::GetRow(int num)
{
    Console::WriteLine("Returning row");
    return rows[num];
}

int Table::GetRows()
{
    Console::WriteLine("Returning amount of rows");
    return rows->Count;
}

void Table::DeleteColumn(String^ name)
{
    Console::WriteLine("Deleting column {0}", name);
    for (int i = 0; i < columns->Count; i++)
        if (columns[i]->GetName() == name)
        {
            for (int j = 0; j < rows->Count; j++) rows[j]->DeleteColumns(i);
            columns->Remove(columns[i]);
        }
}

void Table::DeleteRow(int num)
{
    Console::WriteLine("Deleting row");
    rows->Remove(rows[num]);
}