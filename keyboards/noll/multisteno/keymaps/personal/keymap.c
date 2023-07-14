/* Copyright 2022 Nathan Olivares
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "keymap_steno.h"
// #include "multisteno.h" //makes clangd not redline everything
#include QMK_KEYBOARD_H

enum layers { STENO, NKRO, QWERTY, RAISE, LOWER, MODE };

// combo logic here removed

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [STENO] = LAYOUT(   MO(MODE), STN_N1, STN_N2, STN_N3, STN_N4, STN_N5,   STN_N6, STN_N7, STN_N8, STN_N9, STN_NA, STN_FN,
                        STN_NB, STN_S1, STN_TL, STN_PL, STN_HL, STN_ST1,    STN_ST3, STN_FR, STN_PR, STN_LR, STN_TR, STN_DR,
                        STN_NC, STN_S2, STN_KL, STN_WL, STN_RL, STN_ST2,    STN_ST4, STN_RR, STN_BR, STN_GR, STN_SR, STN_ZR,
                                                STN_A, STN_O, MO(LOWER),    MO(RAISE), STN_E, STN_U),

    [NKRO] = LAYOUT(    KC_GRAVE, KC_1, KC_2, KC_3, KC_4, KC_5,     KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS,
                        _______, KC_Q, KC_W, KC_E, KC_R, KC_T,      KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC,
                        MO(MODE), KC_A, KC_S, KC_D, KC_F, KC_G,     KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,
                                            KC_C, KC_V, KC_Z,       KC_X, KC_N, KC_M),

    [QWERTY] = LAYOUT(  KC_DEL, KC_Q, KC_W, KC_E, KC_R, KC_T,       KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC,
                        KC_ESC, LGUI_T(KC_A), LALT_T(KC_S), LSFT_T(KC_D), LCTL_T(KC_F), KC_G,       KC_H, RCTL_T(KC_J), RSFT_T(KC_K), LALT_T(KC_L), RGUI_T(KC_SCLN), KC_QUOT,
                        KC_TAB, KC_Z, KC_X, KC_C, KC_V, KC_B,       KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, TO(STENO),
                            XXXXXXX, LT(LOWER, KC_ENT), XXXXXXX,    XXXXXXX, LT(RAISE, KC_SPC), XXXXXXX),

    [RAISE] = LAYOUT(_______, KC_1, KC_2, KC_3, KC_4, KC_5,     KC_6, KC_7, KC_8, KC_9, KC_0, _______,
                    _______, KC_LGUI, KC_LALT, KC_LSFT, KC_LCTRL, KC_VOLU,      KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, XXXXXXX, XXXXXXX,
                    _______, KC_MPRV, KC_MUTE, KC_MPLY, KC_MNXT, KC_VOLD,       KC_HOME, KC_PGUP, KC_PGDN, KC_END, KC_SLSH, XXXXXXX,
                                                _______, KC_ENT, _______,      _______, _______, _______),

    [LOWER] = LAYOUT(KC_DEL, KC_AT, KC_LABK, KC_DLR, KC_RABK, XXXXXXX,          XXXXXXX, KC_LBRC, KC_ASTR, KC_RBRC, KC_GRV, KC_BSPC,
                    _______, KC_BSLASH, KC_LPRN, KC_MINUS, KC_RPRN, KC_HASH,    KC_PERC, KC_LCBR, KC_EQUAL, KC_RCBR, KC_COLN, XXXXXXX,
                    _______, KC_PIPE, KC_EXLM, KC_UNDS, KC_PLUS, XXXXXXX,       XXXXXXX, KC_AMPR, KC_CIRC, KC_TILDE, KC_QUES, KC_ENT,
                                            _______, _______, _______,          _______, KC_SPC, _______),

    [MODE] = LAYOUT(            _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______,
                                _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______,
                                _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______,
                                                        _______, _______, TG(QWERTY),           TG(NKRO), _______,  _______)};

void matrix_init_user(void) {
    // steno_set_mode(STENO_MODE_BOLT); // STENO_MODE_GEMINI or STENO_MODE_BOLT
    steno_set_mode(STENO_MODE_GEMINI);
    // STENO_MODE_GEMINI only works if you remove references to TX Bolt in QMK
    // follow ecosteno-geminipr.diff to do this (thanks to dnaq in the Plover discord)
};

layer_state_t layer_state_set_user(layer_state_t state) {
    // or uint8_t layer = get_highest_layer(state);
    switch (get_highest_layer(state)) {
        case (STENO):
            // green LED on
            palSetPad(GPIOA, 1);
            // red LED off
            palClearPad(GPIOA, 0);
            break;
        case (NKRO):
            // red LED on
            palSetPad(GPIOA, 0);
            // green LED off
            palClearPad(GPIOA, 1);
            break;
        case (QWERTY):
            palSetPad(GPIOA, 0);
            palSetPad(GPIOA, 1);
            break;
        case (RAISE):
            palSetPad(GPIOA, 0);
            palSetPad(GPIOA, 1);
            break;
        case (LOWER):
            palSetPad(GPIOA, 0);
            palSetPad(GPIOA, 1);
            break;
        default:
            // shouldn't happen but just in case
            // combo_disable();
            palClearPad(GPIOA, 1);
            palClearPad(GPIOA, 0);
            break;
    }

    return state;
}
