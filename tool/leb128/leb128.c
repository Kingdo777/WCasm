//
// Created by kingdo on 2020/11/20.
//

#include <stdbool.h>
#include <include/tool/type.h>
#include <include/tool/leb128/leb128.h>

/**
 * result = 0;
 * shift = 0;
 * while (true) {
 *   byte = next byte in input;
 *   result |= (low order 7 bits of byte) << shift;
 *   if (high order bit of byte == 0)
 *     break;
 *   shift += 7;
 * }
 *
 * */

leb128_uint64_t leb128_to_uint64(byte leb[]) {
    uint64 result = 0;
    int shift = 0;
    int len = 0;
    while (true) {
        result |= (((uint64) *leb) & 0x7f) << shift;
        len++;
        if ((*(leb++) & 0x80) == 0)
            break;
        shift += 7;
    }
    leb128_uint64_t r = {
            .len=len,
            .value=result
    };
    return r;

}

leb128_uint32_t leb128_to_uint32(byte leb[]) {
    uint32 result = 0;
    int shift = 0;
    int len = 0;
    while (true) {
        result |= (((uint32) *leb) & 0x7f) << shift;
        len++;
        if ((*(leb++) & 0x80) == 0)
            break;
        shift += 7;
    }
    leb128_uint32_t r = {
            .len=len,
            .value=result
    };
    return r;
}

/**
 *
 * Decode signed integer (https://en.wikipedia.org/wiki/LEB128)
 *
 * result = 0;
 * shift = 0;
 * size = number of bits in signed integer;
 * do {
 *    byte = next byte in input;
 *    result |= (low order 7 bits of byte << shift);
 *    shift += 7;
 * } while (high order bit of byte != 0);
 * if ((shift <size) && (sign bit of byte is set))
 * result |= (~0 << shift);
 *
 * */

leb128_int64_t leb128_to_int64(byte leb[]) {
    int64 result = 0;
    int shift = 0;
    int len = 0;
    do {
        result |= ((int64) (*leb) & 0x7f) << shift;
        shift += 7;
        len++;
    } while ((*(leb++) & 0x80) != 0);
    leb--;
    if ((shift < 64) && (*(leb) & 0x40) != 0)
        result |= ((int64) -1 << shift);
    leb128_int64_t r = {
            .len=len,
            .value=result
    };
    return r;
}

leb128_int32_t leb128_to_int32(byte leb[]) {
    int32 result = 0;
    int len = 0;
    int shift = 0;
    do {
        result |= ((int32) (*leb) & 0x7f) << shift;
        shift += 7;
        len++;
    } while ((*(leb++) & 0x80) != 0);
    leb--;
    if ((shift < 64) && (*(leb) & 0x40) != 0)
        result |= ((int32) -1 << shift);
    leb128_int32_t r = {
            .len=len,
            .value=result
    };
    return r;
}