#pragma once
#include "column.h"

using namespace System;
using namespace System::Collections::Generic;

public ref class Row : MarshalByRefObject
{
    int num;
    List<Object^>^ values = gcnew List<Object^>();
    List<Column^>^ columns = gcnew List<Column^>();

public:
    Row(int num);
    void ChangeData(String^ value, int columnIndex);
    void UpdateColumns(Column^ c);
    void DeleteColumns(int i);
    String^ GetData(int columnIndex);
    int GetNum();
};
