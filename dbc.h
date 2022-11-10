#pragma once

#include <cstdint>
#include <string>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <memory>
#include <filesystem>
#include "ioc.h"
#include "util.h"
#include "progressbar.h"

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
}__attribute__((packed));

class DbcInterface {
public:
    virtual void Load() = 0;
    virtual void DumpSql() = 0;
};

#include "header/Spell.h"

template<typename record_type, uint32_t record_count, uint32_t string_block_size>
class Dbc : public DbcInterface {
public:
    explicit Dbc(const char* name) : m_name(name) {}
    void Load() override {
        std::cout << "    [" << __FUNCTION__ << "] start: " << m_name << std::endl;
        std::cout << "        size: " << sizeof(m_file) << std::endl;
        std::string dbcFile = m_name + ".dbc";
        std::filesystem::path dbc = std::filesystem::current_path() / "dbc" / dbcFile;
        std::cout << "        dbc file:" << dbc.string() << std::endl;
        FILE *f = fopen(dbc.string().c_str(), "rb");
        if(!f) {
            std::cout << "        [Err] " << dbc << " file open failed" << std::endl;
            return;
        }
        // dbc_header h;
        if(fread(&m_file, sizeof(m_file), 1, f) != 1) {
        // if(fread(&h, sizeof(h), 1, f) != 1) {
            std::cout << "        [Err] " << dbc << " read " << m_name << ".dbc into m_file failed" << std::endl;
            return;
        }
        std::cout << "        magic:"             << m_file.header.magic << std::endl
                  << "        record_count:"      << m_file.header.record_count << std::endl
                  << "        field_count:"       << m_file.header.field_count << std::endl
                  << "        record_size:"       << m_file.header.record_size << std::endl
                  << "        string_block_size:" << m_file.header.string_block_size << std::endl;
        // std::cout << "        magic:"             << h.magic << std::endl
        //           << "        record_count:"      << h.record_count << std::endl
        //           << "        field_count:"       << h.field_count << std::endl
        //           << "        record_size:"       << h.record_size << std::endl
        //           << "        string_block_size:" << h.string_block_size << std::endl;
        std::cout << "        Spell_record size:" << sizeof(Spell_record) << std::endl;

        std::string bdFile = m_name + ".txt";
        std::filesystem::path bdPath = std::filesystem::current_path() / "binding" / bdFile;
        std::fstream bd;
        bd.open(bdPath.string(), std::ios_base::in);
        if (!bd.is_open()) {
            std::cout << "        [Err] " << " open " << bdPath.string() << " failed" << std::endl;
            return;
        }

        string line;
        int index = 0;
        while (getline(bd, line)) {
            auto vec = split(line, " ");
            if (vec.size() < 2) {
                cout << "    [Err] " << " binding has error line: " << line << ", size=" << vec.size() << endl;
                break;
            }
            if (vec.size() == 3 && vec[2] == "string") { m_translation[index][0] = "char*"; m_translation[index++][1] = vec[1]; continue; }
            if (vec[0] == "uint")  { m_translation[index][0] = "uint32_t"; m_translation[index++][1] = vec[1]; continue; }
            if (vec[0] == "int")   { m_translation[index][0] = "int32_t"; m_translation[index++][1] = vec[1]; continue; }
            if (vec[0] == "float") { m_translation[index][0] = "float"; m_translation[index++][1] = vec[1]; continue; }
        }
        // m_translation[][]
    };
    void DumpSql() override {
        std::cout << "    [" << __FUNCTION__ << "] start: " << m_name << std::endl;
        std::string sqlFile = m_name + ".sql";
        std::filesystem::path sql = std::filesystem::current_path() / "sql" / sqlFile;
        std::cout << "        sql file:" << sql.string() << std::endl;
        FILE *f = fopen(sql.string().c_str(), "w");
        if (!f) {
            std::cout << "        [Err] " << sql << " file open failed" << std::endl;
            return;
        }

        const uint32_t SPELL_DBC_COLUMN_NUMS = m_file.header.field_count;

        std::cout << "        " << m_name << " - Creating the SQL table struct...\n";

        // fprintf(f, "-- DBCtoSQL v%s\n\n", DBCTOSQL_VER);
        // fprintf(f, "-- Web: %s\n\n\n", DBCTOSQL_WEB);

        fprintf(f, "DROP TABLE IF EXISTS `%s`;\n", m_name.c_str());
        fprintf(f, "CREATE TABLE `%s` (\n", m_name.c_str());

        for(uint32_t i = 0; i < SPELL_DBC_COLUMN_NUMS; i++)
        {
            if(m_translation[i][0] == "uint32_t")
                fprintf(f, "    `%s` INT (11) UNSIGNED DEFAULT '0' NOT NULL,\n", m_translation[i][1].c_str());
            else if(m_translation[i][0] == "int32_t")
                fprintf(f, "    `%s` INT (11) DEFAULT '0' NOT NULL,\n", m_translation[i][1].c_str());
            else if(m_translation[i][0] == "float")
                fprintf(f, "    `%s` FLOAT DEFAULT '0' NOT NULL,\n", m_translation[i][1].c_str());
            else if(m_translation[i][0] == "flag96")
                fprintf(f, "    `%s` INT (11) UNSIGNED DEFAULT '0' NOT NULL,\n", m_translation[i][1].c_str());
            else if(m_translation[i][0] == "char*")
                fprintf(f, "    `%s` TEXT,\n", m_translation[i][1].c_str());
            else
                fprintf(f, "    ERROR: unknown column type: %s in column: %s\n", m_translation[i][0].c_str(), m_translation[i][1].c_str());
        }
        fprintf(f, "    PRIMARY KEY(`%s`)\n", m_translation[0][1].c_str());
        fprintf(f, ") ENGINE=MyISAM DEFAULT CHARSET=utf8;\n");
        fprintf(f, "\n\n");
        std::cout << "        " << m_name << " - DONE\n";
        // start dumping the data from the DBC
        std::cout << "        " << m_name << " - Dumping data...\n";

        Bar ProgressSpell(m_file.header.record_count);

        const uint32_t SLASH_BUFFER = 2000;
        const uint32_t SQL_INSERTS_PER_QUERY = 300;
        char tstrSpell[SLASH_BUFFER];

        for(uint32_t j = 0; j < m_file.header.record_count; j++)
        {
            // new insert block
            if((j % SQL_INSERTS_PER_QUERY) == 0)
            {
                fprintf(f, "\nINSERT INTO `%s` (", m_name.c_str());
                for(uint32_t i = 0; i < SPELL_DBC_COLUMN_NUMS; i++)
                {
                    fprintf(f, "`%s`", m_translation[i][1].c_str());
                    if(i != SPELL_DBC_COLUMN_NUMS - 1)
                        fprintf(f, ",");
                }
                fprintf(f, ") VALUES \n");
                fprintf(f, "(");
            }
            else
                fprintf(f, ",(");

            for(uint32_t i = 0; i < SPELL_DBC_COLUMN_NUMS; i++)
            {
                if(m_translation[i][0] == "uint32_t")
                    fprintf(f, "%u", *(uint32_t*)(((char*)&m_file.records[j]) + i * 4));
                else if(m_translation[i][0] == "int32_t")
                    fprintf(f, "%d", *(int32_t*)(((char*)&m_file.records[j]) + i * 4));
                else if(m_translation[i][0] == "float")
                    fprintf(f, "%f",  *(float*)(((char*)&m_file.records[j]) + i * 4));
                else if(m_translation[i][0] == "flag96")
                    fprintf(f, "%u", *(uint32_t*)(((char*)&m_file.records[j]) + i * 4));
                else if(m_translation[i][0] == "char*")
                {
                    size_t offset = *(uint32_t*)(((char*)&m_file.records[j]) + i * 4);
                    if (offset > m_file.header.string_block_size) {
                        std::cout << "        [Err] offset :" << offset << " is bigger than string_block_size :" << m_file.header.string_block_size << std::endl;
                        return ;
                    }
                    const char *dstr = &m_file.string_block[offset];
                    uint32_t otherindex = 0;
                    for(uint32_t k = 0; k <= strlen(dstr); k++)
                    {
                        if(dstr[k] == '\'' || dstr[k] == '"')
                        {
                            tstrSpell[otherindex++] = '\\';
                            tstrSpell[otherindex++] = dstr[k];
                        }
                        else
                            tstrSpell[otherindex++] = dstr[k];
                    }
                    fprintf(f, "\"%s\"", tstrSpell);
                }

                if(i != SPELL_DBC_COLUMN_NUMS - 1)
                    fprintf(f, ",");
            }

            // end of insert block
            if((( j + 1) % SQL_INSERTS_PER_QUERY) == 0)
                fprintf(f, ");\n");
            else if(j == m_file.header.record_count - 1)
                fprintf(f, ");\n");
            else
                fprintf(f, ")\n");

            ProgressSpell.Step();
        }

        std::cout << std::endl << "        " << m_name << " - DONE\n\n";

        fprintf(f, "\n");
        fprintf(f, "-- EOF\n");
        fflush(f);
        fclose(f);

        std::cout << "        " << m_name << " - Closed\n\n";

    };
private:
    std::string m_name;
    dbc_file<record_type, record_count, string_block_size> m_file;
    std::string m_translation[record_count][2];
};

void DbcToSql();
