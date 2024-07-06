#include QMK_KEYBOARD_H
#include "saesh.h"

#define KC_SEC1 KC_SECRET_1
#define KC_SEC2 KC_SECRET_2
#define KC_SEC3 KC_SECRET_3

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
	KC_7,    KC_8, KC_9,
	KC_4,    KC_5, KC_6,
	KC_1,    KC_2, KC_3,
	MO(_FN), KC_0, KC_ENT),

  [_FN] = LAYOUT(
	KC_VOLU,  KC_MUTE, KC_SLEP,
	KC_VOLD,  KC_JIGG, KC_CALC,
	KC_SEC1,  KC_SEC2, KC_SEC3,
	XXXXXXX,  QK_BOOT, XXXXXXX),
};
