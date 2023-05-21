// Copyright 2022 Markus Knutsson (@TweetyDaBird)
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

enum layers {
    _QWE,
    _GAM,
    _SYM,
    _NAV
};

enum custom_keycodes {
    PR_SCR = SAFE_RANGE,
    CH_LANG
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case PR_SCR:
        if (record->event.pressed) {
            // when keycode PR_SCR is pressed
            // snip a part of the screen
            SEND_STRING(SS_TAP(X_PSCR));
        } else {
            // when keycode PR_SCR is released
        }
        break;
    case CH_LANG:
        if (record->event.pressed) {
            // when keycode CH_LANG is pressed
            // change language layout
            SEND_STRING(SS_DOWN(X_LGUI) SS_DELAY(10) SS_TAP(X_SPC) SS_DELAY(10) SS_UP(X_LGUI));
        } else {
            // when keycode CH_LANG is released
        }
        break;
    case LCTL_T(G(KC_SPACE)):
        if (record->tap.count && record->event.pressed) {
            tap_code16(G(KC_SPACE)); // Intercept tap function to send Cmd+Space
            return false;
        }
        break;
    }
    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QWE] = LAYOUT(
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    XXXXXXX,       XXXXXXX, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                            KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_LSFT, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                            KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_RSFT,
    KC_LGUI, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_VOLD,       KC_VOLU, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RGUI,
                               KC_LALT, MO(_SYM),KC_LCTL, KC_ENT,        KC_SPC,  KC_RCTL, MO(_NAV),KC_RALT
),

[_GAM] = LAYOUT(
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    XXXXXXX,      XXXXXXX, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                            KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_LSFT, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                            KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_RSFT,
    KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_VOLD,       KC_VOLU, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RCTL,
                               KC_LALT, MO(_SYM),KC_SPC,  KC_ENT,        DF(_QWE),KC_RGUI, MO(_NAV),KC_RALT
),

[_SYM] = LAYOUT(
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,       _______, XXXXXXX, KC_P7,   KC_P8,   KC_P9,   KC_PSLS, _______,
    _______, KC_BSLS, KC_QUOT, KC_LBRC, KC_RBRC, XXXXXXX,                         XXXXXXX, KC_P4,   KC_P5,   KC_P6,   KC_PAST, _______,
    _______, XXXXXXX, KC_GRV,  KC_MINS, KC_EQL,  XXXXXXX,                         XXXXXXX, KC_P1,   KC_P2,   KC_P3,   KC_PMNS, _______,
    _______, DF(_GAM),XXXXXXX, XXXXXXX, KC_PSCR, CH_LANG, KC_MPLY,       KC_KB_MUTE,XXXXXXX,KC_PDOT,KC_P0,   KC_PEQL, KC_PPLS, _______,
                               _______, _______, _______, _______,       _______, _______, _______, _______
),

[_NAV] = LAYOUT(
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,       _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
    _______, KC_HOME, KC_UP,   KC_END,  KC_PGUP, XXXXXXX,                         XXXXXXX, KC_F1,   KC_F2,   KC_F3,   KC_F4,   _______,
    _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, XXXXXXX,                         XXXXXXX, KC_F5,   KC_F6,   KC_F7,   KC_F8,   _______,
    _______, RGB_TOG, RGB_MOD, RGB_VAD, XXXXXXX, XXXXXXX, KC_MPRV,       KC_MNXT, XXXXXXX, KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,
                               _______, _______, _______, _______,       _______, _______, _______, _______
)

};

// RGB
bool rgb_matrix_indicators_kb(void) {
    uint8_t val = rgb_matrix_get_val();

    HSV white_scaled_hsv = { HSV_WHITE};
    white_scaled_hsv.v = val;
    RGB white_scaled_rgb;

    HSV blue_scaled_hsv = { HSV_BLUE };
    blue_scaled_hsv.v = val;
    RGB blue_scaled_rgb;

    HSV red_scaled_hsv = { HSV_RED };
    red_scaled_hsv.v = val;
    RGB red_scaled_rgb;

    HSV green_scaled_hsv = { HSV_GREEN };
    green_scaled_hsv.v = val;
    RGB green_scaled_rgb;

    switch(get_highest_layer(layer_state | default_layer_state)) {
        case _QWE:
            white_scaled_rgb = hsv_to_rgb(white_scaled_hsv);
            rgb_matrix_set_color_all(white_scaled_rgb.r, white_scaled_rgb.g, white_scaled_rgb.b); // QWERTY
            break;
        case _GAM:
            blue_scaled_rgb = hsv_to_rgb(blue_scaled_hsv);
            rgb_matrix_set_color_all(blue_scaled_rgb.r, blue_scaled_rgb.g, blue_scaled_rgb.b); // GAME
            break;
        case _SYM:
            red_scaled_rgb = hsv_to_rgb(red_scaled_hsv);
            rgb_matrix_set_color_all(red_scaled_rgb.r, red_scaled_rgb.g, red_scaled_rgb.b); // RAISE
            break;
        case _NAV:
            green_scaled_rgb = hsv_to_rgb(green_scaled_hsv);
            rgb_matrix_set_color_all(green_scaled_rgb.r, green_scaled_rgb.g, green_scaled_rgb.b); // NAV
            break;
        default:
            break;
    }
    return false;
}

#define LED_MATRIX_CENTER {110, 21}

led_config_t g_led_config = {
    {
        // Key Matrix to LED Index
        {NO_LED, 4,      3,      2,      1,      0},
        {NO_LED, 9,      8,      7,      6,      5}
    }, {
        // LED Index to Physical Position
        // Left half
        { 70, 27}, { 66, 40}, { 50, 42}, { 39, 41} ,{ 28, 40}, // bottom row, right to left, far outer right key is first
        // Right half
        {150, 27}, {154, 40}, {170, 42}, {181, 41}, {192, 40}, // bottom row, left to right, far outer left key is first
    }, {
        // LED Index to Flag
        4, 4, 4, 4, 4,
        4, 4, 4, 4, 4
    }
};

void suspend_power_down_kb(void) {
    rgb_matrix_set_suspend_state(true);
    suspend_power_down_user();
}

void suspend_wakeup_init_kb(void) {
    rgb_matrix_set_suspend_state(false);
    suspend_wakeup_init_user();
}
