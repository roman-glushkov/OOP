g++ -std=c++20 main.cpp CMyListController.cpp -o mylist_program.exe
.\mylist_program.exe
Get-Content .\input.txt | .\mylist_program.exe

g++ -std=c++20 test_cmylist.cpp -o test_cmylist.exe
.\test_cmylist.exe
