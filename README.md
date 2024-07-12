# Solution optimization of the Travelling Salesman Problem using the evolutionary Genetic Algorithm

Bachelor thesis - July 2024

## Prerequisites

Before you can compile and run this program, make sure you have the following prerequisites installed on your system:

### macOS
1. **Homebrew** (for package management)
   
   To install Homebrew, open your terminal and run this command:
    ```bash
    /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
    ```
    You can use the [link](https://docs.brew.sh/Installation) for detailled installation directives.
    
2. **g++-13**
   
   To install this version of the compiler for C++, open your terminal and run this command: 
    ```bash
    brew install gcc
    ```

### Windows
1. **MinGW-w64** (for GCC)
    - Download and install from [Mingw-w64](https://www.mingw-w64.org/downloads/).

2. **Add MinGW-w64 to PATH**
    - Add the path to the `bin` directory of your MinGW-w64 installation to the system environment variables.

## Compilation

### macOS 
Open your terminal and navigate to the project directory. Use the following command to compile the program:

```bash
/usr/local/bin/g++-13 -fdiagnostics-color=always -g chromosome.cpp crossover.cpp distance_helper.cpp file_reader.cpp mutation.cpp point.cpp population.cpp tsp_ga.cpp main.cpp -o executable_output
```

### Windows
Open your Command Prompt (or PowerShell) and navigate to the project directory. Use the following command to compile the program:
```bash
g++ -g chromosome.cpp crossover.cpp distance_helper.cpp file_reader.cpp mutation.cpp point.cpp population.cpp tsp_ga.cpp main.cpp -o executable_output.exe
```

## Usage

After compiling, you can run the executable. Make sure that you put the executable in the project directory folder `src`, otherwise add your dataset in an outer directory from your executable, in a folder named `data`.

### macOS
Run the following command in your terminal, which is navigated to the correct directory:

```bash
./executable_output
```
*You might need to add the `sudo` prefix to your command, depending on the needed permissions for acceess

### Windows
Run the following command in your Command Prompt (or PowerShell), which is navigated to the correct directory:

```bash
executable_output.exe
```

