@echo off
call setEnv.bat
"E:\Program to Writecode\toolbox\shared\coder\ninja\win64\ninja.exe" -t compdb cc cxx cudac > compile_commands.json
"E:\Program to Writecode\toolbox\shared\coder\ninja\win64\ninja.exe" -v %*
