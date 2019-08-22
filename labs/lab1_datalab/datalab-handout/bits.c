/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
//1
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  /* return the result of x^y */
  int result = ~(~(x & ~y) & (~(~x & y)));
  return result;
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  /* return minimum two's complement integer */
  int result = 0x01 << 31;
  return result;

}
//2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
  /* first check whethen ~(x + 1) equals to x, then exclude 0xffffffff by tmp2 */
  int tmp0 = x + 1;
  int tmp1 = ~(tmp0) ^ x;
  int tmp2 = !(tmp0);
  return !tmp1 & !tmp2;
}
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
  /* construct the check number 0xAAAAAAAA */
  int checkNumber = 0xAA | 0xAA << 8 | 0xAA << 16 | 0xAA << 24;
  return !((x & checkNumber) ^ checkNumber);
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  /* the formula for negating a signed number x ==> ~x + 1 */
  int result = ~x + 1;  
  return result;
}
//3
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
  /* 1. check if x >= 0xFF
     2. check if the last 4 bits in x is 0~9
     3. check if x is between 0x30 ~ 0x39
     Maybe a better solution than mine.
   */
  int tmp0 = x >> 8;
  int tmp1 = !((x & 0xA) ^ 0xA) | !((x & 0xC) ^ 0xC);
  int tmp2 = x >> 4 ^ 0x3;
  return !tmp0 & !tmp1 & !tmp2;
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  /* get some hints from the internet
     the key point is to construct flag_x = 0xFFFFFFFF when x != 0
     using arithmetic right shift.
   */
  int flag_x = (x | (~x + 1)) >> 31;
  int result = (y & flag_x) | (z & ~flag_x); 
  return result;
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  /* the situation for x <= y is divided into 3 cases:
     1. x = y, use x ^ y to judge.
     2. x < 0, y >= 0, see the second part of result statement.
     3. x and y have the same sign bit, use negate(x) + y to judge. 
   */
  int equal = !(x ^ y);
  int x_sign_bit = x >> 31 & 0x1;
  int y_sign_bit = y >> 31 & 0x1;
  int x_y_sign_bit = x_sign_bit ^ y_sign_bit;
  int negate_x = ~x + 1;
  int sum = negate_x + y;
  int sum_sign_bit = sum >> 31 & 0x1;
  int result = equal | (x_sign_bit & !y_sign_bit) | (!x_y_sign_bit & !sum_sign_bit);
  return result;
}
//4
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) { 
  /* get the inspiration from function conditional() */
  int flag_x = (x | (~x + 1)) >> 31;
  int result = (0x0 & flag_x) | (0x1 & ~flag_x);
  return result;
}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
  /* I had to admit that I searched for answers on the internet.
     referenced link: https://www.github.com/jerrylzy/CS33/blob/master/Lab/datalab/bits.c
   */ 
  int bit16, bit8, bit4, bit2, bit1, bit0, sum;
  /* bit invert x */
  int x_sign_bit = x >> 31;
  x = (x_sign_bit & ~x) | (~x_sign_bit & x);
  
  /* binary search on bit level */
  bit16 = !!(x >> 16) << 4;
  x = x >> bit16;
  bit8 = !!(x >> 8) << 3;
  x = x >> bit8;
  bit4 = !!(x >> 4) << 2;
  x = x >> bit4;
  bit2 = !!(x >> 2) << 1;
  x = x >> bit2;
  bit1 = !!(x >> 1);
  x = x >> bit1;
  bit0 = !!x;
  sum = bit16 + bit8 + bit4 + bit2 + bit1 + bit0 + 1;
  return sum;
}
//float
/* 
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf) {
  unsigned result;
  unsigned sign = (uf >> 31) & 0x1;
  unsigned mantissa = uf & 0x7FFFFF;
  unsigned exp = (uf >> 23) & 0xFF;
  /* 
     if uf is a denorm, just left shift uf
     by one bit and keep the sign bit.
   */
  if (exp == 0x0)
      return (uf << 1) | (sign << 31);
  /*
     if uf is a INF or NaN, return uf. 
   */
  if (exp == 0xFF)
      return uf;
  exp = exp + 0x1;
  /*
     if exp + 1 equals 0xFF, return INF,
     so mantissa has to be set 0x0.
   */
  if (exp == 0xFF)
      return (sign << 31) | (exp << 23) | (mantissa & 0x0);
  result = (sign << 31) | (exp << 23) | mantissa;
  return result;

}
/* 
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf) {
  int sign = (uf >> 31) & 0x1;
  int mantissa = (uf & 0x7FFFFF) | 0x800000;
  int exp = ((uf >> 23) & 0xFF) - 0x7F;

  /* if exp > 31, overflow. */
  if (exp > 31)
      return 0x80000000u;
  /* if exp < 0, the absolute value won't be greater than 0. */
  if (exp < 0)
      return 0u;
  /* if exp < 23, mantissa shift left by (exp - 23) bits.
     else, mantissa shift right by (23 - exp) bits.
   */
  if (exp > 23)
      mantissa = mantissa << (exp - 23);
  else
      mantissa = mantissa >> (23 - exp);

  /* if the sign bit of mantissa is the same as the original, return mantissa.
     if not, return the negative value of mantissa.
   */
  if (!((mantissa >> 31) ^ sign))
      return mantissa;
  else
      return ~mantissa + 1;

}
/* 
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 * 
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while 
 *   Max ops: 30 
 *   Rating: 4
 */
unsigned floatPower2(int x) {
  /* first construt the bitwise representation for 2.0 and exponent part for 0.5 */
  int float_2 = 0x40000000;
  int exp_half = 0x40000;
  /* if x < -23, the result is too small, so return 0 */
  if (x < - 23)
      return 0;
  /* if -23 < x < 0, shift right the exponent part for 0.5 by (~x + 1) bits */
  else if (x < 0)
      return float_2 | (exp_half >> (~x + 1));
  /* if 0 <= x <= 127, add the x-1 to the exponent part for 2.0 and do the left shifting */
  else if (x <= 127)
      return ((float_2 >> 23) + x - 1) << 23;
  /* if x > 127, the result is too big, so return +INF */
  else
      return 0x7F800000;
}
