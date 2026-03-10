g++ -std=c++20 main.cpp Car.cpp -o car_program
Get-Content .\input.txt | .\car_program.exe

g++ tests.cpp functions.cpp -o tests
.\tests.exe
.\tests.exe -s
.\tests.exe -r console -s
.\tests.exe -r compact
