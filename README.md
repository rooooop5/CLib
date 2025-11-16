# 📦 CVector — Header-Only, Type-Safe Dynamic Arrays for C
*A modern STL-style vector library for C. Zero void pointers. Zero boilerplate. Maximum ergonomics.*

![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)
![Language: C](https://img.shields.io/badge/language-C-blue)
![Header Only](https://img.shields.io/badge/header--only-yes-purple)
![Zero Dependencies](https://img.shields.io/badge/dependencies-none-brightgreen)

---

# ✨ Features

- 🚀 Type-safe vectors (like `std::vector<int>` but in C)  
- 💡 Header-only  
- 📈 Automatic resizing (amortized O(1) push)  
- 📥 Functions: `push`, `pop`, `insert`, `remove`, `clear`  
- 🔁 Python-like iteration macros: `iterate_byval` and `iterate_byref`  
- 👁 Python-style print macro: `cvec_print`  
- 🧩 Works with any type, including structs  
- ⚡ Zero `void*`, zero casting, zero runtime cost  

---

# 📂 Installation

Copy `cvector.h` into your project:

```c
#include "cvector.h"
```

No compilation of additional files is required. It is fully header-only.

---

# 🛠 Declaring Vector Types

Declare new vector types using:

```c
cvector(int);      // creates cvector_int
cvector(float);    // creates cvector_float
cvector(person);   // works with structs
```

---

# 💡 Initialization

Use the `init_cvector` macro to initialize an empty vector:

```c
cvector_int v = init_cvector(int);
```

- `size = 0`  
- `capacity = 0`  
- `data = NULL`  

Memory is allocated lazily on the first `push`.

---

# 📥 Push

```c
cvec_type_push(cvector_type *v, type value);
```

**Example:**

```c
cvec_int_push(&v, 10);
```

**Behavior:**

- Appends the value to the end of the vector  
- Doubles capacity when full  
- Updates `size`, `last`, and `front`

**Time Complexity:** Amortized **O(1)**

---

# 📤 Pop

```c
type cvec_type_pop(cvector_type *v);
```

**Example:**

```c
int x = cvec_int_pop(&v);
```

**Behavior:**

- Removes the last element and returns it  
- Updates `last`  
- Does **not** shrink capacity  

**Time Complexity:** O(1)  
**Warning:** No bounds check; popping an empty vector is undefined behavior.

---

# 🔹 Insert

```c
cvec_type_insert(cvector_type *v, type value, size_t index, size_t copies);
```

**Example:**

```c
cvec_int_insert(&v, 100, 1, 2); // inserts 100 at index 1, twice
```

**Behavior:**

- Shifts elements at and after `index` to the right  
- Inserts `value` `copies` times  
- Updates `size`, `last`, `front`  

**Time Complexity:** O(n)

**Notes:**

- If `index == size`, behaves like multiple pushes  
- `index > size` → undefined behavior

---

# 🔹 Remove

```c
cvec_type_remove(cvector_type *v, size_t index);
```

**Example:**

```c
cvec_int_remove(&v, 2); // removes v[2]
```

**Behavior:**

- Shifts elements left to fill gap  
- Reduces `size`  
- Updates `last`, `front`  

**Time Complexity:** O(n)  
**Warning:** No bounds check.

---

# 👁 Print

```c
cvec_print(v, "%d");
```

**Example Output:**

```
[10, 20, 30]
```

Prints the vector in Python list style.

---

# 🔁 Iteration Macros

### By-value (read-only)

```c
iterate_byval(v, elem, int) {
    printf("%d\n", elem);
}
```

- Iterates over vector elements by **value**  
- Cannot modify vector elements inside this loop  

---

### By-reference (modifiable)

```c
iterate_byref(v, ptr, int) {
    *ptr *= 2;
}
```

- Iterates over vector elements by **reference**  
- Can modify vector elements

---

# 🧪 Full Example

```c
#include <stdio.h>
#include "cvector.h"

typedef struct person {
    int id;
    char name;
} person;

cvector(int);
cvector(person);

DEFINE_CVECTOR_FUNCTIONS(int)
DEFINE_CVECTOR_FUNCTIONS(person)

int main() {
    cvector_int v = init_cvector(int);

    cvec_int_push(&v, 10);
    cvec_int_push(&v, 20);
    cvec_int_push(&v, 30);

    cvec_print(v, "%d");   // [10, 20, 30]

    cvec_int_insert(&v, 99, 1, 2);
    cvec_print(v, "%d");   // [10, 99, 99, 20, 30]

    iterate_byval(v, x, int)
        printf("%d ", x);  // prints 10 99 99 20 30

    iterate_byref(v, ptr, int)
        *ptr *= 2;

    cvec_print(v, "%d");   // [20, 198, 198, 40, 60]

    return 0;
}
```

---

# ⚠️ Notes & Best Practices

- Always call `DEFINE_CVECTOR_FUNCTIONS(type)` after declaring a vector type.  
- No automatic bounds checking — unsafe index access will crash the program.  
- `insert` and `remove` are O(n) operations; `push`/`pop` are amortized O(1).  
- The vector **never shrinks automatically**; to reduce memory manually, realloc outside the library.  
- Works for **structs, ints, floats, and custom types**.  

---

# 📜 License

MIT License — free for personal or commercial use.
