#include "time_span.h"
#include <cmath>

using namespace std;


/*
    CONSTRUCTOR
*/
TimeSpan::TimeSpan() : _hours(0), _minutes(0), _seconds(0) {   }

/*
    @param seconds
*/
TimeSpan::TimeSpan(double seconds) : _hours(0), _minutes(0), _seconds(0) {
    handleNegativeSeconds(seconds);
}

/*
    @param minutes
    @param seconds
*/
TimeSpan::TimeSpan(double minutes, double seconds) : _hours(0), _minutes(0), _seconds(0) {

    double minutesInTermsOfSeconds = convertMinutesToSeconds(minutes);
    seconds += minutesInTermsOfSeconds;
    handleNegativeSeconds(seconds);
}

/*
    @param hours
    @param minutes
    @param seconds
*/
TimeSpan::TimeSpan(double hours, double minutes, double seconds) : _hours(0), _minutes(0), _seconds(0) {

    double hoursInTermsOfSeconds = convertHoursToSeconds(hours);
    double minutesInTermsOfSeconds = convertMinutesToSeconds(minutes);
    seconds += minutesInTermsOfSeconds + hoursInTermsOfSeconds;
    handleNegativeSeconds(seconds);
}

/*
        CONVERTING TIME METHODS
*/

/*
    Converts time given in minutes to time in terms of seconds
    @param minutes
    @return seconds time in seconds, as double
*/
double TimeSpan::convertMinutesToSeconds(double minutes) const {
    return minutes*60;
}

/*
    Converts time given in hours to time in terms of seconds
    @param hours
    @return seconds time in seconds, as double
*/
double TimeSpan::convertHoursToSeconds(double hours) const {
    return hours*60*60;
}

/*
    Converts time in seconds to time in hours, minutes, seconds and sets as object fields
    @param seconds time in seconds
*/
void TimeSpan::convertSecondsToFullAndSet(double seconds) { // 127.86 seconds = 2 minutes .131 minutes

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

/*
    Converts time in seconds to time in hours, minutes, seconds and subtracts from object fields if negative. Sets object fields.
    @param seconds time in seconds
*/
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

    convertSecondsToFullAndSet(seconds);

}

/*
    Converts time in minutes to hours, minutes, seconds and subtracts from object fields if input is negative. Sets object fields
    @param minutes time in minutes
*/
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

/*
    Return this time object's hours (not full time) as an integer
*/
int TimeSpan::hours() const {
    return _hours;
}
/*
    Return this time object's minutes (not full time) as an integer
*/
int TimeSpan::minutes() const {
    return _minutes;
}
/*
    Return this time object's seconds (not full time) as an integer
*/
int TimeSpan::seconds() const {
    return _seconds;
}

/*
    Sets and overrides this time object's fields with inputted hours, minutes, seconds
    @param hours
    @param minutes
    @param seconds
*/
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

/*
    Prints time object as "Hours: ##, Minutes: ##, Seconds:## "
*/
ostream& operator<<(ostream& stream, const TimeSpan& timeSpan) {
    int hours = timeSpan.hours();
    int minutes = timeSpan.minutes();
    int seconds = timeSpan.seconds();
    stream << "Hours: " << hours << ", Minutes: " << minutes << ", Seconds: " << seconds; 
    return stream;
}

/*
    Takes in three doubles (e.g. "5 9 12.5") and sets this time object's fields with input
    @param INPUT: string with three doubles/ints, separated by space " 8 19.6 4.0"
*/
istream& operator>>(istream& stream, TimeSpan& timeSpan) { // Does not strip leading/trailing whitespace
    // string timeSpanInput;
    // string timeSpanInput2;
    // string timeSpanInput3;

    string hourString, minuteString, secondString;
    stream >> hourString >> minuteString >> secondString;
    double hours, minutes, seconds;

    // int timeSegment = 0;
    // for (int i = 0; i < timeSpanInput.length(); i++) {

    //     char currentChar = timeSpanInput[i];

    //     if (currentChar == ',') {
    //         timeSegment++;
    //         continue;
    //     } else if (currentChar == ' ') {
    //         continue;
    //     }

    //     switch (timeSegment) {
    //         case 0:
    //             hourString += currentChar;
    //             continue;
    //         case 1:
    //             minuteString += currentChar;
    //             continue;
    //         case 2:
    //             secondString += currentChar;
    //             continue;
    //         default:
    //             hourString = minuteString = secondString = "-99999";
    //     }
    // }
    hours = stod(hourString);
    minutes = stod(minuteString);
    seconds = stod(secondString);
    timeSpan.set_time(hours, minutes, seconds);
    return stream;
}

/*
    @return boolean whether this time objet's time is the same as the one to be compared
*/
bool TimeSpan::operator==(const TimeSpan& timeSpanObject) const {
    return (
        _hours == timeSpanObject.hours() &&
        _minutes == timeSpanObject.minutes() &&
        _seconds == timeSpanObject.seconds()
    );
}

/*
    @return boolean whether this time objet's time is not the same as the one to be compared
*/
bool TimeSpan::operator!=(const TimeSpan& timeSpanObject) const {
    return !(
        _hours == timeSpanObject.hours() &&
        _minutes == timeSpanObject.minutes() &&
        _seconds == timeSpanObject.seconds()
    );
}

/*
    @return seconds this time object's full time in terms of seconds,
*/
double TimeSpan::thisTimeInSeconds() const {
    return (
        convertHoursToSeconds(_hours) +
        convertMinutesToSeconds(_minutes) +
        _seconds
    );
}

/*
    @param TimeSpanObject the time object to find the time of
    @return seconds inputted time object's full time in terms of seconds,
*/
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

TimeSpan TimeSpan::operator-() {
    return TimeSpan(-thisTimeInSeconds());
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
