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

typedef enum nazeHardwareRevision_t {
    UNKNOWN = 0,
    NAZE32, // Naze32 and compatible with 8MHz HSE
    NAZE32_REV5, // Naze32 and compatible with 12MHz HSE
    NAZE32_SP // Naze32 w/Sensor Platforms
} nazeHardwareRevision_e;

extern uint8_t hardwareRevision;

void updateHardwareRevision(void);
void detectHardwareRevision(void);

void spiBusInit(void);

ioTag_t selectMPUIntExtiConfigByHardwareRevision(void);
