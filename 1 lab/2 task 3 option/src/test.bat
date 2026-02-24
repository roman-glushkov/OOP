@echo off

set BASE_DIR=%~dp0
set TEST_DIR=%BASE_DIR%tests
set OUTPUT_DIR=%BASE_DIR%output

if not exist "%OUTPUT_DIR%" mkdir "%OUTPUT_DIR%"

set PROGRAM="%~1"
if "%~1"=="" set PROGRAM="%BASE_DIR%bin2dec.exe"

rem Тест 1 – корректное число 110010000 -> 400
%PROGRAM% 110010000 > "%OUTPUT_DIR%\test1_output.txt"
if ERRORLEVEL 1 goto err
fc.exe "%OUTPUT_DIR%\test1_output.txt" "%TEST_DIR%\expected_400.txt" > nul
if ERRORLEVEL 1 goto err
echo Test 1 passed 110010000 to 400

rem Тест 2 – корректное число 1010 -> 10
%PROGRAM% 1010 > "%OUTPUT_DIR%\test2_output.txt"
if ERRORLEVEL 1 goto err
fc.exe "%OUTPUT_DIR%\test2_output.txt" "%TEST_DIR%\expected_10.txt" > nul
if ERRORLEVEL 1 goto err
echo Test 2 passed 1010 to 10

rem Тест 3 – максимальное 32-битное число
%PROGRAM% 11111111111111111111111111111111 > "%OUTPUT_DIR%\test3_output.txt"
if ERRORLEVEL 1 goto err
fc.exe "%OUTPUT_DIR%\test3_output.txt" "%TEST_DIR%\expected_max.txt" > nul
if ERRORLEVEL 1 goto err
echo Test 3 passed max 32-bit to 4294967295

rem Тест 4 – ноль
%PROGRAM% 0 > "%OUTPUT_DIR%\test4_output.txt"
if ERRORLEVEL 1 goto err
fc.exe "%OUTPUT_DIR%\test4_output.txt" "%TEST_DIR%\expected_0.txt" > nul
if ERRORLEVEL 1 goto err
echo Test 4 passed 0 to 0

rem Тест 5 – отрицательное число
%PROGRAM% -100 > "%OUTPUT_DIR%\test5_output.txt"
if NOT ERRORLEVEL 1 goto err
echo Test 5 passed minus 100 returns ERROR

rem Тест 6 – число с буквами
%PROGRAM% 1010a101 > "%OUTPUT_DIR%\test6_output.txt"
if NOT ERRORLEVEL 1 goto err
echo Test 6 passed 1010a101 returns ERROR

rem Тест 7 – пустая строка
%PROGRAM% "" > "%OUTPUT_DIR%\test7_output.txt"
if NOT ERRORLEVEL 1 goto err
echo Test 7 passed empty string returns ERROR

rem Тест 8 – слишком длинное число 33 бита
%PROGRAM% 111111111111111111111111111111111 > "%OUTPUT_DIR%\test8_output.txt"
if NOT ERRORLEVEL 1 goto err
echo Test 8 passed 33 bits returns ERROR

rem Тест 9 – справка
%PROGRAM% -h > "%OUTPUT_DIR%\test9_output.txt"
if ERRORLEVEL 1 goto err
echo Test 9 passed help

rem Тест 10 – без аргументов
%PROGRAM% > "%OUTPUT_DIR%\test10_output.txt"
if NOT ERRORLEVEL 1 goto err
echo Test 10 passed no arguments returns ERROR

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1