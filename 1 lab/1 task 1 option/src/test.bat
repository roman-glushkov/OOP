@echo off

set BASE_DIR=%~dp0
set TEST_DIR=%BASE_DIR%tests
set OUTPUT_DIR=%BASE_DIR%output

if not exist "%OUTPUT_DIR%" mkdir "%OUTPUT_DIR%"

set PROGRAM="%~1"
if "%~1"=="" set PROGRAM="%BASE_DIR%copyfile.exe"

rem Тест 1 – пустой файл
%PROGRAM% "%TEST_DIR%\test-empty.txt" "%OUTPUT_DIR%\empty.txt"
if ERRORLEVEL 1 goto err
fc.exe "%OUTPUT_DIR%\empty.txt" "%TEST_DIR%\test-empty.txt" > nul
if ERRORLEVEL 1 goto err
echo Test 1 (empty file) passed

rem Тест 2 – одна строка
%PROGRAM% "%TEST_DIR%\test-hello.txt" "%OUTPUT_DIR%\hello.txt"
if ERRORLEVEL 1 goto err
fc.exe "%OUTPUT_DIR%\hello.txt" "%TEST_DIR%\test-hello.txt" > nul
if ERRORLEVEL 1 goto err
echo Test 2 (one line) passed

rem Тест 3 – много строк
%PROGRAM% "%TEST_DIR%\test-poem.txt" "%OUTPUT_DIR%\poem.txt"
if ERRORLEVEL 1 goto err
fc.exe "%OUTPUT_DIR%\poem.txt" "%TEST_DIR%\test-poem.txt" > nul
if ERRORLEVEL 1 goto err
echo Test 3 (poem file) passed

rem Тест 4 – числа
%PROGRAM% "%TEST_DIR%\test-numbers.txt" "%OUTPUT_DIR%\numbers.txt"
if ERRORLEVEL 1 goto err
fc.exe "%OUTPUT_DIR%\numbers.txt" "%TEST_DIR%\test-numbers.txt" > nul
if ERRORLEVEL 1 goto err
echo Test 4 (numbers file) passed

rem Тест 5 – неверное количество аргументов
%PROGRAM% > "%OUTPUT_DIR%\invalid_args.txt"
if NOT ERRORLEVEL 1 goto err
echo Test 5 (no arguments) passed

rem Тест 6 – отсутствующий входной файл
%PROGRAM% "%TEST_DIR%\missing.txt" "%OUTPUT_DIR%\missing.txt" > "%OUTPUT_DIR%\error_read_open.txt"
if NOT ERRORLEVEL 1 goto err
echo Test 6 (missing input file) passed

rem Тест 7 – отсутствующий выходной файл
%PROGRAM% "%TEST_DIR%\test-hello.txt" "Z:\invalid\path\hello.txt" > "%OUTPUT_DIR%\error_write_open.txt"
if NOT ERRORLEVEL 1 goto err
echo Test 7 (invalid output path) passed

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1