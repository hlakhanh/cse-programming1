# Programming 1 — Course Overview

> **Language:** C · **Format:** lectures + lab sessions (60 hours) · **Environment:** Linux, VS Code, gcc/gdb/valgrind
> **Assessment:** assignments 20%, final exam 80%

This page summarizes **what you will learn**, **what you will be able to do** at the end of the course, and **where C and each topic are used in the real world**. Code examples for every lecture are in this repository; hands-on practice is in [`labs/`](labs).

---

## 1. Why learn C?

- **It runs the world's infrastructure.** Operating systems (the Linux kernel), databases (SQLite, PostgreSQL), language interpreters (CPython, the reference Python), version control (Git), web servers (nginx), and networking tools (curl) are written in C.
- **It runs on almost every device.** Microcontrollers in cars, medical devices, routers, washing machines and IoT sensors are usually programmed in C (or C/C++, e.g. Arduino), because C is small, fast and close to the hardware.
- **It powers high-level tools.** The fast core of NumPy, many machine-learning kernels and most system libraries are written in C and called from Python, Java, etc.
- **It teaches how computers really work.** Memory, addresses, the stack and the heap, compilation and linking — concepts hidden by other languages are visible in C. This helps in later courses: operating systems, computer networks, compilers, computer architecture.
- **It is the ancestor of many languages.** C++, Java, C#, JavaScript, Go and Rust all borrow C's syntax and ideas. After C, learning them is much easier.

---

## 2. Course objectives

1. Introduction to programming using the C language.
2. The essential features of C: types, operators, control flow, functions, arrays, pointers, structures, dynamic memory, strings, function pointers, the preprocessor.
3. **Structured problem solving:** problem formulation, divide and conquer — splitting a large task into small functions.
4. **Error detection and elimination:** reading compiler messages, debugging with breakpoints, finding memory errors.

---

## 3. Course map

| Lecture | Main topics | Code examples | Lab session |
|---|---|---|---|
| 1. Course introduction | Programming, compiling & linking, the command line, `main`, functions, header files, variables, arithmetic, `++`/`--`, comments | [`lecture01-intro/`](lecture01-intro) | [Lab 0](labs/lab00-setup.md), [Lab 1](labs/lab01-basics.md) |
| 2. Basic elements | Types and sizes, constants, operators (relational, logical), `if/else`, the `char` type and ASCII, type casting, loops | [`lecture02-basic-elements/`](lecture02-basic-elements) | [Lab 1](labs/lab01-basics.md) |
| 3. Array and pointer | `switch`, `break`/`continue`, 1-D and 2-D arrays, debugging in VS Code, pointers, pointer arithmetic, `malloc`/`free`/`realloc`, variable scope, call by value vs. reference, `struct`, linked list, binary tree | [`lecture03-array-pointer/`](lecture03-array-pointer) | [Lab 2](labs/lab02-arrays-strings-debug.md), [Lab 3](labs/lab03-pointers-memory.md), [Lab 4](labs/lab04-structs-modules.md) |
| 7. Review | IDE setup (build tasks, gdb launch), flow control, pointers to structures, freeing linked lists and trees, 2-D and n-D dynamic arrays | [`lecture07-review/`](lecture07-review) | [Lab 2](labs/lab02-arrays-strings-debug.md), [Lab 3](labs/lab03-pointers-memory.md) |
| 8. Function pointers | Multi-dimensional array indexing (data + shape), strings and `<string.h>`, function pointers, external (dynamic-library) functions, `typedef`, `#define`/`#ifdef`/`#if`, Debug vs. Release, compiling and linking multiple files | [`lecture08-function-pointers/`](lecture08-function-pointers) | [Lab 2](labs/lab02-arrays-strings-debug.md), [Lab 4](labs/lab04-structs-modules.md) |

---

## 4. Lecture by lecture: knowledge, outcomes and applications

### Lecture 1 — Course introduction

**What you will learn**

- What a program is: source code (human-readable) vs. machine code (binary).
- The build process: **compile** (`.c` → `.o`) and **link** (`.o` files + libraries → executable), using `cc`/`gcc` on the command line.
- The structure of a C program: `#include`, the `main` function, statements, comments.
- **Functions:** return type, name, parameters, `return`; why functions allow code reuse.
- **Header files** (`.h`) and `#pragma once`: sharing declarations between several source files.
- Variables, arithmetic operators (`+ - * / %`), integer vs. floating-point division, `i++` vs. `++i`.
- Recursion vs. loops (factorial, Fibonacci).

**After this lecture you can**

- Write, compile and run a C program from the terminal and from VS Code.
- Split a simple problem into functions and place shared declarations in a header file.
- Explain why the recursive Fibonacci is slow and rewrite it with a loop.

**Where it is used**

| Concept | Real-world use |
|---|---|
| Compile & link, object files | Every large C project (Linux kernel, Git, SQLite) is built from hundreds of separately compiled `.c` files linked together; build tools like `make` and CMake automate this. |
| Header files | The C standard library itself: `stdio.h`, `math.h` declare functions whose code lives in a library. Every library you use (OpenSSL, SDL, libcurl) ships a header file. |
| Functions, divide and conquer | The basis of all software design — large programs are trees of small, testable functions. |
| Recursion vs. iteration | Choosing efficient algorithms; firmware on small devices avoids deep recursion because stack memory is tiny. |

---

### Lecture 2 — Basic elements

**What you will learn**

- Built-in types and their sizes: `char`, `short`, `int`, `long`, `float`, `double`; `sizeof`.
- Constants: decimal, hexadecimal (`0x2A`), character (`'A'`); naming rules for variables.
- Relational (`== != < > <= >=`) and logical (`! && ||`) operators; "any non-zero value is true".
- Conditional branching with `if / else if / else`; loops with `for`, `while`, `do-while`.
- The `char` type as a small integer: the **ASCII table**; converting `'5'` to `5`; writing `atoi`.
- Automatic and explicit **type casting**, truncation and overflow.

**After this lecture you can**

- Choose a suitable type for a value and predict when overflow or loss of precision happens.
- Write programs with decisions and loops.
- Convert between characters and numbers, and parse a number from a string by hand.

**Where it is used**

| Concept | Real-world use |
|---|---|
| Exact type sizes, overflow | Embedded systems and network protocols, where a value must fit exactly in 8, 16 or 32 bits (sensor readings, packet headers). Overflow bugs have caused real failures, e.g. the Ariane 5 rocket (1996). |
| Hexadecimal constants | Hardware registers, memory addresses, colors (`0xFF0000`), file formats. |
| Characters and ASCII, `atoi` | Parsing text input: command-line arguments, configuration files, CSV data, HTTP headers, GPS messages from a serial port. |
| Casting, integer vs. float | Scientific and financial calculations, digital signal processing — choosing when to round, truncate or use floating point. |

---

### Lecture 3 — Array and pointer

**What you will learn**

- Flow control: `switch` with combined cases, `break` and `continue` in loops.
- **Arrays:** indexing from 0 to N−1, arrays as function parameters, 2-D arrays as arrays of arrays, the "axis" of a 2-D array.
- Debugging an array with breakpoints in VS Code.
- **Pointers:** declaration, `&` (address-of) and `*` (dereference), `NULL`, pointer to an array, moving a pointer (`p + 3`), the quiz `*(++p)` vs. `*(p++)`; array names behave like constant pointers.
- **Dynamic memory:** `malloc`, `free`, `realloc`, memory leaks; stack vs. heap; global vs. local **scope**.
- **Call by value vs. call by reference**; returning arrays from functions (the LeetCode `returnSize` style).
- **Structures:** `struct`, the `.` and `->` operators, pointers to structures.
- Linked data structures: **linked list** (access, insertion, deletion) and **binary tree**.

**After this lecture you can**

- Process 1-D and 2-D data: maximum along an axis, inner product, matrix multiplication, convolution.
- Use pointers to let a function modify its caller's variables or return several results.
- Allocate memory whose size is only known at run time, and release it correctly.
- Model real entities with `struct` and build a linked list or binary search tree from scratch.

**Where it is used**

| Concept | Real-world use |
|---|---|
| 2-D arrays, matrix multiplication | Image processing (an image is a 2-D array of pixels), 3-D graphics transforms, scientific computing (BLAS/LAPACK). |
| Convolution | Image filters (blur, sharpen, edge detection), audio effects, and the convolutional layers of neural networks (CNNs). |
| Pointers | Device drivers write to hardware through pointers to fixed memory addresses; operating systems manage memory with them; every efficient data structure is built from them. |
| `malloc` / `free` / `realloc` | Growing buffers when the data size is unknown: reading a file of any size, dynamic arrays (the idea behind C++ `std::vector` and Python lists). Memory leaks are a major cause of crashes in long-running servers. |
| Call by reference | Swapping, sorting, and APIs that return several values through output parameters (common in system and library APIs). |
| `struct` | Records in databases, network packet headers, file-format headers (BMP, WAV), game entities. |
| Linked list | The Linux kernel uses linked lists everywhere (e.g. the list of running processes); also undo histories and memory allocators. |
| Binary (search) tree | Database indexes, file-system directories, symbol tables in compilers, fast search and sorted data. |

---

### Lecture 7 — Review

**What you will learn**

- Working effectively in an IDE: VS Code extensions, configuring build tasks (`tasks.json`) and a gdb debug configuration (`launch.json`), the code formatter.
- Debugging with breakpoints: continue, step over, step into, step out; inspecting variables.
- Review of flow control, the `char` type, pointers and pointers to structures.
- Correctly **deallocating** a linked list and a binary tree.
- **Multi-dimensional dynamic arrays:** a 2-D array with `int **`, an n-D array allocated recursively and returned as `void *`.

**After this lecture you can**

- Set up a working C environment on Linux, Windows (WSL) or macOS and debug programs step by step.
- Find a bug by observing variables instead of guessing.
- Free complex dynamic structures without leaks.
- Allocate matrices and higher-dimensional arrays whose sizes are decided at run time.

**Where it is used**

| Concept | Real-world use |
|---|---|
| Debuggers (gdb, IDE) | Daily work of every software engineer; essential for embedded systems, where `printf` may not even be available. |
| Correct deallocation | Servers, browsers and operating systems run for weeks — any leak eventually exhausts memory. Tools such as valgrind and AddressSanitizer are used in industry to find these errors. |
| Dynamic 2-D / n-D arrays | Images of any resolution, game maps, spreadsheets, and tensors (n-D arrays) in machine-learning frameworks. |

---

### Lecture 8 — Function pointers

**What you will learn**

- **Indexing multi-dimensional arrays** stored as a flat 1-D array plus a shape (`struct MultiArray`), and converting `[i][j][k]` to a flat index — exactly how NumPy arrays work.
- **Strings:** `char[]` vs. `char *`, the `'\0'` terminator, `strlen`, `strcmp`, `strcat`, `strcpy`, `strstr` and their `n` versions.
- **Function pointers:** declaring `int (*func)(int, int)`, passing a function as a parameter (e.g. a generic `reduce` with `max`, `min`, `sum`).
- **External functions:** loading functions from a dynamic library at run time and calling them through function pointers.
- **`typedef`** for structures, pointers and function-pointer types.
- **The preprocessor:** `#define` constants and macros, `#ifdef`/`#ifndef` for platform-specific code, `#if` for Debug and Release builds.
- **Compiling and linking multiple files:** prototypes (declarations) vs. implementations (definitions).

**After this lecture you can**

- Implement your own simple n-D array type and compute flat indices.
- Manipulate text safely with the standard string functions.
- Write generic code that takes behaviour as a parameter (sorting with `qsort` and a comparison function, `reduce`, filters).
- Organize a program into modules with header files and build it with a Makefile.
- Produce Debug and Release builds of the same code and write code that compiles on both Windows and Linux.

**Where it is used**

| Concept | Real-world use |
|---|---|
| Flat data + shape indexing | NumPy, PyTorch and TensorFlow store every tensor this way; image libraries store pixels row by row the same way. |
| Strings | Parsing user input, text editors, compilers and interpreters, web servers processing HTTP requests. Unsafe string copying (buffer overflow) is a classic security vulnerability — knowing `strncpy`/`snprintf` matters. |
| Function pointers / callbacks | `qsort` comparison functions, event handlers in GUIs and games, interrupt handlers in embedded systems, plugin systems, and the "virtual functions" behind object-oriented languages. |
| Dynamic libraries (`.so`, `.dll`) | Plugins and drivers loaded at run time; using vendor libraries such as a handwriting-recognition engine (the example in Lecture 8), graphics drivers or hardware SDKs. |
| `typedef` | Readable APIs in real libraries (`FILE`, `size_t`, `pthread_t`, `uint8_t`). |
| Preprocessor, Debug/Release | Cross-platform software (one code base for Windows, Linux, macOS), extra logging and checks in Debug builds, feature switches in the Linux kernel configuration. |
| Multi-file programs | Every real project: teams work on separate modules that are compiled separately and linked together. |

---

## 5. Overall learning outcomes

By the end of the course, students will be able to:

| # | Outcome | Lectures | Labs |
|---|---|---|---|
| LO1 | Use a Linux environment (terminal, compiler, editor/IDE, SSH, Git) to write, build and run C programs. | 1, 7 | 0, 1 |
| LO2 | Explain how C source code becomes an executable (preprocess, compile, link) and organize code into functions, header files and modules built with `make`. | 1, 8 | 1, 4 |
| LO3 | Use C types, operators, expressions and control structures correctly, including character/number conversion and type casting. | 1, 2, 3 | 1 |
| LO4 | Process data with 1-D, 2-D and n-D arrays and with strings. | 3, 7, 8 | 2 |
| LO5 | Use pointers, call by reference and dynamic memory (`malloc`, `realloc`, `free`) correctly and without memory leaks. | 3, 7 | 3 |
| LO6 | Design data with `struct` and `typedef`, and implement linked lists and binary trees. | 3, 7, 8 | 4 |
| LO7 | Write generic, reusable code with function pointers and the preprocessor. | 8 | 4 |
| LO8 | Solve problems in a structured way (problem formulation, divide and conquer), and detect and fix errors with compiler warnings, debuggers (gdb / VS Code) and memory checkers (valgrind). | all | 1–4 |

---

## 6. Tools you will use

| Tool | Purpose |
|---|---|
| Linux / WSL terminal | Running commands, compiling, managing files |
| `gcc` | Compiler and linker |
| `make` | Building multi-file programs |
| VS Code + C/C++ extension | Editing, building and debugging |
| `gdb` | Command-line debugger |
| `valgrind` | Finding memory leaks and invalid memory accesses |
| `ssh`, `scp` | Working on the lab server |
| Git, GitHub | Saving and submitting your work (optional) |

---

## 7. References

- Brian W. Kernighan, Dennis M. Ritchie — *The C Programming Language*, 2nd ed. (Dennis Ritchie is the creator of C)
- Nick Parlante — [*Essential C*](https://cs.stanford.edu/people/nick/compdocs/Essential_C.pdf), Stanford CS Education Library
- [Harvard CS50x](https://cs50.harvard.edu/x/)
- Example programs: [bonigarcia/c-programming](https://github.com/bonigarcia/c-programming)
- Practice problems: [LeetCode](https://leetcode.com/) (topics: math, array, string, linked list)
