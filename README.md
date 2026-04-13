# LucasOS

A simple x86 operating system kernel built from scratch as a learning project.

## 📚 About

This project was created out of curiosity and a desire to understand how operating systems work at a low level.

The main goal is not to build a production-ready OS, but to explore concepts such as:

- Boot process
- Bare-metal development
- Memory layout
- Port I/O
- VGA text mode
- Keyboard input handling
- Low-level programming in C and Assembly

---

## ⚙️ Features

- Multiboot-compliant kernel
- Written in C and x86 Assembly
- Direct VGA text mode terminal
- Terminal support for:
  - character output
  - newline
  - scrolling
  - screen clearing
  - color changes
- VGA hardware cursor update
- Basic keyboard input via polling
- Port I/O helpers with `inb` and `outb`
- Custom linker script
- Bootable ISO using GRUB

---

## 🏗️ Project Structure

```
lucasOS/
├── include/
│   ├── arch/
│   │   └── i386/
│   │       └── io.h
│   ├── drivers/
│   │   ├── keyboard.h
│   │   └── terminal.h
│   └── lib/
│       └── kstring.h
├── src/
│   ├── arch/
│   │   └── i386/
│   │       └── boot/
│   │           └── boot.s
│   ├── drivers/
│   │   ├── keyboard.c
│   │   └── terminal.c
│   ├── kernel/
│   │   └── kmain.c
│   └── lib/
│       └── kstring.c
├── linker.ld
├── grub.cfg
├── Makefile
└── README.md
```

---

## 🚀 Build & Run

### Requirements

- `i686-elf-gcc` (cross-compiler)
- `grub`
- `xorriso`
- `mtools`
- `qemu`

---

### Build

```
make
```

---

### Run

```
make run
```

---

## 🧠 What I Learned

Through this project, I learned:

- How a kernel starts execution (`_start`)
- How to interact with memory directly (VGA at `0xB8000`)
- The role of a linker script
- How bootloaders like GRUB load a kernel
- Basics of system-level programming
- How to interact with hardware through I/O ports
- How keyboard input works at a low level using scancodes

---

## 🔮 Future Plans

- Implement serial output for debugging
- Implement GDT (Global Descriptor Table)
- Add interrupt handling (IDT)
- start building basic shell-like interaction
- improve keyboard support

---

## ⚙️ Requirements

To build and run this project, you need a **cross-compiler** targeting `i686-elf`.

### 🔧 Cross-Compiler

This project **cannot be compiled with your system's default compiler** (like `gcc` on Linux), because it targets a bare-metal environment (no operating system).

Instead, you must use a cross-compiler such as:

- `i686-elf-gcc`

This ensures that:

- No host OS dependencies are included
- The generated binary is suitable for a kernel
- The build follows the correct architecture (x86)

---

### 🧰 Required Tools

- `i686-elf-gcc` (cross-compiler)
- `grub` (to create a bootable image)
- `xorriso` (ISO creation)
- `mtools` (filesystem tools used by GRUB)
- `qemu` (to run the OS in a virtual machine)

---

### 📌 Notes

If you try to compile this project with your system compiler (e.g. `gcc`), you will likely encounter errors or unexpected behavior.

This is why a cross-compiler is **required**.

---

## 📌 Disclaimer

This project is for educational purposes only and is not intended to be a full operating system.
