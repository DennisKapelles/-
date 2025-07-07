# Temperature Data Manager (C)

This project implements a complete temperature data processing system in C, which allows the user to load and manage daily temperature measurements from a file using one of two data structures:

- Binary Search Tree (BST)
- Hash Table with Chaining

The application reads from a file (`temp.txt`) where each line represents a day's temperature readings in the format:

{"timestamp1": "value1", "timestamp2": "value2", ..., "timestampN": "valueN"}

## 📦 Features

### 🔸 Mode Selection
- On launch, the user selects one of the following storage modes:
  - **BST by Date**
  - **BST by Average Temperature**
  - **Hash Table with Chaining**

---

### 🔹 BST Functionality (Sorted by Date or Avg Temp)
1. In-order traversal display with headers
2. Search for average temperature by date
3. Modify the average temperature of a given date
4. Delete a date's entry
5. Min/Max temperature search (when sorted by temperature)

---

### 🔹 Hash Table Functionality
1. Search for average temperature by date
2. Modify average temperature for a given date
3. Delete a record by date
4. Exit program

- **Hash function**: Based on the ASCII sum of the date string modulo `m` (odd number of buckets)
  - Example:  
    `Hash("2014-02-13") = (ASCII sum) % 11`

---

## 🔧 Technologies Used

- **Language:** C
- **Data Structures:** Binary Search Tree, Hash Table with Chaining
- **File Parsing:** Custom logic for JSON-like line parsing
- **Memory:** Dynamic memory allocation

---

## 📂 File Structure

- `temp.txt`: Input file with daily timestamp-temperature data
- `temperature_data_manager.c`: Main application source file

---

## ▶️ Compilation & Execution

gcc temperature_data_manager.c -o temp_manager

./temp_manager
