#include <iostream>
#include <fstream>
#include <stack>
#include <set>
#include <vector>
#include <cmath>


using namespace std;

// Global variables
const char file_in[] = "input.txt";
const char file_out[] = "output.txt";
const set<char> dictionary = {'x', 'y', 'z', 'w'};
const int truth_table[16][4] = {{0, 0, 0, 0},
                                {0, 0, 0, 1},
                                {0, 0, 1, 0},
                                {0, 0, 1, 1},
                                {0, 1, 0, 0},
                                {0, 1, 0, 1},
                                {0, 1, 1, 0},
                                {0, 1, 1, 1},
                                {1, 0, 0, 0},
                                {1, 0, 0, 1},
                                {1, 0, 1, 0},
                                {1, 0, 1, 1},
                                {1, 1, 0, 0},
                                {1, 1, 0, 1},
                                {1, 1, 1, 0},
                                {1, 1, 1, 1}};


//Functions
bool checkInput(string);

string infixToPostfix(string);

int Precedence(char);

void processLogic(char, stack<char> &, string &);

void Logic(char, stack<int> &);

vector<int> calculateResult(string);

void outPut(const vector<int> &, ofstream &, const string &);


int main() {

    ifstream input(file_in);
    ofstream output(file_out);
    string data;

    if (!input) {
        cerr << "Error: no such file or directory: " << file_in << endl;
        return -1;
    }

    while (getline(input, data)) {

        if (!checkInput(data)) {
            output << "--------------------------------- Error --------------------------------" << endl;
            output << "Equation [" << data << "] is in incorrect format. Thus, it cannot be processed! " << endl;
            continue;
        }

        string equation = infixToPostfix(data);
        vector<int> answer = calculateResult(equation);
        outPut(answer, output, data);
    }

    input.close();
    output.close();
    return 0;
}

bool checkInput(string data) {
    int letters = 0;
    int operators = 0;
    int space = 0;
    int opening = 0;
    int closing = 0;

    for (int i = 0; i < data.size(); ++i) {
        auto temp = data[i];
        switch (data[i]){
            case ' ': {
                space++;
                break;
            }
            case 'w': {
                letters++;
                break;
            }
            case 'x': {
                letters++;
                break;
            }
            case 'y': {
                letters++;
                break;
            }
            case 'z': {
                letters++;
                break;
            }
            case '{':{
                opening++;
                break;
            }
            case '}':{
                closing++;
                break;
            }
            case '(':{
                opening++;
                break;
            }
            case ')':{
                closing++;
                break;
            }
            case '[':{
                opening++;
                break;
            }
            case ']':{
                closing++;
                break;
            }
            case '=':{
                operators++;
                break;
            }
            case '>':{
                operators++;
                break;
            }
            case '/':{
                operators++;
                break;
            }
            case '|':{
                operators++;
                break;
            }
            case '+':{
                operators++;
                break;
            }
            case 'v':{
                operators++;
                break;
            }
            case '&':{
                operators++;
                break;
            }
            case '!':{
                operators++;
                break;
            }
        }
    }

    bool letter = false;
    bool sign = false;

    for (int i = 0; i < data.size(); ++i) {

        if (data[i] == ' ') {
            continue;
        }

        bool evaluate_letter = data[i] == 'w' or data[i] == 'x' or data[i] == 'y' or data[i] == 'z';
        bool evaluate_sign = data[i] =='&' or data[i] == 'v' or data[i] == '/' or data[i] == '|' or data[i] == '>';

        if(evaluate_letter && letter ){
            return false;
        }

        if(evaluate_sign && sign){
            return false;
        }

        letter = evaluate_letter;
        sign = evaluate_sign;

    }

    if (opening != closing){
        return false;
    }

    return data.size() == letters + space + operators + opening + closing;
}

string infixToPostfix(string data) {
    stack<char> operands;
    string result;


    for (int i = 0; i < data.size(); i++) {
        if (data[i] == ' ') {
            continue;
        }

        int precedence = Precedence(data[i]);

        switch (precedence) {
            case 0 : { // Letter
                result += data[i];
                break;
            }
            case 1: { // Left bracket
                operands.push(data[i]);
                break;
            }
            case 2: { // Right bracket
//                while (brackets_left.count(operands.top()) == 0) {
                while (Precedence(operands.top()) != 1) {
//                    if (brackets_left.count(operands.top()) == 0) {
                    if (Precedence(operands.top()) != 1) {
                        result += operands.top();
                    }
                    operands.pop();
                }
                operands.pop();
                break;
            }
            default: {
                processLogic(data[i], operands, result);
                break;
            }
        }
    }

    if (!(operands.empty())) {
        while (!operands.empty()) {
            result += operands.top();
            operands.pop();
        }
    }
    return result;
}

void processLogic(char operand, stack<char> &Stack, string &result) {
    int priority = 0;

    if (!Stack.empty()) {
        priority = Precedence(Stack.top());
    } else {
        priority = 1;
    }

    if (Precedence(operand) > priority) {
        Stack.push(operand);
    } else {
        result += Stack.top();
        Stack.pop();
        if (!(Stack.empty())) {
            processLogic(operand, Stack, result);
        } else if (Precedence(operand) != 2) {
            Stack.push(operand);
        }
    }
}

int Precedence(char token) {
    switch (token) {
        case '{':
            return 1;
        case '}':
            return 2;
        case '(':
            return 1;
        case ')':
            return 2;
        case '[':
            return 1;
        case ']':
            return 2;
        case '=':
            return 3;
        case '>':
            return 4;
        case '/':
            return 5;
        case '|':
            return 5;
        case '+':
            return 6;
        case 'v':
            return 7;
        case '&':
            return 8;
        case '!':
            return 9;
        default:
            return 0;
    }
}

void Logic(char operand, stack<int> &inputStack) {
    bool x;
    bool y;
    switch (operand) {
        case '!': {
            inputStack.top() = not inputStack.top();
            break;
        }
        case '&': {
            y = inputStack.top();
            inputStack.pop();
            x = inputStack.top();
            inputStack.top() = (y & x);
            break;
        }
        case 'v': {
            y = inputStack.top();
            inputStack.pop();
            x = inputStack.top();
            inputStack.top() = (y || x);
            break;
        }
        case '+': {
            y = inputStack.top();
            inputStack.pop();
            x = inputStack.top();
            inputStack.top() = ((not(x) & y) || (x & not(y)));
            break;
        }
        case '/': {
            y = inputStack.top();
            inputStack.pop();
            x = inputStack.top();
            inputStack.top() = not(y || x);
            break;
        }
        case '|': {
            y = inputStack.top();
            inputStack.pop();
            x = inputStack.top();
            inputStack.top() = not(y & x);
            break;
        }
        case '>': {
            y = inputStack.top();
            inputStack.pop();
            x = inputStack.top();
            inputStack.top() = (not(x) || y);
            break;
        }
        case '=': {
            y = inputStack.top();
            inputStack.pop();
            x = inputStack.top();
            inputStack.top() = (x == y);
            break;
        }
    }
}

vector<int> calculateResult(string data) {

    vector<int> answer;

    for (int i = 0; i < 16; i++) {

        stack<int> Stack;

        for (int j = 0; j < data.size(); j++) {

            auto temp = data[j];

            if (dictionary.count(data[j]) != 0) {
                switch (data[j]) {
                    case 'w': {
                        Stack.push(truth_table[i][0]);
                        break;
                    }
                    case 'x': {
                        Stack.push(truth_table[i][1]);
                        break;
                    }
                    case 'y': {
                        Stack.push(truth_table[i][2]);
                        break;
                    }
                    case 'z': {
                        Stack.push(truth_table[i][3]);
                        break;
                    }
                }
            } else {
                Logic(data[j], Stack);
            }
        }

        if (!Stack.empty()) {
            answer.push_back(Stack.top());
            Stack.pop();
        }
    }

    return answer;
}

void outPut(const vector<int> &data, ofstream &stream, const string &function) {

    stream << "F = " << function << '\n';

    stream << "---+---------+---+" << '\n';
    stream << "№  | w x y z | F |" << '\n';
    stream << "---+---------+---+" << '\n';

    for (int i = 0; i < 16; ++i) {
        stream << i + 1;

        if (i < 9) {
            stream << "  | ";
        } else {
            stream << " | ";
        }

        stream << truth_table[i][0] << " " << truth_table[i][1] << " " << truth_table[i][2] << " "
               << truth_table[i][3] << " | " << data[i] << " |" << '\n';
    }

    stream << "---+---------+---+" << '\n';

    stream << endl << endl;

}