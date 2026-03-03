@echo off

set BASE_DIR=%~dp0
set TEST_DIR=%BASE_DIR%tests
set OUTPUT_DIR=%BASE_DIR%output

if not exist "%OUTPUT_DIR%" mkdir "%OUTPUT_DIR%"

set PROGRAM="%~1"
if "%~1"=="" set PROGRAM="%BASE_DIR%main.exe"

rem Тест 1 – пример 1: 2.0 4 -1.5
%PROGRAM% < "%TEST_DIR%\test1.txt" > "%OUTPUT_DIR%\test1.txt"
if ERRORLEVEL 1 goto err
fc.exe "%OUTPUT_DIR%\test1.txt" "%TEST_DIR%\test1-expected.txt" > nul
if ERRORLEVEL 1 goto err
echo Test 1 example 1: 2.0 4 -1.5 passed

rem Тест 2 – пример 2: 10 7 4
%PROGRAM% < "%TEST_DIR%\test2.txt" > "%OUTPUT_DIR%\test2.txt"
if ERRORLEVEL 1 goto err
fc.exe "%OUTPUT_DIR%\test2.txt" "%TEST_DIR%\test2-expected.txt" > nul
if ERRORLEVEL 1 goto err
echo Test 2 example 2: 10 7 4 passed

rem Тест 3 – пример 3: -1.5 -2.0 -3.0
%PROGRAM% < "%TEST_DIR%\test3.txt" > "%OUTPUT_DIR%\test3.txt"
if ERRORLEVEL 1 goto err
fc.exe "%OUTPUT_DIR%\test3.txt" "%TEST_DIR%\test3-expected.txt" > nul
if ERRORLEVEL 1 goto err
echo Test 3 example 3: -1.5 -2.0 -3.0 passed

rem Тест 4 – пример 4: abc 4.5 7
%PROGRAM% < "%TEST_DIR%\test4.txt" > "%OUTPUT_DIR%\test4.txt"
echo Test 4 example 4: invalid input passed

rem Тест 5 – пустой ввод
type nul | %PROGRAM% > "%OUTPUT_DIR%\empty.txt"
if ERRORLEVEL 1 goto err
fc.exe "%OUTPUT_DIR%\empty.txt" "%TEST_DIR%\empty-expected.txt" > nul
if ERRORLEVEL 1 goto err
echo Test 5 empty input passed

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1