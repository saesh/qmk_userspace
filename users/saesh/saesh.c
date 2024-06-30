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

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // on every key event start or extend `idle_callback()` deferred execution after IDLE_TIMEOUT_MS
    static deferred_token idle_token = INVALID_DEFERRED_TOKEN;

    if (!extend_deferred_exec(idle_token, idle_timeout)) {
        idle_token = defer_exec(idle_timeout, idle_callback, NULL);
    }

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
    }

    return process_record_keymap(keycode, record) && secrets_process_record_user(keycode, record);
}
