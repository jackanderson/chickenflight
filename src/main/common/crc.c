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

#include <stdint.h>

#include "platform.h"

#include "streambuf.h"


uint16_t crc16_ccitt(uint16_t crc, unsigned char a)
{
    crc ^= (uint16_t)a << 8;
    for (int ii = 0; ii < 8; ++ii) {
        if (crc & 0x8000) {
            crc = (crc << 1) ^ 0x1021;
        } else {
            crc = crc << 1;
        }
    }
    return crc;
}

uint16_t crc16_ccitt_update(uint16_t crc, const void *data, uint32_t length)
{
    const uint8_t *p = (const uint8_t *)data;
    const uint8_t *pend = p + length;

    for (; p != pend; p++) {
        crc = crc16_ccitt(crc, *p);
    }
    return crc;
}

void crc16_ccitt_sbuf_append(sbuf_t *dst, uint8_t *start)
{
    uint16_t crc = 0;
    const uint8_t * const end = sbufPtr(dst);
    for (const uint8_t *ptr = start; ptr < end; ++ptr) {
        crc = crc16_ccitt(crc, *ptr);
    }
    sbufWriteU16(dst, crc);
}

uint8_t crc8_dvb_s2(uint8_t crc, unsigned char a)
{
    crc ^= a;
    for (int ii = 0; ii < 8; ++ii) {
        if (crc & 0x80) {
            crc = (crc << 1) ^ 0xD5;
        } else {
            crc = crc << 1;
        }
    }
    return crc;
}

uint8_t crc8_dvb_s2_update(uint8_t crc, const void *data, uint32_t length)
{
    const uint8_t *p = (const uint8_t *)data;
    const uint8_t *pend = p + length;

    for (; p != pend; p++) {
        crc = crc8_dvb_s2(crc, *p);
    }
    return crc;
}

void crc8_dvb_s2_sbuf_append(sbuf_t *dst, uint8_t *start)
{
    uint8_t crc = 0;
    const uint8_t * const end = dst->ptr;
    for (const uint8_t *ptr = start; ptr < end; ++ptr) {
        crc = crc8_dvb_s2(crc, *ptr);
    }
    sbufWriteU8(dst, crc);
}

uint8_t crc8_xor_update(uint8_t crc, const void *data, uint32_t length)
{
    const uint8_t *p = (const uint8_t *)data;
    const uint8_t *pend = p + length;

    for (; p != pend; p++) {
        crc ^= *p;
    }
    return crc;
}

void crc8_xor_sbuf_append(sbuf_t *dst, uint8_t *start)
{
    uint8_t crc = 0;
    const uint8_t *end = dst->ptr;
    for (uint8_t *ptr = start; ptr < end; ++ptr) {
        crc ^= *ptr;
    }
    sbufWriteU8(dst, crc);
}

