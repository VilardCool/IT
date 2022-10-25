#pragma once
#include "database.h"

using namespace System;
using namespace System::Collections::Generic;

namespace NETRem {
    public ref class Manager : MarshalByRefObject
    {
        List<Database^>^ databases = gcnew List<Database^>();
    public:
        void AddDatabase(String^ name);
        Database^ GetDatabase(String^ name);
        List<String^>^ GetDatabases();
        void DeleteDatabase(String^ name);
        void DeleteDatabases();
    };
}
