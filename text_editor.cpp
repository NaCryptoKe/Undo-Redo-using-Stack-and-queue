#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdexcept> // Required for std::out_of_range
#include <sstream>   // Required for potential future enhancements or complex parsing if needed
#include <limits>    // Required for std::numeric_limits
#include <ios>       // Required for std::streamsize
#include <ostream>   // Required for std::flush

// Stack Implementation (Keep as is)
template <typename T>
class Stack {
private:
    std::vector<T> data;
public:
    void push(const T& value) { data.push_back(value); }
    void pop() { if (!data.empty()) data.pop_back(); }
    T top() const { if (!data.empty()) return data.back(); throw std::out_of_range("Stack is empty."); }
    bool empty() const { return data.empty(); }
    void clear() { data.clear(); }
};

// Queue Implementation (Keep as is)
template <typename T>
class Queue {
private:
    std::vector<T> data;
    size_t head = 0;
public:
    void push(const T& value) { data.push_back(value); }
    void pop() { if (head < data.size()) head++; }
    T front() const { if (head < data.size()) return data[head]; throw std::out_of_range("Queue is empty."); }
    bool empty() const { return head >= data.size(); }
    void clear() { data.clear(); head = 0; }
    std::vector<T> get_elements() const {
        std::vector<T> elements;
        for(size_t i = head; i < data.size(); ++i) elements.push_back(data[i]);
        return elements;
    }
};

// showHistory Function (Keep as is)
void showHistory(const Queue<std::string>& undoHistory, const Queue<std::string>& redoHistory) {
    std::cout << "\n--- Undo History (Oldest First) ---\n";
    std::vector<std::string> undoItems = undoHistory.get_elements();
    if (undoItems.empty()) {
        std::cout << " (empty)\n";
    } else {
        for (const auto& item : undoItems) std::cout << " " << item << "\n";
    }
    std::cout << "\n--- Redo History (Oldest First) ---\n";
     std::vector<std::string> redoItems = redoHistory.get_elements();
    if (redoItems.empty()) {
        std::cout << " (empty)\n";
    } else {
         for (const auto& item : redoItems) std::cout << " " << item << "\n";
    }
    std::cout << "-----------------------------------\n" << std::endl; // Keep endl here
}

// *** MODIFIED displayCurrentContent ***
// Prints current content without a trailing newline
void displayCurrentContent(const std::vector<std::string>& content) {
     bool first = true;
     for(const auto& word_part : content) {
         if (!first) {
             std::cout << " ";
         }
         std::cout << word_part;
         first = false;
     }
     // No std::endl here anymore
}

// *** MODIFIED main ***
int main() {
    std::vector<std::string> content;
    Stack<std::string> undoStack;
    Stack<std::string> redoStack;
    Queue<std::string> undoHistory;
    Queue<std::string> redoHistory;

    std::cout << "Welcome to the Word-Based Text Editor\n";
    std::cout << "Type words separated by spaces. Press Enter after each word or command.\n";
    std::cout << "Commands: ':undo', ':redo', ':history', ':exit'\n\n";

    // Initial prompt
    std::cout << "> ";
    std::cout.flush(); // Ensure prompt is visible

    std::string word;
    while (std::cin >> word) {

        bool display_prompt_and_content = true; // Flag to control display at the end

        if (word == ":exit") {
            std::cout << "\nExit command received. Saving your work...\n";
            display_prompt_and_content = false; // Don't display prompt after exit
            break;
        } else if (word == ":undo") {
            if (!content.empty()) {
                std::string lastWord = content.back();
                content.pop_back();
                undoStack.push(lastWord);
                undoHistory.push("Undo: \"" + lastWord + "\"");
                std::cout << "Undid: \"" << lastWord << "\"\n"; // Newline after message
            } else {
                std::cout << "Nothing to undo.\n"; // Newline after message
            }
        } else if (word == ":redo") {
            if (!undoStack.empty()) {
                std::string wordToRedo = undoStack.top();
                undoStack.pop();
                content.push_back(wordToRedo);
                redoStack.push(wordToRedo);
                redoHistory.push("Redo: \"" + wordToRedo + "\"");
                std::cout << "Redid: \"" << wordToRedo << "\"\n"; // Newline after message
            } else {
                std::cout << "Nothing to redo.\n"; // Newline after message
            }
        } else if (word == ":history") {
            showHistory(undoHistory, redoHistory); // showHistory includes its own formatting
            // We still want to show the current content and prompt after history
        } else {
            // Any other input is treated as a content word
            content.push_back(word);
            undoStack.clear();
            redoStack.clear();
            redoHistory.clear();
            // Don't print anything here, let the end-of-loop logic handle it
        }

        // *** Moved prompt and display logic to the end of the loop ***
        if (display_prompt_and_content) {
            std::cout << "> ";                 // Print the prompt
            displayCurrentContent(content);    // Display content on the same line
            std::cout << std::flush;           // Ensure output is visible before waiting
        }
    }

    // --- Rest of main function remains the same ---

    if (!std::cin.eof() && std::cin.fail()) {
        std::cerr << "\nInput error occurred." << std::endl;
    }

    std::cout << "\nYou've written " << content.size() << " word(s).\n";

    if (content.empty()) {
         std::cout << "No content to save.\n";
         return 0;
    }

    std::string filename;
    std::cin.clear();
    // Be careful with multiple ignore calls if issues persist. One is usually enough.
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Enter filename to save: ";
    std::getline(std::cin, filename);

    if (filename.empty()) {
        std::cout << "No filename provided. Using default 'output.txt'.\n";
        filename = "output.txt";
    }

    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Failed to open file '" << filename << "' for writing.\n";
        return 1;
    }

    bool firstWord = true;
    for (const auto& w : content) {
        if (!firstWord) {
            file << ' ';
        }
        file << w;
        firstWord = false;
    }
    file << '\n';

    std::cout << "Content saved to '" << filename << "'.\n";
    return 0;
}