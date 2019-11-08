#ifndef __WEAP_DATETIME_H__
#define __WEAP_DATETIME_H__

#include "Object.h"

namespace WeAP { namespace System {

/**
 * A date and time object 
 * 
 * @author xzwang
 */
class DateTime : public Object
{
public:
    static int Compare(const DateTime& dt1,const DateTime& dt2);
    static bool Equals(const DateTime& value1,const DateTime& value2);
    static DateTime Now();



public:
    DateTime();
    DateTime(time_t seconds);
    DateTime(int year,int month,int day);
    DateTime(int year,int month,int day,int hour,int minute,int second);
    DateTime(const std::string& datetimeStr);
    DateTime(const std::string& datetimeStr, const std::string& formaterStr);
    virtual ~DateTime();

    DateTime& operator=(const DateTime &other);

    void AddYears(const int years);
    //void AddMonths(const int months);
    void AddDays(const int days);
    void AddHours(const int hours);
    void AddMinutes(const int minutes);
    void AddSeconds(const int seconds);
    void AddWeeks(const int weeks);

    int CompareTo(const DateTime& other);
    bool Equals(const DateTime& dateTime);

    int ToDate();
    std::string ToDateString();
    std::string ToDateTimeString();
    std::string ToString(const std::string& formaterStr);
  
    int GetYear();
    int GetMonth();
    int GetDay();
    int GetHour();
    int GetMinute();
    int GetSecond();
    int DayOfWeek();
    int DayOfYear();

    time_t GetSeconds();
    long long GetMicroseconds();

    time_t GetTimeStamp();
    
    bool operator == (const DateTime &dateTime);
    bool operator > (const DateTime &dateTime);
    bool operator < (const DateTime &dateTime);
    bool operator >= (const DateTime &dateTime);
    bool operator <= (const DateTime &dateTime);
    bool operator != (const DateTime &dateTime);

protected:
    void Init(int year,int month,int day,int hour,int minute,int second);
    void Init(const std::string& dateTimeStr, const std::string& formaterStr);

    time_t seconds;
    tm date;
    struct timeval tv;

};

}}


#endif //__WEAP_DATETIME_H__

