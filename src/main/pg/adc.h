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

#include <stdint.h>
#include <stdbool.h>

#include "pg/pg.h"
#include "drivers/io_types.h"

typedef struct adcChannelConfig_t {
    bool enabled;
    ioTag_t ioTag;
} adcChannelConfig_t;

typedef struct adcConfig_s {
    adcChannelConfig_t vbat;
    adcChannelConfig_t rssi;
    adcChannelConfig_t current;
    adcChannelConfig_t external1;
    int8_t device; // ADCDevice

    uint16_t vrefIntCalibration;
    uint16_t tempSensorCalibration1;
    uint16_t tempSensorCalibration2;

    uint8_t dmaopt[3]; // One per ADCDEV_x
} adcConfig_t;

PG_DECLARE(adcConfig_t, adcConfig);
