#----------------------------------------------------------------------------
# make gergo:alexc:dfu
# Make sure you have dfu-programmer installed!
#----------------------------------------------------------------------------
# Firmware options
CONSOLE_ENABLE     = yes
ENCODER_ENABLE     = no
OLED_DRIVER_ENABLE = no
EXTRAKEY_ENABLE    = no
WPM_ENABLE         = yes
THUMBSTICK_ENABLE  = yes

ifeq ($(strip $(THUMBSTICK_ENABLE)), yes)
    POINTING_DEVICE_ENABLE = yes
    OPT_DEFS += -DTHUMBSTICK_ENABLE
	SRC += analog.c
	SRC += thumbstick.c
endif
