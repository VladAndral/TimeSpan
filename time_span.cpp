#include "time_span.h"

using namespace std;


/*
    CONSTRUCTOR
*/
TimeSpan::TimeSpan() : _hours(-999), _minutes(-999), _seconds(-999) {   }
TimeSpan::TimeSpan(int seconds) : _hours(0), _minutes(0), _seconds(seconds) {
    secondsConversion();
}
TimeSpan::TimeSpan(int minutes, int seconds) : _hours(0), _minutes(minutes), _seconds(seconds) {
    minutesConversion();
}
TimeSpan::TimeSpan(int hours, int minutes, int seconds) : _hours(hours), _minutes(minutes), _seconds(seconds) {
    minutesConversion();
}

void TimeSpan::secondsConversion() {
    int convertedSeconds  =  _seconds%60;
    int convertedMinutes = _seconds/60; // Should be integer division and give integer
    int convertedHours = convertedMinutes/60;

    _seconds = convertedSeconds;
    _minutes += convertedMinutes;
    _hours += convertedHours;
}

void TimeSpan::minutesConversion() {
    secondsConversion();
    int convertedMinutes = _minutes%60;
    int convertedHours = _minutes/60;
    _minutes = convertedMinutes;
    _hours += convertedHours;
}

void TimeSpan::set_time(int hours, int minutes, int seconds) {
    _seconds = seconds;
    _minutes = minutes;
    _hours = hours;
}




/*
    GETS AND SETS
*/
/*
int hours() const { 
Without the 'TimeSpan::hours()', this is not a function from the class 'TimeSpan'.
Since it is not a part of the class 'TimeSpan', it does not have access to private data; 
the 'const' specifier is not necessary.
*/
int TimeSpan::hours() const {
    return _hours;
}
int TimeSpan::minutes() const {
    return _minutes;
}
int TimeSpan::seconds() const {
    return _seconds;
}

/*
    OVERLOADS
*/
ostream& operator<<(ostream& stream, const TimeSpan& timeSpan) {
    int hours = timeSpan.hours();
    int minutes = timeSpan.minutes();
    int seconds = timeSpan.seconds();
    stream << hours << ", " << minutes << ", " << seconds;
    return stream;
}