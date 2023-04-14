@echo off

set CMAKE=.\..\..\CMake\bin\cmake.exe
set SRC=..\Src
set PROJECTNAME=Lua54

mkdir .\build
cd .\build

%CMAKE% -DLUABRIDGE_TESTING:BOOL="1" -Dgtest_force_shared_crt:BOOL="0" -DCMAKE_CONFIGURATION_TYPES:STRING="Debug;Release;" -DLUABRIDGE_CXX17:BOOL="1" %SRC%

msbuild "LuaBridge.sln" /t:%PROJECTNAME% /p:configuration=Debug /p:OutDir=%cd%\lib\Debug\ /p:TargetName=%PROJECTNAME%_d 
msbuild "LuaBridge.sln" /t:%PROJECTNAME% /p:configuration=Release /p:OutDir=%cd%\lib\Release\ /p:TargetName=%PROJECTNAME%

cd ..