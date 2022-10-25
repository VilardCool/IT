#pragma once

using namespace System;
using namespace System::Collections::Generic;

public ref class Column : MarshalByRefObject
{
    String^ name;
    String^ type;

public:
    Column(String^ name, String^ type);
    String^ GetType();
    String^ GetName();
};