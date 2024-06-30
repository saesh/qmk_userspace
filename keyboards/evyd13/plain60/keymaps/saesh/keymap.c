#include QMK_KEYBOARD_H
#include "saesh.h"

#define KC_SEC1 KC_SECRET_1
#define KC_SEC2 KC_SECRET_2
#define KC_SEC3 KC_SECRET_3
#define KC_CDBLK SS_MARKDOWNCODEBLOCK

enum _layer {
  _BASE,
  _FN,
  _FN2,
  _MS
};

enum {
    T_1,
};

tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Ctrl, twice for toggle mouse layer
    [T_1] = ACTION_TAP_DANCE_LAYER_TOGGLE(KC_LCTL, _MS),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_BASE] = LAYOUT_60_hhkb(
   KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_MINS,  KC_EQL, KC_BSLS, KC_GRV, \
   KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_LBRC, KC_RBRC, KC_BSPC, \
  TD(T_1),    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,           KC_ENT, \
  KC_LSFT,             KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT, MO(_FN), \
           KC_LGUI, KC_LALT,                    KC_SPC,                                              KC_ALGR, _______),

[_FN] = LAYOUT_60_hhkb(
  _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,  KC_INS, KC_CDBLK, \
  KC_CAPS, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   KC_UP, _______,  KC_DEL, \
  _______, KC_VOLU, KC_VOLD, KC_MUTE, _______, _______, _______, _______, KC_HOME, KC_PGUP, KC_LEFT,KC_RIGHT,          _______, \
  _______,          _______, _______, _______, _______, _______, _______, _______,  KC_END, KC_PGDN, KC_DOWN, _______, _______, \
           _______, _______,                   _______,                                              _______, MO(_FN2)),

[_FN2] = LAYOUT_60_hhkb(
  _______, KC_SEC1, KC_SEC2, KC_SEC3, XXXXXXX, XXXXXXX, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  KC_PWR, _______, _______, _______, \
  _______, _______, KC_SLEP, _______, _______, _______, _______, KC_JIGG, _______, _______, _______, _______,          _______, \
  _______,          _______, _______, KC_CALC, _______, QK_BOOT, _______, _______, _______, _______, _______, _______, _______, \
           _______, _______,                   _______,                                              _______, _______),

[_MS] = LAYOUT_60_hhkb(
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, KC_WH_U ,KC_BTN4, KC_BTN5, _______, _______, _______, KC_MS_U, _______, _______, _______, _______, _______, \
  TD(T_1), _______, KC_WH_D, KC_BTN1, _______, _______, _______, KC_MS_L, KC_MS_D, KC_MS_R, _______, _______,          _______, \
  _______,          _______, _______, KC_BTN2, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
           _______, _______,                   _______,                                              _______, _______)
};
