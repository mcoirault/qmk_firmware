#include "y01.h"
#include "bongo.h"
#include "gol.h"

bool bongo_displayed = true;

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
        case KC_F22:
            if (record->event.pressed) {
                reset_gol();
            }
            return false;
        case KC_F23:
            if (record->event.pressed) {
                bongo_displayed = !bongo_displayed;
            }
            return false;
        case KC_F24:
            if (record->event.pressed) {
                current_default_anim = (current_default_anim + 1) % 3;
            }
            return false;
    }
    if (record->event.pressed) {
        bongo_state_tap = 1;
    }
    return true;
}

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    srand(timer_read());
    return OLED_ROTATION_180;
}

bool oled_task_user(void) {
    if (bongo_displayed) {
        draw_bongo_dynamic();
    }
    else {
        draw_gol();
    }
    return false;
}
#endif
