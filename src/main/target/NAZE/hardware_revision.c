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

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "platform.h"

#include "build/build_config.h"

#include "drivers/accgyro/accgyro.h"
#include "drivers/accgyro/accgyro_mpu.h"
#include "drivers/accgyro/accgyro_mpu6500.h"
#include "drivers/bus_spi.h"
#include "drivers/io.h"
#include "drivers/time.h"
#include "drivers/system.h"

#include "hardware_revision.h"

uint8_t hardwareRevision = UNKNOWN;

void detectHardwareRevision(void)
{
    if (hse_value == 8000000)
        hardwareRevision = NAZE32;
    else if (hse_value == 12000000)
        hardwareRevision = NAZE32_REV5;
}

#ifdef USE_SPI

#define DISABLE_SPI_CS       IOHi(nazeSpiCsPin)
#define ENABLE_SPI_CS        IOLo(nazeSpiCsPin)

#define SPI_DEVICE_NONE (0)
#define SPI_DEVICE_FLASH (1)
#define SPI_DEVICE_MPU (2)

#define M25P16_INSTRUCTION_RDID 0x9F
#define FLASH_M25P16_ID (0x202015)

static IO_t nazeSpiCsPin = IO_NONE;

uint8_t detectSpiDevice(void)
{
#ifdef NAZE_SPI_CS_PIN
    nazeSpiCsPin = IOGetByTag(IO_TAG(NAZE_SPI_CS_PIN));
#endif

    const uint8_t out[] = { M25P16_INSTRUCTION_RDID, 0, 0, 0 };
    uint8_t in[4];
    uint32_t flash_id;

    // try autodetect flash chip
    delay(50); // short delay required after initialisation of SPI device instance.
    ENABLE_SPI_CS;
    spiTransfer(NAZE_SPI_INSTANCE, out, in, sizeof(out));
    DISABLE_SPI_CS;

    flash_id = in[1] << 16 | in[2] << 8 | in[3];
    if (flash_id == FLASH_M25P16_ID)
        return SPI_DEVICE_FLASH;


    // try autodetect MPU
    delay(50);
    ENABLE_SPI_CS;
    spiTransferByte(NAZE_SPI_INSTANCE, MPU_RA_WHO_AM_I | MPU6500_BIT_RESET);
    in[0] = spiTransferByte(NAZE_SPI_INSTANCE, 0xff);
    DISABLE_SPI_CS;

    if (in[0] == MPU6500_WHO_AM_I_CONST)
        return SPI_DEVICE_MPU;

    return SPI_DEVICE_NONE;
}

#endif

void updateHardwareRevision(void)
{
#ifdef USE_SPI
    uint8_t detectedSpiDevice = detectSpiDevice();

    if (detectedSpiDevice == SPI_DEVICE_MPU && hardwareRevision == NAZE32_REV5)
        hardwareRevision = NAZE32_SP;
#endif
}

ioTag_t selectMPUIntExtiConfigByHardwareRevision(void)
{

#ifdef AFROMINI
    return IO_TAG(PC13);
#else
    if (hardwareRevision < NAZE32_REV5) {
        // MPU_INT output on rev4 PB13
        return IO_TAG(PB13);
    } else {
        // MPU_INT output on rev5 PC13
        return IO_TAG(PC13);
    }
#endif
}
