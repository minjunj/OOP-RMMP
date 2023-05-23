#pragma once
#include <iostream>

using namespace std;

class Sample
{
private:
    int n;
public:
    Sample(int n)
    {
        this->n =n;
    }
    void print()
    {
        cout << n <<endl;
        return;
    }
};