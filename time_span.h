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
        void set_time(int hours, int minutes, int seconds);

        // CONSTRUCTOR
        TimeSpan(int hours, int minutes, int seconds);
        TimeSpan(int minutes, int seconds);
        TimeSpan(int seconds);
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
        TimeSpan operator+=(const TimeSpan& timeSpanObject) const;
        TimeSpan operator-=(const TimeSpan& timeSpanObject) const;

        friend ostream& operator<<(ostream& stream, const TimeSpan& timeSpan);


        void secondsConversion(); // Could be private?
        void minutesConversion();



    private:
        int _hours;
        int _minutes;
        int _seconds;



};

#endif