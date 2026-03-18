@echo off

set BASE_DIR=%~dp0
set TEST_DIR=%BASE_DIR%tests
set OUTPUT_DIR=%BASE_DIR%output

if not exist "%OUTPUT_DIR%" mkdir "%OUTPUT_DIR%"

set PROGRAM="%~1"
if "%~1"=="" set PROGRAM="%BASE_DIR%replace.exe"

rem Тест 1 – замена подстроки (ma -> mama)
%PROGRAM% "%TEST_DIR%\test1.txt" "%OUTPUT_DIR%\output1.txt" "ma" "mama"
if ERRORLEVEL 1 goto err
fc.exe "%OUTPUT_DIR%\output1.txt" "%TEST_DIR%\expected1.txt" > nul
if ERRORLEVEL 1 goto err
echo Test 1 (basic replace) passed

rem Тест 2 – перекрывающиеся вхождения (1231234 -> XYZ)
%PROGRAM% "%TEST_DIR%\test2.txt" "%OUTPUT_DIR%\output2.txt" "1231234" "XYZ"
if ERRORLEVEL 1 goto err
fc.exe "%OUTPUT_DIR%\output2.txt" "%TEST_DIR%\expected2.txt" > nul
if ERRORLEVEL 1 goto err
echo Test 2 (overlapping pattern) passed

rem Тест 3 – пустая искомая строка
%PROGRAM% "%TEST_DIR%\test3.txt" "%OUTPUT_DIR%\output3.txt" "" "tut text"
if ERRORLEVEL 1 goto err
fc.exe "%OUTPUT_DIR%\output3.txt" "%TEST_DIR%\expected3.txt" > nul
if ERRORLEVEL 1 goto err
echo Test 3 (empty search) passed

rem Тест 4 – режим stdin
%PROGRAM% < "%TEST_DIR%\stdin_test.txt" > "%OUTPUT_DIR%\stdin_output.txt"
if ERRORLEVEL 1 goto err
fc.exe "%OUTPUT_DIR%\stdin_output.txt" "%TEST_DIR%\stdin_expected.txt" > nul
if ERRORLEVEL 1 goto err
echo Test 4 (stdin mode) passed

rem Тест 5 – неверное количество аргументов
%PROGRAM% arg1 arg2 arg3 > "%OUTPUT_DIR%\invalid_args.txt" 2>&1
if NOT ERRORLEVEL 1 goto err
echo Test 5 (invalid arguments) passed

rem Тест 6 – отсутствующий входной файл
%PROGRAM% "%TEST_DIR%\missing.txt" "%OUTPUT_DIR%\missing.txt" "ma" "mama" > "%OUTPUT_DIR%\error_read.txt" 2>&1
if NOT ERRORLEVEL 1 goto err
echo Test 6 (missing input file) passed

rem Тест 7 – входной и выходной файлы совпадают
%PROGRAM% "%TEST_DIR%\test1.txt" "%TEST_DIR%\test1.txt" "ma" "mama" > "%OUTPUT_DIR%\error_same.txt" 2>&1
if NOT ERRORLEVEL 1 goto err
echo Test 7 (same input/output) passed

rem Тест 8 – справка -h
%PROGRAM% -h > "%OUTPUT_DIR%\help.txt"
if ERRORLEVEL 1 goto err
findstr "Program to replace" "%OUTPUT_DIR%\help.txt" > nul
if ERRORLEVEL 1 goto err
echo Test 8 (help option) passed

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1