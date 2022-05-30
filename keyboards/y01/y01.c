#include "y01.h"
#include "bongo.h"

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case KC_CAPS:
        case KC_LCTL:
        case KC_RCTL:
        case KC_LALT:
        case KC_RALT:
        case KC_LGUI:
        case KC_RGUI:
            anim_timer = 99;  // forces an animation reset
            return true;
    }
    if (record->event.pressed) {
        bongo_state_tap = 1;
    }
    return true;
}

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_180;
}

bool oled_task_user(void) {
    draw_bongo_dynamic();
    return false;
}
#endif
