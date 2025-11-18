# CVector — A Lightweight Macro-Based Dynamic Array for C

A small, **header-only**, macro-driven dynamic array library that generates **type-safe** vectors for any C type.  
This README documents the **user-facing macro API** only — implementation details and generated function names are intentionally hidden.

---

## Table of contents

- [Highlights](#highlights)  
- [Quick start](#quick-start)  
- [Declaring vector types](#declaring-vector-types)  
- [Creating vectors](#creating-vectors)  
- [Core API — Macros (detailed)](#core-api---macros-detailed)  
  - `cvec_push` / `cvec_pop`  
  - `cvec_insert` / `cvec_erase` / `cvec_remove`  
  - `cvec_get` / `cvec_first` / `cvec_last` / `cvec_len` / `cvec_capacity`  
  - `cvec_reserve` / `cvec_resize` / `cvec_shrink_to_fit` / `cvec_clear`  
  - `cvec_find`  
  - `cvec_print`  
- [Iteration helpers](#iteration-helpers)  
- [Examples](#examples)  
  - primitives  
  - structs  
- [Behavior & guarantees](#behavior--guarantees)  
- [Best practices and pitfalls](#best-practices-and-pitfalls)  
- [FAQ](#faq)  
- [License](#license)

---

## Highlights

- Header-only, single macro to generate type-safe vector types.
- No `void*` casts in user code — you use your real types.
- Lightweight: small API surface, predictable behavior.
- Designed for performance and minimal abstraction cost.

---

## Quick start

1. Put `cvector.h` into your project include path.
2. In a C file, declare the types you need with `bring_cvector(type);`
3. Use the macros documented below.

---

## Declaring vector types

Before you can use a vector of a type `T`, you must generate a typed vector:

```c
#include "cvector.h"

bring_cvector(int);
bring_cvector(float);
bring_cvector(Person); // if you have a struct Person
```

This expands compile-time code that defines a `cvector_T` struct and the macros below operate on that struct.

---

## Creating vectors

Use the `new_cvector(type)` macro to create an empty vector value you can initialize on the stack:

```c
cvector(int) v = new_cvector(int);
```

This is equivalent to a `{ .data = NULL, .size = 0, .capacity = 0 }` initializer for the generated vector type.

---

## Core API — Macros (detailed)

> **Note:** All macros take the vector *value* (not a pointer) as the first argument. They internally take the address. Macros are written to accept complex expressions (e.g. `players[i].nums`) — parentheses are used for safety.

---

### `cvec_push(vec, type, value)`
Append `value` to the end of `vec`.

**Parameters**
- `vec` — a `cvector(type)` variable (value, not pointer)
- `type` — the element type used when you `bring_cvector(type)`
- `value` — the value to append (expression)

**Behavior**
- If `size == capacity`, capacity grows (doubling strategy).
- Writes the value into the new slot and increments `size`.
- No return value.

**Example**
```c
cvector(int) v = new_cvector(int);
cvec_push(v, int, 42);
```

---

### `cvec_pop(vec, type)`
Remove and return the last element.

**Parameters**
- Same `vec` and `type`.

**Returns**
- The popped element (type `type`).
- **Precondition:** `vec.size > 0` (no bounds checks provided).

**Example**
```c
int x = cvec_pop(v, int);
```

---

### `cvec_insert(vec, type, value, idx, copies)`
Insert `copies` copies of `value` starting at index `idx`.

**Parameters**
- `vec` — vector
- `type` — element type
- `value` — value to insert
- `idx` — position (0..size) to insert before
- `copies` — number of copies to insert (size_t compatible)

**Behavior**
- Grows capacity if needed to hold `size + copies`.
- Shifts existing elements to the right, inserts copies, updates `size`.
- No bounds checks: supplying `idx > size` is undefined behavior.

**Example**
```c
cvec_insert(v, int, 99, 1, 1); // insert one 99 at index 1
```

---

### `cvec_erase(vec, type, start, end)`
Erase a contiguous range `[start, end]`, inclusive.

**Parameters**
- `start`, `end` — indices with `0 <= start <= end < size`

**Behavior**
- Shifts elements coming after `end` left by `(end - start + 1)`.
- Updates `size`.
- No bounds checks are performed.

**Example**
```c
cvec_erase(v, int, 2, 4); // remove indices 2,3,4
```

---

### `cvec_remove(vec, type, idx)`
Remove a single element at `idx` (shifts tail left by 1).

**Example**
```c
cvec_remove(v, int, 3);
```

---

### `cvec_get(vec, idx)`
Return element at index `idx` (lvalue-style macro).

**Usage**
```c
int a = cvec_get(v, 0);      // read
cvec_get(v, 0) = 7;          // write
```

**Note:** It's implemented as `(vec).data[idx]`; index must be valid.

---

### `cvec_first`, `cvec_last`
- `cvec_first(vec)` — element at index `0`.
- `cvec_last(vec)` — element at index `size - 1`.

Precondition: `size >= 1`.

---

### `cvec_len(vec)` and `cvec_capacity(vec)`
- `cvec_len(vec)` → current number of valid elements (size).
- `cvec_capacity(vec)` → allocated capacity.

Both are implemented as simple macros returning the struct fields.

---

### `cvec_reserve(vec, type, newcap)`
Ensure `capacity >= newcap`. If `newcap > capacity`, reallocate to exactly `newcap`. `size` remains unchanged.

**Use when** you know roughly how many elements you'll add to avoid repeated allocations.

---

### `cvec_resize(vec, type, newsize)`
Set the *logical* size to `newsize`.

Behavior:
- If `newsize > capacity`: reallocate capacity to `newsize` and then set `size = newsize`.
- If `newsize <= capacity`: set `size = newsize`.
- **Important:** newly created elements are **uninitialized** — the library does not perform default initialization.

---

### `cvec_shrink_to_fit(vec, type)`
Reallocates internal buffer to reduce `capacity` to exactly `size`.

---

### `cvec_clear(vec, type)`
Free internal buffer and set `data = NULL, size = 0, capacity = 0`.

---

### `cvec_find(vec, type, value)`
Linear search for `value` using `==`. Returns index (type `size_t`) if found, otherwise `(size_t)-1` (alias `SIZE_MAX`).

**Important:** This only works for types where `==` semantics are appropriate (primitives and POD structs compared bitwise).

---

### `cvec_print(vec, fmt)`
Pretty-print the vector using the `printf` format string `fmt` for elements.

**Example**
```c
cvec_print(v, "%d");
```

Outputs: `[1, 2, 3]`

---

## Iteration helpers

Two macros for idiomatic iteration. They accept arbitrary expression for `vec` safely.

### `iterate_byref(vec, it, type)`
Iterate where `it` is declared as a pointer to the element type.

```c
iterate_byref(v, p, int) {
    *p += 10;
}
```

`p` is `int *` and can be used to mutate elements in place.

---

### `iterate_byval(vec, it, type)`
Iterate where `it` is a value copy of the element (safe for printing or when you don't want to mutate).

```c
iterate_byval(v, x, float) {
    printf("%f
", x);
}
```

---

## Examples

### Primitives
```c
#include <stdio.h>
#include "cvector.h"

bring_cvector(int);

int main(void) {
    cvector(int) v = new_cvector(int);

    for (int i = 0; i < 10; ++i) cvec_push(v, int, i*2);

    printf("len=%zu cap=%zu\n", cvec_len(v), cvec_capacity(v));

    iterate_byval(v, x, int) {
        printf("%d\n", x);
    }

    cvec_clear(v, int);
    return 0;
}
```

### Structs
```c
#include <stdio.h>
#include <string.h>
#include "cvector.h"

typedef struct { int id; char name[32]; } Person;

bring_cvector(Person);

int main(void) {
    cvector(Person) people = new_cvector(Person);

    Person p = {1, "Alice"};
    cvec_push(people, Person, p);

    Person q = {2, "Bob"};
    cvec_push(people, Person, q);

    iterate_byref(people, it, Person) {
        printf("id=%d name=%s\n", it->id, it->name);
    }

    cvec_clear(people, Person);
    return 0;
}
```

**Note about structs:** Assignment copies the struct fields (shallow copy). If your struct contains pointers, the pointer values are copied — you may need to manage ownership manually.

---

## Behavior & guarantees

- **No bounds checking**: Most operations assume caller correctness. Passing invalid indices is undefined behavior.
- **Growth strategy**: push doubles capacity when needed (amortized O(1)).
- **Allocation policy**: `reserve` sets capacity exactly to requested value; `resize` may grow capacity to `newsize`.
- **Find returns `SIZE_MAX` if not found** — check against that value.
- **Performance**: header-only macros inline operations, minimal overhead.

---

## Best practices and pitfalls

- Always `bring_cvector(T)` in translation units where you use type `T`.
- Avoid copying the vector struct by value (`v2 = v1`) — this performs a shallow copy of internal pointer and will lead to double-free or use-after-free if both are freed. Use `cvec_clear` on one and be mindful of ownership.
- `resize` does not initialize new elements. If you need initialization, manually set values after resize or push them one-by-one.
- `find` uses `==` — for complex structs, implement your own search if equality has special meaning.
- Use `cvec_reserve` when you can estimate final size to avoid realloc churn.

---

## FAQ

**Q: Can I use these macros for types defined in another module?**  
A: Yes — `bring_cvector(YourType)` only needs the type name visible at the point where you call it.

**Q: Are these macros thread-safe?**  
A: No. The macros and underlying memory operations are not synchronized.

**Q: Can I store pointers and manage ownership?**  
A: Yes, but pointer copying is shallow. You must handle allocation/freeing semantics yourself.

---

## License

MIT. Use it, modify it, distribute it.

---

*Generated README for your macro-based `cvector.h`. If you'd like, I can:*
- add badges (License, Build)  
- produce an examples folder with `examples/primitive.c` and `examples/struct.c`  
- convert this README into a GitHub release page format  
