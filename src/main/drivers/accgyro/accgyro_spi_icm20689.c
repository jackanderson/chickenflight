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

#include "common/axis.h"
#include "common/maths.h"

#include "drivers/accgyro/accgyro.h"
#include "drivers/accgyro/accgyro_mpu.h"
#include "drivers/accgyro/accgyro_spi_icm20689.h"
#include "drivers/bus_spi.h"
#include "drivers/exti.h"
#include "drivers/io.h"
#include "drivers/sensor.h"
#include "drivers/time.h"


static void icm20689SpiInit(const busDevice_t *bus)
{
    static bool hardwareInitialised = false;

    if (hardwareInitialised) {
        return;
    }


    spiSetDivisor(bus->busdev_u.spi.instance, SPI_CLOCK_STANDARD);

    hardwareInitialised = true;
}

uint8_t icm20689SpiDetect(const busDevice_t *bus)
{
    icm20689SpiInit(bus);

    spiSetDivisor(bus->busdev_u.spi.instance, SPI_CLOCK_INITIALIZATION); //low speed

    spiBusWriteRegister(bus, MPU_RA_PWR_MGMT_1, ICM20689_BIT_RESET);

    uint8_t icmDetected = MPU_NONE;
    uint8_t attemptsRemaining = 20;
    do {
        delay(150);
        const uint8_t whoAmI = spiBusReadRegister(bus, MPU_RA_WHO_AM_I);
        switch (whoAmI) {
        case ICM20601_WHO_AM_I_CONST:
            icmDetected = ICM_20601_SPI;
            break;
        case ICM20602_WHO_AM_I_CONST:
            icmDetected = ICM_20602_SPI;
            break;
        case ICM20608G_WHO_AM_I_CONST:
            icmDetected = ICM_20608_SPI;
            break;
        case ICM20689_WHO_AM_I_CONST:
            icmDetected = ICM_20689_SPI;
            break;
        default:
            icmDetected = MPU_NONE;
            break;
        }
        if (icmDetected != MPU_NONE) {
            break;
        }
        if (!attemptsRemaining) {
            return MPU_NONE;
        }
    } while (attemptsRemaining--);

    spiSetDivisor(bus->busdev_u.spi.instance, SPI_CLOCK_STANDARD);

    return icmDetected;
}

void icm20689AccInit(accDev_t *acc)
{
    acc->acc_1G = 512 * 4;
}

bool icm20689SpiAccDetect(accDev_t *acc)
{
    switch (acc->mpuDetectionResult.sensor) {
    case ICM_20602_SPI:
    case ICM_20689_SPI:
        break;
    default:
        return false;
    }

    acc->initFn = icm20689AccInit;
    acc->readFn = mpuAccRead;

    return true;
}

void icm20689GyroInit(gyroDev_t *gyro)
{
    mpuGyroInit(gyro);

    spiSetDivisor(gyro->bus.busdev_u.spi.instance, SPI_CLOCK_INITIALIZATION);

    spiBusWriteRegister(&gyro->bus, MPU_RA_PWR_MGMT_1, ICM20689_BIT_RESET);
    delay(100);
    spiBusWriteRegister(&gyro->bus, MPU_RA_SIGNAL_PATH_RESET, 0x03);
    delay(100);
//    spiBusWriteRegister(&gyro->bus, MPU_RA_PWR_MGMT_1, 0);
//    delay(100);
    spiBusWriteRegister(&gyro->bus, MPU_RA_PWR_MGMT_1, INV_CLK_PLL);
    delay(15);
    spiBusWriteRegister(&gyro->bus, MPU_RA_GYRO_CONFIG, INV_FSR_2000DPS << 3);
    delay(15);
    spiBusWriteRegister(&gyro->bus, MPU_RA_ACCEL_CONFIG, INV_FSR_16G << 3);
    delay(15);
    spiBusWriteRegister(&gyro->bus, MPU_RA_CONFIG, mpuGyroDLPF(gyro));
    delay(15);
    spiBusWriteRegister(&gyro->bus, MPU_RA_SMPLRT_DIV, gyro->mpuDividerDrops); // Get Divider Drops
    delay(100);

    // Data ready interrupt configuration
//    spiBusWriteRegister(&gyro->bus, MPU_RA_INT_PIN_CFG, 0 << 7 | 0 << 6 | 0 << 5 | 1 << 4 | 0 << 3 | 0 << 2 | 0 << 1 | 0 << 0);  // INT_ANYRD_2CLEAR, BYPASS_EN
    spiBusWriteRegister(&gyro->bus, MPU_RA_INT_PIN_CFG, 0x10);  // INT_ANYRD_2CLEAR, BYPASS_EN

    delay(15);

#ifdef USE_MPU_DATA_READY_SIGNAL
    spiBusWriteRegister(&gyro->bus, MPU_RA_INT_ENABLE, 0x01); // RAW_RDY_EN interrupt enable
#endif

    spiSetDivisor(gyro->bus.busdev_u.spi.instance, SPI_CLOCK_STANDARD);
}

bool icm20689SpiGyroDetect(gyroDev_t *gyro)
{
    switch (gyro->mpuDetectionResult.sensor) {
    case ICM_20601_SPI:
    case ICM_20602_SPI:
    case ICM_20608_SPI:
    case ICM_20689_SPI:
        break;
    default:
        return false;
    }

    gyro->initFn = icm20689GyroInit;
    gyro->readFn = mpuGyroReadSPI;

    // 16.4 dps/lsb scalefactor
    gyro->scale = 1.0f / 16.4f;

    return true;
}
