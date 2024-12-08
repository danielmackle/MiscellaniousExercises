//
// Created by Daniel Mackle on 05/12/2024.
//

#include <iostream>
#include "Stack.h"

int main();
int takeIntInput();
void instantiateStack();
void mainMenu();
void pushMenu();
void peekMenu();
void popMenu();
void deleteStackMenu();
void changeTypeMenu();

IStack<char> *currentStack = nullptr;

std::string type;

int main() {
    instantiateStack();
    mainMenu();
    return 0;
}

int takeIntInput() {
    bool valid = false;
    int input;
    do {
        std::cin >> input;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore();
            std::cout << "Invalid input. Please try again." << std::endl;
        } else {
            valid = true;
        }
    } while (!valid);
    return input;
}

void instantiateStack() {
    bool finished = true;
    do {
        std::cout <<
                "STACK CREATION.\n" <<
                "For int, enter 0.\tFor string, enter 1.\t For bool, enter 2.\t For char, enter 3.\t For float, enter 4.\nPlease enter type of stack:\t"
                << std::endl;
        switch (takeIntInput()) {
            case 0:
                currentStack = new Stack<int>();
                type = "int";
                break;
            case 1:
                currentStack = new Stack<std::string>();
                type = "string";
                break;
            case 2:
                currentStack = new Stack<bool>();
                type = "bool";
                break;
            case 3:
                currentStack = new Stack<char>();
                type = "char";
                break;
            case 4:
                currentStack = new Stack<float>();
                type = "float";
                break;
            default:
                std::cout << "Please enter a valid type." << std::endl;
                type = "erroneous";
                finished = false;
        }
    } while (!finished);
}

void mainMenu() {
    bool quit = false;
    do {
        std::cout <<
                "MAIN MENU\nInput 0 to peek.\tInput 1 to pop.\tInput 2 to push.\tInput 3 to delete stack.\tInput 4 to change type of stack (deleting stack).\tInput -1 to exit.\t";
        switch (takeIntInput()) {
            case 0:
                peekMenu();
                break;
            case 1:
                popMenu();
                break;
            case 2:
                pushMenu();
                break;
            case 3:
                deleteStackMenu();
                break;
            case 4:
                changeTypeMenu();
                break;
            case -1:
                quit = true;
                break;
            default:
                std::cout << "Please enter a valid input." << std::endl;
        }
    } while (!quit);
}

void peekMenu() {
    if (const int output = currentStack.peek(); output == -1) {
        std::cout << "Sorry! The stack is empty! Returning..." << std::endl;
    } else { std::cout << "PEEK\nValue at top of stack :\t" << output << std::endl; }
}

void popMenu() {
    bool valid = false;
    std::cout << "POP" << std::endl;
    int amountToPop;
    do {
        std::cout << "Please enter the amount of items you want to pop (or enter -1 to return):\t";
        amountToPop = takeIntInput();
        if (amountToPop == -1) {
            return;
        }
        if (amountToPop < 0) {
            std::cout << "Please enter a valid amount of items to pop." << std::endl;
        } else {
            valid = true;
        }
    } while (valid == false);
    for (int i = 0; i < amountToPop; i++) {
        const int value = currentStack.pop();
        if (value == -1) {
            std::cout << "Sorry! The stack is empty. Returning..." << std::endl;
            return;
        }
        std::cout << "Pop " << i + 1 << ": \t" << value << std::endl;
    }
    std::cout << "All items popped successfully!" << std::endl;
}

void pushMenu() {
    bool valid = false;
    int amountToPush;
    do {
        std::cout << "Please enter the amount of items you want to push (or enter -1 to return):\t";
        amountToPush = takeIntInput();
        if (amountToPush == -1) {
            return;
        }
        if (amountToPush < 0) {
            std::cout << "Please enter a valid amount of items to push." << std::endl;
        } else {
            valid = true;
        }
    } while (valid == false);
    for (int i = 0; i < amountToPush; i++) {
        std::cout << "Enter value " << i + 1 << ":\t";
        int input = takeIntInput();
        currentStack->push(input);
        std::cout << std::endl;
    }
    std::cout << "All items pushed successfully!" << std::endl;
}

void deleteStackMenu() {
    currentStack->deleteStack();
    std::cout << "Stack deleted successfully." << std::endl;
}

void changeTypeMenu() {
    currentStack->deleteStack();
    instantiateStack();
}
