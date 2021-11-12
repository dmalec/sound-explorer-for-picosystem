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
uint8_t input_num;

// The current increment/decrement step size
uint8_t step_size;

// Capture of starting values so they can be restored if needed
std::array<int32_t, 12> default_values;

// The delays for repeat events when a directional button is held down
#define INITIAL_REPEAT_DELAY 50
#define REPEAT_DELAY 10

// State of buttons
struct button_state_t {
  uint8_t button_id;
  bool pressed;
  uint32_t next_event_tick;
};

button_state_t button_states[8] = {
  { button::UP,    false, 0 },
  { button::DOWN,  false, 0 },
  { button::LEFT,  false, 0 },
  { button::RIGHT, false, 0 },
};

// -------------------------------------------------------------------------------
// Event loop functions
// -------------------------------------------------------------------------------

void init() {
  // Save out the starting values as default values
  for (int i=0; i<12; i++) {
    default_values[i] = dials[i].value;
  }

  // Init the global state
  input_num = 0;
  step_size = dials[input_num].step;
}

void fire_event(uint8_t button) {
  switch (button) {

  case button::UP:
    if (input_num > 0) {
      input_num--;
    }
    break;

  case button::DOWN:
    if (input_num < 11) {
      input_num++;
    }
    break;

  case button::LEFT:
    dials[input_num].value -= step_size;

    if (dials[input_num].value < dials[input_num].min) {
      dials[input_num].value = dials[input_num].min;
    }
    break;

  case button::RIGHT:
    dials[input_num].value += step_size;

    if (dials[input_num].value > dials[input_num].max) {
      dials[input_num].value = dials[input_num].max;
    }
    break;
  }
}

void update(uint32_t tick) {
  // Handle simple button commands
  if (pressed(button::B)) {
    voice_t my_voice = voice(
                             dials[attack].value, dials[decay].value,
                             dials[sustain].value, dials[release].value,
                             dials[bend].value, dials[bend_ms].value, dials[reverb].value,
                             dials[noise].value, dials[distort].value
                             );

    play(my_voice, dials[frequency].value, dials[duration].value, dials[volume].value);
  }

  step_size = dials[input_num].step;
  if (button(button::Y)) {
    step_size = 1;
  } else if (button(button::A)) {
    step_size = step_size * 2;
  }

  if (button(button::X)) {
    for (int i=0; i<12; i++) {
      dials[i].value = default_values[i];
    }
  }

  // Handle button commands with auto repeat
  for (int i=0; i<4; i++) {
    if (button(button_states[i].button_id)) {
      if (!button_states[i].pressed) {
        button_states[i].pressed = true;
        button_states[i].next_event_tick = tick + INITIAL_REPEAT_DELAY;
        fire_event(button_states[i].button_id);
      } else if (tick >= button_states[i].next_event_tick) {
        button_states[i].next_event_tick = tick + REPEAT_DELAY;
        fire_event(button_states[i].button_id);
      }
    } else {
      button_states[i].pressed = false;
      button_states[i].next_event_tick = 0;
    }
  }
}

void center_align_text(uint32_t x, uint32_t y, const std::string &str_value) {
  int32_t width, height;

  measure(str_value, width, height);

  text(str_value, x - (width / 2), y);
}

void right_align_number(uint32_t x, uint32_t y, int32_t value) {
  std::string str_value = str(value);
  int32_t width, height;

  measure(str_value, width, height);

  text(str_value, x - width, y);
}

void draw(uint32_t tick) {
  pen(0, 0, 0);
  clear();

  pen(5, 5, 5);
  center_align_text(60, 0, "sound explorer");
  hline(0,  10, 120);
  hline(0, 110, 120);

  for (int i=0; i<12; i++) {
    if (i==input_num) {
      pen(15, 15, 15);
      text(">", 0, 12 + 8 * i);
    } else {
      pen(10, 10, 10);
    }
    text(dials[i].name,         8, 12 + 8 * i);
    right_align_number(       100, 12 + 8 * i, dials[i].value);
    text(dials[i].unit,       104, 12 + 8 * i);
  }

  if (position() >= 0) {
    pen(0, 10, 0);
    center_align_text(60, 112, ". . . playing . . .");
  }
}
