# BLOCK14PG

Brief project description or introduction here.

## File Structure

- **/src/**: 
  - **cores/**: Core classes used in the project.
  - **globals/**: Global variables utilized throughout the project.
  - **compression/**: Contains algorithms for compression.
  - **input/**: Functions related to input handling.
  - **output/**: Functions dedicated to output.
  - **multi-thread-handling/**: Handlers that utilize multi-threading capabilities.

- **/tests/**: 
  - **unit/**: Unit tests for various components.
    - **cores/**: Tests for core classes.
    - **globals/**: Tests related to global variables.
    - **compression/**: Tests for compression algorithms.
    ... (continue mirroring the `src/` structure)
  - **integration/**: Integration tests for the project.

## Tech Stack

- **Programming Language**: C++

## Static Code Analysis - Cppcheck

We've integrated Cppcheck for static code analysis to maintain code quality. Before committing any changes, it's recommended to run Cppcheck locally to spot any potential issues.

### How to run Cppcheck locally:

1. Install Cppcheck on your machine. For most platforms, you can find installation instructions on the [official Cppcheck website](http://cppcheck.sourceforge.net/).

2. Navigate to your project directory in the terminal or command prompt.

3. Use the following command to run Cppcheck:
   - For `src/` with C++11 standard: 
     ```bash
     cppcheck --enable=all --std=c++11 src/
     ```
   - For `tests/` with C++17 standard: 
     ```bash
     cppcheck --enable=all --std=c++17 tests/
     ```

Make sure you've resolved any warnings or errors flagged by Cppcheck before making a commit.

### Notes:

- If you're a first-time user, the tool might report some false positives or suggest micro-optimizations. Focus on genuine issues or bugs it highlights.

- In case you encounter a lot of "missing include" notifications, you can add `--suppress=missingIncludeSystem` to the command to suppress them. However, these are typically informational and can be ignored.

To be added: "Getting Started", "Installation", "Usage", etc.

