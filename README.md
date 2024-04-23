# Minishell
This 42 project is a simplified version of a Unix shell. It provides a command-line interface where users can execute various commands and manage processes. The project focuses on parsing and executing commands, handling environment variables, and providing basic shell functionalities.

## Features
- Command-line interface with a prompt for user input
- Command parsing and execution
- Support for built-in shell commands
- Environment variable management
- Input/output redirection and piping
- Signal handling and process management
### Not Supported
- ';', '&&', or '||'

## Prerequisites
- To make sure the correct path for your readline by editing the following line in the Makefile

READLINE_DIR = "/opt/homebrew/Cellar/readline/8.2.10"

## Installation
1. Clone the repository  
  `git clone https://github.com/nthoach/2.4_minishell.git`  
2. Navigate to the directory  
  `cd minishell`  
3. Compile the minishell  
   `make`

## Usage
Start the minishell using the following command:  
`./minishell`  
This launches the minishell and displays a prompt where you can enter commands.
