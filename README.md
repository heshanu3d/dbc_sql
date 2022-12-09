# dbc_sql
.dbc .sql converter for wow

## 【Brief】

The converter contains two procedure:
1. Generate the headers
  input dbc descriptions file (also known as dbc structure file) in binding directories.
      + Name it binding because the WoW-Spell-Editor(https://github.com/stoneharry/WoW-Spell-Editor) has a binding directories, and they have the same meaning.
      + the dbc descriptions file can copy from the WoW-Spell-Editor release binary, or write from https://wowdev.wiki/Category:DBC_Vanilla, the type and name in description file will affect the type and value in sql directly.
      + Do not forget to set its suffix to .txt
  input .dbc file which you want to conver (such as Spell.dbc etc.) in dbc directories.
  then start the generator, it will generate a few headers (.h and .cpp) in header directories, this will help the next compile procedure.

2. convert dbc to sql.
  Now you have the specified dbc header files which the c++ could recognize.So we just compile it and run it.Then, we will get the sql files in sql directories.

3. convert sql to dbc is to be continued...
  

## 【Build】
### 【Windows with mingw】 
open project root dir with clion
```
"D:\JetBrains\CLion 2020.1.1\bin\cmake\win\bin\cmake.exe" -DCMAKE_BUILD_TYPE=Debug -G "CodeBlocks - MinGW Makefiles" D:\code\wow\dbc_sql
-- The C compiler identification is GNU 9.2.0
-- The CXX compiler identification is GNU 9.2.0
-- Check for working C compiler: D:/sdk/MINGW/bin/gcc.exe
-- Check for working C compiler: D:/sdk/MINGW/bin/gcc.exe -- works
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Detecting C compile features
-- Detecting C compile features - done
-- Check for working CXX compiler: D:/sdk/MINGW/bin/g++.exe
-- Check for working CXX compiler: D:/sdk/MINGW/bin/g++.exe -- works
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- D:/code/wow/dbc_sql/header/Spell.cpp
-- Configuring done
-- Generating done
-- Build files have been written to: D:/code/wow/dbc_sql/cmake-build-debug

[Finished]
```
+ select target to build_and_run_main
+ click build button
+ this will turn out as a command below 
+ "D:\JetBrains\CLion 2020.1.1\bin\cmake\win\bin\cmake.exe" --build D:\code\wow\dbc_sql\cmake-build-debug --target build_and_run_main -- -j 8
```
====================[ Build | build_and_run_main | Debug ]======================
"D:\JetBrains\CLion 2020.1.1\bin\cmake\win\bin\cmake.exe" --build D:\code\wow\dbc_sql\cmake-build-debug --target build_and_run_main -- -j 8
Scanning dependencies of target generate
[ 14%] Building CXX object CMakeFiles/generate.dir/generate.cpp.obj
[ 28%] Linking CXX executable generate.exe
[ 28%] Built target generate
Scanning dependencies of target generate_header
######################################     start generate .h/.cpp     ######################################
-------------Convert [Spell]
23544,816621
-------------Generate [Spell]
    [Generate] Spell.h &Spell.cpp done...
[ 28%] Built target generate_header
Scanning dependencies of target main
[ 42%] Building CXX object CMakeFiles/main.dir/main.cpp.obj
[ 57%] Building CXX object CMakeFiles/main.dir/dbc.cpp.obj
[ 71%] Building CXX object CMakeFiles/main.dir/header/Spell.cpp.obj
[ 85%] Building CXX object CMakeFiles/main.dir/progressbar.cpp.obj
[100%] Linking CXX executable main.exe
[100%] Built target main
Scanning dependencies of target build_and_run_main
############################################################################################################
#####  All original DBC files can be found here: https://wowdev.wiki/Category:DBC_Vanilla              #####
############################################################################################################
-------------find Spell.dbc
    [Load] start: Spell
        size: 17109089
        dbc file:D:\code\wow\dbc_sql\cmake-build-debug\..\dbc\Spell.dbc
        magic:1128416343
        record_count:23544
        field_count:173
        record_size:692
        string_block_size:816621
    [DumpSql] start: Spell
        sql file:D:\code\wow\dbc_sql\cmake-build-debug\..\sql\Spell.sql
        Spell - Creating the SQL table struct...
        Spell - DONE
        Spell - Dumping data...
=
        Spell - DONE
        Spell - Closed


[100%] Built target build_and_run_main
```
### 【Linux】
I think your compiler should be gcc-9.xx at least  because it must support filesystem.Or you can rewrite it yourself to get rid of filesystem usage, that's not hard.
`sudo apt-get install g++-multilib` is required when build on x64 platform.

```
cd project_root_path
mkdir build
cd build
cmake ..
make build_and_run_main
```
because of file(glob ...) in cmake, dbc incremental compilation isn't supported at the moment, but you can clean the build path to passthrough it, more suitable cmake usage will be added later:
```
cd build
rm -rf *
cmake ..
make build_and_run_main
```

```
hs@zbook:/usr1/test/code/c++/wow/my_dbc_sql$ mkdir build
hs@zbook:/usr1/test/code/c++/wow/my_dbc_sql$ cd build
hs@zbook:/usr1/test/code/c++/wow/my_dbc_sql/build$ cmake ..
-- The C compiler identification is GNU 11.3.0
-- The CXX compiler identification is GNU 11.3.0
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /usr/bin/cc - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- /usr1/test/code/c++/wow/my_dbc_sql/header/Spell.cpp/usr1/test/code/c++/wow/my_dbc_sql/header/SpellVisual.cpp
-- Configuring done
-- Generating done
-- Build files have been written to: /usr1/test/code/c++/wow/my_dbc_sql/build
hs@zbook:/usr1/test/code/c++/wow/my_dbc_sql/build$ make build_and_run_main
[ 12%] Building CXX object CMakeFiles/generate.dir/generate.cpp.o
[ 25%] Linking CXX executable generate
[ 25%] Built target generate
######################################     start generate .h/.cpp     ######################################
-------------Convert [SpellVisual]
2165,1
-------------Generate [SpellVisual]
    [Generate] SpellVisual.h &SpellVisual.cpp done...
-------------Convert [Spell]
23544,816621
-------------Generate [Spell]
    [Generate] Spell.h &Spell.cpp done...
[ 25%] Built target generate_header
[ 37%] Building CXX object CMakeFiles/main.dir/main.cpp.o
[ 50%] Building CXX object CMakeFiles/main.dir/dbc.cpp.o
[ 62%] Building CXX object CMakeFiles/main.dir/header/Spell.cpp.o
[ 75%] Building CXX object CMakeFiles/main.dir/header/SpellVisual.cpp.o
[ 87%] Building CXX object CMakeFiles/main.dir/progressbar.cpp.o
[100%] Linking CXX executable main
[100%] Built target main
############################################################################################################
#####  All original DBC files can be found here: https://wowdev.wiki/Category:DBC_Vanilla              #####
############################################################################################################
-------------find SpellVisual.dbc
    [Load] start: SpellVisual
        size: 138581
        dbc file:/usr1/test/code/c++/wow/my_dbc_sql/build/../dbc/SpellVisual.dbc
        magic:1128416343
        record_count:2165
        field_count:16
        record_size:64
        string_block_size:1
    [DumpSql] start: SpellVisual
        sql file:/usr1/test/code/c++/wow/my_dbc_sql/build/../sql/SpellVisual.sql
        SpellVisual - Creating the SQL table struct...
        SpellVisual - DONE
        SpellVisual - Dumping data...
[**************************************************] 100%  
        SpellVisual - DONE
        SpellVisual - Closed


-------------find Spell.dbc
    [Load] start: Spell
        size: 17109089
        dbc file:/usr1/test/code/c++/wow/my_dbc_sql/build/../dbc/Spell.dbc
        magic:1128416343
        record_count:23544
        field_count:173
        record_size:692
        string_block_size:816621
    [DumpSql] start: Spell
        sql file:/usr1/test/code/c++/wow/my_dbc_sql/build/../sql/Spell.sql
        Spell - Creating the SQL table struct...
        Spell - DONE
        Spell - Dumping data...
[**************************************************] 100%  
        Spell - DONE
        Spell - Closed


[100%] Built target build_and_run_main
```

or you can build and use it like this, but __this method will not be recommend__, because clean project will be a little annoying :

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
