/**
 * MIT License
 *
 * Copyright (c) 2021 Pimoroni Ltd
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

// Taken from https://github.com/pimoroni/picosystem/blob/main/examples/audio/audio.cpp

#include "sound_data.hpp"

std::array<dial_t, 12> dials = {{
  {   "attack", "ms",    0, 1000, 100, 50},
  {    "decay", "ms",    0, 1000,  50, 50},
  {  "sustain",  "%",    0,  100,  80, 10},
  {  "release", "ms",    0, 1000, 250, 50},
  {     "bend", "hz", -100,  100,   0, 10},
  {  "bend ms", "ms",    0, 1000, 100, 50},
  {   "reverb", "ms",    0, 2000,   0, 50},
  {    "noise",  "%",    0,  100,   0, 10},
  {  "distort",  "%",    0,  100,   0, 10},

  {"frequency", "hz",    0, 8000, 440, 50},
  { "duration", "ms",    0, 1000, 500, 50},
  {   "volume",  "%",    0,  100, 100, 10}
}};
