#include "time_span.h"
#include <iostream>

using namespace std;

bool tests();

int main() {
    tests();
    TimeSpan testObj1, testObj2;
    cout << "Enter time1, \"h, m, s\" " << endl;
    cin >> testObj1;
    cout << "Enter time2, \"h, m, s\" " << endl;
    cin >> testObj2;

    cout << testObj1+testObj2 << endl;

}





bool defaultCreated() {
    TimeSpan ts;
    return ((ts.hours() == -999) && (ts.minutes() == -999) && (ts.seconds() == -999));
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
    cout << ts << endl;
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
    cout << add_it_up << endl;
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

    // ts1 += ts2;
    // cout << ts1 << endl;
    // return CheckValues(ts1, 6, 7, 8);

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
    cout << "Testing Complete" << endl;
    return true;
}