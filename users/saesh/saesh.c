#include "saesh.h"

__attribute__ ((weak))
bool secrets_process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case SS_MARKDOWNCODEBLOCK:
            if (record->event.pressed) {
                SEND_STRING("```\n\n```" SS_TAP(X_UP));
            }
            return false;
    }

    return secrets_process_record_user(keycode, record);
}
