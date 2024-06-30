#include "saesh.h"

__attribute__((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    return true;
}

__attribute__ ((weak))
bool secrets_process_record_user(uint16_t keycode, keyrecord_t *record) {
    return true;
}

bool is_jiggling = false;
uint32_t idle_timeout = 30000; // (after 30s)
uint32_t mouse_interval = 10000; // (every 10s)

static uint32_t idle_callback(uint32_t trigger_time, void* cb_arg) {
    if (is_jiggling){
        SEND_STRING(SS_TAP(X_F15));
        return mouse_interval;
    }
    return 0;
}

typedef struct {
    uint16_t tap;
    uint16_t hold;
    uint16_t held;
} tap_dance_tap_hold_t;

void tap_dance_tap_hold_finished(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (state->pressed) {
        if (state->count == 1
#ifndef PERMISSIVE_HOLD
            && !state->interrupted
#endif
        ) {
            register_code16(tap_hold->hold);
            tap_hold->held = tap_hold->hold;
        } else {
            register_code16(tap_hold->tap);
            tap_hold->held = tap_hold->tap;
        }
    }
}

void tap_dance_tap_hold_reset(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (tap_hold->held) {
        unregister_code16(tap_hold->held);
        tap_hold->held = 0;
    }
}

#define ACTION_TAP_DANCE_TAP_HOLD(tap, hold) \
    { .fn = {NULL, tap_dance_tap_hold_finished, tap_dance_tap_hold_reset}, .user_data = (void *)&((tap_dance_tap_hold_t){tap, hold, 0}), }


tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Ctrl, twice for toggle mouse layer
    [T_1] = ACTION_TAP_DANCE_LAYER_TOGGLE(KC_LCTL, _MS),
    [K1_F1] = ACTION_TAP_DANCE_TAP_HOLD(KC_1, KC_F1),
    [K2_F2] = ACTION_TAP_DANCE_TAP_HOLD(KC_2, KC_F2),
    [K3_F3] = ACTION_TAP_DANCE_TAP_HOLD(KC_3, KC_F3),
    [K4_F4] = ACTION_TAP_DANCE_TAP_HOLD(KC_4, KC_F4),
    [K5_F5] = ACTION_TAP_DANCE_TAP_HOLD(KC_5, KC_F5),
    [K6_F6] = ACTION_TAP_DANCE_TAP_HOLD(KC_6, KC_F6),
    [K7_F7] = ACTION_TAP_DANCE_TAP_HOLD(KC_7, KC_F7),
    [K8_F8] = ACTION_TAP_DANCE_TAP_HOLD(KC_8, KC_F8),
    [K9_F9] = ACTION_TAP_DANCE_TAP_HOLD(KC_9, KC_F9),
    [K0_F10] = ACTION_TAP_DANCE_TAP_HOLD(KC_0, KC_F10),
    [Kmin_F11] = ACTION_TAP_DANCE_TAP_HOLD(KC_MINS, KC_F11),
    [Keq_F12] = ACTION_TAP_DANCE_TAP_HOLD(KC_EQL, KC_F12),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // on every key event start or extend `idle_callback()` deferred execution after IDLE_TIMEOUT_MS
    static deferred_token idle_token = INVALID_DEFERRED_TOKEN;

    if (!extend_deferred_exec(idle_token, idle_timeout)) {
        idle_token = defer_exec(idle_timeout, idle_callback, NULL);
    }

    tap_dance_action_t *action;

    switch(keycode) {
        case SS_MARKDOWNCODEBLOCK:
            if (record->event.pressed) {
                SEND_STRING("```\n\n```" SS_TAP(X_UP));
            }
            break;
        case KC_JIGG:
            if (record->event.pressed) {
                is_jiggling = !is_jiggling;
            }
            break;
        case TD(K1_F1):
        case TD(K2_F2):
        case TD(K3_F3):
        case TD(K4_F4):
        case TD(K5_F5):
        case TD(K6_F6):
        case TD(K7_F7):
        case TD(K8_F8):
        case TD(K9_F9):
        case TD(K0_F10):
        case TD(Kmin_F11):
        case TD(Keq_F12):
            action = &tap_dance_actions[QK_TAP_DANCE_GET_INDEX(keycode)];
            if (!record->event.pressed && action->state.count && !action->state.finished) {
                tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
                tap_code16(tap_hold->tap);
            }
            break;
    }

    return process_record_keymap(keycode, record) && secrets_process_record_user(keycode, record);
}
