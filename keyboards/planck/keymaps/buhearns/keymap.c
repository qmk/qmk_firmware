#include QMK_KEYBOARD_H
#include "muse.h"

extern keymap_config_t keymap_config;

#define B_ENT FUNC(0) // Tap for enter, hold for right shift

enum custom_keycodes {
  B_UPD = SAFE_RANGE,
  B_SSH,
  B_SSHK,
  B_USR,
  B_X11,
  B_X112,
  B_X113,
  B_DEAB,
  B_DEAS,
  B_DEOB,
  B_DEOS,
  B_DEUB,
  B_DEUS,
  B_DE_S,
  B_DE_C,
  B_DE_E,
  B_DE_B,
  B_DEQR,
  B_DEQL,
  B_DE_1,
  B_DE_2,
  B_DE_3
};

const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_MODS_TAP_KEY(MOD_RSFT, KC_ENT)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[0] = LAYOUT_planck_grid(
    KC_GESC,     KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    LT(5,KC_TAB),KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, LT(4,KC_BSLS),
    KC_LSFT,     KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, B_ENT,
    KC_LCTL,     KC_LGUI, KC_RALT, MO(3),   MO(2),   KC_SPC,  KC_SPC,  MO(1),   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

[1] = LAYOUT_planck_grid(
    KC_TRNS,     B_UPD,   B_USR,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_7,    KC_8,    KC_9,    KC_DEL,
    KC_TRNS,     B_SSH,   B_SSHK,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_4,    KC_5,    KC_6,    KC_TRNS,
    KC_TRNS,     B_X11,   B_X112,  B_X113,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_1,    KC_2,    KC_3,    KC_TRNS,
    KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_0,    KC_PDOT, KC_PPLS, KC_PMNS
),

[2] = LAYOUT_planck_grid(
    KC_TRNS,     KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,  KC_BSPC,
    KC_TRNS,     KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_SLSH, KC_QUOT, KC_MINS, KC_LCBR, KC_RCBR,  KC_TRNS,
    KC_TRNS,     KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_DQUO, KC_EQL,  KC_LBRC, KC_RBRC,  KC_TRNS,
    KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_UNDS, KC_LT,   KC_GT,    KC_NO
),

[3] = LAYOUT_planck_grid(
    KC_TRNS,     KC_F13,   KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_NO,   KC_PSCR, KC_SLCK, KC_PAUS,  KC_DEL,
    KC_TRNS,     KC_F7,    KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_TRNS, KC_PGUP, KC_MS_U, KC_PGDN,  KC_TRNS,
    KC_TRNS,     KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R,  KC_HOME,
    KC_TRNS,     KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_BTN1, KC_BTN2, KC_BTN3,  KC_END
),

[4] = LAYOUT_planck_grid(
    KC_TRNS,     RESET,    DEBUG,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   MU_MOD,  MUV_IN,  MU_ON,   AU_ON,    KC_EJCT,
    KC_TRNS,     EEP_RST,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   MUV_DE,  MU_OFF,  AU_OFF,   KC_TRNS,
    KC_TRNS,     KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_MUTE, KC_MPRV, KC_MNXT,  KC_NO,
    KC_TRNS,     KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MSTP, KC_VOLD, KC_VOLU,  KC_MPLY
),

[5] = LAYOUT_planck_grid(
    B_DE_C,     B_DE_1,    B_DE_2,  B_DE_3,  B_DE_S,  B_DE_E,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,
    KC_TRNS,    B_DEAB,    B_DEOB,  B_DEUB,  B_DEQR,  B_DEQL,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,
    KC_TRNS,    B_DEAS,    B_DEOS,  B_DEUS,  B_DE_B,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,
    KC_TRNS,    KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS
)};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case B_UPD:
      if (record->event.pressed) {
        SEND_STRING("sudo apt update && sudo apt full-upgrade -yyy" SS_TAP(X_ENTER));
      }
      break;
    case B_SSH:
      if (record->event.pressed) {
        SEND_STRING("cd /etc/ssh" SS_TAP(X_ENTER) "sudo shasum ssh_host_*" SS_TAP(X_ENTER) "sudo rm ssh_host_*" SS_TAP(X_ENTER) "sudo dpkg-reconfigure openssh-server" SS_TAP(X_ENTER));
      }
      break;
    case B_SSHK:
      if (record->event.pressed) {
        SEND_STRING("ssh-keygen -t ed25519" SS_TAP(X_ENTER) SS_TAP(X_ENTER) SS_TAP(X_ENTER) SS_TAP(X_ENTER));
      }
      break;
    case B_USR:
      if (record->event.pressed) {
        SEND_STRING("useradd -m user" SS_TAP(X_ENTER) "usermod -a -G sudo user" SS_TAP(X_ENTER) "chsh -s /bin/bash user" SS_TAP(X_ENTER) "passwd user" SS_TAP(X_ENTER));
      }
      break;
    case B_X11:
      if (record->event.pressed) {
        SEND_STRING("sudo x11vnc -storepasswd /etc/x11vnc.pass" SS_TAP(X_ENTER));
      }
      break;
    case B_X112:
      if (record->event.pressed) {
        SEND_STRING("sudo nano /lib/systemd/system/x11vnc.service" SS_TAP(X_ENTER) "[Unit]" SS_TAP(X_ENTER) "Description=Start X11VNC" SS_TAP(X_ENTER) "After=multi-user.target" SS_TAP(X_ENTER) SS_TAP(X_ENTER) "[Service]" SS_TAP(X_ENTER) "Type=simple" SS_TAP(X_ENTER) "ExecStart=/usr/bin/x11vnc -display :0 -auth guess -forever -loop -noxdamage -repeat -rfbauth /etc/x11vnc.pass -rfbport 5900 -shared -localhost -o /var/log/x11vnc.log" SS_TAP(X_ENTER) SS_TAP(X_ENTER) "[Install]" SS_TAP(X_ENTER) "WantedBy=multi-user.target");
      }
      break;
    case B_X113:
      if (record->event.pressed) {
        SEND_STRING("sudo systemctl enable x11vnc.service" SS_TAP(X_ENTER));
      }
      break;
    case B_DEAB:
      if (record->event.pressed) {
        SEND_STRING(SS_DOWN(X_RALT) SS_TAP(X_KP_0) SS_TAP(X_KP_1) SS_TAP(X_KP_9) SS_TAP(X_KP_6) SS_UP(X_RALT));
      }
      break;
    case B_DEAS:
      if (record->event.pressed) {
        SEND_STRING(SS_DOWN(X_RALT) SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_2) SS_TAP(X_KP_8) SS_UP(X_RALT));
      }
      break;
    case B_DEOB:
      if (record->event.pressed) {
        SEND_STRING(SS_DOWN(X_RALT) SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_1) SS_TAP(X_KP_4) SS_UP(X_RALT));
      }
      break;
    case B_DEOS:
      if (record->event.pressed) {
        SEND_STRING(SS_DOWN(X_RALT) SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_4) SS_TAP(X_KP_6) SS_UP(X_RALT));
      }
      break;
    case B_DEUB:
      if (record->event.pressed) {
        SEND_STRING(SS_DOWN(X_RALT) SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_2) SS_TAP(X_KP_0) SS_UP(X_RALT));
      }
      break;
    case B_DEUS:
      if (record->event.pressed) {
        SEND_STRING(SS_DOWN(X_RALT) SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_5) SS_TAP(X_KP_2) SS_UP(X_RALT));
      }
      break;
    case B_DE_S:
      if (record->event.pressed) {
        SEND_STRING(SS_DOWN(X_RALT) SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_2) SS_TAP(X_KP_3) SS_UP(X_RALT));
      }
      break;
    case B_DE_C:
      if (record->event.pressed) {
        SEND_STRING(SS_DOWN(X_RALT) SS_TAP(X_KP_0) SS_TAP(X_KP_1) SS_TAP(X_KP_7) SS_TAP(X_KP_6) SS_UP(X_RALT));
      }
      break;
    case B_DE_E:
      if (record->event.pressed) {
        SEND_STRING(SS_DOWN(X_RALT) SS_TAP(X_KP_0) SS_TAP(X_KP_1) SS_TAP(X_KP_2) SS_TAP(X_KP_8) SS_UP(X_RALT));
      }
      break;
    case B_DE_B:
      if (record->event.pressed) {
        SEND_STRING(SS_DOWN(X_RALT) SS_TAP(X_KP_0) SS_TAP(X_KP_1) SS_TAP(X_KP_4) SS_TAP(X_KP_9) SS_UP(X_RALT));
      }
      break;
    case B_DEQR:
      if (record->event.pressed) {
        SEND_STRING(SS_DOWN(X_RALT) SS_TAP(X_KP_0) SS_TAP(X_KP_1) SS_TAP(X_KP_8) SS_TAP(X_KP_7) SS_UP(X_RALT));
      }
      break;
    case B_DEQL:
      if (record->event.pressed) {
        SEND_STRING(SS_DOWN(X_RALT) SS_TAP(X_KP_0) SS_TAP(X_KP_1) SS_TAP(X_KP_7) SS_TAP(X_KP_1) SS_UP(X_RALT));
      }
      break;
    case B_DE_1:
      if (record->event.pressed) {
        SEND_STRING(SS_DOWN(X_RALT) SS_TAP(X_KP_0) SS_TAP(X_KP_1) SS_TAP(X_KP_8) SS_TAP(X_KP_5) SS_UP(X_RALT));
      }
      break;
    case B_DE_2:
      if (record->event.pressed) {
        SEND_STRING(SS_DOWN(X_RALT) SS_TAP(X_KP_0) SS_TAP(X_KP_1) SS_TAP(X_KP_7) SS_TAP(X_KP_8) SS_UP(X_RALT));
      }
      break;
    case B_DE_3:
      if (record->event.pressed) {
        SEND_STRING(SS_DOWN(X_RALT) SS_TAP(X_KP_0) SS_TAP(X_KP_1) SS_TAP(X_KP_7) SS_TAP(X_KP_9) SS_UP(X_RALT));
      }
      break;
    }
  return true;
};
