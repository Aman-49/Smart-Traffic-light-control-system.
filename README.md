# Smart-Traffic-light-control-system.
Design a C++ program that simulates an intelligent traffic light controller that adjusts signal timing based on traffic density input. It mimics real-world adaptive systems used in smart cities.
Program Overview

This program simulates an intelligent (adaptive) traffic light control system for a four-way intersection — North, East, South, and West.

It mimics how real smart city systems manage traffic dynamically — by adjusting signal timing based on conditions.
Although this version uses fixed timing, it can easily be modified to change green time depending on traffic density input.

 Header Files
#include <iostream>   // for input/output
#include <thread>     // for sleep and parallel execution
#include <chrono>     // for time duration (seconds)


These libraries allow you to print messages, pause the program for specific durations, and simulate real-time countdowns.

 Color Definitions
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define YELLOW  "\033[33m"
#define GREEN   "\033[32m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"


These are ANSI escape codes used to print colorful text in the terminal (Red for STOP, Green for GO, etc.) — making the simulation visually clear.

 Countdown Function
void countdown(int seconds) {
    for (int i = seconds; i > 0; --i) {
        cout << "   Remaining: " << i << " seconds\r";
        cout.flush();
        this_thread::sleep_for(chrono::seconds(1));
    }
    cout << endl;
}


It runs a simple timer that counts down from the specified number of seconds.

The \r brings the cursor back to the start of the line — so the countdown updates dynamically.

sleep_for() pauses execution for one second each loop.

 Example Output:

Remaining: 10 seconds
Remaining: 9 seconds
...

 Show Signal Function
void showSignal(string activeDirection, string phase)


This function displays the current state of the traffic lights for all four directions.

Logic:

Takes two inputs:

activeDirection: which side currently has the right of way.

phase: "RED", "YELLOW", or "GREEN".

Loops through all directions and prints the status:

The active direction changes color and message.

All others remain RED (STOP).

 Example:
If activeDirection = "North" and phase = "GREEN", output might be:

North : GREEN (GO)
East  : RED (STOP)
South : RED (STOP)
West  : RED (STOP)

 Run Signal Function
void runSignal(string direction, int greenTime, int yellowTime, int redTime)


This simulates the entire signal cycle for one direction — including all three phases:

RED phase – vehicles must wait before the green starts.

YELLOW phase – get ready (short warning).

GREEN phase – vehicles move.

Switches back to RED before the next direction takes over.

Each phase calls:

showSignal(direction, "PHASE");
countdown(time);


Then, a short 2-second pause is added between direction changes.

 Main Function
int main() {
    cout << "SMART TRAFFIC LIGHT CONTROL SYSTEM" << endl;

    int greenTime = 15;  // 15 seconds
    int yellowTime = 3;  // 3 seconds
    int redTime = 2;     // 2 seconds before turning green

    string directions[4] = {"North", "East", "South", "West"};

    while (true) {
        for (int i = 0; i < 4; i++) {
            runSignal(directions[i], greenTime, yellowTime, redTime);
        }

        cout << "ONE FULL CYCLE COMPLETED\n";
        this_thread::sleep_for(chrono::seconds(3));
    }

    return 0;
}

Explanation:

Defines the timing for each phase.

Defines the four directions.

Uses an infinite loop (while (true)) to continuously run the system.

Each direction gets a full light cycle using runSignal().

 After one full rotation through all four directions, it waits for 3 seconds, then repeats.

 How It Imitates a Smart System

While this version uses fixed times, a real “smart” system can:

Take input from traffic sensors or cameras.

Adjust greenTime dynamically based on vehicle count or traffic density.

Example:

if (trafficDensity == "High") greenTime = 25;
else if (trafficDensity == "Medium") greenTime = 15;
else greenTime = 10;

 Sample Output (Simplified)
         SMART TRAFFIC LIGHT CONTROL SYSTEM

Now active direction: North
North : RED (STOP)
...
North : GREEN (GO)
Remaining: 15 seconds
...

Switching signal to next direction...
Now active direction: East
...

