# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = atmel-dfu

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
EXTRAKEY_ENABLE = yes       # Audio control and System control
NKRO_ENABLE = yes           # Enable N-Key Rollover
WPM_ENABLE = yes
LTO_ENABLE = yes
VIA_ENABLE = yes

MOUSEKEY_ENABLE = no        # Mouse keys
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
AUDIO_ENABLE = no
SPACE_CADET_ENABLE = no
MUSIC_ENABLE = no
MAGIC_ENABLE = no

OLED_ENABLE = yes
OLED_DRIVER_ENABLE = yes
OLED_DRIVER = SSD1306

VIA_FIRMWARE_VERSION = 1
