#pragma once
#include "column.h"
#include "row.h"

using namespace System;
using namespace System::Collections::Generic;

public ref class Table : MarshalByRefObject
{
    String^ name;
    List<Column^>^ columns = gcnew List<Column^>();
    List<Row^>^ rows = gcnew List<Row^>();

public:
    Table(String^ name);
    void AddColumn(String^ name, String^ type);
    void AddRow();
    String^ GetName();
    Column^ GetColumn(String^ name);
    Row^ GetRow(int num);
    List<String^>^ GetColumns();
    int GetRows();
    void DeleteColumn(String^ name);
    void DeleteRow(int num);
};