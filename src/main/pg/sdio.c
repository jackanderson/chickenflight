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

#include "platform.h"

#if defined(USE_SDCARD_SDIO)

#include "drivers/io.h"
#include "drivers/sdio.h"
#include "pg/pg_ids.h"
#include "pg/sdio.h"

PG_REGISTER_WITH_RESET_TEMPLATE(sdioConfig_t, sdioConfig, PG_SDIO_CONFIG, 0);

PG_RESET_TEMPLATE(sdioConfig_t, sdioConfig,
    .clockBypass = 0,
    .useCache = 0,
    .use4BitWidth = SDIO_USE_4BIT,
    .dmaopt = SDCARD_SDIO_DMA_OPT,
    .device = SDIO_DEV_TO_CFG(SDIO_DEVICE),
);

#ifdef STM32H7
PG_REGISTER_WITH_RESET_TEMPLATE(sdioPinConfig_t, sdioPinConfig, PG_SDIO_PIN_CONFIG, 0);

PG_RESET_TEMPLATE(sdioPinConfig_t, sdioPinConfig,
    .CKPin = IO_TAG(SDIO_CK_PIN),
    .CMDPin = IO_TAG(SDIO_CMD_PIN),
    .D0Pin = IO_TAG(SDIO_D0_PIN),
    .D1Pin = IO_TAG(SDIO_D1_PIN),
    .D2Pin = IO_TAG(SDIO_D2_PIN),
    .D3Pin = IO_TAG(SDIO_D3_PIN),
);
#endif

#endif
