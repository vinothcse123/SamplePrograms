#include<iostream>
#include<string>
#include<vector>
#include <chrono>
#include <thread>

using std::vector;
using std::cout;
using std::string;
using namespace std::chrono_literals;


void function2()
{
    std::this_thread::sleep_for(2s);
}

void function1()
{
    std::this_thread::sleep_for(1s);

    function2();
}

int main()
{

    function1();

    return 0;
}
