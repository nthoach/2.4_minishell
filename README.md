# Minishell
This 42 project serves as a streamlined emulation of a Unix shell. It furnishes users with a command-line interface for executing diverse commands and overseeing processes. The project emphasizes parsing and executing commands, managing environment variables, and delivering fundamental shell capabilities.

## Features
- Console interface with a prompt for user interaction
- Parsing and execution of commands
- Integration of internal shell commands
- Oversight of environment variables
- Direction of input/output and implementation of pipelines
- Management of signals and supervision of processes

### Not Supported
- ';', '&&', or '||'

## Prerequisites
- To ensure the accurate path for your readline library, modify the line below in the Makefile

READLINE_DIR = "/opt/homebrew/Cellar/readline/8.2.10"

## Installation
1. Clone the repository  
  `git clone https://github.com/nthoach/2.4_minishell.git`  
2. Go to the directory  
  `cd minishell`  
3. Compile the minishell  
   `make`

## Usage
Launch the minishell with the following command:  
`./minishell`  
Executing this command initiates the minishell and presents a prompt, enabling you to input commands.
