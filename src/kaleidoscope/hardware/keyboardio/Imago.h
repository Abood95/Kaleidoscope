/* -*- mode: c++ -*-
 * Kaleidoscope-Hardware-Keyboardio-Imago -- Imago hardware support for Kaleidoscope
 * Copyright (C) 2018, 2019  Keyboard.io, Inc
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of version 3 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#ifdef ARDUINO_AVR_KEYBOARDIO_IMAGO

#include <Arduino.h>
#define HARDWARE_IMPLEMENTATION kaleidoscope::hardware::keyboardio::Imago

#include "kaleidoscope/driver/keyscanner/ATMega.h"
#include "kaleidoscope/driver/leddriver/IS31FL3741.h"
#include "kaleidoscope/driver/bootloader/avr/Caterina.h"
#include "kaleidoscope/hardware/avr/AVRDevice.h"

namespace kaleidoscope {
namespace hardware {
namespace keyboardio {

struct ImagoDeviceProps : kaleidoscope::hardware::avr::AVRDeviceProps {
  typedef struct ImagoKeyScannerProps : public kaleidoscope::driver::keyscanner::ATMegaProps {
    ATMEGA_KEYSCANNER_PROPS(
        ROW_PIN_LIST({ PIN_F6, PIN_F5, PIN_F4, PIN_F1, PIN_F0}),
        COL_PIN_LIST({ PIN_B2, PIN_B7, PIN_E2, PIN_C7, PIN_C6, PIN_B6, PIN_B5, PIN_B4, PIN_D7, PIN_D6,  PIN_D4, PIN_D5, PIN_D3, PIN_D2, PIN_E6, PIN_F7})
                            );
  } KeyScannerProps;
  typedef kaleidoscope::driver::keyscanner::ATMega<KeyScannerProps> KeyScanner;

  typedef struct ImagoLEDDriverProps: public kaleidoscope::driver::leddriver::IS31FL3741Props {
    static constexpr LEDCountType led_count = 78;
    //static constexpr uint8_t NOLED = 254;
    static constexpr uint8_t key_led_map[5][16] PROGMEM = {
      { 104,    0,     1,    2,     3,    4,    5,     6,    7,     8,    9,   10,   11,   115,   12,   116},
      {  91,   13, NOLED,   15,    16,   17,   18,    19,   20,    21,   22,   23,   24,   102,   15,   103},
      {  78,   26,    27,   28,    29,   30,   31, NOLED,   33,    34,   35,   36,   37,   89,    38, NOLED},
      {  65,   39,    40,   41,    42,   43,   44,    45,   46,    47,   48,   49,   50,   51, NOLED,    90},
      {  52,   66,    53,   54, NOLED,   56,   57,    71,   59, NOLED,   61,   62,   63,   64, NOLED,    77}
    };
  } LEDDriverProps;
  typedef kaleidoscope::driver::leddriver::IS31FL3741<ImagoLEDDriverProps> LEDDriver;

  typedef kaleidoscope::driver::bootloader::avr::Caterina BootLoader;
};

class Imago: public kaleidoscope::hardware::avr::AVRDevice<ImagoDeviceProps> {
 public:
  void setup();
};

#define PER_KEY_DATA(dflt,                                              \
         R0C0, R0C1, R0C2, R0C3, R0C4, R0C5, R0C6, R0C7, R0C8, R0C9, R0C10, R0C11, R0C12, R0C13, R0C14, R0C15, \
         R1C0, R1C1,       R1C3, R1C4, R1C5, R1C6, R1C7, R1C8, R1C9, R1C10, R1C11, R1C12, R1C13, R1C14, R1C15, \
         R2C0, R2C1, R2C2, R2C3, R2C4, R2C5, R2C6,       R2C8, R2C9, R2C10, R2C11, R2C12, R2C13, R2C14,        \
         R3C0, R3C1, R3C2, R3C3, R3C4, R3C5, R3C6, R3C7, R3C8, R3C9, R3C10, R3C11, R3C12, R3C13,        R3C15, \
         R4C0, R4C1, R4C2, R4C3,       R4C5, R4C6, R4C7, R4C8,       R4C10, R4C11, R4C12, R4C13,        R4C15  \
                     ,...  )                                              \
         R0C0, R0C1, R0C2, R0C3, R0C4, R0C5, R0C6, R0C7, R0C8, R0C9, R0C10, R0C11, R0C12, R0C13, R0C14, R0C15, \
         R1C0, R1C1, XXX,  R1C3, R1C4, R1C5, R1C6, R1C7, R1C8, R1C9, R1C10, R1C11, R1C12, R1C13, R1C14, R1C15, \
         R2C0, R2C1, R2C2, R2C3, R2C4, R2C5, R2C6, XXX,  R2C8, R2C9, R2C10, R2C11, R2C12, R2C13, R2C14, XXX  , \
         R3C0, R3C1, R3C2, R3C3, R3C4, R3C5, R3C6, R3C7, R3C8, R3C9, R3C10, R3C11, R3C12, R3C13, XXX,   R3C15, \
         R4C0, R4C1, R4C2, R4C3, XXX,  R4C5, R4C6, R4C7, R4C8, XXX,  R4C10, R4C11, R4C12, R4C13, XXX,   R4C15

}
}
}

#include "kaleidoscope/hardware/key_indexes.h"

#endif
