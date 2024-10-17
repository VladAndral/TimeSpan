#include "time_span.h"
#include <cmath>

using namespace std;


/*
    CONSTRUCTOR
*/
TimeSpan::TimeSpan() : _hours(0), _minutes(0), _seconds(0) {   }

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
double TimeSpan::convertMinutesToSeconds(double minutes) const {
    return minutes*60;
}

double TimeSpan::convertHoursToSeconds(double hours) const {
    return hours*60*60;
}

void TimeSpan::secondsConversion(double seconds) { // 127.86 seconds = 2 minutes .131 minutes

    double timeInMinutes = seconds/60; // 127.86(seconds)/60 = 2.131 (minutes)
    int convertedMinutes = int(timeInMinutes); // 2
    double secondsLeftOverInDecimal = (int(timeInMinutes*100)%100)/100.0; // .13
    double convertedSeconds = 60*secondsLeftOverInDecimal; // 60*.13 = 7.8 (seconds)
    int secondsDecimal = int(convertedSeconds*100)%100; // .86 --> 86
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

void TimeSpan::set_time(double hours, double minutes, double seconds) {
    _hours = _minutes = _seconds = 0;
    double hoursInTermsOfSeconds = convertHoursToSeconds(hours);
    double minutesInTermsOfSeconds = convertMinutesToSeconds(minutes);
    seconds += minutesInTermsOfSeconds + hoursInTermsOfSeconds;
    handleNegativeSeconds(seconds);
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

istream& operator>>(istream& stream, TimeSpan& timeSpan) { // Does not strip leading/trailing whitespace
    string timeSpanInput;
    stream >> timeSpanInput;

    string hourString, minuteString, secondString;
    double hours, minutes, seconds;
    int timeSegment = 0;
    for (int i = 0; i < timeSpanInput.length(); i++) {

        char currentChar = timeSpanInput[i];

        if (currentChar == ',') {
            timeSegment++;
            continue;
        } else if (currentChar == ' ') {
            continue;
        }

        switch (timeSegment) {
            case 0:
                hourString += currentChar;
                continue;
            case 1:
                minuteString += currentChar;
                continue;
            case 2:
                secondString += currentChar;
                continue;
            default:
                hourString = minuteString = secondString = "-99999";
        }
    }
    hours = stod(hourString);
    minutes = stod(minuteString);
    seconds = stod(secondString);
    timeSpan.set_time(hours, minutes, seconds);
    return stream;
}

bool TimeSpan::operator==(const TimeSpan& timeSpanObject) const {
    return (
        _hours == timeSpanObject.hours() &&
        _minutes == timeSpanObject.minutes() &&
        _seconds == timeSpanObject.seconds()
    );
}

bool TimeSpan::operator!=(const TimeSpan& timeSpanObject) const {
    return !(
        _hours == timeSpanObject.hours() &&
        _minutes == timeSpanObject.minutes() &&
        _seconds == timeSpanObject.seconds()
    );
}

double TimeSpan::thisTimeInSeconds() const {
    return (
        convertHoursToSeconds(_hours) +
        convertMinutesToSeconds(_minutes) +
        _seconds
    );
}

double TimeSpan::tsObjectTimeInSeconds(const TimeSpan& timeSpanObject) const {
    return (
        convertHoursToSeconds(timeSpanObject.hours()) +
        convertMinutesToSeconds(timeSpanObject.minutes()) +
        timeSpanObject.seconds()
    );
}

bool TimeSpan::operator>(const TimeSpan& timeSpanObject) const {
    return thisTimeInSeconds() > tsObjectTimeInSeconds(timeSpanObject);
}

bool TimeSpan::operator>=(const TimeSpan& timeSpanObject) const {
    return thisTimeInSeconds() >= tsObjectTimeInSeconds(timeSpanObject);
}

bool TimeSpan::operator<(const TimeSpan& timeSpanObject) const {
    return thisTimeInSeconds() < tsObjectTimeInSeconds(timeSpanObject);
}

bool TimeSpan::operator<=(const TimeSpan& timeSpanObject) const {
    return thisTimeInSeconds() <= tsObjectTimeInSeconds(timeSpanObject);
}

TimeSpan TimeSpan::operator+(const TimeSpan& timeSpanObject) const {
    return TimeSpan(thisTimeInSeconds()+tsObjectTimeInSeconds(timeSpanObject));
}

TimeSpan TimeSpan::operator-(const TimeSpan& timeSpanObject) const {
    return TimeSpan(thisTimeInSeconds()-tsObjectTimeInSeconds(timeSpanObject));
}

TimeSpan TimeSpan::operator+=(const TimeSpan& timeSpanObject)  {
    
    double timeInSeconds = thisTimeInSeconds();
    set_time(0, 0, timeInSeconds+=tsObjectTimeInSeconds(timeSpanObject));

    return *this;
}

TimeSpan TimeSpan::operator-=(const TimeSpan& timeSpanObject)  {
    double timeInSeconds = thisTimeInSeconds();
    set_time(0, 0, timeInSeconds-=tsObjectTimeInSeconds(timeSpanObject));

    return *this;
}
