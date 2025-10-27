# Dynamic Inventory Management System

This project is a **Dynamic Inventory Management System** implemented in C.
It manages product details for a shop using **dynamic memory allocation**, allowing the inventory to grow or shrink at runtime.

## Features

- Uses **heap memory** to store product information dynamically.
- Supports the following operations through a menu-driven interface:

  - **Add New Product** – increases inventory size using `realloc()`
  - **View All Products**
  - **Update Quantity** of an existing product
  - **Search by Product ID**
  - **Search by Product Name** (supports partial matches)
  - **Search by Price Range**
  - **Delete a Product by ID** – decreases inventory size dynamically
  - **Exit the Program** – safely frees all allocated memory

- Demonstrates the use of:

  - `malloc()`, `calloc()`, `realloc()`, and `free()`
  - Pointers, structures, and dynamic arrays

## Usage

### 1. Compile the program

```bash
gcc dynamicInventoryManagementSystem.c lib/product.c lib/userInput.c -o ./out/dynamicInventoryManagementSystem
```

### 2. Run the program

```bash
./out/dynamicInventoryManagementSystem
```
