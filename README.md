# Minishell 🐚

Minishell is a minimal Unix shell implementation written in C, developed as part of the 42 curriculum.  
It replicates core behaviors of Bash, focusing on process management, parsing, and command execution.

The project explores how shells work internally, including parsing user input, handling processes, managing file descriptors, and implementing built-in commands.

---

## 🚀 Features

- Interactive command prompt
- Execution of system commands using `PATH`
- Support for pipes (`|`)
- Input/output redirections (`>`, `>>`, `<`)
- Environment variable expansion (`$VAR`)
- Signal handling (Ctrl+C, Ctrl+D, Ctrl+\)
- Built-in commands implementation
- Proper exit status handling
- Robust parsing of complex command inputs

---

## 🧠 How It Works

Minishell is structured around several core components:

### 1. Input Handling
- Reads user input using `readline`
- Maintains command history

### 2. Parsing
- Tokenizes input into commands, arguments, and operators
- Handles quotes (`'` and `"`)
- Expands environment variables
- Builds an internal representation (AST or command structure)

### 3. Execution
- Resolves commands using the system `PATH`
- Forks processes for command execution
- Sets up pipes and redirections using file descriptors
- Executes built-ins directly in the parent process when required

### 4. Process Management
- Uses `fork`, `execve`, and `wait`
- Manages multiple processes for pipelines
- Handles exit codes and signals properly

---

## 🛠️ Built-in Commands

- `echo` (with `-n`)
- `cd`
- `pwd`
- `export`
- `unset`
- `env`
- `exit`

---

## 🔀 Redirections & Pipes

Examples:
```
ls -l | grep .c
cat file.txt > output.txt
echo "hello" >> log.txt
wc -l < input.txt
```

---

## ⚙️ Installation & Usage

### 1. Clone the repository
```
git clone <repository_url>
cd minishell
```

### 2. Compile
```
make
```

### 3. Run
```
./minishell
```

---

## ⚠️ Limitations

- Does not support advanced Bash features (e.g., `&&`, `||`, wildcards)
- No job control (background processes)
- Limited syntax compared to a full shell

---

## 🧪 Requirements

- Make
- GCC or Clang
- `readline` library
- Unix-based system (Linux/macOS)

---

## 📜 License

This project was developed for educational purposes as part of the 42 curriculum, focusing on system programming concepts and Unix shell behavior.
