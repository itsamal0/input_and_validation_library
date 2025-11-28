# Utility Library

A simple C++ library designed to handle **user input safely** and **validate data integrity** (numbers and dates) using static helper methods.

This project is part of my **Learning Path**, done during **Course 11 (OOP Level 2)**  
from the **Programming Advices roadmap**.  
You can explore my full Learning Path repository here: [Learning Path Repository](https://github.com/itsamal0/learning-path)

---

## Features

* **Secure Numeric Input:** Reads any numeric type (`Int`, `Double`, etc.) and automatically validates input errors (non-numeric entries).
* **Flexible Range Check:** Ensures input (numbers or dates) falls within specified `Min` and `Max` boundary values.
* **Date Integrity:** Verifies the mathematical validity of any date object (`isValidDate`).
* **Generic Utility:** Uses C++ Templates (`<typename T>`) to make reading and range-checking functions compatible with all numeric types.

---

## Getting Started

### 1. Clone the repository

```bash
git clone https://github.com/itsamal0/input_and_validation_library.git
cd input_and_validation_library
```

### 2. Build the project

```bash
g++ main.cpp -o input_and_validation_library
```

### 3. Run the program

```bash
./input_and_validation_library
```

---

## Example Output

```
==========================================
  Input & Validation Library Test
==========================================


Enter Int: 3
-> Read: 3

Enter Double: 2.5
-> Read: 2.5

Enter Int [10-50]: 9
Out of Range. Try again [10-50]:
14
-> Read: 14

Enter Double [2.5-7.5]: 1.5
Out of Range. Try again [2.5-7.5]:
3
-> Read: 3


Date check (2024 in range 2023-2025)? -> true

Is 33/10/2024 Valid? -> false