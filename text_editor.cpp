#include <iostream>
#include <string>
#include <vector>
#include <fstream>

// Stack Implementation
template <typename T>
class Stack {
private:
    std::vector<T> data;
public:
    void push(const T& value) {
        data.push_back(value);
    }

    void pop() {
        if (!data.empty()) {
            data.pop_back();
        }
    }

    T top() const {
        if (!data.empty()) {
            return data.back();
        }
        throw std::out_of_range("Stack is empty.");
    }

    bool empty() const {
        return data.empty();
    }
};

// Queue Implementation
template <typename T>
class Queue {
private:
    std::vector<T> data;
public:
    void push(const T& value) {
        data.push_back(value);
    }

    void pop() {
        if (!data.empty()) {
            data.erase(data.begin());
        }
    }

    T front() const {
        if (!data.empty()) {
            return data.front();
        }
        throw std::out_of_range("Queue is empty.");
    }

    bool empty() const {
        return data.empty();
    }
};

void showHistory(const Queue<std::string>& undoHistory, const Queue<std::string>& redoHistory) {
    std::cout << "\nUndo History:\n";
    if (undoHistory.empty()) {
        std::cout << "  (empty)\n";
    } else {
        auto temp = undoHistory;
        while (!temp.empty()) {
            std::cout << "  " << temp.front() << "\n";
            temp.pop();
        }
    }

    std::cout << "\nRedo History:\n";
    if (redoHistory.empty()) {
        std::cout << "  (empty)\n";
    } else {
        auto temp = redoHistory;
        while (!temp.empty()) {
            std::cout << "  " << temp.front() << "\n";
            temp.pop();
        }
    }

    std::cout << std::endl;
}

int main() {
    std::vector<std::string> content;
    Stack<std::string> undoStack;
    Stack<std::string> redoStack;
    Queue<std::string> undoHistory;
    Queue<std::string> redoHistory;

    std::cout << "Welcome to the Write-Only Text Editor\n";
    std::cout << "Start typing below.\n";
    std::cout << "Commands: ':undo', ':redo', ':history', ':exit'\n";

    std::string line;
    while (true) {
        std::getline(std::cin, line);

        if (line == ":exit") {
            std::cout << "\nExit command received. Saving your work...\n";
            break;
        } else if (line == ":undo") {
            if (!content.empty()) {
                std::string last = content.back();
                content.pop_back();
                undoStack.push(last);
                undoHistory.push("Undo: " + last);
                std::cout << "Undid: " << last << "\n";
            } else {
                std::cout << "Nothing to undo.\n";
            }
        } else if (line == ":redo") {
            if (!undoStack.empty()) {
                std::string redoLine = undoStack.top();
                undoStack.pop();
                content.push_back(redoLine);
                redoStack.push(redoLine);
                redoHistory.push("Redo: " + redoLine);
                std::cout << "Redid: " << redoLine << "\n";
            } else {
                std::cout << "Nothing to redo.\n";
            }
        } else if (line == ":history") {
            showHistory(undoHistory, redoHistory);
        } else {
            content.push_back(line);
            while (!undoStack.empty()) undoStack.pop();
            while (!redoStack.empty()) redoStack.pop();
        }
    }

    std::cout << "\nYou've written " << content.size() << " line(s).\n";
    std::string filename;
    std::cout << "Enter filename to save: ";
    std::getline(std::cin, filename);

    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Failed to open file for writing.\n";
        return 1;
    }

    for (const auto& l : content) {
        file << l << '\n';
    }

    std::cout << "Saved to '" << filename << "'.\n";
    return 0;
}
