# Chapter 2

The chapter gives the implementation details of three most important representations of numbers, including *Unsigned* encodings, *Two's-complement* encodings and *Floating-point* encodings.

## 2.1 Information Storage

**Key Points:**

* *bytes*, consisting of eight bits, is the smallest addressable unit of memory.
* *virtual memory* is viewed as a large array of bytes by machine-level programs.
* Every byte of memory is identified by a unique number known as *address*.

### 2.1.1 Hexadecimal Notation

**Key Points:**

* Hexadecimal uses digits '0' through '9' along with characters 'A' through 'F' to represent 16 possible values.

* In C, numeric constants starting with `0x` OR `0x` are interpreted as being in hexadecimal. `FA1D37B` in hexadecimal form can be written as `0xFA1D37B` or `0xfa1d37b`. 
* To convert a decimal number *x* to hexadecimal, use the equation `x = q · 16 + r`. *r* is the remainder for each computation. Take 65 as an example, 65 = 4 * 16 + 1, 4 = 0 * 16 + 4, so the hexadecimal form for 65 is `0x41`.

### 2.1.2 Words

**Key Points:**

* *word size* indicates the nominal size of integer and pointer data.
* *word size* determines the maximum size of the virtual address space. A machine with a *w-bit* word size can achieve $2^{w}$ bytes virtual address space.

### 2.1.3 Data Sizes

**Key Points:**

Sizes(in bytes) of C numeric data types.

| C declaration | 32-bit | 64-bit |
| :-----------: | :----: | :----: |
|     char      |   1    |   1    |
|   short int   |   2    |   2    |
|      int      |   4    |   4    |
|   long int    |   4    |   8    |
| long long int |   8    |   8    |
|    char *     |   4    |   8    |
|     float     |   4    |   4    |
|    double     |   8    |   8    |

### 2.1.4 Addressing and Byte Ordering

**Key Points:**

Suppose the variable `x` of type `int` and at address `0x100` has a hexadecimal value of `0x01234567`, the ordering of bytes is depicted as the following.

![Big endian vs Little endian](https://images.app.goo.gl/iRqLT62oohd9P6Eq8)

### 2.1.5 Representing Strings

**Key Points:**

* A string in C is encoded by an array of characters terminated by the null (having value 0) character.
* The most common standard encoding for strings is ASCII character code.

### 2.1.6 Representing Code

**Key Points:**

* Different machine types use different and incompatible instructions and encodings.
* From the perspective of the machine, a program is simply a sequence of bytes.

### 2.1.7 Introduction to Boolean Algebra

**Key Points:**

* `~` corresponds to the logical operation `Not`.
* `&` corresponds to the logical operation `And`.
* `|` corresponds to the logical operation `Or`.
* `^` corresponds to the logical operation `Exclusive-Or`.

### 2.1.8 Bit-Level Operations in C

**Key Points:**

* The best way to determine the effect of a bit-level expression is to expand the hexadecimal arguments to their binary representations, perform the operations in binary, and then convert back to hexadecimal.

### 2.1.9 Logical Operations in C

**Key Points:**

* C provides a set of *logical* operators `||`, `&&`, and `!`, corresponding to `Or`, `And` and `Not` operations of logic.
* Don't confuse these operators with bitwise operators above. The logical operations treat any nonzero argument as representing `TRUE` and argument 0 as representing `FALSE`.

### 2.1.10 Shift Operation in C

**Key Points:**

* *left shift*: *x* is shifted *k* bits to the left, dropping off the *k* most significant bits and filling the right end with `k` zeros.
* *right shift*: two forms: *logical* and *arithmetic*. A logical right shift fills the left end with *k* zeros, while an arithmetic right shift fills the left end with *k* repetitions of the most significant bit.

