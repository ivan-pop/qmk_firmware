#include QMK_KEYBOARD_H


/*
  LAYOUT(
  _, _, _, _, _,       _, _, _, _, _,
  _, _, _, _, _,       _, _, _, _, _,
  _, _, _, _, _,       _, _, _, _, _,
           _, _,       _, _
  )
*/

#define _ KC_TRNS

enum layers {
  _MAIN,  // Main colemak-dh layout
  _UKR,   // Qwerty layout used for ukrainian language compatibility
  _UKR2,  // Layout width additional keys that dont fit in previous one
  _GAME,  // Layout for game keys
  _GAME2, // Layout with additional game keys
  _WMCL,  // Layout for keys to control WM
  _NUMS,  // Number keys
  _SYMS,  // Symbol keys
  _MOV,   // Movement keys
  _MDIA   // Media keys
};

enum custom_keycodes {
  KC_TOGGLE = SAFE_RANGE,
  KC_GAME = SAFE_RANGE + 1,
  _RGUI,
  _LGUI
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_MAIN] = LAYOUT(
                   KC_Q, KC_W, KC_F, KC_P, KC_B, KC_J, KC_L, KC_U, KC_Y, KC_SCLN,
                   LT(_WMCL, KC_A), LALT_T(KC_R), LSFT_T(KC_S), LCTL_T(KC_T), KC_G, KC_M, RCTL_T(KC_N), RSFT_T(KC_E), RALT_T(KC_I), LT(_WMCL, KC_O),
                   KC_Z, KC_X, KC_C, KC_D, KC_V, KC_K, KC_H, KC_COMM, KC_DOT, KC_SLSH,
                   KC_BSPC, LT(_NUMS, KC_TAB), LT(_SYMS,KC_ENT), KC_SPC
                   ),
  [_UKR] = LAYOUT(
                    KC_Q, KC_W, KC_E, KC_R, KC_T,                        KC_Y,   KC_U, KC_I, KC_O, KC_P,
                    KC_A, RALT_T(KC_S), LSFT_T(KC_D), LT(_UKR2, KC_F), KC_G,   KC_H, KC_J, LSFT_T(KC_K), RALT_T(KC_L), KC_SCLN,
                    KC_Z, KC_X,         KC_C,         KC_V,              KC_B,   KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH,
                    KC_BSPC, LT(_NUMS, KC_TAB),   LT(_SYMS, KC_ENT), KC_SPC
                    ),

  [_UKR2] = LAYOUT(
                     _, _, _, _, _,       _, KC_BSLS, _, _, LSFT(KC_6),
                     _, _, _, _, _,       _, KC_LBRC, KC_RBRC, KC_BSLS, KC_QUOT,
                     _, _, _, _, _,       _, _, _, _, LSFT(KC_7),
                     _, _,       LCTL(KC_ENT), _
                    ),
  // Layouts that I update from time to time for specific games
  [_GAME] = LAYOUT(
                   KC_LALT,  KC_Q, KC_W, KC_E, KC_R,      KC_GAME, _, _, _, _,
                   KC_LCTL, KC_A, KC_S, KC_D, KC_TAB,     _, _, _, _, _,
                   KC_LSFT, KC_X, KC_F, KC_G, KC_C,       _, _, _, _, _,
                   KC_SPC, LT(_GAME2, KC_ENT),            _, _
                   ),
  [_GAME2] = LAYOUT(
                    KC_8, KC_7, KC_6, KC_5, KC_9,       _, _, _, _, _,
                    KC_4, KC_3, KC_2, KC_1, KC_0,       _, _, _, _, _,
                    _, _, _, _, _,       _, _, _, _, _,
                    _, _,       _, _
                    ),
  [_WMCL] = LAYOUT(
                   _, _, _, _, _, _, _, _, _, _,
                   LGUI_T(KC_4), LALT_T(KC_3), LSFT_T(KC_2), LCTL_T(KC_1), KC_5, _, _, _, _, _,
                   _, _, _, _, _, _, _, _, _, _,
                   _, _ ,_, _
                   ),
  [_NUMS] = LAYOUT(
                   KC_ESC, KC_GAME,            KC_DOWN,      KC_UP, KC_BTN1,                              KC_PMNS, KC_7,    KC_8, KC_9, KC_EQL,
                   MO(_MDIA),      LALT_T(KC_R), LSFT_T(KC_S), LCTL_T(KC_CAPS), KC_TOGGLE, KC_PPLS, RCTL_T(KC_4), RSFT_T(KC_5), RALT_T(KC_6), KC_0,
                   MO(_MOV),      _,            _,            _,                       _,       KC_PAST, KC_1, KC_2, KC_3, KC_SLSH,
                                         RESET,            _,                       KC_LPRN, KC_RPRN
                   ),
  [_SYMS] = LAYOUT(
                   KC_GRV,  KC_AT,   KC_MINS, KC_PIPE, KC_HASH,           _, _, KC_PMNS, _, _,
                   KC_PERC, KC_AMPR, KC_QUOT, KC_LPRN, KC_RPRN,           KC_PPLS, _, _, _, _,
                   KC_CIRC, KC_BSLS, KC_EXLM, KC_LBRC, KC_RBRC,           _, _, _, _, _,
                                                       KC_DLR, _ , _, _
                   ),
  [_MOV] = LAYOUT(
                  _, _, _, _, _,       _, _, _, _, _,
                  _, _, _, _, _,       _, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT,
                  _, _, _, _, _,       _, _, _, _, _,
                           _, _,       _, _
                  ),

  [_MDIA] = LAYOUT(
                   _, _, _, _, _,       KC_VOLU, KC_F7, KC_F8, KC_F9, KC_F12,
                   _, _, _, _, _,       KC_VOLD, KC_F4, KC_F5, KC_F6, KC_F11,
                   _, _, _, _, _,       KC_PSCR, KC_F1, KC_F2, KC_F3, KC_F10,
                            _, _,       KC_BRIU, KC_BRID
                   ),
};

// TODO: I think I can make scheme wrapper for things like these
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case KC_TOGGLE:
    if (record->event.pressed) {
      // Toggle layer from ukrainian to normal layout
      if (layer_state_is(_UKR)) {
        layer_off(_UKR);
        layer_on(_MAIN);
        tap_code(KC_F14); // Tap f14 to make DE aware of switch and change layout
      }
      else {
        layer_on(_UKR);
        layer_off(_MAIN);
        tap_code(KC_F14);
      }
    }
    break;
  case KC_GAME:
    if (record->event.pressed) {
      // Toggle layer from game to normal layout
      if (layer_state_is(_GAME)) {
        layer_off(_GAME);
        layer_on(_MAIN);
      }
      else {
        layer_on(_GAME);
        layer_off(_MAIN);
      }
    }
    break;
  }
  return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
  // Make it so when _WMCL layer is active - lgui mod will be activated
  switch (get_highest_layer(state)) {
  case _WMCL:
    register_mods(mod_config(MOD_LGUI));
    break;
  default:
    clear_mods();
    break;
  }
  return state;
}
