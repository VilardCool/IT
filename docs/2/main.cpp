#include <iostream>
#include "manager.h"
#include <wx/wxprec.h>
#include <wx/frame.h>
#include <wx/grid.h>
#include <wx/textctrl.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/wfstream.h>
#include <wx/textfile.h>
#include <sstream>
#include <cassert>

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

using namespace std;

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

class MyFrame : public wxFrame
{
public:
    MyFrame();

private:
    void OnOpen(wxCommandEvent& event);
    void OnSave(wxCommandEvent& event);
    void OnJoin(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnDatabaseSelected(wxCommandEvent& event);
    void OnAddDatabaseView(wxCommandEvent& event);
    void OnAddDatabase(wxCommandEvent& event);
    void OnDeleteDatabase(wxCommandEvent& event);
    void OnTableSelected(wxCommandEvent& event);
    void OnAddTableView(wxCommandEvent& event);
    void OnAddTable(wxCommandEvent& event);
    void OnDeleteTable(wxCommandEvent& event);
    void OnAddColumnView(wxCommandEvent& event);
    void OnAddColumn(wxCommandEvent& event);
    void OnDeleteColumn(wxCommandEvent& event);
    void OnAddRow(wxCommandEvent& event);
    void OnDeleteRow(wxCommandEvent& event);
    void OnGridChanged(wxGridEvent& event);
    void OnJoinDatabaseSelected(wxCommandEvent& event);
    void OnJoinFTableSelected(wxCommandEvent& event);
    void OnJoinSTableSelected(wxCommandEvent& event);
    void OnJoinFColumnSelected(wxCommandEvent& event);
    void OnJoinAllSelected(wxCommandEvent& event);
};

enum
{
    ID_Open = 1,
    ID_Save,
    ID_Join,
    ID_DatabaseSelected,
    ID_TableSelected,
    ID_AddDatabaseName,
    ID_AddDatabaseButton,
    ID_AddDatabaseViewButton,
    ID_DeleteDatabaseButton,
    ID_AddTableName,
    ID_AddTableButton,
    ID_AddTableViewButton,
    ID_DeleteTableButton,
    ID_AddColumnName,
    ID_AddColumnViewButton,
    ID_AddColumnButton,
    ID_DeleteColumnButton,
    ID_ColumnSelected,
    ID_AddRowButton,
    ID_DeleteRowButton,
    ID_GridChanged,
    ID_JoinDatabaseSelected,
    ID_JoinFTableSelected,
    ID_JoinFColumnSelected,
    ID_JoinSTableSelected,
    ID_JoinSColumnSelected,
    ID_JoinAllButton
};

wxIMPLEMENT_APP(MyApp);
wxArrayString databasesName;
wxArrayString tablesName;
Manager m;

wxWindow *window;
wxComboBox *databaseBox;
wxComboBox *tableBox;
wxGrid *grid;
wxButton *addDatabase;
wxTextCtrl *addDatabaseName;
wxStaticText *databaseNameUsed;
wxButton *addTable;
wxTextCtrl *addTableName;
wxStaticText *tableNameUsed;

wxComboBox *columnBox;
wxButton *addColumn;
wxTextCtrl *addColumnName;
wxStaticText *columnNameUsed;
wxArrayString columnName;

wxDialog *joinTablesDialog;
wxComboBox *joinDatabaseBox;
wxComboBox *joinFTableBox;
wxComboBox *joinSTableBox;
wxComboBox *joinFColumnBox;
wxComboBox *joinSColumnBox;
wxButton *joinAll;

template <typename T>
struct ValueT
{
    T value;
};

void TestColumn()
{
    Manager mTest;
    mTest.AddDatabase("dTest");
    mTest.GetDatabase("dTest").AddTable("tTest");
    mTest.GetDatabase("dTest").GetTable("tTest").AddColumn("cTest", "int");
    assert(string(mTest.GetDatabase("dTest").GetTable("tTest").GetColumn("cTest").GetType()) == "int");
    cout<<"Column Test: OK\n";
}

void TestData()
{
    Manager mTest;
    mTest.AddDatabase("dTest");
    mTest.GetDatabase("dTest").AddTable("tTest");
    mTest.GetDatabase("dTest").GetTable("tTest").AddColumn("cTest", "int");
    mTest.GetDatabase("dTest").GetTable("tTest").AddRow();
    mTest.GetDatabase("dTest").GetTable("tTest").GetRow(0).ChangeData("5", 0);
    assert(string(mTest.GetDatabase("dTest").GetTable("tTest").GetRow(0).GetData(0)) == "5");
    cout<<"Data Test: OK\n";
}

void TestOperation()
{
    Manager mTest;
    mTest.AddDatabase("dTest");
    mTest.GetDatabase("dTest").AddTable("tFTest");
    mTest.GetDatabase("dTest").AddTable("tSTest");
    mTest.GetDatabase("dTest").GetTable("tFTest").AddColumn("cFTest", "int");
    mTest.GetDatabase("dTest").GetTable("tFTest").AddRow();
    mTest.GetDatabase("dTest").GetTable("tSTest").AddColumn("cSTest", "int");
    mTest.GetDatabase("dTest").GetTable("tSTest").AddRow();
    mTest.GetDatabase("dTest").GetTable("tFTest").GetRow(0).ChangeData("5", 0);
    mTest.GetDatabase("dTest").GetTable("tSTest").GetRow(0).ChangeData("5", 0);
    Table resT = mTest.GetDatabase("dTest").JoinTables("tFTest", "tSTest", "cFTest", "cSTest");
    assert(string(resT.GetRow(0).GetData(1)) == "5");
    cout<<"Operation Test: OK\n";
}

bool MyApp::OnInit()
{
    TestColumn();
    TestData();
    TestOperation();

    m.AddDatabase("1");
    m.AddDatabase("asd");
    Database& a = m.GetDatabase("1");
    a.AddTable("1");
    a.AddTable("2");
    a.AddTable("3");
    Table& t = a.GetTable("1");
    Table& t1 = a.GetTable("2");
    t.AddColumn("1", "int");
    t1.AddColumn("11", "int");
    t1.AddColumn("s", "string");
    t.AddColumn("2", "double");
    t.AddColumn("3", "char");
    t.AddColumn("4", "string");
    t.AddColumn("5", "hex");
    t.AddColumn("6", "hexInvl");
    t.AddRow();
    t.AddRow();
    t.AddRow();
    t.AddRow();
    t1.AddRow();
    Row& r = t.GetRow(0);
    Row& r1 = t.GetRow(1);
    Row& r2 = t1.GetRow(0);
    r.ChangeData("5", 0);
    r.ChangeData("5.5", 1);
    r.ChangeData("a", 2);
    r.ChangeData("abc", 3);
    r.ChangeData("#98F1A2", 4);
    r.ChangeData("#A1A1A1#BBBBBB", 5);
    r1.ChangeData("5", 0);
    r2.ChangeData("5", 0);
    r2.ChangeData("aaa", 1);

    columnName.Add("int");
    columnName.Add("double");
    columnName.Add("char");
    columnName.Add("string");
    columnName.Add("hex");
    columnName.Add("hexInvl");

    vector<string> databases = m.GetDatabases();

    for (int i=0; i<databases.size(); i++)
        databasesName.Add(databases[i]);

    MyFrame *frame = new MyFrame();
    frame->Show(true);

    return true;
}

MyFrame::MyFrame() : wxFrame(NULL, wxID_ANY, "DBMS", wxDefaultPosition, wxSize(1000, 600))
{
    window = new wxWindow(this, wxID_ANY);

    wxMenu *menuFile = new wxMenu;
    menuFile->Append(ID_Open, "Open", "Open file");
    menuFile->Append(ID_Save, "Save", "Save file");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);

    wxMenu *menuJoin = new wxMenu;
    menuJoin->Append(ID_Join, "Join", "Join tables");

    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuJoin, "&Operation");

    SetMenuBar( menuBar );

    CreateStatusBar();

    Bind(wxEVT_MENU, &MyFrame::OnOpen, this, ID_Open);
    Bind(wxEVT_MENU, &MyFrame::OnSave, this, ID_Save);
    Bind(wxEVT_MENU, &MyFrame::OnJoin, this, ID_Join);
    Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);

    databaseBox = new wxComboBox(window, ID_DatabaseSelected, wxEmptyString, wxDefaultPosition, wxSize(110, 20), databasesName, wxCB_READONLY);
    tableBox = new wxComboBox(window, ID_TableSelected, wxEmptyString, wxPoint(0,30), wxSize(110, 20), tablesName, wxCB_READONLY);

    wxButton *addDatabaseView = new wxButton(window, ID_AddDatabaseViewButton, "+", wxPoint(120, 0), wxSize(20, 20));
    wxButton *deleteDatabase = new wxButton(window, ID_DeleteDatabaseButton, "-", wxPoint(150, 0), wxSize(20, 20));
    wxButton *addTableView = new wxButton(window, ID_AddTableViewButton, "+", wxPoint(120, 30), wxSize(20, 20));
    wxButton *deleteTable = new wxButton(window, ID_DeleteTableButton, "-", wxPoint(150, 30), wxSize(20, 20));

    wxStaticText *rowsEdit = new wxStaticText(window, wxID_ANY, "Rows:", wxPoint(500,0));
    wxButton *addRow = new wxButton(window, ID_AddRowButton, "+", wxPoint(540, 0), wxSize(20, 20));
    wxButton *deleteRow = new wxButton(window, ID_DeleteRowButton, "-", wxPoint(540, 30), wxSize(20, 20));

    wxStaticText *columnsEdit = new wxStaticText(window, wxID_ANY, "Columns:", wxPoint(580,0));
    wxButton *addColumnView = new wxButton(window, ID_AddColumnViewButton, "+", wxPoint(640, 0), wxSize(20, 20));
    wxButton *deleteColumn = new wxButton(window, ID_DeleteColumnButton, "-", wxPoint(640, 30), wxSize(20, 20));

    grid = new wxGrid(window, ID_GridChanged, wxPoint(0, 60), wxSize(930, 440));
    grid->CreateGrid(1, 1);

    databaseBox->Bind(wxEVT_COMBOBOX, &MyFrame::OnDatabaseSelected, this, ID_DatabaseSelected);
    tableBox->Bind(wxEVT_COMBOBOX, &MyFrame::OnTableSelected, this, ID_TableSelected);
    addDatabaseView->Bind(wxEVT_BUTTON, &MyFrame::OnAddDatabaseView, this, ID_AddDatabaseViewButton);
    deleteDatabase->Bind(wxEVT_BUTTON, &MyFrame::OnDeleteDatabase, this, ID_DeleteDatabaseButton);
    addTableView->Bind(wxEVT_BUTTON, &MyFrame::OnAddTableView, this, ID_AddTableViewButton);
    deleteTable->Bind(wxEVT_BUTTON, &MyFrame::OnDeleteTable, this, ID_DeleteTableButton);

    addColumnView->Bind(wxEVT_BUTTON, &MyFrame::OnAddColumnView, this, ID_AddColumnViewButton);
    deleteColumn->Bind(wxEVT_BUTTON, &MyFrame::OnDeleteColumn, this, ID_DeleteColumnButton);
    addRow->Bind(wxEVT_BUTTON, &MyFrame::OnAddRow, this, ID_AddRowButton);
    deleteRow->Bind(wxEVT_BUTTON, &MyFrame::OnDeleteRow, this, ID_DeleteRowButton);

    grid->Bind(wxEVT_GRID_CELL_CHANGED, &MyFrame::OnGridChanged, this, ID_GridChanged);
}

void MyFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}

void RenderGrid()
{
    grid->ClearGrid();
    if (grid->GetNumberCols() != 0) grid->DeleteCols(0, grid->GetNumberCols());
    if (grid->GetNumberRows() != 0) grid->DeleteRows(0, grid->GetNumberRows());
    vector<string> columns = m.GetDatabase(string(databaseBox->GetStringSelection())).GetTable(string(tableBox->GetStringSelection())).GetColumns();
    int rows = m.GetDatabase(string(databaseBox->GetStringSelection())).GetTable(string(tableBox->GetStringSelection())).GetRows();
    grid->AppendCols(columns.size());
    grid->AppendRows(rows);
    for (int i=0; i<columns.size(); i++)
        grid->SetColLabelValue(i, columns[i]);

    for (int i=0; i<rows; i++)
        for (int j=0; j<columns.size(); j++)
            grid->SetCellValue(i, j, m.GetDatabase(string(databaseBox->GetStringSelection())).GetTable(string(tableBox->GetStringSelection())).GetRow(i).GetData(j));
}

void RenderFrame()
{
    vector<string> names = m.GetDatabases();
    databaseBox->Clear();
    for (int i=0; i<names.size(); i++)
        databaseBox->Append(names[i]);
}

void MyFrame::OnOpen(wxCommandEvent& event)
{
    if (wxMessageBox(_("Not saved data will be lost! Proceed?"), _("Please confirm"), wxICON_QUESTION | wxYES_NO, this) == wxNO )
        return;

    wxFileDialog openFileDialog(this, _("Open file"), "", "", "*.txt", wxFD_OPEN|wxFD_FILE_MUST_EXIST);
    if (openFileDialog.ShowModal() == wxID_CANCEL) return;

    wxTextFile file;
    file.Open(openFileDialog.GetPath());

    m.DeleteDatabases();
    string curLine;
    string database;
    string table;
    string columns;
    string value;

    curLine = file.GetFirstLine();

    while (!file.Eof())
    {
        if(curLine.substr(0, 9) == "Database:")
        {
            database = curLine.substr(10);
            m.AddDatabase(database);
        }
        else if(curLine.substr(0, 6) == "Table:")
        {
            table = curLine.substr(7);
            m.GetDatabase(database).AddTable(table);
        }
        else if(curLine.substr(0, 8) == "Columns:")
        {
            string types;
            string type;
            types = file.GetNextLine();
            stringstream curStream(curLine.substr(9));
            stringstream curType(types);
            while(getline(curStream, columns, ' ') && getline(curType, type, ' '))
                m.GetDatabase(database).GetTable(table).AddColumn(columns, type);
        }
        else if(curLine == "\n") {continue;}
        else
        {
            stringstream curStream(curLine);
            m.GetDatabase(database).GetTable(table).AddRow();
            int columnIndex=0;
            while(getline(curStream, value, ' '))
            {
                m.GetDatabase(database).GetTable(table).GetRow(m.GetDatabase(database).GetTable(table).GetRows()-1).ChangeData(value, columnIndex);
                columnIndex++;
            }
        }
        curLine = file.GetNextLine();
    }
    RenderFrame();
}

void MyFrame::OnSave(wxCommandEvent& event)
{
    wxFileDialog saveFileDialog(this, "Save file", "", "", "*.txt", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
    if (saveFileDialog.ShowModal() == wxID_CANCEL) return;

    vector<string> databases = m.GetDatabases();

    wxFile file( saveFileDialog.GetPath(), wxFile::write);
    if(file.IsOpened())
    {
        for (int i=0; i<databases.size(); i++)
        {
            file.Write("Database: "+databases[i]+"\n");
            vector<string> tables = m.GetDatabase(databases[i]).GetTables();
            for (int j=0; j<tables.size(); j++)
            {
                file.Write("Table: "+tables[j]+"\n");
                vector<string> columns = m.GetDatabase(databases[i]).GetTable(tables[j]).GetColumns();
                if (columns.size() == 0) continue;
                file.Write("Columns: ");
                for (int k=0; k<columns.size(); k++) file.Write(columns[k]+" ");
                file.Write("\n");
                for (int k=0; k<columns.size(); k++)
                    file.Write(m.GetDatabase(databases[i]).GetTable(tables[j]).GetColumn(columns[k]).GetType()+" ");
                file.Write("\n");
                int rows = m.GetDatabase(databases[i]).GetTable(tables[j]).GetRows();
                for (int k=0; k<rows; k++)
                {
                    for (int l=0; l<columns.size(); l++)
                    {
                        file.Write(m.GetDatabase(databases[i]).GetTable(tables[j]).GetRow(k).GetData(l)+" ");
                    }
                    file.Write("\n");
                }
                file.Write("\n");
            }
        }
    }
}

void MyFrame::OnJoin(wxCommandEvent& event)
{
    joinTablesDialog = new wxDialog(this, wxID_ANY, "Join tables", wxDefaultPosition, wxSize(230, 150));
    joinTablesDialog->Show(true);
    wxArrayString emptyArrayString;

    joinDatabaseBox = new wxComboBox(joinTablesDialog, ID_JoinDatabaseSelected, wxEmptyString, wxDefaultPosition, wxSize(110, 20), emptyArrayString, wxCB_READONLY);
    vector<string> databases = m.GetDatabases();
    for (int i=0; i<databases.size(); i++)
        joinDatabaseBox->Append(databases[i]);

    joinFTableBox = new wxComboBox(joinTablesDialog, ID_JoinFTableSelected, wxEmptyString, wxPoint(0,30), wxSize(110, 20), emptyArrayString, wxCB_READONLY);
    joinFColumnBox = new wxComboBox(joinTablesDialog, ID_JoinFColumnSelected, wxEmptyString, wxPoint(0,60), wxSize(110, 20), emptyArrayString, wxCB_READONLY);

    joinSTableBox = new wxComboBox(joinTablesDialog, ID_JoinSTableSelected, wxEmptyString, wxPoint(120,30), wxSize(110, 20), emptyArrayString, wxCB_READONLY);
    joinSColumnBox = new wxComboBox(joinTablesDialog, ID_JoinSColumnSelected, wxEmptyString, wxPoint(120,60), wxSize(110, 20), emptyArrayString, wxCB_READONLY);

    joinAll = new wxButton(joinTablesDialog, ID_JoinAllButton, "OK", wxPoint(100, 90), wxSize(30, 20));

    joinDatabaseBox->Bind(wxEVT_COMBOBOX, &MyFrame::OnJoinDatabaseSelected, this, ID_JoinDatabaseSelected);
    joinFTableBox->Bind(wxEVT_COMBOBOX, &MyFrame::OnJoinFTableSelected, this, ID_JoinFTableSelected);
    joinSTableBox->Bind(wxEVT_COMBOBOX, &MyFrame::OnJoinSTableSelected, this, ID_JoinSTableSelected);
    joinFColumnBox->Bind(wxEVT_COMBOBOX, &MyFrame::OnJoinFColumnSelected, this, ID_JoinFColumnSelected);
    joinAll->Bind(wxEVT_BUTTON, &MyFrame::OnJoinAllSelected, this, ID_JoinAllButton);
}

void MyFrame::OnJoinDatabaseSelected(wxCommandEvent& event)
{
    joinFTableBox->Clear();
    vector<string> tables = m.GetDatabase(string(joinDatabaseBox->GetStringSelection())).GetTables();
    for (int i=0; i<tables.size(); i++)
        joinFTableBox->Append(tables[i]);
}

void MyFrame::OnJoinFTableSelected(wxCommandEvent& event)
{
    joinSTableBox->Clear();
    vector<string> tables = m.GetDatabase(string(joinDatabaseBox->GetStringSelection())).GetTables();
    for (int i=0; i<tables.size(); i++)
        if (tables[i]!= string(joinFTableBox->GetValue()))
            joinSTableBox->Append(tables[i]);

    joinFColumnBox->Clear();
    vector<string> columns = m.GetDatabase(string(joinDatabaseBox->GetStringSelection())).GetTable(string(joinFTableBox->GetStringSelection())).GetColumns();
    for (int i=0; i<columns.size(); i++)
        joinFColumnBox->Append(columns[i]);
}

void MyFrame::OnJoinSTableSelected(wxCommandEvent& event)
{
    if (string(joinFColumnBox->GetValue()) != "")
    {
        joinSColumnBox->Clear();
        vector<string> columns = m.GetDatabase(string(joinDatabaseBox->GetStringSelection())).GetTable(string(joinSTableBox->GetStringSelection())).GetColumns();
        string type = m.GetDatabase(string(joinDatabaseBox->GetStringSelection())).GetTable(string(joinFTableBox->GetStringSelection())).GetColumn(string(joinFColumnBox->GetStringSelection())).GetType();
        for (int i=0; i<columns.size(); i++)
            if(m.GetDatabase(string(joinDatabaseBox->GetStringSelection())).GetTable(string(joinSTableBox->GetStringSelection())).GetColumn(columns[i]).GetType() == type)
                joinSColumnBox->Append(columns[i]);
    }
}

void MyFrame::OnJoinFColumnSelected(wxCommandEvent& event)
{
    if (string(joinSTableBox->GetValue()) != "")
    {
        joinSColumnBox->Clear();
        vector<string> columns = m.GetDatabase(string(joinDatabaseBox->GetStringSelection())).GetTable(string(joinSTableBox->GetStringSelection())).GetColumns();
        string type = m.GetDatabase(string(joinDatabaseBox->GetStringSelection())).GetTable(string(joinFTableBox->GetStringSelection())).GetColumn(string(joinFColumnBox->GetStringSelection())).GetType();
        for (int i=0; i<columns.size(); i++)
            if(m.GetDatabase(string(joinDatabaseBox->GetStringSelection())).GetTable(string(joinSTableBox->GetStringSelection())).GetColumn(columns[i]).GetType() == type)
                joinSColumnBox->Append(columns[i]);
    }
}

void MyFrame::OnJoinAllSelected(wxCommandEvent& event)
{
    Table joinTable = m.GetDatabase(string(joinDatabaseBox->GetStringSelection())).JoinTables(string(joinFTableBox->GetStringSelection()),
                                                                                              string(joinSTableBox->GetStringSelection()),
                                                                                              string(joinFColumnBox->GetStringSelection()),
                                                                                              string(joinSColumnBox->GetStringSelection()));
    joinTablesDialog->SetSize(wxSize(800, 600));
    delete joinDatabaseBox;
    delete joinFTableBox;
    delete joinSTableBox;
    delete joinFColumnBox;
    delete joinSColumnBox;
    delete joinAll;
    wxGrid *joinGrid = new wxGrid(joinTablesDialog, wxID_ANY, wxDefaultPosition, wxSize(780, 550));
    joinGrid->CreateGrid(0, 0);

    vector<string> columns = joinTable.GetColumns();
    int rows = joinTable.GetRows();
    joinGrid->AppendCols(columns.size());
    joinGrid->AppendRows(rows);
    for (int i=0; i<columns.size(); i++)
        joinGrid->SetColLabelValue(i, columns[i]);

    for (int i=0; i<rows; i++)
        for (int j=0; j<columns.size(); j++)
            joinGrid->SetCellValue(i, j, joinTable.GetRow(i).GetData(j));
}

void MyFrame::OnDatabaseSelected(wxCommandEvent& event)
{
    tableBox->Clear();
    vector<string> tables = m.GetDatabase(string(databaseBox->GetStringSelection())).GetTables();
    for (int i=0; i<tables.size(); i++)
        tableBox->Append(tables[i]);
}

void MyFrame::OnTableSelected(wxCommandEvent& event)
{
    RenderGrid();
}

void MyFrame::OnAddDatabaseView(wxCommandEvent& event)
{
    addDatabaseName = new wxTextCtrl(window, ID_AddDatabaseName, wxEmptyString, wxPoint(200,0), wxSize(110, 20));
    addDatabase = new wxButton(window, ID_AddDatabaseButton, "+", wxPoint(320, 0), wxSize(20, 20));
    databaseNameUsed = new wxStaticText(window, wxID_ANY, "", wxPoint(350,0));
    addDatabase->Bind(wxEVT_BUTTON, &MyFrame::OnAddDatabase, this, ID_AddDatabaseButton);
}

void MyFrame::OnAddDatabase(wxCommandEvent& event)
{
    vector<string> names = m.GetDatabases();
    for (int i=0; i<names.size(); i++)
        if (string(addDatabaseName->GetValue()) == names[i])
        {
            databaseNameUsed->SetLabel("Database name is used");
            return;
        }

    m.AddDatabase(string(addDatabaseName->GetLineText(0)));
    names = m.GetDatabases();

    databaseBox->Clear();
    for (int i=0; i<names.size(); i++)
        databaseBox->Append(names[i]);

    delete databaseNameUsed;
    delete addDatabaseName;
    delete addDatabase;
}

void MyFrame::OnDeleteDatabase(wxCommandEvent& event)
{
    m.DeleteDatabase(string(databaseBox->GetStringSelection()));
    vector<string> names = m.GetDatabases();
    databaseBox->Clear();
    for (int i=0; i<names.size(); i++)
        databaseBox->Append(names[i]);
}

void MyFrame::OnAddTableView(wxCommandEvent& event)
{
    addTableName = new wxTextCtrl(window, ID_AddTableName, wxEmptyString, wxPoint(200,30), wxSize(110, 20));
    addTable = new wxButton(window, ID_AddTableButton, "+", wxPoint(320, 30), wxSize(20, 20));
    tableNameUsed = new wxStaticText(window, wxID_ANY, "", wxPoint(350,30));
    addTable->Bind(wxEVT_BUTTON, &MyFrame::OnAddTable, this, ID_AddTableButton);
}

void MyFrame::OnAddTable(wxCommandEvent& event)
{
    if (databaseBox->GetValue().empty())
    {
        tableNameUsed->SetLabel("Choose database first");
        return;
    }
    vector<string> names = m.GetDatabase(string(databaseBox->GetValue())).GetTables();
    for (int i=0; i<names.size(); i++)
        if (string(addTableName->GetValue()) == names[i])
        {
            tableNameUsed->SetLabel("Table name is used");
            return;
        }

    m.GetDatabase(string(databaseBox->GetValue())).AddTable(string(addTableName->GetValue()));
    names = m.GetDatabase(string(databaseBox->GetValue())).GetTables();

    tableBox->Clear();
    for (int i=0; i<names.size(); i++)
        tableBox->Append(names[i]);

    delete tableNameUsed;
    delete addTableName;
    delete addTable;
}

void MyFrame::OnDeleteTable(wxCommandEvent& event)
{
    m.GetDatabase(string(databaseBox->GetStringSelection())).DeleteTable(string(tableBox->GetValue()));
    vector<string> names = m.GetDatabase(string(databaseBox->GetValue())).GetTables();
    tableBox->Clear();
    for (int i=0; i<names.size(); i++)
        tableBox->Append(names[i]);
}

void MyFrame::OnAddColumnView(wxCommandEvent& event)
{
    addColumnName = new wxTextCtrl(window, ID_AddColumnName, wxEmptyString, wxPoint(670, 0), wxSize(110, 20));
    addColumn = new wxButton(window, ID_AddColumnButton, "+", wxPoint(790, 0), wxSize(20, 20));
    columnNameUsed = new wxStaticText(window, wxID_ANY, "", wxPoint(820,0));
    columnBox = new wxComboBox(window, ID_ColumnSelected, wxEmptyString, wxPoint(670, 30), wxSize(110, 20), columnName, wxCB_READONLY);
    addColumn->Bind(wxEVT_BUTTON, &MyFrame::OnAddColumn, this, ID_AddColumnButton);
}

void MyFrame::OnAddColumn(wxCommandEvent& event)
{
    if (tableBox->GetValue().empty())
    {
        columnNameUsed->SetLabel("Choose table first");
        return;
    }

    if (columnBox->GetValue().empty())
    {
        columnNameUsed->SetLabel("Choose type first");
        return;
    }

    vector<string> names = m.GetDatabase(string(databaseBox->GetValue())).GetTable(string(tableBox->GetValue())).GetColumns();
    for (int i=0; i<names.size(); i++)
        if (string(addColumnName->GetValue()) == names[i])
        {
            columnNameUsed->SetLabel("Column name is used");
            return;
        }

    m.GetDatabase(string(databaseBox->GetValue())).GetTable(string(tableBox->GetValue())).AddColumn(string(addColumnName->GetValue()), string(columnBox->GetValue()));
    RenderGrid();

    delete columnNameUsed;
    delete columnBox;
    delete addColumnName;
    delete addColumn;
}

void MyFrame::OnDeleteColumn(wxCommandEvent& event)
{
    vector<string> names = m.GetDatabase(string(databaseBox->GetValue())).GetTable(string(tableBox->GetValue())).GetColumns();
    m.GetDatabase(string(databaseBox->GetStringSelection())).GetTable(string(tableBox->GetValue())).DeleteColumn(names[names.size()-1]);
    RenderGrid();
}

void MyFrame::OnAddRow(wxCommandEvent& event)
{
    if (tableBox->GetValue().empty()) return;
    m.GetDatabase(string(databaseBox->GetValue())).GetTable(string(tableBox->GetValue())).AddRow();
    RenderGrid();
}

void MyFrame::OnDeleteRow(wxCommandEvent& event)
{
    if (tableBox->GetValue().empty()) return;
    int rows = m.GetDatabase(string(databaseBox->GetValue())).GetTable(string(tableBox->GetValue())).GetRows();
    m.GetDatabase(string(databaseBox->GetValue())).GetTable(string(tableBox->GetValue())).DeleteRow(rows-1);
    RenderGrid();
}

void MyFrame::OnGridChanged(wxGridEvent& event)
{
    int columnIndex = event.GetCol();
    int rowIndex = event.GetRow();
    string value = string(grid->GetCellValue(rowIndex, columnIndex));

    vector<string> columns = m.GetDatabase(string(databaseBox->GetValue())).GetTable(string(tableBox->GetValue())).GetColumns();
    string type = m.GetDatabase(string(databaseBox->GetValue())).GetTable(string(tableBox->GetValue())).GetColumn(columns[columnIndex]).GetType();

    if (type == "int"){
        for(int i=0; i<value.size(); i++)
            if (isdigit(value[i]) == 0) {grid->SetCellValue(wxGridCellCoords(rowIndex, columnIndex), wxString::Format(wxT("%i"),0)); return;}}
    else if (type == "double")
    {
        bool dot = true;
        for(int i=0; i<value.size(); i++)
            if (isdigit(value[i]) == 0)
                if (dot && value[i] == '.') dot = false;
                else {grid->SetCellValue(wxGridCellCoords(rowIndex, columnIndex), wxString::Format(wxT("%f"),0.0)); return;}
    }
    else if (type == "hex")
    {
        if (value[0] != '#' || value.substr(1).find_first_not_of("ABCDEF0123456789") != string::npos || value.size()!=7)
            {grid->SetCellValue(wxGridCellCoords(rowIndex, columnIndex), "#000000"); return;}
    }
    else if (type == "hexInvl")
    {
        if (value[0] != '#' || value.substr(1,6).find_first_not_of("ABCDEF0123456789") != string::npos || value.size()!=14 ||
            value[7] != '#' || value.substr(8).find_first_not_of("ABCDEF0123456789") != string::npos ||
            value.substr(1,2).compare(value.substr(8,2)) > 0 ||
            value.substr(3,2).compare(value.substr(10,2)) > 0 ||
            value.substr(5,2).compare(value.substr(12,2)) > 0)
            {grid->SetCellValue(wxGridCellCoords(rowIndex, columnIndex), "#000000#000000"); return;}
    }
    m.GetDatabase(string(databaseBox->GetValue())).GetTable(string(tableBox->GetValue())).GetRow(rowIndex).ChangeData(value, columnIndex);
    RenderGrid();
}
