// Copyright 2022 Markus Knutsson (@TweetyDaBird)
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

enum layers {
    _QWERTY,
    _GAME,
    _SYM,
};

enum custom_keycodes {
    KC_QWERTY = SAFE_RANGE,
    KC_NUMERIC,
    KC_FUNCTION,
	KC_SYSTEM,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QWERTY] = LAYOUT(
      KC_ESC, 	 KC_1, 	    KC_2,      KC_3,	  KC_4,      KC_5,  	KC_KB_MUTE,    KC_NO,      KC_6,  	 KC_7,   	KC_8,      KC_9,      KC_0,      KC_DEL,
      KC_TAB, 	 KC_Q, 	    KC_W,      KC_E,      KC_R,      KC_T,                     		       KC_Y,     KC_U,      KC_I,      KC_O,      KC_P,      KC_BSPC,
      KC_LSFT, 	 KC_A, 	    KC_S,      KC_D,      KC_F,      KC_G,                     			   KC_H, 	 KC_J,      KC_K,      KC_L,      KC_SCLN,   KC_RSFT,
      KC_LGUI,   KC_Z, 	    KC_X,      KC_C,      KC_V,      KC_B,      KC_VOLD,       KC_VOLU,    KC_N,	 KC_M,      KC_COMM,   KC_DOT,    KC_SLSH,   KC_RGUI,
                                       KC_LALT,   MO(_SYM),  KC_LCTL,   KC_ENT,        KC_SPC,     KC_RCTL,  MO(_SYM),  KC_RALT
),

[_GAME] = LAYOUT(
      KC_ESC, 	 KC_1, 	    KC_2,      KC_3,	  KC_4,      KC_5,  	KC_KB_MUTE,    KC_NO,      KC_6,  	 KC_7,   	KC_8,      KC_9,      KC_0,      EE_CLR,
      KC_TAB, 	 KC_Q, 	    KC_W,      KC_E,      KC_R,      KC_T,                     		       KC_Y,     KC_U,      KC_I,      KC_O,      KC_P,      KC_BSPC,
      KC_LSFT, 	 KC_A, 	    KC_S,      KC_D,      KC_F,      KC_G,                     			   KC_H, 	 KC_J,      KC_K,      KC_L,      KC_SCLN,   KC_RSFT,
      KC_LCTL,   KC_Z, 	    KC_X,      KC_C,      KC_V,      KC_B,      KC_VOLD,       KC_VOLU,    KC_N,	 KC_M,      KC_COMM,   KC_DOT,    KC_SLSH,   KC_RGUI,
                                       KC_LALT,   MO(_SYM),  KC_SPC,    KC_ENT,        KC_SPC,     KC_RCTL,  DF(_QWERTY),KC_RALT
),

[_SYM] = LAYOUT(
      _______, 	 KC_F2,	    KC_F3,     KC_F4,	  KC_F5,     KC_F6,  	KC_MPLY,       KC_NO,      KC_F7,  	 KC_F8,   	KC_F9,     KC_F10,    KC_F11,    _______,
      _______, 	 KC_F1, 	KC_UP,     KC_GRV,    KC_MINS,   KC_EQL,                   		       KC_LBRC,  KC_RBRC,   KC_QUOT,   KC_MS_U,   KC_F12,    _______,
      _______, 	 KC_LEFT,   KC_DOWN,   KC_RGHT,   S(KC_MINS),S(KC_EQL),                     	   S(KC_LBRC),S(KC_RBRC),KC_MS_L,  KC_MS_D,   KC_MS_R,   _______,
      _______,   DF(_GAME), RGB_TOG,   RGB_MOD,   RGB_VAD,   CH_LANG,   KC_MPRV,       KC_MNXT,    KC_PSCR,	 KC_BSLS,   KC_BTN1,   KC_BTN3,   KC_BTN2,   _______,
                                       _______,   _______,   _______,   _______,       _______,    _______,  _______,   _______
),
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

    switch(get_highest_layer(layer_state | default_layer_state)) {
        case _QWERTY:
            white_scaled_rgb = hsv_to_rgb(white_scaled_hsv);
            rgb_matrix_set_color_all(white_scaled_rgb.r, white_scaled_rgb.g, white_scaled_rgb.b); // QWERTY
            break;
        case _GAME:
            blue_scaled_rgb = hsv_to_rgb(blue_scaled_hsv);
            rgb_matrix_set_color_all(blue_scaled_rgb.r, blue_scaled_rgb.g, blue_scaled_rgb.b); // GAME
            break;
        case _SYM:
            red_scaled_rgb = hsv_to_rgb(red_scaled_hsv);
            rgb_matrix_set_color_all(red_scaled_rgb.r, red_scaled_rgb.g, red_scaled_rgb.b); // RAISE
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
