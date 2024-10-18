#include "time_span.h"
#include <iostream>

using namespace std;

bool tests();

int main() {
    // tests();
    TimeSpan testObj1, testObj2;
    cout << "Enter time1, \"h, m, s\" " << endl;
    cin >> testObj1;
    cout << "Enter time2, \"h, m, s\" " << endl;
    cin >> testObj2;

    cout << testObj1+testObj2 << endl;

}



bool defaultCreated() {
    TimeSpan ts;
    return ((ts.hours() == 0) && (ts.minutes() == 0) && (ts.seconds() == 0));
}

bool CheckValues(TimeSpan time, int hours, int minutes, int seconds) {
    if ((time.hours() != hours) || (time.minutes() != minutes) || (time.seconds() != seconds)) {
        return false;
    }
    return true;
}

bool TestZeros() {
    TimeSpan ts(0, 0, 0);
    return CheckValues(ts, 0, 0, 0);
}

bool TestNormal() {
    TimeSpan ts(1, 2, 3);
    // cout << ts << endl;
    return CheckValues(ts, 1, 2, 3);
}

bool Test60() {
    TimeSpan ts(60, 60, 60);
    // cout << ts << endl;
    return CheckValues(ts, 60, 60, 60);
}

bool TestSecondsConversion() {
    TimeSpan ts(90);
    // cout << ts << endl;
    return CheckValues(ts, 0, 1, 30);
}

bool TestMinutesConversion() {
    TimeSpan ts(90, 0);
    // cout << ts << endl;
    return CheckValues(ts, 1, 30, 0);
}

bool TestFullConversion() {
    TimeSpan ts(90, 90, 90);
    // cout << ts << endl;
    return CheckValues(ts, 91, 31, 30);
}

bool TestFloatSeconds() {
    TimeSpan ts(127.86);
    // cout << ts << endl;
    return CheckValues(ts, 0, 2, 8);
}

bool TestFloatMinutes() {
    TimeSpan ts(127.86, 0);
    // cout << ts << endl;
    return CheckValues(ts, 2, 7, 52);
}

bool TestNegativeSeconds() {
    TimeSpan ts(0, 0, -9000);
    // cout << ts << endl;
    return CheckValues(ts, -2, -30, 0);
}

bool TestNegativeMinute() {
    TimeSpan ts(8, -23, 0);
    // cout << ts << endl;
    return CheckValues(ts, 7, 37, 0);
}

bool TestNegativeHour() {
    TimeSpan ts(-3, 73, 2);
    // cout << ts << endl;
    return CheckValues(ts, -1, -46, -58);
}

bool TestSetTime() {
    TimeSpan ts(0, 0, 0);
    ts.set_time(-3, 73, 2);
    return CheckValues(ts, -1, -46, -58);
    
}

bool TestAdd() {
    TimeSpan ts1, ts2(5), ts3(7, 0), ts4(4, 0, 0);
    TimeSpan add_it_up = ts1 + ts2 + ts3 + ts4;
    // cout << add_it_up << endl;
    return CheckValues(add_it_up, 4, 7, 5);
}

bool TestAddInPlace() {
    TimeSpan ts1(5, 6, 7);
    TimeSpan ts2(1, 1, 1);
    if ((!CheckValues(ts1, 5, 6, 7)) || (!CheckValues(ts2, 1, 1, 1))) {
        return false;
    }
    ts1 += ts2;
    // cout << ts1 << endl;
    if ((!CheckValues(ts1, 6, 7, 8)) || (!CheckValues(ts2, 1, 1, 1))) {
        return false;
    } else {
        return true;

    }
}

bool TestSubtract() {
    TimeSpan ts1, ts2(5), ts3(7, 0), ts4(4, 0, 0);
    TimeSpan add_it_up = ts1 - ts2 - ts3 - ts4;
    // cout << add_it_up << endl;
    return CheckValues(add_it_up, -4, -7, -5);
}

bool TestSubtractInPlace() {
    TimeSpan ts1(5, 6, 7);
    TimeSpan ts2(1, 1, 1);
    if ((!CheckValues(ts1, 5, 6, 7)) || (!CheckValues(ts2, 1, 1, 1))) {
        return false;
    }
    ts1 -= ts2;
    // cout << ts1 << endl;
    if ((!CheckValues(ts1, 4, 5, 6)) || (!CheckValues(ts2, 1, 1, 1))) {
        return false;
    } else {
        return true;
    }
}

bool TestUnaryNegation() {
    TimeSpan ts1(5, 6, 7);
    TimeSpan ts2 = -ts1;
    return CheckValues(ts2, -5, -6, -7);
}

bool tests() {
    cout << "Testing TimeSpan Class" << endl;
    if (!defaultCreated()) cout << "    Failed: DefaultCreated" << endl;
    if (!TestZeros()) cout << "    Failed: TestZeros" << endl;
    if (!TestNormal()) cout << "    Failed: TestNormal" << endl;
    if (!Test60()) cout << "    Failed: Test60" << endl;
    if (!TestSecondsConversion()) cout << "    Failed: TestSecondsConversion" << endl;
    if (!TestMinutesConversion()) cout << "    Failed: TestMinutesConversion" << endl;
    if (!TestFullConversion()) cout << "    Failed: TestFullConversion" << endl;
    if (!TestFloatSeconds()) cout << "    Failed: TestFloatSeconds" << endl;
    if (!TestFloatMinutes()) cout << "    Failed: TestFloatMinutes" << endl;
    if (!TestNegativeSeconds()) cout << "    Failed: TestNegativeSeconds" << endl;
    if (!TestNegativeMinute()) cout << "    Failed: TestNegativeMinute" << endl;
    if (!TestNegativeHour()) cout << "    Failed: TestNegativeHour" << endl;
    if (!TestSetTime()) cout << "    Failed: TestSetTime" << endl;
    if (!TestAdd()) cout << "	Failed: TestAdd" << endl;
    if (!TestAddInPlace()) cout << "	Failed: TestAddInPlace" << endl;
    if (!TestSubtract()) cout << "	Failed: TestSubtract" << endl;
    if (!TestSubtractInPlace()) cout << "	Failed: TestSubtractInPlace" << endl;
    if (!TestUnaryNegation()) cout << "	Failed: TestUnaryNegation" << endl;
    cout << "Testing Complete" << endl;
    return true;
}


// int main() {
// cout << "CONSTRUCTION TEST" << endl;
// TimeSpan dur1(77, 15, 6);
// string expected1 = "";
// cout << "Hours: 77, Minutes: 15, Seconds: 6 <- Expected" << endl;
// cout << dur1 << endl << endl;
// TimeSpan dur2(8, -23, 0);
// cout << "Hours: 7, Minutes: 37, Seconds: 0 <- Expected" << endl;
// cout << dur2 << endl << endl;
// TimeSpan dur3(3, 123, 7658);
// cout << "Hours: 7, Minutes: 10, Seconds: 38 <- Expected" << endl;
// cout << dur3 << endl << endl;
// TimeSpan dur5(7, -85);
// cout << "Hours: 0, Minutes: 5, Seconds: 35 <- Expected" << endl;
// cout << dur5 << endl << endl;
// TimeSpan dur6(12343);
// cout << "Hours: 3, Minutes: 25, Seconds: 43 <- Expected" << endl;
// cout << dur6 << endl << endl;
// TimeSpan dur99(0, 0, 600);
// cout << "Hours: 0, Minutes 10, Seconds: 0 <- Expected" << endl;
// cout << dur99 << endl << endl;
// //Unary negation
// cout << "UNARY NEGATION TESTS" << endl;
// TimeSpan dur7(-8, 23, 0), dur8;
// dur8 = -dur7;
// cout << "Hours: -7, Minutes: -37, Seconds: 0 <- Expected" << endl;
// cout << dur7 << endl << endl;
// cout << "Hours: 7, Minutes: 37, Seconds: 0 <- Expected" << endl;
// cout << dur8 << endl << endl;
// //setTestsAndgetTests
// cout << "SET AND GET TESTS" << endl;
// dur7.set_time(1, 2, 3);
// cout << "Hours: 1, Minutes: 2, Seconds: 3 <- Expected" << endl;
// cout << dur7 << endl << endl;
// dur8.set_time(0, 987, 0);
// cout << "Hours: 16, Minutes: 27, Seconds: 0 <- Expected" << endl;
// cout << dur8 << endl << endl;
// //FloatParamTests
// cout << "FLOATING PARAMS TEST" << endl;
// TimeSpan dur9(1, 6, -1);
// cout << "Hours: 1, Minutes: 5, Seconds: 59 <- Expected" << endl;
// cout << dur9 << endl << endl;
// //AddandSubTests
// cout << "ADD AND SUBTRACT TESTS" << endl;
// TimeSpan dur10(77, 15, 6), dur11(8, -25, 0), dur12, dur13, dur14, dur15(-3,
// 75, 2), dur16(5, 1, 10), dur17(1, 2, 3), dur18(1, 3, 2), dur19;
// dur12 = dur10 + dur11;
// dur19 = dur16 + dur17 - dur18;
// cout << "Hours: 5, Minutes: 0, Seconds: 11 <- Expected" << endl;
// cout << dur19 << endl << endl;
// //normal add
// cout << "NORMAL ADD TESTS" << endl;
// TimeSpan dur20(77, 15, 6), dur21(8, -25, 0), dur22, dur23, dur24, dur25(-3,
// 75, 2), dur26(5, 1, 10), dur27(1, 2, 3), dur28(1, 3, 2), dur29;
// dur22 = dur20 + dur21;
// cout << "Hours: 84, Minutes: 50, Seconds: 6 <- Expected" << endl;
// cout << dur22 << endl << endl;
// //addoverload
// cout << "ADD OVERLOAD TESTS" << endl;
// TimeSpan dur30(77, 15, 6), dur31(8, -25, 0), dur32, dur33, dur34, dur35(-3,
// 75, 2), dur36(5, 1, 10), dur37(1, 2, 3), dur38(1, 3, 2), dur39;
// dur32 = dur30 + dur31;
// dur33 += dur31;
// cout << "Hours: 7, Minutes: 35, Seconds: 0 <- Expected" << endl;
// cout << dur33 << endl << endl;
// //sub overload
// cout << "SUB OVERLOAD TESTS" << endl;
// TimeSpan dur40(77, 15, 6), dur41(8, -25, 0), dur42, dur43, dur44, dur45(-3,
// 75, 2), dur46(5, 1, 10), dur47(1, 2, 3), dur48(1, 3, 2), dur49;
// dur42 = dur40 + dur41;
// dur40 -= dur41;
// cout << "Hours: 69, Minutes: 40, Seconds: 6 <- Expected" << endl;
// cout << dur40 << endl << endl;
// //sub
// cout << "NORMAL SUB TESTS" << endl;
// TimeSpan dur50(77, 15, 6), dur51(8, -25, 0), dur52, dur53, dur54, dur55(-3,
// 75, 2), dur56(5, 1, 10), dur57(1, 2, 3), dur58(1, 3, 2), dur59;
// dur52 = dur50 + dur51;
// dur54 = dur55 - dur51;
// cout << "Hours: -9, Minutes: -19, Seconds: -58 <- Expected" << endl;
// cout << dur54 << endl << endl;
// //EqualityTests
// cout << "EQUALITY TESTS" << endl;
// TimeSpan dur64(77.4, 15.0, 6.0), dur65(8, -23, 0), dur66(7, 37, 0);
// cout << "Expected: 0 " << (bool) (dur64 == dur65) << endl;
// cout << "Expected: 1 " << (bool) (dur64 != dur65) << endl;
// cout << "Expected: 1 " << (bool) (dur66 == dur65) << endl;
// //Cin & CoutTest
// TimeSpan dur70;
// cout << "Enter time in the following format: hours mintues seconds" << endl;
// cin >> dur70;
// cout << dur70 << endl;
// system("echo \"hello world\" ");
// return 0;
// }