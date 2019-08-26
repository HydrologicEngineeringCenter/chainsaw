@echo off


cd %~dp0

 
SET DIR1=x64\debug

if  "%1"=="Win32" (
call  ..\vs_env32.bat
SET DIR1=Win32\Debug
) else (
call  ..\vs_env.bat
)

:: compile chainsaw
cd chainsaw
msbuild /t:clean chainsaw.vcxproj
msbuild  chainsaw.vcxproj

%DIR1%\chainsaw test 6 read write

%DIR1%\chainsaw test 7 read write

