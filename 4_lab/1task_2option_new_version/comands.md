g++ -std=c++17 -I./include -o tests/tests.exe tests/ShapeTests.cpp src/shapes/_.cpp src/utils/_.cpp
./tests/tests.exe

g++ -std=c++17 -I./include -o app.exe main.cpp src/shapes/_.cpp src/utils/_.cpp
Get-Content tests/input.txt | ./app.exe
