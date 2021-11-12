/*
 * MIT License
 *
 * Copyright (c) 2021 Dan Malec
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "picosystem.hpp"
#include "sound_data.hpp"

using namespace picosystem;

// Enum of sound fields to simplify calling sound functions
enum sound_field {
  attack = 0,
  decay = 1,
  sustain = 2,
  release = 3,
  bend = 4,
  bend_ms = 5,
  reverb = 6,
  noise = 7,
  distort = 8,

  frequency = 9,
  duration = 10,
  volume = 11
};

// The currently selected sound field input
uint8_t input_num = 0;

// Capture of starting values so they can be restored if needed
std::array<int32_t, 12> default_values;

// -------------------------------------------------------------------------------
// Event loop functions
// -------------------------------------------------------------------------------

void init() {
  // Save out the starting values as default values
  for (int i=0; i<12; i++) {
    default_values[i] = dials[i].value;
  }
}

void update(uint32_t tick) {
  if (pressed(button::B)) {
    voice_t my_voice = voice(
                          dials[attack].value, dials[decay].value,
                          dials[sustain].value, dials[release].value,
                          dials[bend].value, dials[bend_ms].value, dials[reverb].value,
                          dials[noise].value, dials[distort].value
                          );

    play(my_voice, dials[frequency].value, dials[duration].value, dials[volume].value);
  }

  if (pressed(button::UP) && input_num > 0) {
    input_num--;
  }
  if (pressed(button::DOWN) && input_num < 11) {
    input_num++;
  }

  uint8_t step_size = dials[input_num].step;

  if (button(button::Y)) {
    step_size = 1;
  } else if (button(button::A)) {
    step_size = step_size * 2;
  }

  if (pressed(button::LEFT)) {
    dials[input_num].value -= step_size;

    if (dials[input_num].value < dials[input_num].min) {
      dials[input_num].value = dials[input_num].min;
    }
  }

  if (pressed(button::RIGHT)) {
    dials[input_num].value += step_size;

    if (dials[input_num].value > dials[input_num].max) {
      dials[input_num].value = dials[input_num].max;
    }
  }

  if (button(button::X)) {
    for (int i=0; i<12; i++) {
      dials[i].value = default_values[i];
    }
  }
}

void draw(uint32_t tick) {
  pen(0, 0, 0);
  clear();

  for (int i=0; i<12; i++) {
    if (i==input_num) {
      pen(15, 15, 15);
      text(">", 0, 8 * i);
    } else {
      pen(10, 10, 10);
    }
    text(dials[i].name,         8, 8 * i);
    text(str(dials[i].value),  76, 8 * i);
    text(dials[i].unit,       104, 8 * i);
  }

  if (position() >= 0) {
    pen(0, 10, 0);
    text("Playing...", 0, 112);
  }
}
