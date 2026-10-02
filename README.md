# Drone Delivery

A beginner C++ console program for the first two project objectives:

1. Show the trip price based on distance, the current market rate, the chosen day and the weather.
2. Let the user choose standard or express delivery.

## Inputs and outputs

| User input | Program output |
| --- | --- |
| Delivery distance in kilometres (positive number) | Distance and calculated distance charge |
| Current market delivery rate in RM per kilometre (positive number) | Rate used for this calculation |
| Delivery day: 1 (Monday) through 7 (Sunday) | Selected day and its trip price |
| Service: 1 (Standard) or 2 (Express) | Selected service, service charge, and total payment |

Invalid choices prompt the user to try again. Ending input exits the program.

## Logic and pricing

All money amounts use Malaysian ringgit (RM). Enter the current delivery rate
manually each time you run the program. There is no live market price connection.
The rate means the delivery charge per kilometre, not fuel prices or exchange rates.

[Lalamove Malaysia's official pricing page](https://www.lalamove.com/en-my/all-vehicle-pricing-detail)
(checked 30 September 2026) directs users to its app for accurate quotes and
explains that fares vary. It does not establish a fixed drone delivery rate.
This program therefore uses a supplied RM/km rate rather than claiming a sample
price is the current market price.

The following surcharges are project assumptions, editable at the top of `Drone.cpp`:

| Choice | Added charge |
| --- | ---: |
| Monday-Friday | RM0.00 |
| Saturday-Sunday | RM5.00 |
| Standard | RM0.00 |
| Express | RM5.00 |

A `switch` selects the day and weekend surcharge. An `if/else` selects the service charge.

`Distance charge = distance in km x supplied market rate in RM/km`

`Total payment = distance charge + day surcharge + service charge`

The distance charge is rounded to the nearest sen before adding surcharges.
For example, using an **illustrative** rate of RM1.50/km, a 10 km Saturday
express delivery costs `RM15.00 + RM5.00 + RM5.00 = RM25.00`.
At RM2.00/km, that same trip costs RM30.00.

This version calculates prices only; delivery availability and arrival estimates are future objectives.

## Build and run

### VS Code terminal (Windows)

1. Open this project folder in VS Code using **File > Open Folder**.
2. Open **Run and Debug** and select **Drone - VS Code terminal**.
3. Press **F5** to build and debug, or **Ctrl+F5** to run without debugging.
4. Click the **Terminal** panel and type an answer at each prompt, pressing Enter.

You can also choose **Terminal > Run Task > Run Drone in terminal**.
The terminal stays open after the program finishes so you can read the result.

The included configuration uses the installed CodeBlocks MinGW `g++.exe` and
`gdb.exe` under `C:\Program Files\CodeBlocks\MinGW\bin`. If you move this
project to another computer, update these paths in `.vscode/tasks.json` and
`.vscode/launch.json`. Use `g++` to link the C++ standard library correctly.
The Debug Console is for debugger commands; enter program answers in Terminal.

### Manual build

With a C++ compiler such as g++:

```powershell
g++ -std=c++11 -Wall -Wextra -pedantic Drone.cpp -o Drone.exe
.\Drone.exe
```
