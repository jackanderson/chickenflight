/*
 * This file is part of Cleanflight and Chickenflight.
 *
 * Cleanflight and Chickenflight are free software. You can redistribute
 * this software and/or modify this software under the terms of the
 * GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * Cleanflight and Chickenflight are distributed in the hope that they
 * will be useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software.
 *
 * If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "common/time.h"

void srxlCollectTelemetryNow(void);
void initSrxlTelemetry(void);
bool checkSrxlTelemetryState(void);
void handleSrxlTelemetry(timeUs_t currentTimeUs);

#define SPEKTRUM_SRXL_TEXTGEN_BUFFER_ROWS 9
#define SPEKTRUM_SRXL_TEXTGEN_BUFFER_COLS 12 // Airware 1.20
//#define SPEKTRUM_SRXL_TEXTGEN_BUFFER_COLS 13 // Airware 1.21
#define SPEKTRUM_SRXL_TEXTGEN_CLEAR_SCREEN 255

int spektrumTmTextGenPutChar(uint8_t col, uint8_t row, char c);
