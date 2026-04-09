#define CATCH_CONFIG_MAIN
#include "../catch2/catch.hpp"
#include "CMyList.h"
#include <string>
#include <sstream>

TEST_CASE("Default constructor creates empty list")
{
    SECTION("Empty list properties")
    {
        CMyList<int> list;
        CHECK(list.Size() == 0);
        CHECK(list.Empty());
    }
    
    SECTION("Empty list begin == end")
    {
        CMyList<int> list;
        CHECK(list.begin() == list.end());
    }
}

TEST_CASE("PushBack and PushFront")
{
    SECTION("PushBack adds elements to the end")
    {
        CMyList<int> list;
        list.PushBack(1);
        list.PushBack(2);
        list.PushBack(3);
        
        CHECK(list.Size() == 3);
        CHECK_FALSE(list.Empty());
        
        auto it = list.begin();
        CHECK(*it == 1);
        ++it;
        CHECK(*it == 2);
        ++it;
        CHECK(*it == 3);
        ++it;
        CHECK(it == list.end());
    }
    
    SECTION("PushFront adds elements to the beginning")
    {
        CMyList<std::string> list;
        list.PushFront("first");
        list.PushFront("second");
        list.PushFront("third");
        
        CHECK(list.Size() == 3);
        
        auto it = list.begin();
        CHECK(*it == "third");
        ++it;
        CHECK(*it == "second");
        ++it;
        CHECK(*it == "first");
    }
}

TEST_CASE("PopBack and PopFront")
{
    SECTION("PopFront removes first element")
    {
        CMyList<int> list;
        list.PushBack(1);
        list.PushBack(2);
        list.PushBack(3);
        
        list.PopFront();
        CHECK(list.Size() == 2);
        
        auto it = list.begin();
        CHECK(*it == 2);
        ++it;
        CHECK(*it == 3);
    }
    
    SECTION("PopBack removes last element")
    {
        CMyList<int> list;
        list.PushBack(1);
        list.PushBack(2);
        list.PushBack(3);
        
        list.PopBack();
        CHECK(list.Size() == 2);
        
        auto it = list.begin();
        CHECK(*it == 1);
        ++it;
        CHECK(*it == 2);
    }
    
    SECTION("Pop on single element makes list empty")
    {
        CMyList<int> list;
        list.PushBack(42);
        list.PopFront();
        CHECK(list.Empty());
        CHECK(list.Size() == 0);
        
        list.PushBack(100);
        list.PopBack();
        CHECK(list.Empty());
    }
    
    SECTION("Pop on empty list throws exception")
    {
        CMyList<int> list;
        CHECK_THROWS_AS(list.PopFront(), std::out_of_range);
        CHECK_THROWS_AS(list.PopBack(), std::out_of_range);
    }
}

TEST_CASE("Iterator operations")
{
    SECTION("Forward iteration")
    {
        CMyList<int> list;
        for (int i = 1; i <= 5; ++i)
            list.PushBack(i);
        
        int expected = 1;
        for (auto it = list.begin(); it != list.end(); ++it)
        {
            CHECK(*it == expected);
            ++expected;
        }
    }
    
    SECTION("Iterator increment and decrement")
    {
        CMyList<int> list;
        list.PushBack(1);
        list.PushBack(2);
        list.PushBack(3);
        
        auto it = list.begin();
        CHECK(*it == 1);
        
        auto it2 = ++it;
        CHECK(*it == 2);
        CHECK(*it2 == 2);
        
        auto it3 = it++;
        CHECK(*it == 3);
        CHECK(*it3 == 2);
        
        --it;
        CHECK(*it == 2);
        
        it--;
        CHECK(*it == 1);
    }
}

TEST_CASE("Insert at position")
{
    SECTION("Insert in the middle")
    {
        CMyList<std::string> list;
        list.PushBack("A");
        list.PushBack("C");
        list.PushBack("D");
        
        auto it = list.begin();
        ++it;
        list.insert(it, "B");
        
        CHECK(list.Size() == 4);
        
        auto check = list.begin();
        CHECK(*check == "A");
        ++check;
        CHECK(*check == "B");
        ++check;
        CHECK(*check == "C");
        ++check;
        CHECK(*check == "D");
    }
    
    SECTION("Insert at beginning")
    {
        CMyList<int> list;
        list.PushBack(2);
        list.PushBack(3);
        
        list.insert(list.begin(), 1);
        
        CHECK(list.Size() == 3);
        CHECK(*list.begin() == 1);
    }
    
    SECTION("Insert at end")
    {
        CMyList<int> list;
        list.PushBack(1);
        list.PushBack(2);
        
        list.insert(list.end(), 3);
        
        CHECK(list.Size() == 3);
        
        auto it = list.begin();
        ++it;
        ++it;
        CHECK(*it == 3);
    }
}

TEST_CASE("Erase at position")
{
    SECTION("Erase from middle")
    {
        CMyList<int> list;
        for (int i = 1; i <= 5; ++i)
            list.PushBack(i);
        
        auto it = list.begin();
        ++it;
        ++it;
        list.erase(it);
        
        CHECK(list.Size() == 4);
        
        auto check = list.begin();
        CHECK(*check == 1);
        ++check;
        CHECK(*check == 2);
        ++check;
        CHECK(*check == 4);
        ++check;
        CHECK(*check == 5);
    }
    
    SECTION("Erase from beginning")
    {
        CMyList<int> list;
        list.PushBack(1);
        list.PushBack(2);
        list.PushBack(3);
        
        list.erase(list.begin());
        
        CHECK(list.Size() == 2);
        CHECK(*list.begin() == 2);
    }
    
    SECTION("Erase from end throws exception")
    {
        CMyList<int> list;
        list.PushBack(1);
        
        CHECK_THROWS_AS(list.erase(list.end()), std::out_of_range);
    }
}

TEST_CASE("Copy constructor")
{
    SECTION("Copy creates independent list")
    {
        CMyList<int> original;
        original.PushBack(1);
        original.PushBack(2);
        original.PushBack(3);
        
        CMyList<int> copy(original);
        
        CHECK(copy.Size() == 3);
        
        auto it1 = original.begin();
        auto it2 = copy.begin();
        CHECK(*it1 == *it2);
        
        copy.PushBack(4);
        CHECK(original.Size() == 3);
        CHECK(copy.Size() == 4);
    }
    
    SECTION("Copy of empty list")
    {
        CMyList<int> original;
        CMyList<int> copy(original);
        
        CHECK(copy.Empty());
        CHECK(copy.begin() == copy.end());
    }
}

TEST_CASE("Assignment operator")
{
    SECTION("Assign to empty list")
    {
        CMyList<int> source;
        source.PushBack(1);
        source.PushBack(2);
        
        CMyList<int> dest;
        dest = source;
        
        CHECK(dest.Size() == 2);
        
        auto it = dest.begin();
        CHECK(*it == 1);
        ++it;
        CHECK(*it == 2);
    }
    
    SECTION("Self assignment")
    {
        CMyList<int> list;
        list.PushBack(1);
        list.PushBack(2);
        
        list = list;
        
        CHECK(list.Size() == 2);
        CHECK(*list.begin() == 1);
    }
}

TEST_CASE("Move constructor")
{
    SECTION("Move transfers ownership")
    {
        CMyList<int> source;
        source.PushBack(1);
        source.PushBack(2);
        source.PushBack(3);
        
        size_t originalSize = source.Size();
        
        CMyList<int> dest(std::move(source));
        
        CHECK(dest.Size() == originalSize);
        CHECK(source.Empty());
        CHECK(source.Size() == 0);
        
        auto it = dest.begin();
        CHECK(*it == 1);
    }
}

TEST_CASE("Move assignment")
{
    SECTION("Move assignment transfers ownership")
    {
        CMyList<int> source;
        source.PushBack(10);
        source.PushBack(20);
        
        CMyList<int> dest;
        dest.PushBack(1);
        
        dest = std::move(source);
        
        CHECK(dest.Size() == 2);
        CHECK(source.Empty());
        
        auto it = dest.begin();
        CHECK(*it == 10);
        ++it;
        CHECK(*it == 20);
    }
}

TEST_CASE("Clear removes all elements")
{
    CMyList<int> list;
    list.PushBack(1);
    list.PushBack(2);
    list.PushBack(3);
    
    CHECK_FALSE(list.Empty());
    
    list.Clear();
    
    CHECK(list.Empty());
    CHECK(list.Size() == 0);
    CHECK(list.begin() == list.end());
}

TEST_CASE("String list works")
{
    CMyList<std::string> list;
    list.PushBack("Hello");
    list.PushBack("World");
    list.PushFront("First");
    
    CHECK(list.Size() == 3);
    
    auto it = list.begin();
    CHECK(*it == "First");
    ++it;
    CHECK(*it == "Hello");
    ++it;
    CHECK(*it == "World");
}

TEST_CASE("Multiple lists independent")
{
    CMyList<int> list1;
    CMyList<int> list2;
    
    list1.PushBack(1);
    list1.PushBack(2);
    list2.PushBack(100);
    list2.PushBack(200);
    
    CHECK(list1.Size() == 2);
    CHECK(list2.Size() == 2);
    
    auto it1 = list1.begin();
    CHECK(*it1 == 1);
    
    auto it2 = list2.begin();
    CHECK(*it2 == 100);
}