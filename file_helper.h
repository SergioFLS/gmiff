#ifndef FILE_HELPER_H
#define FILE_HELPER_H

#include <stdint.h>
#include <stdbool.h>

uint32_t reverseBytes32(uint32_t value);
inline uint16_t reverseBytes16(uint16_t value);
uint32_t ereadUint32(FILE *f, bool be);
uint16_t ereadUint16(FILE *f, bool be);

#endif
