
#include <iostream>
#include <fstream>
#include <filesystem>
#include <stdio.h>
#include "ioc.h"
#include "dbc.h"
#include "util.h"

using namespace std;
namespace fs = filesystem;

void create_dirs(const fs::path &path) {
    if (!fs::exists(path)) {
        cout << path << " is not exists, create it and move dbc files into it!" << endl;
        if (!fs::create_directories(path)) {
            cout << "create_directories " << path << " error!" << endl;
        }
        return ;
    }
}

bool Generate(string name, uint32_t record_count, uint32_t string_block_size) {
    cout << "-------------" << __FUNCTION__ << " [" << name << "]" << endl;
    fs::path binding = fs::current_path() / "binding";
    string bdName = binding.string() + "/" + name + ".txt";
    if (!fs::exists(bdName)) {
        cout << "    [Err] " << bdName << " file not exists" << endl;
        return false;
    }
    fstream bd;
    bd.open(bdName, ios_base::in);
    if (!bd.is_open()) {
        cout << "    [Err] " << bdName << " file open failed" << endl;
        return false;
    }

    fs::path header = fs::current_path() / "header";
    string hPath = header.string() + "/" + name + ".h";
    string cppPath = header.string() + "/" + name + ".cpp";
    fstream h, cpp;
    h.open(hPath, ios_base::out);
    cpp.open(cppPath, ios_base::out);
    if (!cpp.is_open()) {
        cout << "    [Err] " << cppPath << " file open failed" << endl;
        return false;
    }
    if (!h.is_open()) {
        cout << "    [Err] " << hPath << " file open failed" << endl;
        return false;
    }

    h << "#pragma once" << endl;
    h << "#include <cstdint>" << endl;
    h << "constexpr uint32_t " << name << "_record_count = " << record_count << ";" << endl;
    h << "constexpr uint32_t " << name << "_string_block_size = " << string_block_size << ";" << endl;
    h << "struct " << name << "_record {" << endl;

    cpp << "#include \"" << name << ".h\"" << endl;
    cpp << "#include \"dbc.h\"" << endl;
    cpp << "#include \"ioc.h\"" << endl;
    cpp << "REGISTER(" << name << ");" << endl;
    string line;
    while (getline(bd, line)) {
        auto vec = split(line, " ");
        if (vec.size() < 2) {
            cout << "    [Err] " << " binding has error line: " << line << ", size=" << vec.size() << endl;
            break;
        }
        if (vec.size() == 3 && vec[2] == "string") { h << "    char* "    << vec[1] << ";" << endl; continue; }
        if (vec[0] == "uint")  { h << "    uint32_t " << vec[1] << ";" << endl; continue; }
        if (vec[0] == "int")   { h << "    int32_t "  << vec[1] << ";" << endl; continue; }
        if (vec[0] == "float") { h << "    float "    << vec[1] << ";" << endl; continue; }
    }
    h << "};" << endl;
    cout << "    [" << __FUNCTION__ << "] " << name << ".h &" << name << ".cpp " << "done..." << endl;
    return true;
}

bool Convert(string path, string name) {
    cout << "-------------" << __FUNCTION__ << " [" << name << "]" << endl;
    FILE *f = fopen(path.c_str(), "rb");
    if(!f) {
        cout << "    [Err] " << path << " file open failed" << endl;
        return false;
    }
    uint32_t header, recordCount, fieldCount, recordSize, stringSize;
    if(fread(&header, 4, 1, f) != 1)
        return false;
    if(header != WDBC_HEADER)
        return false;
    if(fread(&recordCount, 4, 1, f) != 1) // Number of records
        return false;
    if(fread(&fieldCount, 4, 1, f) != 1) // Number of fields
        return false;
    if(fread(&recordSize, 4, 1, f) != 1) // Size of a record
        return false;
    if(fread(&stringSize, 4, 1, f) != 1) // String size
        return false;
    fclose(f);
    cout << recordCount << "," << stringSize << endl;
    return Generate(name, recordCount, stringSize);
}

int main() {
    cout << "######################################     start generate .h/.cpp     ######################################" << endl;
    fs::path dbc = fs::current_path() / "dbc", binding = fs::current_path() / "binding", 
    header = fs::current_path() / "header", sql = fs::current_path() / "sql";
    create_dirs(dbc);
    create_dirs(binding);
    create_dirs(header);
    create_dirs(sql);

    for (auto& i : filesystem::directory_iterator(dbc)) {
        std::string fileName = i.path().filename().string();
        if (fileName.find(".dbc") == string::npos) continue;
        fileName.erase(fileName.find("."));
        Convert(i.path().string(), fileName);
	}
    return 0;
}