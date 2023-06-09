#include QMK_KEYBOARD_H

enum custom_keycodes {
    NEXT_SENTENCE = SAFE_RANGE,
};

// Tap Dance declarations
enum {
    TD_CW_CL, // Tap for CAPS WORD, double tap for CAPS LOCK
};

void td_capswork_lock(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        caps_word_toggle();
    } else if (state->count == 2) {
        register_code(KC_CAPS);
        unregister_code(KC_CAPS);
    }
};

// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Caps Word, twice for Caps Lock
    [TD_CW_CL] = ACTION_TAP_DANCE_FN(td_capswork_lock),
};

// Keymap layers
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_split_3x6_3(KC_NO, KC_Q, KC_W, KC_F, KC_P, KC_B, KC_J, KC_L, KC_U, KC_Y, KC_SCLN, KC_NO, KC_NO, LGUI_T(KC_A), LALT_T(KC_R), LCTL_T(KC_S), LSFT_T(KC_T), ALL_T(KC_G), ALL_T(KC_M), LSFT_T(KC_N), LCTL_T(KC_E), LALT_T(KC_I), LGUI_T(KC_O), KC_NO, KC_NO, KC_Z, KC_X, KC_C, KC_D, KC_V, KC_K, KC_H, KC_COMM, KC_DOT, KC_SLSH, KC_NO, KC_NO, LT(1,KC_BSPC), LT(3,KC_TAB), LT(4,KC_ENT), LT(2,KC_SPC), KC_NO),
    [1] = LAYOUT_split_3x6_3(KC_NO, KC_NO, KC_NO, LCTL(KC_PGUP), LCTL(KC_PGDN), KC_NO, KC_PGUP, KC_HOME, KC_UP, KC_END, KC_ESC, KC_NO, KC_NO, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_HYPR, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_DEL, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, LCTL(KC_Z), LCTL(KC_C), LCTL(KC_V), LCTL(KC_X), LCTL(KC_Y), KC_NO, KC_NO, KC_TRNS, KC_NO, KC_ENT, TD(TD_CW_CL), KC_NO),
    [2] = LAYOUT_split_3x6_3(KC_NO, KC_GRV, KC_SLSH, KC_ASTR, KC_AMPR, KC_MINS, KC_NO, KC_LBRC, KC_RBRC, KC_NO, KC_NO, KC_NO, KC_NO, KC_QUOT, KC_CIRC, KC_PERC, KC_DLR, KC_EQL, KC_HYPR, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, KC_NO, KC_NO, KC_TILD, KC_HASH, KC_AT, KC_EXLM, KC_BSLS, KC_NO, KC_LCBR, KC_RCBR, KC_NO, KC_NO, KC_NO, KC_NO, KC_LPRN, KC_RPRN, KC_NO, KC_TRNS, KC_NO),
    [3] = LAYOUT_split_3x6_3(KC_NO, KC_NO, KC_F9, KC_F8, KC_F7, KC_F12, KC_PLUS, KC_7, KC_8, KC_9, KC_ASTR, KC_NO, KC_NO, KC_ESC, KC_F6, KC_F5, KC_F4, KC_F11, KC_MINS, KC_4, KC_5, KC_6, KC_SLSH, KC_NO, KC_NO, KC_NO, KC_F3, KC_F2, KC_F1, KC_F10, KC_0, KC_1, KC_2, KC_3, OSM(MOD_LALT), KC_NO, KC_NO, KC_NO, KC_TRNS, KC_ENT, KC_DOT, KC_NO),
    [4] = LAYOUT_split_3x6_3(KC_NO, KC_NO, KC_BTN1, KC_MS_U, KC_BTN2, KC_BTN3, KC_NO, KC_MPRV, KC_MPLY, KC_MNXT, KC_NO, KC_NO, KC_NO, KC_NO, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_U, KC_NO, KC_VOLD, KC_MUTE, KC_VOLU, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_WH_D, KC_NO, RGB_RMOD, RGB_TOG, RGB_MOD, KC_NO, KC_NO, KC_NO, KC_PSCR, LGUI(KC_ESC), KC_TRNS, KC_NO, KC_NO)
};

// Process custom keycodes
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case NEXT_SENTENCE:
            if (record->event.pressed) {
                SEND_STRING(". ");
                add_oneshot_mods(MOD_BIT(KC_LSFT));  // Set one-shot mod for shift.
            }
            break;
    }
    return true;
};

// Combo keys
enum combos {
  PL_MINUS,
  DH_UNDERSCORE,
  VK_NEXT_SENTENCE,
  FU_ESCAPE,
};

const uint16_t PROGMEM pl_combo[] = {KC_P, KC_L, COMBO_END};
const uint16_t PROGMEM dh_combo[] = {KC_D, KC_H, COMBO_END};
const uint16_t PROGMEM vk_combo[] = {KC_V, KC_K, COMBO_END};
const uint16_t PROGMEM fu_combo[] = {KC_F, KC_U, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    [PL_MINUS] = COMBO(pl_combo, KC_MINUS),
    [DH_UNDERSCORE] = COMBO(dh_combo, LSFT(KC_MINUS)),
    [VK_NEXT_SENTENCE] = COMBO(vk_combo, NEXT_SENTENCE),
    [FU_ESCAPE] = COMBO(fu_combo, KC_ESC),
};
