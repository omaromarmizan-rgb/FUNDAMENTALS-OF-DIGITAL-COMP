#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

// Project surcharges in Malaysian ringgit.
const double WEEKEND_SURCHARGE = 5.00;
const double EXPRESS_SURCHARGE = 10.00;
const int WEEKDAY_OPEN_HOUR = 8;
const int WEEKDAY_CLOSE_HOUR = 20;
const int WEEKEND_OPEN_HOUR = 9;
const int WEEKEND_CLOSE_HOUR = 17;
const double MAX_RANGE_KM = 30.0;

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

bool checkDeliveryAvailability(int day, const string& dayName, int hour,
                               int weather, double distanceKm)
{
    bool possible = true;
    cout << "\nDelivery availability check for " << dayName << '\n';

    
    if (day >= 6) {
        if (hour < WEEKEND_OPEN_HOUR || hour >= WEEKEND_CLOSE_HOUR) {
            cout << "[X] Weekend deliveries only run from 9:00 to 17:00.\n";
            possible = false;
        }
    } else {
        if (hour < WEEKDAY_OPEN_HOUR || hour >= WEEKDAY_CLOSE_HOUR) {
            cout << "[X] Weekday deliveries only run from 8:00 to 20:00.\n";
            possible = false;
        }
    }

    
    switch (weather) {
        case 1:
            cout << "[OK] Clear weather.\n";
            break;
        case 2:
            cout << "[!] Light rain: delivery allowed, but the drone flies slower.\n";
            break;
        case 3:
            cout << "[X] Thunderstorm: drones cannot fly safely.\n";
            possible = false;
            break;
        case 4:
            cout << "[X] Strong wind: drones cannot fly safely.\n";
            possible = false;
            break;
    }

    
    if (distanceKm > MAX_RANGE_KM) {
        cout << "[X] " << distanceKm << " km is beyond the drone's "
             << MAX_RANGE_KM << " km range.\n";
        possible = false;
    }

    if (possible) {
        cout << "Result: delivery is POSSIBLE on " << dayName << ".\n";
    } else {
        cout << "Result: delivery is NOT possible. Please choose another day or time.\n";
    }
    return possible;
}


void showArrivalTime(double distanceKm, bool isExpress, int weather,
                     int orderHour, int orderMinute)
{
    double speedKmh;
    int prepMinutes; 

    if (isExpress) {
        speedKmh = 60.0;
        prepMinutes = 10;
    } else {
        speedKmh = 40.0;
        prepMinutes = 30;
    }

    
    if (weather == 2) {
        speedKmh = speedKmh * 0.8;
    }

    const int flightMinutes = static_cast<int>(ceil(distanceKm / speedKmh * 60.0));
    const int totalMinutes = prepMinutes + flightMinutes;

    
    const int arrival = orderHour * 60 + orderMinute + totalMinutes;
    const int arrivalHour = (arrival / 60) % 24;
    const int arrivalMinute = arrival % 60;

    cout << "\nEstimated arrival\n"
         << "Preparation time: " << prepMinutes << " min\n"
         << "Flight time: " << flightMinutes << " min\n"
         << "Total wait: ";
    if (totalMinutes >= 60) {
        cout << totalMinutes / 60 << " hr " << totalMinutes % 60 << " min\n";
    } else {
        cout << totalMinutes << " min\n";
    }
    cout << "Drone arrives at about: " << setfill('0') << setw(2) << arrivalHour
         << ':' << setw(2) << arrivalMinute << setfill(' ') << '\n';
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
    const double distanceCharge = distanceKm * marketRate ;  // I have made the cost of the distance. 
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

    
    int orderHour;
    int orderMinute;
    int weather;
    cout << "\nWhat time are you placing the order? (24-hour clock)\n";
    if (!readChoice("Hour (0-23): ", 0, 23, orderHour)
        || !readChoice("Minute (0-59): ", 0, 59, orderMinute)) {
        return 0;
    }

    cout << "\nCurrent weather:\n"
         << "1. Clear\n2. Light rain\n3. Thunderstorm\n4. Strong wind\n";
    if (!readChoice("Weather (1-4): ", 1, 4, weather)) {
        return 0;
    }

    if (!checkDeliveryAvailability(day, dayName, orderHour, weather, distanceKm)) {
        return 0;
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


    showArrivalTime(distanceKm, service == 2, weather, orderHour, orderMinute);
    
    return 0;
}
