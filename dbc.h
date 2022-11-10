#pragma once

#include <cstdint>
#include <string>
#include <stdio.h>
#include <iostream>
#include <memory>

#define WDBC_HEADER     0x43424457

struct dbc_header
{
    uint32_t magic; // always 'WDBC'
    uint32_t record_count; // records per file
    uint32_t field_count; // fields per record
    uint32_t record_size; // sum (sizeof (field_type_i)) | 0 <= i < field_count. field_type_i is NOT defined in the files.
    uint32_t string_block_size;
};

template<typename record_type, uint32_t record_count, uint32_t string_block_size>
struct dbc_file
{
    dbc_header header; // static_assert (header.record_size == sizeof (record_type));
    record_type records[record_count];
    char string_block[string_block_size];
};

class DbcInterface {
public:
    virtual void Load() = 0;
    virtual void DumpSql() = 0;
};

// using DbcInterfacePtr = std::shared_ptr<DbcInterface>;

template<typename record_type, uint32_t record_count, uint32_t string_block_size>
class Dbc : public DbcInterface {
public:
    explicit Dbc(const char* name) : m_name(name) {}
    void Load() override {
        std::cout << "    [" << __FUNCTION__ << "] start: " << m_name << std::endl;
    };
    void DumpSql() override {
        std::cout << "    [" << __FUNCTION__ << "] start: " << m_name << std::endl;
    };
private:
    std::string m_name;
    dbc_file<record_type, record_count, string_block_size> m_file;
};

void DbcToSql();
