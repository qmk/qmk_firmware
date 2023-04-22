// Copyright 2018 Wez Furlong (@wez)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "config.h"
#if ENABLE_TOUCHPAD
#include "proxsense.h"
#include "i2c.h"
#include "pincontrol.h"
#include "debug.h"
#include "mousekey.h"
#include "lib/lufa/LUFA/Common/Endianness.h"

#define DRPin F6 // ~INT on A1

#define i2cAddress  0b1110100
namespace {
enum Addr : uint16_t {
  ProductNumber = 0,
  ProjectNumber = 2,
  MajorVersion = 4,
  MinorVersion = 5,
  BootloaderStatus = 6,

  MaxTouchColAndRow = 0xb,
  PreviousCycleTimeMs = 0xc,
  GestureEvents0 = 0xd,
  GestureEvents1 = 0xe,
  SystemInfo0 = 0xf,
  SystemInfo1 = 0x10,
  NumberOfFingers=0x11,

  Finger1RelativeX = 0x12,
  Finger1RelativeY = 0x14,

  Finger1AbsoluteX = 0x16,
  Finger1AbsoluteY = 0x18,
  Finger1TouchStrenth = 0x1a,
  Finger1TouchArea = 0x1c,

  Finger2AbsoluteX = 0x1d,
  Finger2AbsoluteY = 0x1f,
  Finger2TouchStrenth = 0x21,
  Finger2TouchArea = 0x23,

  Finger3AbsoluteX = 0x24,
  Finger3AbsoluteY = 0x26,
  Finger3TouchStrenth = 0x28,
  Finger3TouchArea = 0x2a,

  Finger4AbsoluteX = 0x2b,
  Finger4AbsoluteY = 0x2d,
  Finger4TouchStrenth = 0x2f,
  Finger4TouchArea = 0x31,

  Finger5AbsoluteX = 0x32,
  Finger5AbsoluteY = 0x34,
  Finger5TouchStrenth = 0x36,
  Finger5TouchArea = 0x38,

  ProxStatus = 0x39,
  TouchStatus = 0x59,
  SnapStatus = 0x77,
  CountValues = 0x95,
  DeltaValues = 0x1c1,
  ALPCountValue = 0x2ed,
  ALPIndividualCountValues = 0x2ef,
  ReferenceValues = 0x303,
  ALPLTA = 0x42f,

  SystemControl0 = 0x431,
  SystemControl1 = 0x432,

  ALPATICompensation = 0x435,
  ATICompensation = 0x43f,
  ATICIndividualAdjust = 0x4d5,
  GlobalATIC = 0x56b,
  ALPATIC = 0x56c,

  ReportRateMs = 0x57a,

  SystemConfig0 = 0x58e,
  SystemConfig1 = 0x58f,
  XYConfig0 = 0x669,
  PalmRejectThreshold = 0x66c,
  // measured in multiples of 32ms
  PalmRejectTimeout = 0x66d,

  SingleFingerGestures = 0x6b7,
  MultiFingerGestures = 0x6b8,
  TapTimeMs = 0x6b9,
  TapDistancePixels = 0x6bb,
  HoldTimeMs = 0x6bd,

  ScrollInitialDistancePixels = 0x6c8,
  // 64tan(deg)
  ScrollAngle = 0x6ca,
  EndCommunicationWindow = 0xeeeeUL,
};

// A helper class for defining and consuming bitfields in registers
struct ByteField {
  uint8_t raw;

  inline uint8_t get_value(uint8_t bit, uint8_t width) const {
    uint8_t mask = (1 << width) - 1;
    return (raw >> bit) & mask;
  }

  inline void set_value(uint8_t bit, uint8_t width, uint8_t value) {
    uint8_t mask = (1 << width) - 1;
    raw &= ~(mask << bit);
    raw |= (value & mask) << bit;
  }

  inline bool get_bit(uint8_t bit) const {
    return (raw & (1 << bit)) != 0;
  }

  inline void set_bit(uint8_t bit, bool value) {
    uint8_t shifted = (1 << bit);
    if (value) {
      raw |= shifted;
    } else {
      raw &= ~shifted;
    }
  }
};

// Declare a single bit wide bit field in a ByteField descendant
#define defineBit(name, bitno)                                                 \
  inline bool name(void) const { return get_bit(bitno); }                      \
  inline void set_##name(bool value) { set_bit(bitno, value); }
// Declare a multi-bit wide bit field in a ByteField descendant
#define defineField(name, bitno, width)                                        \
  inline uint8_t name(void) const { return get_value(bitno, width); }          \
  inline void set_##name(bool value) { set_value(bitno, width, value); }


// unsigned 16 bit value stored big endian
struct BigEndianU16 {
  uint16_t be{0};

  inline uint16_t get_value() const {
    return be16_to_cpu(be);
  }

  inline void set_value(uint16_t value) {
    be = cpu_to_be16(value);
  }

  BigEndianU16() = default;
  BigEndianU16(uint16_t value) : be(cpu_to_be16(value)) {}
  BigEndianU16& operator=(uint16_t value) {
    set_value(value);
    return *this;
  }

  operator uint16_t() const {
    return get_value();
  }
};

// Signed 16 bit value stored big endian
struct BigEndianI16 {
  int16_t be{0};

  inline int16_t get_value() const {
    return be16_to_cpu(be);
  }

  inline void set_value(int16_t value) {
    be = cpu_to_be16(value);
  }

  BigEndianI16() = default;
  BigEndianI16(int16_t value) : be(cpu_to_be16(value)) {}
  BigEndianI16& operator=(int16_t value) {
    set_value(value);
    return *this;
  }

  operator int16_t() const {
    return get_value();
  }
};

// The layout of the GestureEvents0 register
struct GestureEvents0Reg : ByteField {
  defineBit(single_tap, 0);
  defineBit(press_and_hold, 1);
  defineBit(swipe_x_negative, 2);
  defineBit(swipe_x_positive, 3);
  defineBit(swipe_y_positive, 4);
  defineBit(swipe_y_negative, 5);
};

struct GestureEvents1Reg : ByteField {
  defineBit(two_finger_tap, 0);
  defineBit(scroll, 1);
  defineBit(zoom, 2);
};

struct SystemInfo0Reg : ByteField {
  defineField(charging_mode, 0, 3);
  defineBit(ati_error, 3);
  defineBit(reati_occurred, 4);
  defineBit(alp_ati_error, 5);
  defineBit(alp_reati_occurred, 6);
  defineBit(show_reset, 7);
};

struct SystemInfo1Reg : ByteField {
  defineBit(tp_movement, 0);
  defineBit(palm_detect, 1);
  defineBit(too_many_fingers, 2);
  defineBit(rr_missed, 3);
  defineBit(snap_toggle,  4);
  defineBit(switch_state, 5);
};

struct Finger0 {
  BigEndianU16 relative_x;
  BigEndianU16 relative_y;
  BigEndianU16 absolute_x;
  BigEndianU16 absolute_y;
  BigEndianU16 touch_strength;
  uint8_t touch_size;
};

struct CommonFingerData {
  BigEndianU16 absolute_x;
  BigEndianU16 absolute_y;
  BigEndianU16 touch_strength;
  uint8_t touch_size;
};

struct AllFingerData {
  BigEndianI16 relative_x;
  BigEndianI16 relative_y;
  CommonFingerData finger[5];
};

struct SystemControl0Reg : ByteField {
  defineField(mode_select, 0, 3);
  defineBit(reseed, 3);
  defineBit(alp_reseed, 4);
  defineBit(auto_ati, 5);
  defineBit(ack_reset, 7);
};

struct SystemControl1Reg : ByteField {
  defineBit(suspend, 0);
  defineBit(reset, 1);
};

struct SystemConfig0Reg : ByteField {
  defineBit(sw_input, 0);
  defineBit(sw_input_select, 1);
  // 1 re-ati is enabled for alternate trackpad channels
  defineBit(reati, 2);
  // 1 re-ati is enabled for alternate LP channel
  defineBit(alp_reati, 3);
  defineBit(sw_input_event, 4);
  // 1 = watchdog timer is enabled
  defineBit(wdt, 5);
  // 1 = setup is complete, run auto start procedure
  defineBit(setup_complete, 6);
  // 1 = power save modes are controlled manually
  defineBit(manual_control, 7);
};

struct XYConfig0Reg : ByteField {
  // 1 = invert x values
  defineBit(flip_x, 0);
  // 1 = invert y values
  defineBit(flip_y, 1);
  // 1 = switch x axis with y axis
  defineBit(switch_xy_axis, 2);
  // 1 = enable rejection of large objects on the pad
  defineBit(palm_reject, 3);

  // Bits 4-7 are not specified in the datasheet
};

bool write(uint16_t regNo, uint8_t *buf, uint8_t len) {
  uint8_t addr[2] = {regNo >> 8, regNo & 0xff};
  uint8_t result;
  for (uint8_t i = 0; i < 4; ++i) {
    result = TWI_WritePacket(i2cAddress << 1, i2cTimeout, addr,
                                     sizeof(addr), buf, len);
    if (result == TWI_ERROR_NoError) {
      return true;
    }
    if (result == TWI_ERROR_SlaveNotReady) {
      _delay_ms(1);
      continue;
    }
    break;
  }
  xprintf("proxsense: set_register %d = %d failed: %s\n", regNo, buf[0],
          twi_err_str(result));
  return false;
}

bool read(uint16_t regNo, uint8_t *buf, uint8_t len) {
  uint8_t addr[2] = {regNo >> 8, regNo & 0xff};
  uint8_t result;

  for (uint8_t i = 0; i < 4; i++) {
    result = TWI_ReadPacket(i2cAddress << 1, i2cTimeout, addr, sizeof(addr),
                            buf, len);
    if (result == TWI_ERROR_NoError) {
      return true;
    }
    if (result == TWI_ERROR_SlaveNotReady) {
      _delay_ms(1);
      continue;
    }
    break;
  }
  xprintf("proxsense: device %d: read reg %d: %s %s\n", i2cAddress, regNo,
          result, twi_err_str(result));
  return false;
}

bool write(uint16_t regNo, uint16_t value) {
  uint8_t buf[2];
  buf[0] = value >> 8;
  buf[1] = value & 0xff;
  return write(regNo, buf, sizeof(buf));
}

bool write(uint16_t regNo, uint8_t value) {
  return write(regNo, &value, sizeof(value));
}

bool read(uint16_t regNo, uint16_t &value) {
  uint8_t buf[2];
  if (!read(regNo, buf, sizeof(buf))) {
    return false;
  }
  value = (uint16_t(buf[0]) << 8) | buf[1];
  return true;
}

bool read(uint16_t regNo, uint8_t &value) {
  return read(regNo, &value, sizeof(value));
}

template <class T>
bool read(uint16_t regNo, T* value) {
  return read(regNo, (uint8_t*)value, sizeof(T));
}

template <class T>
bool write(uint16_t regNo, const T* value) {
  return write(regNo, (uint8_t*)value, sizeof(T));
}

}

bool ProxSense::init() {
  pinMode(DRPin, PinDirectionInput);
  digitalWrite(DRPin, PinLevelLow);

  if (!write(SystemControl0, uint8_t(0x80))) {
    print("failed to ack reset\n");
    return false;
  }

  SystemConfig0Reg config;
  if (!read(SystemConfig0, &config)) {
    print("failed to read SystemConfig0\n");
    return false;
  }
  // Disable automatic tuning
  config.set_reati(false);
  config.set_alp_reati(false);
  if (!write(SystemConfig0, &config)) {
    print("failed to set SystemConfig0\n");
    return false;
  }

  if (!write(ReportRateMs, uint16_t(10))) {
    print("failed to set report rate\n");
    return false;
  }

  if (!write(ScrollInitialDistancePixels, uint16_t(2))) {
    print("failed to set scroll distance\n");
    return false;
  }
  if (!write(HoldTimeMs, uint16_t(100))) {
    print("failed to set HoldTimeMs\n");
    return false;
  }

  endCommunicationWindow();

  hadState_ = true;

  return true;
}

bool ProxSense::endCommunicationWindow() {
  return write(EndCommunicationWindow, uint8_t(0));
}

bool ProxSense::getData(struct TrackpadData *result) {
  memset(result, 0, sizeof(*result));
  if (!digitalRead(DRPin)) {
    hadState_ = false;
    return true;
  }

  bool success = false;

  // This is the sequence of registers starting at GestureEvents0
  // up through the end of the finger data we need here.  This
  // must match the register definition in the datasheet!
  struct DataPacket {
    GestureEvents0Reg gesture0;
    GestureEvents1Reg gesture1;
    SystemInfo0Reg info0;
    SystemInfo1Reg info1;
    uint8_t number_of_fingers;
    Finger0 finger0;
  };

  DataPacket data;

  if (!read(GestureEvents0, &data)) {
    xprintf("failed to read finger data\n");
    goto done;
  }

#if 1
  print("fingers=");
  pdec(data.number_of_fingers);
  print(" x= ");
  phex(data.finger0.relative_x);
  print(" y= ");
  phex(data.finger0.relative_y);
  print(" absx= ");
  phex(data.finger0.absolute_x);
  print(" absy= ");
  phex(data.finger0.absolute_y);
  print(" str= ");
  phex(data.finger0.touch_strength);
  print(" size= ");
  phex(data.finger0.touch_size);

  print(" event=");
  if (data.gesture0.single_tap()) {
    print(" SINGLE_TAP");
  }
  if (data.gesture0.press_and_hold()) {
    print(" PRESS_AND_HOLD");
  }
  if (data.gesture1.two_finger_tap()) {
    print(" TWO_FINGER_TAP");
  }
  if (data.gesture1.scroll()) {
    print(" SCROLL");
  }

  if (data.info0.show_reset()) {
    init();
    print(" SHOW_RESET");
  }
  if (data.info0.alp_reati_occurred()) {
    print(" ALP_REATI_OCCURRED");
  }
  if (data.info0.alp_ati_error()) {
    print(" ALP_ATI_ERROR");
  }
  if (data.info0.reati_occurred()) {
    print(" REATI_OCC");
  }
  if (data.info0.ati_error()) {
    print(" ATI_ERR");
  }
  if (data.info1.rr_missed()) {
    print(" RR_MISSED");
  }
  if (data.info1.too_many_fingers()) {
    print(" TOO_MANY_FINGERS");
  }
  if (data.info1.palm_detect()) {
    print(" PALM_DETECT");
  }
  if (data.info1.tp_movement()) {
    print(" TP_MOVEMENT");
  }

  print("\n");
#endif

#if 1
  if (data.gesture0.single_tap()) {
    result->buttons = 1;
    hadState_ = true;
  } else if (data.gesture1.two_finger_tap()) {
    result->buttons = 2;
  } else if (data.gesture1.scroll()) {
    result->buttons = 0;
    result->yWheel = data.finger0.relative_y;
    if (result->yWheel > mk_wheel_max_speed) {
      result->yWheel = mk_wheel_max_speed;
    } else if (result->yWheel < -int8_t(mk_wheel_max_speed)) {
      result->yWheel = -int8_t(mk_wheel_max_speed);
    }
    result->xWheel = data.finger0.relative_x;
    if (result->xWheel > mk_wheel_max_speed) {
      result->xWheel = mk_wheel_max_speed;
    } else if (result->xWheel < -int8_t(mk_wheel_max_speed)) {
      result->xWheel = -int8_t(mk_wheel_max_speed);
    }
  } else if (data.number_of_fingers == 1) {
    if (data.gesture0.press_and_hold()) {
      result->buttons = 1;
#if 0
      uint16_t hold;
      uint16_t tap;
      if (read(HoldTimeMs, hold) && read(TapTimeMs, tap)) {
        print("HoldTimeMs ");
        pdec(hold);
        print("TapTime ");
        pdec(tap);
        print("\n");
      }
#endif
    }
    result->xDelta = data.finger0.relative_x;
    result->yDelta = -data.finger0.relative_y;
  }
#endif

  success = true;
done:
  endCommunicationWindow();
  return success;
}

bool ProxSense::dataIsReady() {
  return digitalRead(DRPin) || hadState_;
}

static ProxSense trackpad;

bool trackpad_init() { return trackpad.init(); }

bool trackpad_get_data(struct TrackpadData *data) {
  if (!trackpad.dataIsReady()) {
    return false;
  }
  if (!trackpad.getData(data)) {
    print("Error reading trackpad data\n");
    return false;
  }
  return true;
}
#endif
