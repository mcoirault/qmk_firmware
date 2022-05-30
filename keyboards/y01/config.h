#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x592d /* "Y-" */
#define PRODUCT_ID      0x3031 /* "01" */
#define DEVICE_VER      0x0001
#define MANUFACTURER    Yornn
#define PRODUCT         Y-01

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 15

/* key matrix pins */
#define MATRIX_ROW_PINS { F0, F1, C7, D5, B7 }
#define MATRIX_COL_PINS { B0, F4, F5, F6, F7, B1, B3, B2, B6, B5, B4, E6, D7, C6, D4 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define OLED_UPDATE_INTERVAL 66

#define DEBOUNCE 5

#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE
#define NO_ACTION_ONESHOT
// #define NO_ACTION_TAPPING
#define NO_MUSIC_MODE
