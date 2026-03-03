g++ main.cpp functions.cpp -o program
echo 5 2 3 | .\program.exe

g++ tests.cpp functions.cpp -o tests
.\tests.exe
.\tests.exe -s
.\tests.exe -r console -s
.\tests.exe -r compact
