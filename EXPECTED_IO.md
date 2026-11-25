# Left Factoring Tool: Expected Input / Output

## How to run

```bash
g++ -std=c++11 main.cpp -o main
./main
```

## Input format

1. Non-terminal name (one word)
2. Number of productions
3. Each production on its own line (no `->`, no `|`, no spaces)

---

## Test 1: basic factoring

**Input**
```
A
4
abc
abd
abe
xyz
```

**Expected output** (after the banner)
```
Original Grammar:
A -> abc | abd | abe | xyz

Applying Left Factoring...

Step 1:
A -> xyz | ab A_factor1
A_factor1 -> c | d | e

Original Grammar:
A_factor1 -> c | d | e

Applying Left Factoring...

Final productions for A_factor1:
A_factor1 -> c | d | e

Final productions for A:
A -> xyz | ab A_factor1
```

## Test 2: nested factoring (two levels)

**Input**
```
A
3
abcd
abce
abf
```

**Expected final result**
```
A -> ab A_factor2
A_factor2 -> f | c A_factor1
A_factor1 -> d | e
```

## Test 3: one production is a prefix of another (epsilon)

**Input**
```
A
2
ab
abc
```

**Expected final result**
```
A -> ab A_factor1
A_factor1 -> epsilon | c
```

## Test 4: no common prefix (nothing to factor)

**Input**
```
A
2
abc
xyz
```

**Expected output**
```
Original Grammar:
A -> abc | xyz

Applying Left Factoring...

Final productions for A:
A -> abc | xyz
```

## Test 5: invalid number of productions

**Input**
```
A
0
```

**Expected output**
```
Invalid number of productions!
```

---

## Limitations

1. **Duplicate productions cause an infinite loop.**
   Input such as `ab`, `ab`, `ac` never finishes: the program prints forever
   (`A_factor1 -> epsilon | epsilon` keeps being factored). Do not enter the
   same production twice.
2. **Character-level matching, not symbol-level.**
   `epsilon` and `end` are treated as sharing the prefix `e`, giving
   `A -> e A_factor1` and `A_factor1 -> psilon | nd`. Use single-character
   symbols (e.g. `abc`, `aBc`) for correct results.
3. **No spaces in productions.**
   Input is read with `cin >>`, so `a B c` would be read as three separate
   tokens. Write it as `aBc`.
4. **Typing `epsilon` / `#` as a production is not handled specially.**
   `epsilon` is only generated in the output when a suffix becomes empty.
   (The `isEpsilon` function exists but is never called.)
5. **One non-terminal at a time.**
   It does not read a whole grammar, and does not find prefixes hidden behind
   other non-terminals (indirect factoring).
6. **Does not remove left recursion.** That is a separate transformation.
7. **Little input validation.**
   The "Invalid production!" check can never trigger because `cin >>` never
   produces an empty string, and running out of input is not detected.
   Duplicate productions are not rejected (see limitation 1).
8. **Name clashes.**
   New non-terminals are named `<name>_factorN`; if your grammar already uses
   such a name, they will collide.
9. **Verbose output.**
   Every recursive call prints its own "Original Grammar" and "Final
   productions" blocks, so deeper nesting means longer output.
