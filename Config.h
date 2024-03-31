#ifndef CONFIG_H
#define CONFIG_H

const int SpeedOfSound = 350; // m/s, at 30C
const int BaseSignalOut = 11;
const int HeadSignalOut = 10;
const int PumpSignalOut = 4;
const int USSignalOut = 7;
const int USEchoIn = 8;
const int OIRSignalIn = 9;
const int[] StateLEDsOut = { 3, 5, 6 };
enum RobotState { Analyzing, OK, Error };
RobotState CurrentState = 0;

#endif