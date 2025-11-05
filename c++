#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

// ANSI color codes for colorful output
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define YELLOW  "\033[33m"
#define GREEN   "\033[32m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"

// Function to simulate a countdown timer
void countdown(int seconds) {
    for (int i = seconds; i > 0; --i) {
        cout << "   Remaining: " << i << " seconds\r";
        cout.flush();
        this_thread::sleep_for(chrono::seconds(1));
    }
    cout << endl;
}

// Function to display full traffic light status
void showSignal(string activeDirection, string phase) {
    string directions[4] = {"North", "East", "South", "West"};
    cout << "\n--------------------------------------------------" << endl;
    cout << "             TRAFFIC LIGHT STATUS                 " << endl;
    cout << "--------------------------------------------------" << endl;

    for (int i = 0; i < 4; i++) {
        if (directions[i] == activeDirection) {
            if (phase == "GREEN")
                cout << directions[i] << " : " << GREEN << "GREEN (GO)" << RESET << endl;
            else if (phase == "YELLOW")
                cout << directions[i] << " : " << YELLOW << "YELLOW (READY)" << RESET << endl;
            else
                cout << directions[i] << " : " << RED << "RED (STOP)" << RESET << endl;
        } else {
            cout << directions[i] << " : " << RED << "RED (STOP)" << RESET << endl;
        }
    }
    cout << "--------------------------------------------------" << endl;
}

// Function to simulate full light cycle for one direction
void runSignal(string direction, int greenTime, int yellowTime, int redTime) {
    cout << CYAN << "\nNow active direction: " << direction << RESET << endl;

    // 1. RED phase (for a few seconds before turning green)
    showSignal(direction, "RED");
    countdown(redTime);

    // 2. YELLOW phase (ready to go)
    showSignal(direction, "YELLOW");
    countdown(yellowTime);

    // 3. GREEN phase (vehicles move)
    showSignal(direction, "GREEN");
    countdown(greenTime);

    // After green, automatically turn back to red for next cycle
    showSignal(direction, "RED");
    cout << BLUE << "\nSwitching signal to next direction..." << RESET << endl;
    this_thread::sleep_for(chrono::seconds(2));
}

int main() {
    cout << BLUE;
    cout << "======================================================" << endl;
    cout << "         SMART TRAFFIC LIGHT CONTROL SYSTEM            " << endl;
    cout << "======================================================" << RESET << endl;

    // Timing setup for each phase
    int greenTime = 15;   // 15 seconds green
    int yellowTime = 3;   // 3 seconds yellow
    int redTime = 2;      // 2 seconds red before green

    // Directions in clockwise order
    string directions[4] = {"North", "East", "South", "West"};

    // Continuous operation loop
    while (true) {
        for (int i = 0; i < 4; i++) {
            runSignal(directions[i], greenTime, yellowTime, redTime);
        }

        cout << "\n===============================" << endl;
        cout << " ONE FULL CYCLE COMPLETED      " << endl;
        cout << "===============================\n" << endl;
        this_thread::sleep_for(chrono::seconds(3));
    }

    return 0;
}