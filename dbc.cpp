#include "dbc.h"
#include "ioc.h"
#include <filesystem>
#include <iostream>

using namespace std;
namespace fs = filesystem;
void DbcToSql() {
    fs::path current = getCurrentPath() / "dbc";
    if (!fs::exists(current)) {
        cout << current << " is not exists, create it and move according files into it!" << endl;
        if (!fs::create_directories(current)) {
            cout << "create_directories " << current << " error!" << endl;
        }
        return ;
    }

    for (auto& i : filesystem::directory_iterator(current)) {
        auto dbcStr = i.path().string();
        auto dbcFileName = i.path().filename().string();
        cout << "-------------find " << dbcFileName << endl;
        string dbcName = dbcFileName.erase(dbcFileName.find("."));
        auto dbc = GetInstance(dbcName.c_str());
        if (!dbc) {
            cout << "    [Err]" << dbcName << ".h & " << dbcName << ".cpp is not linked!" << endl;
            continue;
        }
        dbc->Load();
        dbc->DumpSql();
	}
}
