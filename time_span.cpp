#include "time_span.h"
#include <math.h>

using namespace std;


/*
    CONSTRUCTOR
*/
TimeSpan::TimeSpan() : _hours(-999), _minutes(-999), _seconds(-999) {   }
TimeSpan::TimeSpan(double seconds) : _hours(0), _minutes(0), _seconds(0) {

    handleNegativeSeconds(seconds);
}
TimeSpan::TimeSpan(double minutes, double seconds) : _hours(0), _minutes(0), _seconds(0) {

    double minutesInTermsOfSeconds = convertMinutesToSeconds(minutes);
    seconds += minutesInTermsOfSeconds;
    handleNegativeSeconds(seconds);
}
TimeSpan::TimeSpan(double hours, double minutes, double seconds) : _hours(0), _minutes(0), _seconds(0) {

    double hoursInTermsOfSeconds = convertHoursToSeconds(hours);
    double minutesInTermsOfSeconds = convertMinutesToSeconds(minutes);
    seconds += minutesInTermsOfSeconds + hoursInTermsOfSeconds;
    handleNegativeSeconds(seconds);
}

/*
        CONVERTING TIME METHODS
*/
double TimeSpan::convertMinutesToSeconds(double minutes) {
    return minutes*60;
}

double TimeSpan::convertHoursToSeconds(double hours) {
    return hours*60*60;
}

void TimeSpan::secondsConversion(double seconds) { // 127.86 seconds = 2 minutes .131 minutes

    double timeInMinutes = seconds/60; // 127.86(seconds)/60 = 2.131 (minutes)
    int convertedMinutes = int(timeInMinutes); // 2
    double secondsLeftOverInDecimal = (int(timeInMinutes*100)%100)/100.0; // .13
    double convertedSeconds = 60*secondsLeftOverInDecimal; // 60*.13 = 7.8 (seconds)
    int secondsDecimal = int(convertedSeconds*100)%100; // 86
    if (secondsDecimal >= 50) {
        convertedSeconds=ceil(convertedSeconds); // 7.86 --> 8
    } else {
        convertedSeconds=floor(convertedSeconds); // 7.44 --> 7
    }

    int convertedHours = convertedMinutes/60;
    convertedMinutes -= 60*convertedHours;

    _seconds = convertedSeconds;
    _minutes += convertedMinutes;
    _hours += convertedHours;
}

void TimeSpan::handleNegativeSeconds(double seconds) {

    if ((seconds != 0) && (abs(seconds-1)) > abs(seconds) ) { // Check if seconds is negative
        
        int minutesToRemove = 0;
        int hoursToRemove = 0;
        minutesToRemove += abs(int(-seconds/60)); // -65 secs = 1 minute +extra, remove minute
        if (minutesToRemove > 60) {
            hoursToRemove += abs(int(minutesToRemove/60));
            minutesToRemove -= 60*hoursToRemove; // Remove hours we just converted
        }
        // Minutes will always be a whole number, no need to worry about decimals
        _hours -= hoursToRemove;
        _minutes -= minutesToRemove;

        int secondsDecimal = abs(int(seconds*100)%100); // 7.86 --> 86
        if (secondsDecimal >= 50) {
            seconds=ceil(seconds); // 7.86 --> 8
        } else {
            seconds=floor(seconds); // 7.44 --> 7
        }

        seconds = int(seconds)%60; // loop around from the subrtraction
    }

    secondsConversion(seconds);

}

void TimeSpan::handleNegativeMinutes(double minutes) {
    handleNegativeSeconds(convertMinutesToSeconds(minutes));
}

void TimeSpan::handleNegativeHours(double hours) {
    handleNegativeSeconds(convertHoursToSeconds(hours));
}

void TimeSpan::set_time(int hours, int minutes, int seconds) {
    double hoursInTermsOfSeconds = convertHoursToSeconds(hours);
    double minutesInTermsOfSeconds = convertMinutesToSeconds(minutes);
    seconds += minutesInTermsOfSeconds + hoursInTermsOfSeconds;
    handleNegativeSeconds(seconds);
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