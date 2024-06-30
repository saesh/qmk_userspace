#include "saesh.h"

__attribute__ ((weak))
bool secrets_process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    return secrets_process_record_user(keycode, record);
}
