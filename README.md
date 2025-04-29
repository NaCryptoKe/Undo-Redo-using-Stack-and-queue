# 📝 Write-Only Text Editor

A simple terminal-based text editor built in C++ with basic **undo**, **redo**, and **history** features using custom stack and queue implementations.

## ⚙️ Features

- ✅ Add text line by line
- 🔁 Undo last action with `:undo`
- 🔄 Redo undone action with `:redo`
- 📜 View history of undo/redo actions with `:history`
- 💾 Save written content to a text file with `:exit`

## 🧱 Data Structures Used

- `Stack<T>` – LIFO (Last In, First Out)
- `Queue<T>` – FIFO (First In, First Out)

No STL stack or queue used. Everything’s hand-coded for the grind. 💪

## 🚀 How to Run

1. **Compile the code**
   ```bash
   g++ -o text_editor text_editor.cpp
   ```

2. **Run the executable**
    ```bash
    ./text_editor
    ```

3. **Start typing. Use these commands anytime:**
    - `:undo` - undo the last line
    - `:redo` - redo the last undone line
    - `:history` - show undo/redo history
    - `:exit` - save and exit

**💡 Example Usage**
```bash
Welcome to the Write-Only Text Editor
Start typing below.
Commands: ':undo', ':redo', ':history', ':exit'

> This is my first line.
> This is my second line.
> :undo
Undid: This is my second line.
> :redo
Redid: This is my second line.
> :history

Undo History:
  Undo: This is my second line.

Redo History:
  Redo: This is my second line.

> :exit
Enter filename to save: notes.txt
Saved to 'notes.txt'.
```

**🛠️ Future Improvements**
- Load existing files
- Word/line editing
- Command shortcuts
- Persistent history
**Built from scratch. No excuses. Just execution. 🧠⚔️**