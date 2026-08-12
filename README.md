# ⚡ MYalloc

> A lightweight, custom mark-and-sweep garbage collector & heap allocator implemented in modern C11.

---

## Overview

`MYalloc` is an explicit, custom heap memory manager built to demonstrate low-level systems architecture, custom heap chunking, boundary coalescing, and exact stack-scanned **Mark-and-Sweep Garbage Collection**.

It features zero dependency requirements outside standard C libraries and comes with a custom JSON structural serializer for AST tree visualization (`Debjit.h`).

---

## 🔥 Key Features

- **Custom Heap Allocator**: Allocates memory regions out of a static internal heap word-aligned array (`HEAP_CAP_BYTES`).
- **Mark & Sweep GC**: Automatic reachability tracing via full frame pointer inspection starting from `stack_base` down to current frame bounds.
- **Dynamic Chunk Lists**: Automatic tracking and splitting of free and allocated memory chunks.
- **Chunk Merging**: Boundary coalescing to mitigate external fragmentation during allocation passes.
- **Custom JSON Serializer (`Debjit.h`)**: Header-only lightweight JSON emitter for tree/AST visual debugging.

---

## 📐 Architecture & Layout

```
                  ┌─────────────────────────────────────┐
                  │          Stack Scan Pointer         │
                  └──────────────────┬──────────────────┘
                                     │
                                     ▼
                   ┌──────────────────────────────────┐
                   │       mark_region(start, end)    │
                   └─────────────────┬────────────────┘
                                     │
                        (Trace reachable pointers)
                                     │
                                     ▼
             ┌──────────────────────────────────────────────┐
             │            Reachable Chunk Bitmap             │
             └──────────────────────┬───────────────────────┘
                                    │
                                    ▼
             ┌──────────────────────────────────────────────┐
             │       heap_collect() -> Free Unreachable     │
             └──────────────────────────────────────────────┘
```

---

## Project Structure

```text
MYalloc/
├── main.c        # Main entrypoint, AST tree generation & GC stress test
├── heap.c        # Custom heap allocator & Mark-and-Sweep GC engine
├── heap.h        # Memory manager definitions, constants, and chunk definitions
├── Debjit.h      # Single-header JSON serializer & formatter
└── Makefile      # Build targets (all, run, clean)
```

---

## Quickstart

### Prerequisites
* `gcc` or `clang` supporting C11 (`-std=c11`)
* `make`

### Building & Running

```bash
# Clone the repository
git clone https://github.com/Debjit28/MYalloc.git
cd MYalloc

# Build and execute
make run
```

### Cleanup

```bash
make clean
```

---

## Sample Output

```text
root: 0x7fff5fbff010
{
  "value": "a",
  "left": {
    "value": "b",
    "left": null,
    "right": null
  },
  "right": {
    "value": "b",
    "left": null,
    "right": null
  }
}

------------------------------
Alloced Chunks (11):
  start: 0x55f1a0123000, size: 8
  ...
Freed Chunks (1):
  start: 0x55f1a0123080, size: 79984
------------------------------
```

---

## License

Distributed under the MIT License. Feel free to fork, tinker, and hack!