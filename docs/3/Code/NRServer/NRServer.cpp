#include "pch.h"
using namespace System;
using namespace System::Runtime::Remoting;

[STAThread]
int main()
{
    RemotingConfiguration::Configure("..\\NRServer\\app.config", false);
    Console::WriteLine("Start server");
    Console::ReadLine();

    return 0;
}