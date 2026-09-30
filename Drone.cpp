#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

// Project surcharges in Malaysian ringgit.
const double WEEKEND_SURCHARGE = 5.00;
const double EXPRESS_SURCHARGE = 10.00;

bool readChoice(const string& prompt, int minimum, int maximum, int& choice)
{
    string input;
    while (true) {
        cout << prompt;
        if (!getline(cin, input)) {
            cout << "\nInput ended. No delivery selected.\n";
            return false;
        }

        istringstream stream(input);
        char extra;
        if ((stream >> choice) && !(stream >> extra)
            && choice >= minimum && choice <= maximum) {
            return true;
        }
        cout << "Please enter a whole number from " << minimum
                  << " to " << maximum << ".\n";
    }
}

bool readPositiveNumber(const string& prompt, double& value)
{
    string input;
    while (true) {
        cout << prompt;
        if (!getline(cin, input)) {
            cout << "\nInput ended. No delivery selected.\n";
            return false;
        }

        istringstream stream(input);
        char extra;
        if ((stream >> value) && !(stream >> extra)
            && isfinite(value) && value > 0.0) {
            return true;
        }
        cout << "Please enter a positive number (for example, 2.50).\n";
    }
}

int main()
{
    int day;
    int service;
    string dayName;
    double distanceKm;
    const double marketRate = 15.55; // This is an example of the market rate; We can change it whenever we want to test the program with different rates.
    double dayCharge = 0.00;

    cout << "\nDrone Delivery - Price Calculator\n"
              << "All prices are in Malaysian ringgit (RM).\n"
              << "Project surcharges: weekends +RM5.00; express +RM10.00.\n\n";

    if (!readPositiveNumber("Delivery distance (km): ", distanceKm)) {
        return 0;
    }

    // Round the distance charge to the nearest sen before adding surcharges.
    const double distanceCharge = round(distanceKm * marketRate); // I have made the cost of the distance. 
    if (!isfinite(distanceCharge)) {
        cout << "The distance and rate are too large to calculate a price.\n";
        return 1;
    }

    cout
              << "Choose your delivery day:\n"
              << "1. Monday\n2. Tuesday\n3. Wednesday\n4. Thursday\n"
              << "5. Friday\n6. Saturday\n7. Sunday\n";

    if (!readChoice("Day (1-7): ", 1, 7, day)) {
        return 0;
    }

    switch (day) {
        case 1: dayName = "Monday"; break;
        case 2: dayName = "Tuesday"; break;
        case 3: dayName = "Wednesday"; break;
        case 4: dayName = "Thursday"; break;
        case 5: dayName = "Friday"; break;
        case 6:
            dayName = "Saturday";
            dayCharge = WEEKEND_SURCHARGE;
            break;
        case 7:
            dayName = "Sunday";
            dayCharge = WEEKEND_SURCHARGE;
            break;
    }

    const double tripPrice = distanceCharge + dayCharge;
    cout << fixed << setprecision(2)
              << "\nTrip price for " << dayName << ": RM" << tripPrice
              << "\n\nChoose your delivery service:\n"
              << "1. Standard (no extra charge)\n"
              << "2. Express (+RM" << EXPRESS_SURCHARGE << ")\n";

    if (!readChoice("Service (1-2): ", 1, 2, service)) {
        return 0;
    }

    string serviceName;
    double serviceCharge;
    if (service == 2) {
        serviceName = "Express";
        serviceCharge = EXPRESS_SURCHARGE;
    } else {
        serviceName = "Standard";
        serviceCharge = 0.00;
    }

    cout << "\nDelivery price summary\n"
              << "Day: " << dayName << '\n'
              << "Service: " << serviceName << '\n'
              << setprecision(6) << defaultfloat
              << "Distance: " << distanceKm << " km\n"
              << "Market rate entered: RM" << marketRate << " per km\n"
              << fixed << setprecision(2)
              << "Distance charge: RM" << distanceCharge << '\n'
              << "Day surcharge: RM" << dayCharge << '\n'
              << "Trip price: RM" << tripPrice << '\n'
              << "Service charge: RM" << serviceCharge << '\n'
              << "Total payment: RM" << tripPrice + serviceCharge << '\n';

    return 0;
}
