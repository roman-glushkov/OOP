g++ -std=c++17 main.cpp Shapes.cpp ShapeController.cpp -o shapes_program
Get-Content .\input.txt | .\shapes_program.exe

g++ -std=c++17 -o tests tests.cpp Shapes.cpp ShapeController.cpp
.\tests.exe
.\tests.exe -s
.\tests.exe -r console -s
.\tests.exe -r compact
