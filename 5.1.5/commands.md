g++ -std=c++20 main.cpp CDateController.cpp CDate.cpp -o date_program.exe
Get-Content .\input.txt | .\date_program.exe

g++ test_cdate.cpp CDate.cpp CDateController.cpp -std=c++17 -o tests
.\tests.exe
.\tests.exe -s
.\tests.exe -r console -s
.\tests.exe -r compact
