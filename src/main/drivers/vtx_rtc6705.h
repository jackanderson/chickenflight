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

/*
 * Author: Giles Burgess (giles@multiflite.co.uk)
 *
 * This source code is provided as is and can be used/modified so long
 * as this header is maintained with the file at all times.
 */

#pragma once

#include <stdint.h>

#include "pg/vtx_io.h"

#define VTX_RTC6705_POWER_COUNT           3
#define VTX_RTC6705_DEFAULT_POWER_INDEX   2

#if defined(RTC6705_POWER_PIN)
#define VTX_RTC6705_MIN_POWER_VALUE   0
#else
#define VTX_RTC6705_MIN_POWER_VALUE   1
#endif

#define VTX_RTC6705_FREQ_MIN    5600
#define VTX_RTC6705_FREQ_MAX    5950

#define VTX_RTC6705_BOOT_DELAY  350 // milliseconds

bool rtc6705IOInit(const vtxIOConfig_t *vtxIOConfig);
void rtc6705SetFrequency(uint16_t freq);
void rtc6705SetRFPower(uint8_t rf_power);
void rtc6705Disable(void);
void rtc6705Enable(void);


