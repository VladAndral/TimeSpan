#ifndef TIME_SPAN_
#define TIME_SPAN_
#include <iostream>

using namespace std;

class TimeSpan {

    public:

        // SETS N GETS
        int hours() const;
        int minutes() const;
        int seconds() const;
        double thisTimeInSeconds() const;
        double tsObjectTimeInSeconds(const TimeSpan& timeSpanObject) const;
        void set_time(double hours, double minutes, double seconds);

        // CONSTRUCTOR
        TimeSpan(double hours, double minutes, double seconds);
        TimeSpan(double minutes, double seconds);
        TimeSpan(double seconds);
        TimeSpan();

        // OPERATOR OVERLOADS
        bool operator==(const TimeSpan& timeSpanObject) const;
        bool operator!=(const TimeSpan& timeSpanObject) const;
        bool operator>(const TimeSpan& timeSpanObject) const;
        bool operator<=(const TimeSpan& timeSpanObject) const;
        bool operator<(const TimeSpan& timeSpanObject) const;
        bool operator>=(const TimeSpan& timeSpanObject) const;
        
        TimeSpan operator+(const TimeSpan& timeSpanObject) const;
        TimeSpan operator-(const TimeSpan& timeSpanObject) const;
        TimeSpan operator-();
        TimeSpan operator+=(const TimeSpan& timeSpanObject);
        TimeSpan operator-=(const TimeSpan& timeSpanObject);

        friend ostream& operator<<(ostream& stream, const TimeSpan& timeSpan);
        friend istream& operator>>(istream& stream, TimeSpan& timeSpan);

    private:
        int _hours;
        int _minutes;
        int _seconds;

        void negativeToPositive(double& hours, double& minutes, double& seconds);
        double convertMinutesToSeconds(double minutes) const;
        double convertHoursToSeconds(double hours) const;
        void secondsConversion(double seconds);
        void handleNegativeSeconds(double seconds);
        void handleNegativeMinutes(double minutes);
        void handleNegativeHours(double hours);




};

#endif