#include "pch.h"
#include "NETRem.h"

using namespace NETRem;

void Manager::AddDatabase(String^ name)
{
    Console::WriteLine("Adding database {0}", name);
    Database^ d = gcnew Database(name);
    databases->Add(d);
}

Database^ Manager::GetDatabase(String^ name)
{
    Console::WriteLine("Returning database {0}", name);
    for (int i = 0; i < databases->Count; i++)
        if (databases[i]->GetName() == name)
            return databases[i];
}

List<String^>^ Manager::GetDatabases()
{
    Console::WriteLine("Returning all databases");
    List<String^>^ names = gcnew List<String^>();
    for (int i = 0; i < databases->Count; i++)
    {
        names->Add(databases[i]->GetName());
    }
    return names;
}

void Manager::DeleteDatabase(String^ name)
{
    Console::WriteLine("Deleting database {0}", name);
    for (int i = 0; i < databases->Count; i++)
        if (databases[i]->GetName() == name)
            databases->Remove(databases[i]);
}

void Manager::DeleteDatabases()
{
    Console::WriteLine("Deleting all databases");
    databases->Clear();
}
