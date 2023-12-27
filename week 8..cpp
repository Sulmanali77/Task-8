#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
using namespace std;
struct Boat {
    int boatNumber;
    double moneyTaken;
    double totalHoursHired;
    string returnTime;
};

const double HOURLY_RATE = 20.0;
const double HALF_HOUR_RATE = 12.0;
const int NUM_BOATS = 10;
const string OPEN_TIME = "10:00";
const string CLOSE_TIME = "17:00";

void calculateMoneyForBoat(Boat& boat) {
    cout << "Enter the hours you want to hire Boat " << boat.boatNumber << " (between 0.5 and 7): ";
    double hoursToHire;
    cin >> hoursToHire;

    while (hoursToHire < 0.5 || hoursToHire > 7 || boat.returnTime.compare(CLOSE_TIME) >= 0) {
        cout << "Invalid hours or boat cannot be hired after " << CLOSE_TIME << ". Please enter a valid duration: ";
        cin >> hoursToHire;
    }

    double cost;
    if (hoursToHire <= 1) {
        cost = HOURLY_RATE * hoursToHire;
    } else {
        cost = HALF_HOUR_RATE * hoursToHire;
    }

    boat.moneyTaken += cost;
    boat.totalHoursHired += hoursToHire;

    size_t colonPos = boat.returnTime.find(':');
    int currentHour = stoi(boat.returnTime.substr(0, colonPos));
    int currentMinute = stoi(boat.returnTime.substr(colonPos + 1));

    currentHour += static_cast<int>(hoursToHire);
    boat.returnTime = to_string(currentHour) + ":" + to_string(currentMinute);

    std::cout << "Boat " << boat.boatNumber << " hired for " << hoursToHire << " hours. Total cost: $" << cost << "\n";
}

void findAvailableBoats(const std::vector<Boat>& boats, const std::string& currentTime) {
    cout << "\n--- Available Boats and Slots ---\n";
    for (const auto& boat : boats) {
        if (boat.returnTime.compare(currentTime) <= 0) {
            cout << "Boat " << boat.boatNumber << " is available until " << boat.returnTime << "\n";
        }
    }
}

void calculateTotalMoney(const std::vector<Boat>& boats) {
    double totalMoney = 0.0;
    double totalHours = 0.0;
    int unusedBoats = 0;
    int mostUsedBoat = 1;
    double maxHoursHired = boats[0].totalHoursHired;

    for (const auto& boat : boats) {
        totalMoney += boat.moneyTaken;
        totalHours += boat.totalHoursHired;

        if (boat.totalHoursHired == 0) {
            ++unusedBoats;
        }

        if (boat.totalHoursHired > maxHoursHired) {
            mostUsedBoat = boat.boatNumber;
            maxHoursHired = boat.totalHoursHired;
        }
    }

    cout << "\n--- End of Day Report ---\n";
    cout << "Total revenue from all boats: $" << totalMoney << "\n";
    cout << "Total hours boats were hired: " << totalHours << " hours\n";
    cout << "Number of boats not used today: " << unusedBoats << "\n";
    cout << "Boat #" << mostUsedBoat << " was used the most, with " << maxHoursHired << " hours hired.\n";
}

int main() {
    vector<Boat> boats;

    for (int i = 1; i <= NUM_BOATS; ++i) {
        boats.push_back({i, 0.0, 0.0, OPEN_TIME});
    }

    cout << "Enter the current time (24-hour format, e.g., 14:30): ";
    string currentTime;
    cin >> currentTime;

    while (true) {
        cout << "\nOptions:\n";
        cout << "1. Hire a boat\n";
        cout << "2. View available boats and slots\n";
        cout << "3. View end-of-day report\n";
        cout << "4. End the program\n";
        cout << "Enter your choice (1-4): ";
        
        int choice;
        cin >> choice;

        if (choice == 1) {
            int boatNumber;
            cout << "Enter the boat number you want to hire: ";
            cin >> boatNumber;

            if (boatNumber >= 1 && boatNumber <= NUM_BOATS) {
                calculateMoneyForBoat(boats[boatNumber - 1]);
            } else {
                cout << "Invalid boat number. Please enter a number between 1 and " << NUM_BOATS << ".\n";
            }
        } else if (choice == 2) {
            findAvailableBoats(boats, currentTime);
        } else if (choice == 3) {
            calculateTotalMoney(boats);
            break; // End the program after generating the report
        } else if (choice == 4) {
            break; // End the program
        } else {
            cout << "Invalid choice. Please enter a number between 1 and 4.\n";
        }
    }

    return 0;
}
