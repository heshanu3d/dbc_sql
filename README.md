# dbc_sql
.dbc .sql converter for wow

【Brief】

The converter contains two procedure:
1. Generate the headers
  input dbc descriptions file (also known as dbc structure file) in binding directories.
      Name it binding because the WoW-Spell-Editor(https://github.com/stoneharry/WoW-Spell-Editor) has a binding directories, and they have the same meaning.
      the dbc descriptions file can copy from the WoW-Spell-Editor release binary, or write from https://wowdev.wiki/Category:DBC_Vanilla, the type and name in description file will affect the type and value in sql directly.
      Do not forget to set its suffix to .txt
  input .dbc file which you want to conver (such as Spell.dbc etc.) in dbc directories.
  then start the generator, it will generate a few headers (.h and .cpp) in header directories, this will help the next compile procedure.

2. convert dbc to sql.
  Now you have the specified dbc header files which the c++ could recognize.So we just compile it and run it.Then, we will get the sql files in sql directories.
  

【Build】

I think your compiler should be gcc-9.xx at least  because it must support filesystem.Or you can rewrite it yourself to get rid of filesystem usage, that's not hard.

```
cd project_root_path
cmake .
make build_and_run_main
```

```
hs@zbook:/usr1/test/code/c++/wow/my$ make build_and_run_main
[ 14%] Building CXX object CMakeFiles/generate.dir/generate.cpp.o
[ 28%] Linking CXX executable generate
[ 28%] Built target generate
######################################     start generate .h/.cpp     ######################################
-------------Convert [Spell]
23544,816621
-------------Generate [Spell]
    [Generate] Spell.h &Spell.cpp done...
[ 28%] Built target generate_header
[ 42%] Building CXX object CMakeFiles/main.dir/main.cpp.o
[ 57%] Building CXX object CMakeFiles/main.dir/dbc.cpp.o
[ 71%] Building CXX object CMakeFiles/main.dir/header/Spell.cpp.o
[ 85%] Building CXX object CMakeFiles/main.dir/progressbar.cpp.o
[100%] Linking CXX executable main
[100%] Built target main
############################################################################################################
#####  All original DBC files can be found here: https://wowdev.wiki/Category:DBC_Vanilla              #####
############################################################################################################
-------------find Spell.dbc
    [Load] start: Spell
        size: 17109089
        dbc file:/usr1/test/code/c++/wow/my/dbc/Spell.dbc
        magic:1128416343
        record_count:23544
        field_count:173
        record_size:692
        string_block_size:816621
        Spell_record size:692
    [DumpSql] start: Spell
        sql file:/usr1/test/code/c++/wow/my/sql/Spell.sql
        Spell - Creating the SQL table struct...
        Spell - DONE
        Spell - Dumping data...
[**************************************************] 100%  
        Spell - DONE

        Spell - Closed


[100%] Built target build_and_run_main

```
