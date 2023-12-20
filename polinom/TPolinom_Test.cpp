#include <iostream>
#include "TList.h"
#include "TPolinom.h"
using namespace std;


int main()
{
	setlocale(LC_ALL, "ru");
    cout << "Сумма одинаковых по длине полиномов с одним общим слагаемым" << endl;
    TPolinom p1("123245762398");
    TPolinom p2("523276457895");

    cout << "Полином p1: " << p1.ToString() << endl;
    cout << "Полином p2: " << p2.ToString() << endl;

    TPolinom sum = p1 + p2;
    cout << endl;
    cout << "Сумма разных по длине полиномов с одним общим слагаемым" << endl;
    TPolinom p3("1232");
    TPolinom p4("523276457895");

    cout << "Полином p3: " << p3.ToString() << endl;
    cout << "Полином p4: " << p4.ToString() << endl;

    sum = p3 + p4;
    
    //cout << "result1 "<< sum.ToString() << endl;

    /*TMonom m(2, 1, 1, 1);
    TPolinom mult = p1.MultMonom(m);
    cout << "Умножение полинома p1 на моном m: " << mult.ToString() << endl;*/

	

}