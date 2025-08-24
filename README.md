# CDC LabWork: FIRST & FOLLOW Calculator

This project provides a **C++ implementation** to compute the **FIRST** and **FOLLOW** sets for a given context-free grammar.  
It is useful for **compiler design** and **parsing algorithm** studies.

---

## Features

- Calculates **FIRST** and **FOLLOW** sets for all non-terminals.
- Supports **epsilon (`#`)** as the empty string.
- Interactive input for grammar productions.
- Designed for educational purposes in compiler design labs.

---

## Usage

### 1. Compile the Code
```bash
g++ first_follow.cpp -o first_follow

```
Example:
``` bash 
Enter number of productions: 3
E->TR
R->+TR
R->#

