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

#if defined(PLUMF4)
#define TARGET_BOARD_IDENTIFIER "PLUM"
#define USBD_PRODUCT_STRING     "PLUMF4"

#elif defined(KIWIF4V2)
#define TARGET_BOARD_IDENTIFIER "KIW2"
#define USBD_PRODUCT_STRING     "KIWIF4V2"

#else
#define TARGET_BOARD_IDENTIFIER "KIWI"
#define USBD_PRODUCT_STRING     "KIWIF4"

#endif

#if defined(PLUMF4) || defined(KIWIF4V2)
#define LED0_PIN                PB4

#else
#define LED0_PIN                PB5
#define LED1_PIN                PB4
#endif

#define USE_BEEPER
#define BEEPER_PIN              PA8

#define INVERTER_PIN_UART1      PC0 // PC0 used as inverter select GPIO

// MPU6000 interrupts
#define USE_EXTI
#define USE_GYRO_EXTI
#define GYRO_1_EXTI_PIN         PC4
#define USE_MPU_DATA_READY_SIGNAL

#define GYRO_1_CS_PIN           PA4
#define GYRO_1_SPI_INSTANCE     SPI1

#define USE_GYRO
#define USE_ACC

#define USE_GYRO_SPI_MPU6000
#define GYRO_1_ALIGN            CW180_DEG
#define USE_ACC_SPI_MPU6000

#if defined(KIWIF4) || defined(KIWIF4V2)
#define USE_MAX7456
#endif

#if defined(KIWIF4V2)
#define MAX7456_SPI_INSTANCE                SPI3
#define MAX7456_SPI_CS_PIN                  PA15

#else
#define MAX7456_SPI_INSTANCE                SPI2
#define MAX7456_SPI_CS_PIN                  PB12
//#define MAX7456_DMA_CHANNEL_TX              DMA1_Stream5 // Can't convert to dmaopt
//#define MAX7456_DMA_CHANNEL_RX              DMA1_Stream0 // Can't convert to dmaopt
#endif

#if defined(KIWIF4V2)
#define USE_SDCARD
#define USE_SDCARD_SPI
//#define SDCARD_DETECT_PIN                   PB9
#define SDCARD_SPI_INSTANCE                 SPI2
#define SDCARD_SPI_CS_PIN                   PB12
#define SPI2_TX_DMA_OPT                     0     // DMA 1 Stream 4 Channel 0
#define SPI2_TX_DMA_OPT                     0     // DMA 1 Stream 4 Channel 0

#else
#define USE_FLASHFS
#define USE_FLASH_M25P16
#define FLASH_CS_PIN            SPI3_NSS_PIN
#define FLASH_SPI_INSTANCE      SPI3
#endif

#define USE_VCP
#define USB_DETECT_PIN          PC5
#define USE_USB_DETECT

#define USE_UART1
#define UART1_RX_PIN            PA10
#define UART1_TX_PIN            PA9

#define USE_UART3
#define UART3_RX_PIN            PB11
#define UART3_TX_PIN            PB10

#define USE_UART6
#define UART6_RX_PIN            PC7
#define UART6_TX_PIN            PC6

#define USE_SOFTSERIAL1
#define USE_SOFTSERIAL2

#define SERIAL_PORT_COUNT       6 //VCP, USART1, USART3, USART6, SOFTSERIAL x 2

#define USE_ESCSERIAL
#define ESCSERIAL_TIMER_TX_PIN  PA3  // (HARDARE=0)

#define USE_SPI

#define USE_SPI_DEVICE_1

#ifdef KIWIF4
#define USE_SPI_DEVICE_2
#define SPI2_NSS_PIN            PB12
#define SPI2_SCK_PIN            PB13
#define SPI2_MISO_PIN           PB14
#define SPI2_MOSI_PIN           PB15
#endif

#define USE_SPI_DEVICE_3
#define SPI3_NSS_PIN            PA15
#define SPI3_SCK_PIN            PC10
#define SPI3_MISO_PIN           PC11
#define SPI3_MOSI_PIN           PC12

/*
#define USE_I2C
#define USE_I2C_DEVICE_1
#define I2C_DEVICE              (I2CDEV_1)
#define USE_I2C_PULLUP
#define I2C1_SCL                PB6
#define I2C1_SDA                PB7
*/

#define USE_ADC
#define DEFAULT_VOLTAGE_METER_SOURCE VOLTAGE_METER_ADC
#define VBAT_ADC_PIN            PC1
#define RSSI_ADC_PIN            PC2
#define CURRENT_METER_ADC_PIN   PC3

#define CURRENT_METER_SCALE_DEFAULT 444
#define VBAT_SCALE_DEFAULT          57

#define DEFAULT_FEATURES        (FEATURE_OSD)

#define DEFAULT_RX_FEATURE      FEATURE_RX_SERIAL
#define SERIALRX_PROVIDER       SERIALRX_SBUS
#define SERIALRX_UART           SERIAL_PORT_USART1

#define TARGET_IO_PORTA         0xffff
#define TARGET_IO_PORTB         0xffff
#define TARGET_IO_PORTC         0xffff
#define TARGET_IO_PORTD         (BIT(2))

#define USABLE_TIMER_CHANNEL_COUNT 5

#define USED_TIMERS             ( TIM_N(2) | TIM_N(3) | TIM_N(4) )
