/* Good on you for modifying your layout! if you don't have
 * time to read the QMK docs, a list of keycodes can be found at
 *
 * https://github.com/qmk/qmk_firmware/blob/master/docs/keycodes.md
 *
 * There's also a template for adding new layers at the bottom of this file!
 */

#include QMK_KEYBOARD_H
#ifdef OLED_DRIVER_ENABLE
    #include "keyboard_pet.c"
#endif

#ifdef THUMBSTICK_ENABLE
#    include "thumbstick.h"
#endif

#define BASE 0 // default layer
#define SYMB 1 // symbols
#define NUMB 2 // numbers/motion
#define GAMER 3 // gaming

//macros
#define CTL_TAB MT(MOD_LCTL, KC_TAB)
#define WIN_NUM LT(NUMB, KC_LGUI)
#define SPC_ALT MT(MOD_LALT, KC_SPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[BASE] = LAYOUT_gergo(
    KC_ESC, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                                                    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    CTL_TAB,KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_TRNS,                      KC_VOLU, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT,KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_TRNS, KC_PGUP,             KC_PGDN, KC_TRNS, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, TG(GAMER),
                     KC_BSPC, SPC_ALT, WIN_NUM, MO(SYMB),                      MO(NUMB),MO(SYMB),LT(SYMB, KC_SPC), KC_ENT
    ),

[SYMB] = LAYOUT_gergo(
    KC_TILD, KC_EXLM, KC_AT, KC_HASH, KC_DLR,  KC_PERC,                                            KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL,
    KC_F1,   KC_F2,   KC_F3, KC_F4,   KC_F5,   KC_F6,   KC_TRNS,                          KC_TRNS, KC_TRNS, KC_MINS, KC_EQL, KC_LBRC, KC_RBRC, KC_PIPE,
    KC_F7,   KC_F8,   KC_F9, KC_F10,  KC_F11,  KC_F12,  KC_TRNS, KC_TRNS,        KC_TRNS, KC_TRNS, KC_TRNS, KC_PLUS, KC_UNDS, KC_TRNS, KC_TRNS, KC_TRNS,
                                      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
[NUMB] = LAYOUT_gergo(
    KC_TRNS, KC_1, 	  KC_2,    KC_3,    KC_4,    KC_5,                                             KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_TRNS,
    KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                         KC_TRNS,  KC_TRNS, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_TRNS,
    KC_TRNS, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_TRNS,     KC_TRNS, KC_TRNS,  KC_TRNS, KC_MPRV, KC_MPLY, KC_MSTP, KC_MNXT, KC_TRNS,
                                        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS
    ),
[GAMER] = LAYOUT_gergo(
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                               KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                             KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_F2,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,           KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, TG(GAMER),
                                        KC_RCTL, KC_TRNS, KC_1, KC_2,           KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    )
};

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
	return OLED_ROTATION_90;
}

static void print_status_narrow(void) {

    oled_set_cursor(0,5);

    // Print current layer
    oled_write("LAYER", false);

    oled_set_cursor(0,6);

    switch (get_highest_layer(layer_state)) {
        case BASE:
            oled_write("BASE ", false);
            break;
        case SYMB:
            oled_write("PEACH", false);
            break;
        case NUMB:
            oled_write("CHERY", false);
            break;
        case GAMER:
            oled_write("GAMER", false);
            break;
        default:
            oled_write("undef", false);
    }

    // caps lock
    oled_set_cursor(0,8);
    oled_write("CPSLK", led_usb_state.caps_lock);

    // KEYBOARD PET RENDER START

    render_luna(0,13);

    // KEYBOARD PET RENDER END
}

void oled_task_user(void) {
    current_wpm = get_current_wpm();
    led_usb_state = host_keyboard_led_state();

    print_status_narrow();
    render_luna(0,13);
}
#endif

#ifdef THUMBSTICK_ENABLE
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case KC_LSFT:
            if (record->event.pressed) {
                thumbstick_mode_cycle(false);
            }
    }
    return true;
}
#endif