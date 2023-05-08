// Copyright 2022 Markus Knutsson (@TweetyDaBird)
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H
#include "bongo.h"

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
    }
    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QWE] = LAYOUT(
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_KB_MUTE,    XXXXXXX, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                            KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_LSFT, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                            KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_RSFT,
    KC_LGUI, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_VOLD,       KC_VOLU, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RGUI,
                               KC_LALT, MO(_NAV),KC_LCTL, KC_ENT,        KC_SPC,  KC_RCTL, MO(_SYM),KC_RALT
),

[_GAM] = LAYOUT(
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_KB_MUTE,    XXXXXXX, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                            KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_LSFT, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                            KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_RSFT,
    KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_VOLD,       KC_VOLU, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RGUI,
                               KC_LALT, MO(_NAV),KC_SPC,  KC_ENT,        DF(_QWE),KC_RCTL, MO(_SYM),KC_RALT
),

[_SYM] = LAYOUT(
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   _______,       _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
    _______, XXXXXXX, KC_GRV,  KC_MINS, KC_EQL,  XXXXXXX,                         XXXXXXX, KC_LBRC, KC_RBRC, KC_QUOT, KC_BSLS, _______,
    _______, DF(_GAM),XXXXXXX, XXXXXXX, XXXXXXX, CH_LANG, _______,       _______, PR_SCR,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
                               _______, _______, _______, _______,       _______, _______, _______, _______
),

[_NAV] = LAYOUT(
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MPLY,       _______, XXXXXXX, KC_P7,   KC_P8,   KC_P9,   KC_PSLS, _______,
    _______, KC_HOME, KC_UP,   KC_END,  KC_PGUP, XXXXXXX,                         XXXXXXX, KC_P4,   KC_P5,   KC_P6,   KC_PAST, _______,
    _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, XXXXXXX,                         XXXXXXX, KC_P1,   KC_P2,   KC_P3,   KC_PMNS, _______,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MPRV,       KC_MNXT, XXXXXXX, KC_PDOT, KC_P0,   KC_PEQL, KC_PPLS, _______,
                               _______, _______, _______, _______,       _______, _______, _______, _______
)
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_QWE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(XXXXXXX, XXXXXXX) },
    [_GAM] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(XXXXXXX, XXXXXXX) },
    [_SYM] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(XXXXXXX, XXXXXXX) },
    [_NAV] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(XXXXXXX, XXXXXXX) }
};
#endif

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_left()) {
        return OLED_ROTATION_0;
    } else {
        return OLED_ROTATION_180;
    }
    return rotation;
}

bool oled_task_user(void) {
    draw_bongo(is_keyboard_master());
    return false;
}
