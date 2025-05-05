# 📝 Word-Based Text Editor (CLI Edition)
Welcome to the nerdiest, stack-powered, queue-fueled text editor you didn’t know you needed. Built with good old C++, this command-line tool lets you enter words one at a time, supports undo/redo like a champ, and even saves your poetic nonsense into a file!

## 📦 Features
- ✍️ Word-by-word input – Because who wants paragraphs anyway?

- 🔁 Undo/Redo support – Oops? No worries. Redo your undo or undo your redo.

- 🕒 History tracking – See all your questionable decisions, listed clearly.

- 💾 Save to file – Don’t lose your masterpiece.

- 🧠 Custom Stack & Queue structs – No STL stack/queue here. We went full DIY.

## 🛠️ Tech Stuff
## Language
- C++17 (or newer)

## Dependencies
- Standard C++ Libraries only. No external dependencies, no nonsense.

## Data Structures Used
- `Stack<T>` – Handles undo/redo operations.

- `Queue<T>` – Stores undo and redo history logs.

## 🚀 How It Works
Run the program and just start typing words. Hit `Enter` after each word or command.

## Available Commands
| Command    | Description                         |
| ---------- | ----------------------------------- |
| `:undo`    | Undoes the last word entered        |
| `:redo`    | Redoes the last undone word         |
| `:history` | Displays undo and redo history logs |
| `:exit`    | Ends the session and saves the file |

After `:exit`, you’ll be prompted for a filename. If you ghost the prompt, we’ll save your brilliance in `output.txt`.

## 🧪 Example Session
```
Welcome to the Word-Based Text Editor
Type words separated by spaces. Press Enter after each word or command.
Commands: ':undo', ':redo', ':history', ':exit'

> Hello
> world
> :undo
Undid: "world"
> :redo
Redid: "world"
> :history

--- Undo History (Oldest First) ---
 Undo: "world"

--- Redo History (Oldest First) ---
 Redo: "world"
-----------------------------------

> :exit
Exit command received. Saving your work...
Enter filename to save: epic.txt
Content saved to 'epic.txt'.

```

## 💡 Why?
Because we can. And because Stack and Queue deserve to shine outside boring CS homework.

## ⚠️ Known Limitations
- It’s word-based only. You can’t backspace mid-word. Don’t mess up!

- `:undo` doesn't support batching. One word at a time.

- No GUI. Just glorious text mode. Deal with it.

## 🧹 File Structure
All logic is inside one clean `.cpp` file:

- Stack/Queue structs

- Word input handler

- Undo/redo logic

- History logger

- File output handler

## 🧠 Ideal For
- CS students flexing data structure muscles 💪

- CLI lovers who don’t fear the terminal

- People with too much free time

---
## 🐛 Contributing
Found a bug? Wanna add cool new commands like `:clear` or `:save?` Fork it, tweak it, and submit a pull request. Or don’t. Be mysterious.

---
## 📜 License
MIT – Go wild. Just don’t sell this to billion-dollar companies and act like you invented Word.
