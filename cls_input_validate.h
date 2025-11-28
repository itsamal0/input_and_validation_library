#pragma once
#include <iostream>
#include <string>
#include "cls_string.h"
#include "cls_date.h"
#include <limits>

using namespace std;

class clsInputValidate {

public:
    
    // --- Basic Checks ---
    static bool isValidNumber() {
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return false;
        }
        return true;
    }

    static bool isValidDate(clsDate date) {
        return clsDate::IsValidDate(date);
    }
    
    // --- Range Checks ---
    template <typename T>
    static bool isNumberInRange(T n, T minValue, T maxValue) {
        return n >= minValue && n <= maxValue;
    }

    static bool isDateBetween(clsDate date, clsDate from, clsDate to) {
        if ((clsDate::isDate1AfterDate2(date, from) || clsDate::isDate1EqualDate2(date, from))
            &&
            (clsDate::isDate1BeforeDate2(date, to) || clsDate::isDate1EqualDate2(date, to))
           ) {
            return true;
        }

        if ((clsDate::isDate1AfterDate2(date, to) || clsDate::isDate1EqualDate2(date, to))
            &&
            (clsDate::isDate1BeforeDate2(date, from) || clsDate::isDate1EqualDate2(date, from))
           ) {
            return true;
        }

        return false;
    }
    
    // --- Reading Functions ---
    template <typename T>
    static T readNumber(string errorMessage = "Invalid input! Please enter a valid number:\n") {
        T num;
        while (!(cin >> num)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << errorMessage;
        }
        
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return num;
    }

    template <typename T>
    static T readNumberBetween(T from, T to, string errorMessage = "The number is out of the allowed range! Enter again:\n") {
        T num = readNumber<T>();

        while (!isNumberInRange(num, from, to)) {
            cout << errorMessage;
            num = readNumber<T>();
        }
        return num;
    }
    
};