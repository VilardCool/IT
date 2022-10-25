#include "pch.h"
#include "database.h"

Database::Database(String^ name)
{
    this->name = name;
}

void Database::AddTable(String^ name)
{
    Console::WriteLine("Adding table {0}", name);
    Table^ t = gcnew Table(name);
    tables->Add(t);
}

void Database::DeleteTable(String^ name)
{
    Console::WriteLine("Deleting table {0}", name);
    for (int i = 0; i < tables->Count; i++)
        if (tables[i]->GetName() == name)
            tables->Remove(tables[i]);
}

Table^ Database::GetTable(String^ name)
{
    Console::WriteLine("Returning table {0}", name);
    for (int i = 0; i < tables->Count; i++)
        if (tables[i]->GetName() == name)
            return tables[i];
}

String^ Database::GetName()
{
    Console::WriteLine("Returning table name");
    return name;
}

List<String^>^ Database::GetTables()
{
    Console::WriteLine("Returning all tables");
    List<String^>^ names = gcnew List<String^>();
    for (int i = 0; i < tables->Count; i++) names->Add(tables[i]->GetName());
    return names;
}

Table^ Database::JoinTables(String^ fTable, String^ sTable, String^ fColumn, String^ sColumn)
{
    Console::WriteLine("Joining tables");
    Table^ joinTable = gcnew Table("join");
    Table^ fTab;
    Table^ sTab;
    for (int i = 0; i < tables->Count; i++)
    {
        if (tables[i]->GetName() == fTable)
            fTab = tables[i];
        if (tables[i]->GetName() == sTable)
            sTab = tables[i];
    }
    List<String^>^ fColumns = fTab->GetColumns();
    List<String^>^ sColumns = sTab->GetColumns();
    int fCol=0, sCol=0;
    for (int i = 0; i < fColumns->Count; i++)
    {
        if (fColumns[i] == fColumn) fCol = i;
        joinTable->AddColumn(fColumns[i], fTab->GetColumn(fColumns[i])->GetType());
    }
    for (int i = 0; i < sColumns->Count; i++)
    {
        if (sColumns[i] == sColumn) sCol = i;
        joinTable->AddColumn(sColumns[i], sTab->GetColumn(sColumns[i])->GetType());
    }

    for (int i = 0; i < fTab->GetRows(); i++)
    {
        for (int j = 0; j < sTab->GetRows(); j++)
        {
            if (fTab->GetRow(i)->GetData(fCol) == sTab->GetRow(j)->GetData(sCol))
            {
                joinTable->AddRow();
                for (int k = 0; k < fColumns->Count; k++)
                    joinTable->GetRow(joinTable->GetRows() - 1)->ChangeData(fTab->GetRow(i)->GetData(k), k);
                for (int k = 0; k < sColumns->Count; k++)
                {
                    joinTable->GetRow(joinTable->GetRows() - 1)->ChangeData(sTab->GetRow(j)->GetData(k), k + fColumns->Count);
                }
            }
        }
    }

    return joinTable;
}