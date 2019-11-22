# Tiny+ Parser
Based on the original Tiny language definition.

## What's new
* Added new comparison operators: <, >, <=, >=
* Added a new keyword: WHILE
* Added a brand-new WHILE loop: WHILE ( BoolExpression ) Statement

## How to compile
Make sure your compiler supports C++11 and above and simply run  ```make```. The Makefile is written for -nix systems.

On -nix systems, ```./bin``` and ```./obj``` folders are created automaticly. On Windows, you need to modify the Makefile manually (Use Windows version of ```mkdir``` syntax, set up ```g++``` on Windows, remove ```chmod``` commands, use ```xcopy``` instead of ```cp```, etc.) to make it work on Windows.

## How can I test the parser
Sample Tiny+ source files are stored in ```./test``` folder and is copied to ```./bin``` folder when building via Makefile. Run ```tiny example.tiny``` to see it in action.

On a successful parsing, the program will print out a long line of LaTeX code. Insert the output into the following template and compile the LaTeX file to see the grammar tree.

```LaTeX
\documentclass{standalone}
\usepackage{forest}

\begin{document}
    % Insert the output here
\end{document}
```

If the source file contains some kind of error, the program will print out the error info instead.