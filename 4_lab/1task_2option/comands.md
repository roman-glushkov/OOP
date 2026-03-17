g++ -std=c++20 main.cpp Car.cpp -o car_program
Get-Content .\input.txt | .\car_program.exe

g++ -o tests tests.cpp Car.cpp CarController.cpp
.\tests.exe
.\tests.exe -s
.\tests.exe -r console -s
.\tests.exe -r compact
