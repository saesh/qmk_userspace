#pragma once

#include "quantum.h"

// https://thomasbaart.nl/2018/12/01/reducing-firmware-size-in-qmk/
#ifndef NO_DEBUG
#define NO_DEBUG
#endif // !NO_DEBUG
#if !defined(NO_PRINT) && !defined(CONSOLE_ENABLE)
#define NO_PRINT
#endif // !NO_PRINT

#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

enum _layer {
  _BASE,
  _FN,
  _FN2,
  _MS,
  _PRG,
  _ENGR,
};

enum {
    T_1, // toggle mouse layer
    K1_F1,
    K2_F2,
    K3_F3,
    K4_F4,
    K5_F5,
    K6_F6,
    K7_F7,
    K8_F8,
    K9_F9,
    K0_F10,
    Kmin_F11,
    Keq_F12,
};

enum user_custom_keys {
  KC_SECRET_1 = SAFE_RANGE,
  KC_SECRET_2,
  KC_SECRET_3,
  KC_SECRET_4,
  KC_SECRET_5,
  SS_MARKDOWNCODEBLOCK, // send string Markdown code block
  KC_JIGG,
  NEW_SAFE_RANGE
};

