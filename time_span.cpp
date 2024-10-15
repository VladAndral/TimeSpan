#include "time_span.h"
#include <math.h>

using namespace std;


/*
    CONSTRUCTOR
*/
TimeSpan::TimeSpan() : _hours(-999), _minutes(-999), _seconds(-999) {   }
TimeSpan::TimeSpan(double seconds) : _hours(0), _minutes(0), _seconds(0) {
    secondsConversion(seconds);
}
TimeSpan::TimeSpan(double minutes, double seconds) : _hours(0), _minutes(0), _seconds(0) {
    minutesConversion(minutes, seconds);
}
TimeSpan::TimeSpan(double hours, double minutes, double seconds) : _hours(0), _minutes(0), _seconds(0) {
    hoursConversion(hours, minutes, seconds);
}

void TimeSpan::secondsConversion(double seconds) { // 127.86 seconds = 2 minutes .131 minutes

    double timeInMinutes = seconds/60; // 127.86(seconds)/60 = 2.131 (minutes)
    int minutesWholeNumber = int(timeInMinutes); // 2
    double secondsLeftOverInDecimal = (int(timeInMinutes*100)%100)/100.0; // .13
    double convertedSeconds = 60*secondsLeftOverInDecimal; // 60*.13 = 7.8 (seconds)
    int secondsDecimal = int(convertedSeconds*100)%100; // 86
    if (secondsDecimal >= 50) {
        convertedSeconds=ceil(convertedSeconds); // 7.86 --> 8
    } else {
        convertedSeconds=floor(convertedSeconds); // 7.44 --> 7
    }

    int convertedHours = minutesWholeNumber/60;

    _seconds = convertedSeconds;
    _minutes += minutesWholeNumber;
    _hours += convertedHours;
}

void TimeSpan::minutesConversion(double minutes, double seconds) { // 127.86 minutes = 2 hours .131 hours
    secondsConversion(seconds);
    double timeInHours = minutes/60; // 127.86(seconds)/60 = 2.131 (hours)
    int hoursWholeNumber = int(timeInHours); // 2
    if (hoursWholeNumber) { // If hours is zero, no need to change minutes
        double minutesLeftOverInDecimal = (int(timeInHours*100)%100)/100.0; // .13
        double convertedMinutes = 60*minutesLeftOverInDecimal; // 60*.13 = 7.8 (minutes)
        int minutesDecimal = int(convertedMinutes*100)%100; // 86
        _seconds += 60*(minutesDecimal/100.0); // Add extra to seconds
        if (_seconds > 60) {
            secondsConversion(_seconds); // Make sure seconds isn't over 60
        }
        _minutes += convertedMinutes;
    } else {
        _minutes += minutes;
    }
    // if (minutesDecimal >= 50) {
    //     convertedMinutes=ceil(convertedMinutes); // 7.86 --> 8
    // } else {
    //     convertedMinutes=floor(convertedMinutes); // 7.44 --> 7
    // }

    _hours += hoursWholeNumber;
}

    void TimeSpan::hoursConversion(double hours, double minutes, double seconds) {
        minutesConversion(minutes, seconds);
        // double timeInHours = minutes/60; // 127.86(seconds)/60 = 2.131 (minutes)
        // int HoursWholeNumber = int(timeInHours); // 2
        double minutesLeftOverInDecimal = (int(hours*100)%100)/100.0; // .13
        double convertedMinutes = 60*minutesLeftOverInDecimal; // 60*.13 = 7.8 (seconds)
        int minutesDecimal = int(convertedMinutes*100)%100; // 86
        if (minutesDecimal >= 50) {
            convertedMinutes=ceil(convertedMinutes); // 7.86 --> 8
        } else {
            convertedMinutes=floor(convertedMinutes); // 7.44 --> 7
        }

        _hours += int(hours);
        _minutes += convertedMinutes;
        if (_minutes > 60) {
            minutesConversion(_minutes, 0);
        }
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
    stream << hours << " hours, " << minutes << " minutes, " << seconds << " seconds";
    return stream;
}