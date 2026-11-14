# C-Projects: a console text editor in C++

A text editor for the Windows console, uploaded in July 2021 during my bachelor's studies in computer science. The whole program is in [`text editor.cpp`](text%20editor.cpp). Despite the repository name, it is written in C++, not C.

## Features

- Type and edit text: insert characters anywhere in a line, delete with Backspace and start a new line with Enter. Long lines continue on a new line automatically.
- Move the cursor with the arrow keys.
- **Ctrl+S** saves the text to a file you name. If the file already exists, the text is added to the end of it.
- **Ctrl+O** opens a file you name.
- **Ctrl+J** opens a menu of text functions. Each one asks for a word and applies to every occurrence of it:
  - add a prefix or a suffix,
  - replace it with another word,
  - convert it to upper or lower case,
  - find it and highlight it in green.

The menu also lists "average word length", but that option is not implemented.

## How it works

The document is a dynamic array of lines, and each line is a dynamic array of characters. Both are reallocated with `new` whenever text is typed or deleted. After each change, the screen is redrawn, and the cursor position and text colour are set through the Windows console API.

## Building

The program uses the Windows-only headers `conio.h` and `windows.h` and the Microsoft function `strcpy_s`, so it needs a Windows compiler such as Visual Studio. From a Visual Studio Developer Command Prompt:

```bat
cl /EHsc "text editor.cpp"
```
