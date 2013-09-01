

/**
 * Calculate 2-logarithm.
 * 
 * Function is usable to map a 16-bit linear value to 16-bit logarithmic
 * with maximum use of available range.
 *
 * Input x = 0 is illegal, will return 0.
 *
 * @param x Integer input argument, must be >0.
 * @return log2 of x in Q12 format (4 integer bits, 12 fractional bits)
 */
uint16_t log2(uint16_t x)
{
  static const int Q = 12;
  uint16_t y;
  uint32_t xp;

  /// Determine integer part by locating highest set bit in x.
  y = 0;
  if (x & 0xFF00)        y = 8;
  if ((x >> y) & 0x00F0) y += 4;
  if ((x >> y) & 0x000C) y += 2;
  if ((x >> y) & 0x0002) y += 1;

  /// Representation of x is now Q15 (1 integer bits, 15 fractional bits).
  /// The bit shift asserts that 1.0 <= x < 2.0
  x = x << (15 - y);

  /// Determine fractional part one bit at a time.  
  for(int i = 0; i < Q; i++) {
    y <<= 1;
    if ((int32_t)(xp = (uint32_t)(x) * (uint32_t)(x) + 0x4000) < 0) {
      y++;
      x = xp >> 16;
    } else {
      x = xp >> 15;
    }
  }
  return y;
}

/**
 * Calculate 2-logarithm.
 * 
 * Function is usable to map a 32-bit linear value to 32-bit logarithmic
 * with maximum use of available range.
 *
 * Input x = 0 is illegal, will return 0.
 *
 * @param x Integer input argument, must be >0.
 * @return log2 of x in Q27 format (5 integer bits, 27 fractional bits)
 */
uint32_t log2(uint32_t x)
{
  static const int Q = 27;
  uint32_t y;
  uint64_t xp;

  /// Determine integer part by locating highest set bit in x.
  y = 0;
  if (x & 0xFFFF0000UL)        y = 16;
  if ((x >> y) & 0x0000FF00UL) y += 8;
  if ((x >> y) & 0x000000F0UL) y += 4;
  if ((x >> y) & 0x0000000CUL) y += 2;
  if ((x >> y) & 0x00000002UL) y += 1;

  /// Representation of x is now Q31 (1 integer bits, 31 fractional bits).
  /// The bit shift asserts that 1.0 <= x < 2.0
  x = x << (31 - y);

  /// Determine fractional part one bit at a time.  
  for(int i = 0; i < Q; i++) {
    y <<= 1;
    if ((int64_t)(xp = (uint64_t)(x) * (uint64_t)(x) + 0x40000000UL) < 0) {
      y++;
      x = xp >> 32;
    } else {
      x = xp >> 31;
    }
  }
  return y;
}

/**
 * Calculate 'signed' 2-logarithm.
 * 
 * Function is usable to map a 32-bit signed linear value to 16-bit
 * signed logarithmic with maximum use of available range.
 *
 * @param x Integer input argument.
 * @return log2 of x in Q10 format (1 sign bit, 5 integer bits, 10 fractional bits)
 */
int16_t log2(int32_t x)
{
  static const int Q = 10;
  uint32_t y = 0;
  uint32_t xu = (x < 0 ? -x : x);
  

  /// Determine integer part by locating highest set bit in x.
  if (xu & 0xFFFF0000UL)        y = 16;
  if ((xu >> y) & 0x0000FF00UL) y += 8;
  if ((xu >> y) & 0x000000F0UL) y += 4;
  if ((xu >> y) & 0x0000000CUL) y += 2;
  if ((xu >> y) & 0x00000002UL) y += 1;

  /// Representation of x is now Q31 (1 integer bits, 31 fractional bits).
  /// The bit shift asserts that 1.0 <= x < 2.0
  xu = xu << (31 - y);

  /// Determine fractional part one bit at a time.  
  for(int i = 0; i < Q; i++) {
    y <<= 1;
    if ((int64_t)(uint64_t xp = (uint64_t)(xu) * (uint64_t)(xu) + 0x40000000UL) < 0) {
      y++;
      xu = xp >> 32;
    } else {
      xu = xp >> 31;
    }
  }
  return (x < 0 ? -y : y);
}
