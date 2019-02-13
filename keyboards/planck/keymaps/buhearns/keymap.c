#include QMK_KEYBOARD_H
#include "muse.h"

extern keymap_config_t keymap_config;

enum custom_keycodes {
  B_UPD = SAFE_RANGE,
  B_SSH,
  B_SSHK,
  B_USR,
  B_X11,
  B_X12,
  B_X13
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[0] = LAYOUT_planck_grid(
  KC_ESC,      KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
  LT(5,KC_TAB),KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, LT(4,KC_BSLS),
  KC_LSFT,     KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, MT(MOD_RSFT,KC_ENT),
  KC_LCTL,     KC_LGUI, KC_LALT, MO(3),   MO(2),   KC_SPC,  KC_SPC,  MO(1),   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

[1] = LAYOUT_planck_grid(
  KC_TRNS, B_UPD,   B_USR,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_7,    KC_8,    KC_9,    KC_DEL,
  KC_TRNS, B_SSH,   B_SSHK,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_4,    KC_5,    KC_6,    KC_TRNS,
  KC_TRNS, B_X11,   B_X12,   B_X13,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_1,    KC_2,    KC_3,    KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_0,    KC_PDOT, KC_PPLS, KC_PMNS
),

[2] = LAYOUT_planck_grid(
  KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,  KC_BSPC,
  KC_TRNS, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_SLSH, KC_QUOT, KC_MINS, KC_LCBR, KC_RCBR,  KC_TRNS,
  KC_TRNS, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_DQUO, KC_EQL,  KC_LBRC, KC_RBRC,  KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_UNDS, KC_LT,   KC_GT,    KC_NO
),

[3] = LAYOUT_planck_grid(
  KC_TRNS, KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_NO,   KC_PSCR, KC_SLCK, KC_PAUS,  KC_DEL,
  KC_TRNS, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_TRNS, KC_PGUP, KC_MS_U, KC_PGDN,  KC_TRNS,
  KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R,  KC_HOME,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_BTN1, KC_BTN2, KC_BTN3,  KC_END
),

[4] = LAYOUT_planck_grid(
  KC_TRNS, RESET,   DEBUG,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   MU_MOD,  MUV_IN,  MU_ON,   AU_ON,    KC_EJCT,
  KC_TRNS, EEP_RST, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   MUV_DE,  MU_OFF,  AU_OFF,   KC_TRNS,
  KC_TRNS, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_MUTE, KC_MPRV, KC_MNXT,  KC_NO,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MSTP, KC_VOLD, KC_VOLU,  KC_MPLY
),

[5] = LAYOUT_planck_grid(
  UC(0xB0), UC(0xB9), UC(0xB2), UC(0xB3), UC(0xDF),   UC(0x20AC), KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
  KC_TRNS,  UC(0xC4), UC(0xD6), UC(0xDC), UC(0xBB),   UC(0xAB),   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
  KC_TRNS,  UC(0xE4), UC(0xF6), UC(0xFC), UC(0x2022), KC_NO,      KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS, KC_TRNS, UC_M_OS, UC_M_LN, UC_M_WI, UC_M_WC
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
    case B_X12:
      if (record->event.pressed) {
        SEND_STRING("sudo nano /lib/systemd/system/x11vnc.service" SS_TAP(X_ENTER) "[Unit]" SS_TAP(X_ENTER) "Description=Start X11VNC" SS_TAP(X_ENTER) "After=multi-user.target" SS_TAP(X_ENTER) SS_TAP(X_ENTER) "[Service]" SS_TAP(X_ENTER) "Type=simple" SS_TAP(X_ENTER) "ExecStart=/usr/bin/x11vnc -display :0 -auth guess -forever -loop -noxdamage -repeat -rfbauth /etc/x11vnc.pass -rfbport 5900 -shared -localhost -o /var/log/x11vnc.log" SS_TAP(X_ENTER) SS_TAP(X_ENTER) "[Install]" SS_TAP(X_ENTER) "WantedBy=multi-user.target");
      }
      break;
    case B_X13:
      if (record->event.pressed) {
        SEND_STRING("sudo systemctl enable x11vnc.service" SS_TAP(X_ENTER));
      }
      break;
    }
  return true;
};
