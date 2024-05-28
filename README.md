# E++ Compiler Project

## Introduction

This project involves creating a compiler for a simple language of arithmetic expressions, E++. The compiler will take an input program in E++ and generate code in a target language, Targ, which can be executed on a stack machine.

## Project Structure

The project directory is organized as follows:

- `bin`: Contains the compiled binaries.
- `include`: Contains all the header files needed for the assignment.
- `samples`: Provides examples of Targ and E++ files for reference.
- `src`: Contains the required `.cpp` files for implementation.
- `tests`: Contains testing files. Do not modify this folder.

## Compilation and Execution

### Building the Compiler

Run the following command from the main parent directory to build the compiler:

```bash
make
```

If the build process is successful, a binary file named `e++` will be generated in the `bin` folder.

### Running the Compiler

To test your compiler with a set of E++ expressions, create a file (e.g., `a.txt`) with tokenized E++ expressions separated by spaces. Place your built compiler in the same directory as the `a.txt` file and run:

```bash
./e++ a.txt
```

If there are no errors, a file named `targ.txt` containing the Targ commands for `a.txt` will be generated.

### Testing Targ Syntax

In the `tests/targ` directory, there are binaries for each OS. Copy the respective binary file to the same folder where your `filename.txt` with Targ commands is located. Run:

```bash
./targ++ filename.txt
```

To resolve permission issues, you may need to run:

```bash
sudo chmod +x targ++
```

### Tester

The tester is designed for Unix-based systems. Build and run the tester with:

```bash
make tester
cd bin
./tester
```

Follow the on-screen instructions to run the tests.

## Components

### 1. Expression Evaluator Improvements

- **Symbol Table**: Implemented using AVL Trees to ensure logarithmic time complexity for search, insert, and delete operations.

### 2. Code Generator

- **Stack Machine Architecture**:
  - Stack: Used to store temporary values.
  - Memory: Limited indexable memory.
  
- **Targ Syntax**: Commands include `PUSH`, `ADD`, `SUB`, `MUL`, `DIV`, `RET`, etc.

### 3. Memory Management

- **Memory Allocation**: Managed using a vector (`mem_loc`) or a min-heap (`least_mem_loc`).

## Classes and Functions

### Parser (parser.h)

- `int last_deleted`
- `vector<ExprTreeNode*> expr_trees`
- `SymbolTable* symtable`
- `parse(vector<string> expression)`

### Symbol Table (symtable.h)

- `assign_address(string k, int idx)`

### EPPCompiler (eppcompiler.h)

- `Parser targ`
- `int memory_size`
- `string output_file`
- `vector<int> mem_loc`
- `MinHeap least_mem_loc`
- `compile(vector<vector<string>> code)`
- `generate_targ_commands()`
- `write_to_file(vector<string> commands)`