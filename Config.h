#ifndef CONFIG_H
#define CONFIG_H
enum {
    SPEED_OF_SOUND = 350, // m/s, at 30C
    BASE_SIGNAL_OUT = 11,
    HEAD_SIGNAL_OUT = 10,
    PUMP_SIGNAL_OUT = 4,
    USSIGNAL_OUT = 7,
    USECHO_IN = 8,
    OIRSIGNAL_IN = 9,
};
static const int STATE_LEDS_OUT[] = { 3, 5, 6 };
enum { STATE_LEDS_OUT_LEN = sizeof(STATE_LEDS_OUT) / sizeof(STATE_LEDS_OUT[0]) };
enum { Analyzing, OK, Error } CurrentState = Analyzing;

#endif
