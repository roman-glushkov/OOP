g++ -std=c++17 main.cpp Shapes.cpp -o shapes_program
Get-Content .\input.txt | .\shapes_program.exe

g++ -o tests tests.cpp Car.cpp CarController.cpp
.\tests.exe
.\tests.exe -s
.\tests.exe -r console -s
.\tests.exe -r compact
