# Chapter 1

This chapter gives the overview of how the computer system are laid out and how a *hello* program written by *C* is running on the computer.

## 1.1 Information = Bits + Context

**Key Points:**

* Most modern systems represent text characters using the ASCII standard that represents each character with a unique byte-sized integer value. One can type in `man ascii` command in Linux to see the whole ASCII chart.
* All information in a system is represented as a bunch of bits. The only thing that distinguishes different data objects is the context in which we view them.

## 1.2 The procedure of a C source file to object file

**Key Points:**

* The procedure of compiling a C source file into object file is depicted in the above picture. It contains four phases:
  * *Preprocessing phase.* The preprocessor (cpp) reads the contents of the system header file defined in the beginning of source file with `#include` characters and inserts it directly into the program text.
  * *Compilation phase.* The compiler (cc1) translates the text file `hello.i` into the text file `hello.s`, which contains an *assembly-language program.*
  * *Assembly phase.* The assembler (as) translates `hello.s` into machine-language instructions, packages them in a form known as a *relocatable object program*.
  * *Linking phase.* The linker (ld) handles different object files merging together into an *executable object file.*

## 1.3 Why need to know how compilation systems work

There are some important reasons why programmers need to understand how compilation systems work.

**Reasons:**

* *Optimizing program performance.*
* *Understanding link-time errors.*
* *Avoiding security holes.*

## 1.4 Processors read and interpret instructions stored in memory

**Key Points:**

* Hardware organization of a system:
  * *Buses.*
  * *I/O Devices.*
  * *Main Memory.*
  * *Processor.*
* The flow of running `hello` program:
  * keyboard waiting => shell reads command => shell loads `hello` from disk to main memory => processor executes instructions => instructions copy data from main memory to register file => strings in register transferred to display device => strings displayed on the screen.

## 1.5 Caches matter

**Key Points:**

* A system spends a lot of time moving information from one place to another.
* Larger storage devices are slower than smaller storage devices.
* Faster devices are more expansive to build than their slower devices.
* Caches serve the role as temporary staging areas to deal with processor-memory gap.

## 1.6 Memory hierarchy

The memory hierarchy for a typical computer system is depicted in the picture 1.9.

## 1.7 Basic concepts in operating system

**Key Points:**

* The operating system has two primary purposes:
  * to protect the hardware from misuse by runaway applications.
  * to provide applications with simple and uniform mechanisms for manipulating complicated and different low-level hardware devices.
* *Process.* A process is the operating system's abstraction for a running program.
* *Threads.* A process can consist of multiple execution units, named *threads.*
* *Virtual Memory.* Virtual memory is an abstraction that provides each process with the illusion that it has excusive use of the main memory. It consists of a number of well-defined areas:
  * *Program code and data.*
  * *Heap.*
  * *Shared libraries.*
  * *Stack.*
  * *Kernel virtual memory.*
* *Files.* Every I/O devices, including disks, keyboards, displays, and networks, is modeled as a file.

## 1.8 Networks

Get to know the flow of using telnet to run `hello` remotely over a network.

## 1.9 Important Themes

**Key Points:**

* Concurrency & Parallelism.  We use the term *concurrency* to refer to the general concept of a system with multiple, simultaneous activities, and the term *parallelism* to refer to the use of concurrency to make a system run faster. To put it shortly, my understanding is that parallelism is the subset of concurrency. Parallelism can be exploited at multiple levels of abstraction in a computer system.
  * *Thread-Level Concurrency.*
  * *Instruction-Level Parallelism.*
  * *Single-Instruction, Multiple-Data(SIMD) Parallelism.*
* Abstractions in computer systems.
  * *Virtual machine* => Operating system + Processor + Main memory + I/O devices.
  * *Processes* => Processor + Main memory + I/O devices.
  * *Virtual memory* => Main memory + I/O devices.
  * *Files* => I/O devices.