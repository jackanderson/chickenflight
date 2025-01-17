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

#include <stdbool.h>

#include "drivers/io_types.h"
#include "drivers/time.h"

#ifndef ADC_INSTANCE
#define ADC_INSTANCE                ADC1
#endif

#if defined(STM32F4) || defined(STM32F7)
#ifndef ADC1_DMA_STREAM
#define ADC1_DMA_STREAM DMA2_Stream4 // ST0 or ST4
#endif

#ifndef ADC2_DMA_STREAM
#define ADC2_DMA_STREAM DMA2_Stream3 // ST2 or ST3
#endif

#ifndef ADC3_DMA_STREAM
#define ADC3_DMA_STREAM DMA2_Stream0 // ST0 or ST1
#endif
#endif

typedef enum ADCDevice {
    ADCINVALID = -1,
    ADCDEV_1   = 0,
#if defined(STM32F3) || defined(STM32F4) || defined(STM32F7) || defined(STM32H7)
    ADCDEV_2,
    ADCDEV_3,
#endif
#if defined(STM32F3)
    ADCDEV_4,
#endif
    ADCDEV_COUNT
} ADCDevice;

#define ADC_CFG_TO_DEV(x) ((x) - 1)
#define ADC_DEV_TO_CFG(x) ((x) + 1)

typedef enum {
    ADC_BATTERY = 0,
    ADC_CURRENT = 1,
    ADC_EXTERNAL1 = 2,
    ADC_RSSI = 3,
#ifdef STM32H7
    // On STM32H7, internal sensors are treated in the similar fashion as regular ADC inputs
    ADC_CHANNEL_INTERNAL = 4,
    ADC_TEMPSENSOR = 4,
    ADC_VREFINT = 5,
#endif
    ADC_CHANNEL_COUNT
} AdcChannel;

typedef struct adcOperatingConfig_s {
    ioTag_t tag;
#ifdef STM32H7
    ADCDevice adcDevice;        // ADCDEV_x for this input
    uint32_t adcChannel;        // ADCy_INxx channel ID for this input
#else
    uint8_t adcChannel;         // ADCy_INxx channel number for this input
#endif
    uint8_t dmaIndex;           // index into DMA buffer in case of sparse channels
    bool enabled;
    uint8_t sampleTime;
} adcOperatingConfig_t;

struct adcConfig_s;
void adcInit(const struct adcConfig_s *config);
uint16_t adcGetChannel(uint8_t channel);

#ifdef USE_ADC_INTERNAL
bool adcInternalIsBusy(void);
void adcInternalStartConversion(void);
uint16_t adcInternalReadVrefint(void);
uint16_t adcInternalReadTempsensor(void);
uint16_t adcInternalCompensateVref(uint16_t vrefAdcValue);
int16_t adcInternalComputeTemperature(uint16_t tempAdcValue, uint16_t vrefValue);
#endif

#if !defined(SIMULATOR_BUILD)
ADCDevice adcDeviceByInstance(ADC_TypeDef *instance);
#endif
