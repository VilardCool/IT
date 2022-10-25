#pragma once
#include "table.h"

using namespace System;
using namespace System::Collections::Generic;

public ref class Database : MarshalByRefObject
{
    String^ name;
    List<Table^>^ tables = gcnew List<Table^>();

public:
    Database(String^ name);
    void AddTable(String^ name);
    void DeleteTable(String^ name);
    Table^ JoinTables(String^ fTable,
        String^ sTable,
        String^ fColumn,
        String^ sColumn);
    Table^ GetTable(String^ name);
    String^ GetName();
    List<String^>^ GetTables();
};
