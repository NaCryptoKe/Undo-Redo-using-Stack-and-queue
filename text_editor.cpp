#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdexcept> // Required for out_of_range
#include <sstream>   // Required for potential future enhancements or complex parsing if needed
#include <limits>    // Required for numeric_limits
#include <ios>       // Required for streamsize
#include <ostream>   // Required for flush

using namespace std;

// Stack Implementation using struct
#include <vector>

// Define a generic Stack struct
template <typename T>
struct Stack {
    vector<T> data; // Internal storage for stack elements

    void push(const T& value) { data.push_back(value); } // Add element to the stack
    void pop() { if (!data.empty()) data.pop_back(); }   // Remove top element from the stack
    T top() const { 
        if (!data.empty()) return data.back();          // Return top element
        throw out_of_range("Stack is empty.");   // Throw exception if stack is empty
    }
    bool empty() const { return data.empty(); }         // Check if stack is empty
    void clear() { data.clear(); }                      // Clear all elements in the stack
};

// Queue Implementation using struct
template <typename T>
struct Queue {
    vector<T> data; // Internal storage for queue elements
    size_t head = 0; // Index of the front element

    void push(const T& value) { data.push_back(value); } // Add element to the queue
    void pop() { if (head < data.size()) head++; }       // Remove front element from the queue
    T front() const { 
        if (head < data.size()) return data[head];       // Return front element
        throw out_of_range("Queue is empty.");         // Throw exception if queue is empty
    }
    bool empty() const { return head >= data.size(); }   // Check if queue is empty
    void clear() { data.clear(); head = 0; }             // Clear all elements in the queue
    vector<T> get_elements() const {                    // Get all elements from the queue
        vector<T> elements;
        for(size_t i = head; i < data.size(); ++i) 
            elements.push_back(data[i]);
        return elements;
    }
};

// Function to display undo and redo history
void showHistory(const Queue<string>& undoHistory, const Queue<string>& redoHistory) {
    cout << "\n--- Undo History (Oldest First) ---\n";
    vector<string> undoItems = undoHistory.get_elements();
    if (undoItems.empty()) {
        cout << " (empty)\n";
    } else {
        for (const auto& item : undoItems) cout << " " << item << "\n";
    }
    cout << "\n--- Redo History (Oldest First) ---\n";
    vector<string> redoItems = redoHistory.get_elements();
    if (redoItems.empty()) {
        cout << " (empty)\n";
    } else {
        for (const auto& item : redoItems) cout << " " << item << "\n";
    }
    cout << "-----------------------------------\n" << endl; // Keep endl here
}

// Function to display the current content without a trailing newline
void displayCurrentContent(const vector<string>& content) {
    bool first = true;
    for(const auto& word_part : content) {
        if (!first) {
            cout << " "; // Add space between words
        }
        cout << word_part; // Print each word
        first = false;
    }
    // No endl here to keep the output on the same line
}

int main() {
    vector<string> content; // Stores the current text content
    Stack<string> undoStack; // Stack to store words for undo operations
    Stack<string> redoStack; // Stack to store words for redo operations
    Queue<string> undoHistory; // Queue to store undo history
    Queue<string> redoHistory; // Queue to store redo history

    // Display welcome message and instructions
    cout << "Welcome to the Word-Based Text Editor\n";
    cout << "Type words separated by spaces. Press Enter after each word or command.\n";
    cout << "Commands: ':undo', ':redo', ':history', ':exit'\n\n";

    // Initial prompt
    cout << "> ";
    cout.flush(); // Ensure prompt is visible

    string word;
    while (cin >> word) {

        bool display_prompt_and_content = true; // Flag to control display at the end

        if (word == ":exit") {
            // Exit command: Save work and terminate the program
            cout << "\nExit command received. Saving your work...\n";
            display_prompt_and_content = false; // Don't display prompt after exit
            break;
        } else if (word == ":undo") {
            // Undo command: Remove the last word and store it in undo stack
            if (!content.empty()) {
                string lastWord = content.back();
                content.pop_back();
                undoStack.push(lastWord);
                undoHistory.push("Undo: \"" + lastWord + "\"");
                cout << "Undid: \"" << lastWord << "\"\n"; // Print the undone word on a new line
            } else {
                cout << "Nothing to undo.\n"; // Newline after message
            }
                cout << "> ";                 // Start the editor on a new line
                displayCurrentContent(content);    // Display content on the same line
                cout << " ";                  // Add a space to clear any leftover characters
                cout << flush;

        } else if (word == ":redo") {
            // Redo command: Restore the last undone word
            if (!undoStack.empty()) {
                string wordToRedo = undoStack.top();
                undoStack.pop();
                content.push_back(wordToRedo);
                redoStack.push(wordToRedo);
                redoHistory.push("Redo: \"" + wordToRedo + "\"");
                cout << "Redid: \"" << wordToRedo << "\"\n"; // Newline after message
            } else {
                cout << "Nothing to redo.\n"; // Newline after message
            }
        } else if (word == ":history") {
            // History command: Display undo and redo history
            showHistory(undoHistory, redoHistory); // showHistory includes its own formatting
        } else {
            // Any other input is treated as a content word
            content.push_back(word); // Add word to content
            undoStack.clear(); // Clear undo stack after new input
            redoStack.clear(); // Clear redo stack after new input
            redoHistory.clear(); // Clear redo history after new input
        }

        // Display the prompt and current content
        if (display_prompt_and_content) {
            cout << "\r> ";                 // Print the prompt on the same line
            displayCurrentContent(content);    // Display content on the same line
            cout << " ";                  // Add a space to clear any leftover characters
            cout << flush;           // Ensure output is visible before waiting
        }
    }

    // Handle input errors
    if (!cin.eof() && cin.fail()) {
        cerr << "\nInput error occurred." << endl;
    }

    // Display summary of written content
    cout << "\nYou've written " << content.size() << " word(s).\n";

    if (content.empty()) {
         cout << "No content to save.\n";
         return 0;
    }

    // Prompt user for filename to save content
    string filename;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter filename to save: ";
    getline(cin, filename);

    if (filename.empty()) {
        cout << "No filename provided. Using default 'output.txt'.\n";
        filename = "output.txt";
    }

    // Save content to file
    ofstream file(filename);
    if (!file) {
        cerr << "Failed to open file '" << filename << "' for writing.\n";
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

    cout << "Content saved to '" << filename << "'.\n";
    return 0;
}