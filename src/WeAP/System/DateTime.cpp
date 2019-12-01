#include "DateTime.h"

namespace WeAP { namespace System {


DateTime::DateTime()
{
    gettimeofday(&this->tv, NULL);
    this->seconds = this->tv.tv_sec;
    localtime_r(&this->seconds, &this->date);
}

DateTime::DateTime(time_t seconds)
{
    this->tv.tv_sec = seconds;
    this->tv.tv_usec = 0;
    this->seconds = seconds;
    localtime_r(&this->seconds, &this->date);

}

DateTime::DateTime(int year, int month, int day)
{
    this->Init(year, month, day, 0, 0, 0);
}

DateTime::DateTime(int year, int month, int day, int hour,  int minute,int second)
{
    this->Init(year, month, day, hour, minute, second);
}

DateTime::DateTime(const std::string& datetimeStr)
{
    this->Init(datetimeStr, "%Y-%m-%d %H:%M:%S");
}

DateTime::DateTime(const std::string& datetimeStr, const std::string& formaterStr)
{
    this->Init(datetimeStr, formaterStr);
}

DateTime::~DateTime()
{
}

DateTime& DateTime::operator=(const DateTime &other)
{
    if(this == &other)
    {
        return *this;
    }
    
    this->seconds = other.seconds;
    this->date = other.date;

    return *this;
}

void DateTime::AddYears(const int years)
{       
    this->date.tm_year = this->date.tm_year+years;
    this->seconds = mktime(&this->date);

    return *this;
}

/*
@todo
void DateTime::AddMonths(const int months)
{
    int a  =(int)((this->date.tm_mon + months)/12);

    cout << "a:" << a << endl;

    this->date.tm_year = this->date.tm_year+a;
    this->date.tm_mon = this->date.tm_mon+(int)((this->date.tm_mon+months)%12)-1;
    this->seconds = mktime(&this->date);
    return *this;
}
*/

void DateTime::AddDays(const int days)
{
    this->AddSeconds(days*24*60*60);
    return *this;
}

void DateTime::AddHours(const int hours)
{
    this->AddSeconds(hours*60*60);
    return *this;
}

void DateTime::AddMinutes(const int minutes)
{
    this->AddSeconds(minutes *60);
    return *this;
}

void DateTime::AddSeconds(const int seconds)
{
    this->seconds = this->seconds+seconds;
    localtime_r(&this->seconds,&this->date);
    return *this; 
}

void DateTime::AddWeeks(const int weeks)
{
    this->AddDays(weeks*7);
    return *this;
}

int DateTime::Compare(const DateTime& dt1,const DateTime& dt2)
{
    if( dt1.seconds == dt2.seconds)
    {
        return 0;
    }
        
    if(dt1.seconds < dt2.seconds)
    {
        return -1;
    }

    return 1;
}

int DateTime::CompareTo(const DateTime& other)
{
    if(this->seconds == other.seconds)
    {
        return 0;
    }
        
    if(this->seconds < other.seconds)
    {
        return -1;
    }

    return 1;
}

bool DateTime::Equals(const DateTime& dateTime)
{
    if(this->seconds == dateTime.seconds)
    {
        return true;
    }
        
    return false;
}

bool DateTime::Equals(const DateTime& value1,const DateTime& value2)
{
    if(value1.seconds == value2.seconds)
    {
        return true;
    }
        
    return false;
}

int DateTime::ToDate()
{
    return this->GetYear() *10000 + this->GetMonth()*100 + this->GetDay();
}

std::string DateTime::ToDateString()
{        
    return this->ToString("%Y-%m-%d");
}

std::string DateTime::ToDateTimeString()
{
    return this->ToString("%Y-%m-%d %H:%M:%S");
}

std::string DateTime::ToString(const std::string& formaterStr)
{
    char s[256] = {0};
    strftime(s, sizeof(s), formaterStr.c_str(), &this->date);
    std::string str(s);
    return str;
}

int DateTime::GetYear()
{
    return this->date.tm_year + 1900;
}

int DateTime::GetMonth()
{
    return this->date.tm_mon + 1;
}

int DateTime::GetDay()
{
    return this->date.tm_mday;
}
int DateTime::GetHour()
{
    return this->date.tm_hour;
}

int DateTime::GetMinute()
{
    return this->date.tm_min;
}

int DateTime::GetSecond()
{
    return this->date.tm_sec;
}

int DateTime::DayOfWeek() 
{
    return this->date.tm_wday;
}

int DateTime::DayOfYear()
{
    return this->date.tm_yday;
}

time_t DateTime::GetSeconds()
{
    return this->seconds;
}

long long DateTime::GetMicroseconds()
{
    long long timestampMicro = this->tv.tv_sec * 1000000 + this->tv.tv_usec;
    return timestampMicro;
}

time_t DateTime::GetTimestamp()
{
    return this->seconds;
}


DateTime DateTime::Now()
{
    DateTime datetime;
    return datetime;
}


bool DateTime::operator == (const DateTime &dateTime)
{
    return this->Equals(dateTime);
}

bool DateTime::operator > (const DateTime &dateTime)
{
    if(this->seconds > dateTime.seconds)
        return true;
    return false;
}

bool DateTime::operator < (const DateTime &dateTime)
{
    if(this->seconds <dateTime.seconds)
        return true;
    return false;    
}

bool DateTime::operator >= (const DateTime &dateTime)
{
    if(this->seconds >= dateTime.seconds)
        return true;
    return false;
}

bool DateTime::operator <= (const DateTime &dateTime)
{
    if(this->seconds <= dateTime.seconds)
        return true;
    return false;    
}

bool DateTime::operator != (const DateTime &dateTime)
{
        if(this->seconds != dateTime.seconds)
            return true;
        return false;
}

void DateTime::Init(int year,int month,int day,int hour,int minute,int second)
{
    tm t;
    memset(&t, 0, sizeof(struct tm));
    t.tm_year = year-1900;
    t.tm_mon = month-1;
    t.tm_mday = day;
    t.tm_hour = hour;
    t.tm_min = minute;
    t.tm_sec = second;
    this->seconds = mktime(&t);
    localtime_r(&this->seconds,&this->date);
    this->tv.tv_sec = this->seconds;
    this->tv.tv_usec = 0;
}

void DateTime::Init(const std::string& dateTimeStr,const std::string& formaterStr)
{
    memset(&this->date, 0, sizeof(struct tm));
    strptime(dateTimeStr.c_str(), formaterStr.c_str(), &this->date);
    this->seconds = mktime(&this->date);
    this->tv.tv_sec = this->seconds;
    this->tv.tv_usec = 0;
}

}}
