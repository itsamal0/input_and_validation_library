#pragma warning(disable : 4996) // Disable unsafe function warning in Visual Studio
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <algorithm>
#include "cls_string.h"

using namespace std;

class clsDate {
private:
  short _Day = 1;
  short _Month = 1;
  short _Year = 1900;

public:
  clsDate() {
    time_t t = time(0);
    tm *now = localtime( & t);
    _Day = now -> tm_mday;
    _Month = now -> tm_mon + 1;
    _Year = now -> tm_year + 1900;
  }

  clsDate(string sDate) {

    vector < string > vDate;
    vDate = ClsString::splitString(sDate, "/");

    _Day = stoi(vDate[0]);
    _Month = stoi(vDate[1]);
    _Year = stoi(vDate[2]);

  }

  clsDate(short Day, short Month, short Year) {

    _Day = Day;
    _Month = Month;
    _Year = Year;

  }

  clsDate(short DateOrderInYear, short Year) {
    *this = getDateFromDayOrderInYear(DateOrderInYear, Year);
  }

  void SetDay(short Day) {
    _Day = Day;
  }

  short GetDay() {
    return _Day;
  }

  void SetMonth(short Month) {
    _Month = Month;
  }

  short GetMonth() {
    return _Month;
  }

  void SetYear(short Year) {
    _Year = Year;
  }

  short GetYear() {
    return _Year;
  }

  void Print() {
    cout << DateToString() << endl;
  }

  static clsDate GetSystemDate() {
    //system date
    time_t t = time(0);
    tm *now = localtime( & t);

    short Day, Month, Year;

    Year = now -> tm_year + 1900;
    Month = now -> tm_mon + 1;
    Day = now -> tm_mday;

    return clsDate(Day, Month, Year);
  }

  static bool IsValidDate(clsDate Date) {

    if (Date._Day < 1 || Date._Day > 31)
      return false;

    if (Date._Month < 1 || Date._Month > 12)
      return false;

    if (Date._Month == 2) {
      if (isLeapYear(Date._Year)) {
        if (Date._Day > 29)
          return false;
      } else {
        if (Date._Day > 28)
          return false;
      }
    }

    short DaysInMonth = getDaysInMonth(Date._Year, Date._Month);

    if (Date._Day > DaysInMonth)
      return false;

    return true;

  }

  bool IsValid() {
    return IsValidDate( *this);
  }

  static string DateToString(clsDate Date) {
    return to_string(Date._Day) + "/" + to_string(Date._Month) + "/" + to_string(Date._Year);
  }

  string DateToString() {
    return DateToString( *this);
  }

  // =====================================
  //       Static Utility Functions
  // =====================================
  // ===== Year Functions =====
  static bool isLeapYear(short Year) {
    return (Year % 400 == 0) || (Year % 4 == 0 && Year % 100 != 0);
  }

  static clsDate getDateFromDayOrderInYear(short DateOrderInYear, short Year) {

    clsDate Date;
    short RemainingDays = DateOrderInYear;
    short MonthDays = 0;

    Date._Year = Year;
    Date._Month = 1;

    while (true) {
      MonthDays = getDaysInMonth(Year, Date._Month);

      if (RemainingDays > MonthDays) {
        RemainingDays -= MonthDays;
        Date._Month++;
      } else {
        Date._Day = RemainingDays;
        break;
      }

    }

    return Date;
  }

  static short getDaysInYear(int year) {
    return isLeapYear(year) ? 366 : 365;
  }

  static short getHoursInYear(int year) {
    return getDaysInYear(year) *24;
  }

  static int getMinutesInYear(int year) {
    return getHoursInYear(year) *60;
  }

  static int getSecondsInYear(int year) {
    return getMinutesInYear(year) *60;
  }

  // ===== Month Functions =====
  static short getDaysInMonth(short year, short month) {
    const short MONTHS_31[7] = {1, 3, 5, 7, 8, 10, 12};
    if (month == 2) {
      return isLeapYear(year) ? 29 : 28;
    }

    return (find(begin(MONTHS_31), end(MONTHS_31), month) != end(MONTHS_31)) ? 31 : 30;
  }

  static short getHoursInMonth(short year, short month) {
    return getDaysInMonth(year, month) *24;
  }

  static int getMinutesInMonth(short year, short month) {
    return getHoursInMonth(year, month) *60;
  }

  static int getSecondsInMonth(short year, short month) {
    return getMinutesInMonth(year, month) *60;
  }

  static string getMonthShortName(short month) {
    string months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    if (month < 1 || month > 12)
      return "Invalid";
    return months[month - 1];
  }

  // ===== Week & Day Utilities =====
  static short getDayOfWeekOrder(short year, short month, short day) {
    short a = (14 - month) / 12;
    year = year - a;
    month = month + (12 *a) - 2;
    return (day + year + (year / 4) - (year / 100) + (year / 400) + (31 *month / 12)) % 7;
  }

  static string getDayShortName(short day) {
    string days[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    if (day < 0 || day > 6)
      return "Invalid";
    return days[day];
  }

  static bool isEndOfWeek(short dayOrderInWeek) {
    return dayOrderInWeek == 6; // Saturday
  }

  static bool isWeekEnd(short dayOrderInWeek) {
    return (dayOrderInWeek == 0 || dayOrderInWeek == 6);
  }

  static bool isBusinessDay(short dayOrderInWeek) {
    return !isWeekEnd(dayOrderInWeek);
  }

  static short daysUntilTheEndOfWeek(short dayOrderInWeek) {
    return 6 - dayOrderInWeek;
  }

  static short countDaysFromYearStart(short day, short month, short year) {
    short totalDays = 0;
    for (short i = 1; i < month; i++) {
      totalDays += getDaysInMonth(year, i);
    }
    totalDays += day;
    return totalDays;
  }

  static short daysUntilTheEndOfMonth(short year, short month, short day) {
    return getDaysInMonth(year, month) - day;
  }

  static short daysUntilTheEndOfYear(short year, short month, short day) {
    return getDaysInYear(year) - countDaysFromYearStart(day, month, year);
  }

  static bool isLastDayInMonth(short year, short month, short day) {
    return day == getDaysInMonth(year, month);
  }

  static bool isLastMonthInYear(short month) {
    return month == 12;
  }

  // ===== Increment Functions =====
  static clsDate increaseDateByOneDay(clsDate Date) {
    if (isLastDayInMonth(Date._Year, Date._Month, Date._Day) && isLastMonthInYear(Date._Month)) {
      Date._Day = 1;
      Date._Month = 1;
      Date._Year++;
    } else if (isLastDayInMonth(Date._Year, Date._Month, Date._Day)) {
      Date._Day = 1;
      Date._Month++;
    } else {
      Date._Day++;
    }
    return Date;
  }

  static clsDate increaseDateByXDays(clsDate Date, short days) {
    for (short i = 0; i < days; i++) {
      Date = increaseDateByOneDay(Date);
    }
    return Date;
  }

  static clsDate increaseDateByOneWeek(clsDate Date) {
    return increaseDateByXDays(Date, 7);
  }

  static clsDate increaseDateByXWeeks(clsDate Date, short weeks) {
    for (short i = 0; i < weeks; i++) {
      Date = increaseDateByOneWeek(Date);
    }
    return Date;
  }

  static clsDate increaseDateByOneMonth(clsDate Date) {
    if (Date._Month == 12) {
      Date._Month = 1;
      Date._Year++;
    } else {
      Date._Month++;
    }

    short numberOfDaysInMonth = getDaysInMonth(Date._Year, Date._Month);
    if (Date._Day > numberOfDaysInMonth) {
      Date._Day = numberOfDaysInMonth;
    }
    return Date;
  }

  static clsDate increaseDateByXMonths(clsDate Date, short months) {
    for (short i = 0; i < months; i++) {
      Date = increaseDateByOneMonth(Date);
    }
    return Date;
  }

  static clsDate increaseDateByOneYear(clsDate Date) {
    Date._Year++;
    return Date;
  }

  static clsDate increaseDateByXYears(clsDate Date, short years) {
    Date._Year += years;
    return Date;
  }

  static clsDate increaseDateByOneDecade(clsDate Date) {
    Date._Year += 10;
    return Date;
  }

  static clsDate increaseDateByOneCentury(clsDate Date) {
    Date._Year += 100;
    return Date;
  }

  static clsDate increaseDateByOneMillennium(clsDate Date) {
    Date._Year += 1000;
    return Date;
  }

  // ===== Decrement Functions =====
  static clsDate decreaseDateByOneDay(clsDate Date) {
    if (Date._Day == 1) {
      if (Date._Month == 1) {
        Date._Month = 12;
        Date._Year--;
      } else {
        Date._Month--;
      }
      Date._Day = getDaysInMonth(Date._Year, Date._Month);
    } else {
      Date._Day--;
    }
    return Date;
  }

  static clsDate decreaseDateByXDays(clsDate Date, short days) {
    for (short i = 0; i < days; i++) {
      Date = decreaseDateByOneDay(Date);
    }
    return Date;
  }

  static clsDate decreaseDateByOneWeek(clsDate Date) {
    return decreaseDateByXDays(Date, 7);
  }

  static clsDate decreaseDateByXWeeks(clsDate Date, short weeks) {
    for (short i = 0; i < weeks; i++) {
      Date = decreaseDateByOneWeek(Date);
    }
    return Date;
  }

  static clsDate decreaseDateByOneMonth(clsDate Date) {
    if (Date._Month == 1) {
      Date._Month = 12;
      Date._Year--;
    } else {
      Date._Month--;
    }

    short numberOfDaysInMonth = getDaysInMonth(Date._Year, Date._Month);
    if (Date._Day > numberOfDaysInMonth) {
      Date._Day = numberOfDaysInMonth;
    }
    return Date;
  }

  static clsDate decreaseDateByXMonths(clsDate Date, short months) {
    for (short i = 0; i < months; i++) {
      Date = decreaseDateByOneMonth(Date);
    }
    return Date;
  }

  static clsDate decreaseDateByOneYear(clsDate Date) {
    Date._Year--;
    return Date;
  }

  static clsDate decreaseDateByXYears(clsDate Date, short years) {
    Date._Year -= years;
    return Date;
  }

  static clsDate decreaseDateByOneDecade(clsDate Date) {
    Date._Year -= 10;
    return Date;
  }

  static clsDate decreaseDateByOneCentury(clsDate Date) {
    Date._Year -= 100;
    return Date;
  }

  static clsDate decreaseDateByOneMillennium(clsDate Date) {
    Date._Year -= 1000;
    return Date;
  }

  // ===== Comparison & Difference Functions =====
  static bool isDate1BeforeDate2(const clsDate & Date1,
    const clsDate & Date2) {
    if (Date1._Year != Date2._Year)
      return Date1._Year < Date2._Year;
    if (Date1._Month != Date2._Month)
      return Date1._Month < Date2._Month;
    return Date1._Day < Date2._Day;
  }

  static bool isDate1EqualDate2(const clsDate & Date1,
    const clsDate & Date2) {
    return (Date1._Year == Date2._Year &&
      Date1._Month == Date2._Month &&
      Date1._Day == Date2._Day);
  }

  static bool isDate1AfterDate2(const clsDate & Date1,
    const clsDate & Date2) {
    return (!isDate1BeforeDate2(Date1, Date2) &&
      !isDate1EqualDate2(Date1, Date2));
  }

  static void swapDates(clsDate & Date1, clsDate & Date2) {
    clsDate TempDate = Date1;
    Date1 = Date2;
    Date2 = TempDate;
  }

  static int getDifferenceInDays(clsDate Date1, clsDate Date2, bool includeEndDay = false) {
		//this will take care of negative diff
		int days = 0;
		short sawpFlagValue = 1;

		if (!isDate1BeforeDate2(Date1, Date2))
		{
			//Swap Dates 
			swapDates(Date1, Date2);
			sawpFlagValue = -1;

		}

		while (isDate1BeforeDate2(Date1, Date2))
		{
			days++;
			Date1 = increaseDateByOneDay(Date1);
		}

		return includeEndDay ? ++days * sawpFlagValue : days * sawpFlagValue;
   }

  enum enCompareTwoDates {
    BEFORE = -1, EQUAL = 0, AFTER = 1
  };

  static enCompareTwoDates compareTwoDates(clsDate Date1, clsDate Date2) {
    if (isDate1BeforeDate2(Date1, Date2))
      return BEFORE;
    if (isDate1EqualDate2(Date1, Date2))
      return EQUAL;
    return AFTER;
  }

  // =====================================
  //      Object Member Functions
  // =====================================
  // ===== Year Functions =====
  bool isLeapYear() {
    return isLeapYear(_Year);
  }

  short getDaysInYear() {
    return getDaysInYear(_Year);
  }

  short getHoursInYear() {
    return getHoursInYear(_Year);
  }

  int getMinutesInYear() {
    return getMinutesInYear(_Year);
  }

  int getSecondsInYear() {
    return getSecondsInYear(_Year);
  }

  // ===== Month Functions =====
  short getDaysInMonth() {
    return getDaysInMonth(_Year, _Month);
  }

  short getHoursInMonth() {
    return getHoursInMonth(_Year, _Month);
  }

  int getMinutesInMonth() {
    return getMinutesInMonth(_Year, _Month);
  }

  int getSecondsInMonth() {
    return getSecondsInMonth(_Year, _Month);
  }

  string getMonthShortName() {
    return getMonthShortName(_Month);
  }

  // ===== Week & Day Utilities =====
  short getDayOfWeekOrder() {
    return getDayOfWeekOrder(_Year, _Month, _Day);
  }

  string getDayShortName() {
    return getDayShortName(getDayOfWeekOrder());
  }

  bool isEndOfWeek() {
    return isEndOfWeek(getDayOfWeekOrder());
  }

  bool isWeekEnd() {
    return isWeekEnd(getDayOfWeekOrder());
  }

  bool isBusinessDay() {
    return isBusinessDay(getDayOfWeekOrder());
  }

  short daysUntilTheEndOfWeek() {
    return daysUntilTheEndOfWeek(getDayOfWeekOrder());
  }

  short daysUntilTheEndOfMonth() {
    return getDaysInMonth(_Year, _Month) - _Day;
  }

  short daysUntilTheEndOfYear() {
    return getDaysInYear(_Year) - countDaysFromYearStart(_Day, _Month, _Year);
  }

  bool isLastDayInMonth() {
    return _Day == getDaysInMonth(_Year, _Month);
  }

  // ===== Increment Functions =====
  void increaseDateByOneDay() {
    *this = increaseDateByOneDay( *this);
  }

  void increaseDateByXDays(short Days) {
    *this = increaseDateByXDays( *this, Days);
  }

  void increaseDateByOneWeek() {
    *this = increaseDateByOneWeek( *this);
  }

  void increaseDateByXWeeks(short Weeks) {
    *this = increaseDateByXWeeks( *this, Weeks);
  }

  void increaseDateByOneMonth() {
    *this = increaseDateByOneMonth( *this);
  }

  void increaseDateByXMonths(short Months) {
    *this = increaseDateByXMonths( *this, Months);
  }

  void increaseDateByOneYear() {
    *this = increaseDateByOneYear( *this);
  }

  void increaseDateByXYears(short Years) {
    *this = increaseDateByXYears( *this, Years);
  }

  void increaseDateByOneDecade() {
    *this = increaseDateByOneDecade( *this);
  }

  void increaseDateByOneCentury() {
    *this = increaseDateByOneCentury( *this);
  }

  void increaseDateByOneMillennium() {
    *this = increaseDateByOneMillennium( *this);
  }

  // ===== Decrement Functions =====
  void decreaseDateByOneDay() {
    *this = decreaseDateByOneDay( *this);
  }

  void decreaseDateByXDays(short Days) {
    *this = decreaseDateByXDays( *this, Days);
  }

  void decreaseDateByOneWeek() {
    *this = decreaseDateByOneWeek( *this);
  }

  void decreaseDateByXWeeks(short Weeks) {
    *this = decreaseDateByXWeeks( *this, Weeks);
  }

  void decreaseDateByOneMonth() {
    *this = decreaseDateByOneMonth( *this);
  }

  void decreaseDateByXMonths(short Months) {
    *this = decreaseDateByXMonths( *this, Months);
  }

  void decreaseDateByOneYear() {
    *this = decreaseDateByOneYear( *this);
  }

  void decreaseDateByXYears(short Years) {
    *this = decreaseDateByXYears( *this, Years);
  }

  void decreaseDateByOneDecade() {
    *this = decreaseDateByOneDecade( *this);
  }

  void decreaseDateByOneCentury() {
    *this = decreaseDateByOneCentury( *this);
  }

  void decreaseDateByOneMillennium() {
    *this = decreaseDateByOneMillennium( *this);
  }
 
  // ===== Comparison & Difference Functions =====
  bool isBefore(const clsDate & Date2) {
    return isDate1BeforeDate2( *this, Date2);
  }

  bool isEqual(const clsDate & Date2) {
    return isDate1EqualDate2( *this, Date2);
  }

  bool isAfter(const clsDate & Date2) {
    return isDate1AfterDate2( *this, Date2);
  }

  int getDifferenceInDays(clsDate Date2, bool IncludeEndDay = false) {
    return getDifferenceInDays( *this, Date2, IncludeEndDay);
  }

  enCompareTwoDates compareTo(clsDate Date2) {
    return compareTwoDates( *this, Date2);
  }
};