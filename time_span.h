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
        TimeSpan operator+=(const TimeSpan& timeSpanObject) const;
        TimeSpan operator-=(const TimeSpan& timeSpanObject) const;

        friend ostream& operator<<(ostream& stream, const TimeSpan& timeSpan);


        void secondsConversion(double seconds); // Could be private?
        void handleNegativeSeconds(double seconds);
        void handleNegativeMinutes(double minutes);
        void handleNegativeHours(double hours);



    private:
        int _hours;
        int _minutes;
        int _seconds;
        void negativeToPositive(double& hours, double& minutes, double& seconds);
        double convertMinutesToSeconds(double minutes);
        double convertHoursToSeconds(double hours);




};

#endif