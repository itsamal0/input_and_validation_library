#include <iostream>
#include <string>
#include "cls_input_validate.h"
#include "cls_date.h"
using namespace std;

int main() {
    // Sets cout to display "true" or "false" instead of 1 or 0
    cout << boolalpha; 

    cout << "==========================================\n";
    cout << "  Input & Validation Library Test\n";
    cout << "==========================================\n\n";

    cout << "\nEnter Int: ";
    auto num1 = clsInputValidate::readNumber<int>("Try again (Int):\n-> Read: ");
    cout << "-> Read: " << num1 << "\n";

    cout << "\nEnter Double: ";
    auto num2 = clsInputValidate::readNumber<double>("Try again (Double):\n-> Read: ");
    cout << "-> Read: " << num2 << "\n";

    cout << "\nEnter Int [10-50]: ";
    auto num3 = clsInputValidate::readNumberBetween<int>(10, 50, "Out of Range. Try again [10-50]:\n");
    cout << "-> Read: " << num3 << "\n";

    cout << "\nEnter Double [2.5-7.5]: ";
    auto num4 = clsInputValidate::readNumberBetween<double>(2.5, 7.5, "Out of Range. Try again [2.5-7.5]:\n");
    cout << "-> Read: " << num4 << "\n\n";

    cout << "\nDate check (2024 in range 2023-2025)? -> " 
          << clsInputValidate::isDateBetween(clsDate(1, 1, 2024), clsDate(1, 1, 2023), clsDate(1, 1, 2025));
    
    cout << "\n\nIs 33/10/2024 Valid? -> " 
          << clsInputValidate::isValidDate(clsDate(35, 12, 2022)) 
          << "\n\n";

    system("pause>0");
    return 0;
}