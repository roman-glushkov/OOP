g++ -std=c++17 Solve3.cpp main.cpp -o cubic.exe
Get-Content input.txt | .\cubic.exe

g++ -std=c++11 -o test_solve3 test_solve3.cpp Solve3.cpp
./test_solve3
