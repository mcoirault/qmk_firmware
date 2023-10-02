#include "y01.h"
#include "bongo.h"
#include "gol.h"

uint8_t active_animation = 0;

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
                active_animation = (active_animation + 1) % 3;
            }
            return false;
        case KC_F24:
            if (record->event.pressed) {
                bongo_animation = (bongo_animation + 1) % BONGO_ANIMATIONS;
            }
            return false;
    }

    if (record->event.pressed) {
        bongo_tapped = true;
    }

    return true;
}

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    srand(timer_read());
    return OLED_ROTATION_180;
}

bool oled_task_user(void) {
    switch (active_animation) {
        case 1:
            draw_gol();
            break;
        default:
            draw_bongo();
            break;
    }
    return false;
}
#endif
