// Created by David Zashkolny on 22.04.19.
// 2 course, comp math
// Taras Shevchenko National University of Kyiv
// email: davendiy@gmail.com
//

#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include "stdlib.h"

using namespace std;

enum typeToken{
    OPERATION,
    LEFT_BR,
    RIGHT_BR,
    NUMBER,
};


string NUMBERS = "0123456789";
string OPERATIONS = "+-/*";

class Stack{
public:

    Stack(){
        cur_pos = 0;
    }

    int pop(){
        int result;
        if (cur_pos == 0){
            throw 0;
        }
        cur_pos--;
        result = array[cur_pos];
        cout << "pop from stack: " << result << endl;
        return result;
    };

    void push(int element){
        if (cur_pos >= 1000){
            throw 1;
        }
        cout << "pushing to stack: " << element << endl;
        array[cur_pos] = element;
        cur_pos++;
    };

    bool empty(){
        return cur_pos == 0;
    }

private:
    int array[1000];
    int cur_pos;
};

Stack STACK;
vector<string> CODE;

/* NORM PAIRS:  ( and NUMBER,
 *              NUMBER and OPERATION,
 *              OPERATION and NUMBER,
 *              NUMBER and ),
 *              ( and (,
 *              ) and ),
 *              ) and OPERATION,
 *              OPERATION and (*/


struct Token{
    string str;
    string left_str;
    typeToken type;
};


bool checkIn(char symbol, string &needed){
    bool success = false;
    for (string::iterator itr = needed.begin(); itr != needed.end(); ++itr){
        if (*itr == symbol){
            success = true;
            break;
        }
    }
    return success;
}

vector<Token> tokenizer(string &expression);

// get any str
Token getToken(string &expression);

// get operation (+, -, /, *)
Token getOperation(string &expression);

// get number
Token getNumber(string &expression);

Token getMulExp(string &expression);

Token getLeftBr(string &expression);

Token getRightBr(string &expression);

void term(vector<Token> &tokens);
void factor(vector<Token> &tokens);
void factor(vector<Token> &tokens);

Token getNumber(string &expression) {
    string res_text = "";
    string left = "";
    string::iterator begin = expression.begin();
    while (*begin == ' ') ++begin;
    bool flag_add = true;

    for (string::iterator itr = begin; itr != expression.end(); ++itr) {
        if (checkIn(*itr, NUMBERS) && flag_add) {
            res_text += *itr;
        } else {
            if (flag_add) {
                flag_add = false;
            }
            left += *itr;
        }
    }

    Token result;
    result.left_str = left;
    result.str = res_text;
    result.type = NUMBER;
    return result;
}


Token getOperation(string &expression){
    string::iterator begin = expression.begin();
    string left = "";

    while (*begin == ' ') ++begin;

    Token result;
    result.type = OPERATION;
    result.str = "";

    if (checkIn(*begin, OPERATIONS)){
        result.str = *begin;
        ++begin;
    }

    for (string::iterator itr = begin; itr != expression.end(); ++itr){
        left += *itr;
    }

    result.left_str = left;

    return result;
}

Token getLeftBr(string &expression){
    string::iterator begin = expression.begin();
    string left = "";
    while (*begin == ' ') ++begin;

    Token result;
    result.type = LEFT_BR;

    if (*begin == '('){
        result.str = '(';
        ++begin;
    }
    for (string::iterator itr = begin; itr != expression.end(); ++itr){
        left += *itr;
    }

    result.left_str  = left;
    return result;
}

Token getRightBr(string &expression){
    string::iterator begin = expression.begin();
    string left = "";
    while (*begin == ' ') ++begin;

    Token result;
    result.type = RIGHT_BR;

    if (*begin == ')'){
        result.str = ')';
        ++begin;
    }
    for (string::iterator itr = begin; itr != expression.end(); ++itr){
        left += *itr;
    }

    result.left_str  = left;
    return result;
}


Token getToken(string &expression){
    Token result;
    result = getLeftBr(expression);
    if (!result.str.empty()) return result;

    result = getRightBr(expression);
    if (!result.str.empty()) return result;

    result = getNumber(expression);
    if (!result.str.empty()) return result;

    result = getOperation(expression);
    if (!result.str.empty()) return result;

    throw 1;
}


vector<Token> tokenizer(string &expression){
    vector<Token> result;
    string tmp_expression = expression;
    while (true){
        Token tmp;
        tmp = getToken(tmp_expression);
        if (tmp.left_str.empty()){
            result.push_back(tmp);
            break;
        }
        tmp_expression = tmp.left_str;
        tmp.left_str = "";
        result.push_back(tmp);
    }
    return result;
}

void pop(vector<Token> &array){
    for (int i = 0; i < array.size()-1; i++)
    {
        array[i] = array[i+1];
    }

    array.pop_back();
}


void expression(vector<Token> &tokens){
    term(tokens);
    while (!tokens.empty() and ((tokens[0].str == "+" || tokens[0].str == "-"))){
        string tmp = tokens[0].str;
        pop(tokens);
        term(tokens);
        CODE.push_back(tmp);
    }

}


void term(vector<Token> &tokens){
    factor(tokens);
    while(!tokens.empty() && (tokens[0].str == "*" || tokens[0].str == "/")){
        string tmp = tokens[0].str;
        pop(tokens);
        factor (tokens);
        CODE.push_back(tmp);
    }
}


void factor(vector<Token> &tokens){
    int n = 1;
    if (tokens[0].type == LEFT_BR){
        int t = 0;
        for (vector<Token>::iterator itr = tokens.begin(); itr != tokens.end(); ++itr){
            if (itr->type == LEFT_BR) t++;
            else if (itr->type == RIGHT_BR) t--;
            if (t == 0){
                vector<Token> tmp_tokens;
                pop(tokens);
                for (int i = 0; i < n-2; i++){
                    tmp_tokens.push_back(tokens[0]);
                    pop(tokens);
                }
                pop(tokens);
                expression(tmp_tokens);
                break;
            } n++;
        }
    } else { CODE.push_back((tokens[0].str.c_str()));
        pop(tokens);
    }
}

void print(){
    for (vector<string>::iterator itr = CODE.begin(); itr != CODE.end(); ++itr){
        cout << *itr << endl;
    }

}


int execute(){
    print();
    for (vector<string>::iterator itr = CODE.begin(); itr != CODE.end(); ++itr){

        if (*itr == "+"){
            int tmp_add1 = STACK.pop();
            int tmp_add2 = STACK.pop();
            STACK.push(tmp_add1 + tmp_add2);
        } else if (*itr == "-"){
            int tmp_sub1 = STACK.pop();
            int tmp_sub2 = STACK.pop();
            STACK.push(tmp_sub2 - tmp_sub1);
        } else if (*itr == "*"){
            int tmp_mul1 = STACK.pop();
            int tmp_mul2 = STACK.pop();
            STACK.push(tmp_mul1 * tmp_mul2);
        } else if (*itr == "/"){
            int tmp_div1 = STACK.pop();
            int tmp_div2 = STACK.pop();
            STACK.push(tmp_div2 / tmp_div1);
        } else {
            STACK.push(atoi((*itr).c_str()));
        }
    }
    return STACK.pop();
}


int main(){
    ifstream file("/home/davidas/Документы/univer/c-cpp_course2/cpp/input.txt", ios::in);
    char tmp_symbol;
    string str = "";
    while(file >> tmp_symbol){
        str += tmp_symbol;
    }
    if (file.fail() && !file.eof()){
        cout << "could not read file";
        return 1;
    }

    vector<Token> test_tokens;

    test_tokens = tokenizer(str);
    expression(test_tokens);
    int res = execute();
    cout << res;
    return 0;
}







