#include <cctype>
#include <algorithm>
#include <bits/stdc++.h>
#include "ShuntingYard.h"
#include "Number.h"
#include "Minus.h"
#include "Plus.h"
#include "Mult.h"
#include "Div.h"


int ShuntingYard::getPriority(string C) {
    if (C == "-" || C == "+")
        return 1;
    else if (C == "*" || C == "/")
        return 2;
    else if (C == "^")
        return 3;
    return 0;
}

/*
 * replaces the string with expression
 */
Expression *ShuntingYard::infixToPostfix(string str) {
    stack<string> stack;
    stack.push("N");
    //swap vars whith their value
    vector<string> s = checkMinus(swapVars(splitString(str)));

    int l = s.size();
    vector<string> output;
    for (int i = 0; i < l; i++) {
        // If the scanned character is an operand, add it to output string.
        if (!isOperator(s[i][0]) && s[i] != "(" && s[i] != ")")
            output.push_back((s[i]));

            // If the scanned character is an ‘(‘, push it to the stack.
        else if (s[i] == "(")
            stack.push("(");

            // If the scanned character is an ‘)’, pop and to output string from the stack
            // until an ‘(‘ is encountered.
        else if (s[i] == ")") {
            while (stack.top() != "N" && stack.top() != "(") {
                string c = stack.top();
                stack.pop();
                output.push_back((c));
            }
            if (stack.top() == "(") {
                string c = stack.top();
                stack.pop();
            }
        }
            //If an operator is scanned
        else {
            while (stack.top() != "N" && getPriority(s[i]) <= getPriority(stack.top())) {
                string c = stack.top();
                stack.pop();
                output.push_back((c));
            }
            stack.push(s[i]);
        }
    }
    //Pop all
    while (stack.top() != "N") {
        string c = stack.top();
        stack.pop();
        output.push_back((c));
    }
    return stringToExpression(output);
}


Expression *ShuntingYard::stringToExpression(vector<string> postfix) {
    stack<Expression *> stack;
    Expression *newExpression;
    for (auto post : postfix) {
        if (!isOperator(post[0]) || (isOperator(post[0]) && post.size() != 1)) {
            newExpression = new Number(stod(post));
            stack.push(newExpression);
            toBeDeleted.push_back(newExpression);
        } else {
            Expression *right = stack.top();
            stack.pop();
            Expression *left = stack.top();
            stack.pop();
            switch (post[0]) {
                case '+':
                    newExpression = new Plus(left, right);
                    stack.push(newExpression);
                    toBeDeleted.push_back(newExpression);
                    break;
                case '-':
                    newExpression = new Minus(left, right);
                    stack.push(newExpression);
                    toBeDeleted.push_back(newExpression);
                    break;
                case '/':
                    newExpression = new Div(left, right);
                    stack.push(newExpression);
                    toBeDeleted.push_back(newExpression);
                    break;
                case '*':
                    newExpression = new Mult(left, right);
                    stack.push(newExpression);
                    toBeDeleted.push_back(newExpression);
                    break;
            }

        }
    }
    Expression *result = stack.top();
    return result;
}

bool ShuntingYard::isOperator(char s) {
    if (s == '+' || s == '-' || s == '/' || s == '*') {
        return true;
    }
    return false;
}

vector<string> ShuntingYard::splitString(string str) {
    vector<string> chopped;
    int i = 0;
    string s;
    while (i != str.length()) {
        //if isnt an operator or brackets
        if (!isOperator(str[i]) && str[i] != '(' && str[i] != ')' && str[i] != ' ') {
            s += str[i];
        } else {
            if (!s.empty()) {
                chopped.push_back(s);
            }
            //adding operator or '(' or ')'
            if (str[i] != ' ') {
                switch (str[i]) {
                    case 42:
                        chopped.emplace_back("*");
                        break;
                    case 43:
                        chopped.emplace_back("+");
                        break;
                    case 45:
                        chopped.emplace_back("-");
                        break;
                    case 47:
                        chopped.emplace_back("/");
                        break;
                    case 40:
                        chopped.emplace_back("(");
                        break;
                    case 41:
                        chopped.emplace_back(")");
                        break;
                }

            }
            s = "";
        }
        i++;
    }
    if (!s.empty()) {
        chopped.push_back(s);
    }
    return chopped;
}


vector<string> ShuntingYard::swapVars(vector<string> chunks) {
    for (int i = 0; i < chunks.size(); i++) {
        if (data->isVar(chunks[i])) {

            chunks[i] = to_string(data->getValueOfVar(chunks[i]));

        }
    }
    return chunks;
}

/*
 * swap any unary minus operators with (0-x)
 */
vector<string> ShuntingYard::checkMinus(vector<string> str) {
    int flag = 0;
    vector<string> s;
    int temp = 1;

    for (int i = 0; i < str.size(); i++) {
        if (i == 0) {
            if (str[i][0] == '-') {
                s.emplace_back("(");
                s.emplace_back("0");
                if (str[i].size() > 1) {
                    s.emplace_back("-");
                    s.emplace_back(str[i].substr(1, str[i].size()));
                } else {
                    s.emplace_back(str[i]);
                }
                flag = 1;
            } else {
                s.emplace_back(str[i]);
            }
            continue;
        }
        int j = 0;
        if (flag && !isOperator(str[i][0])) {
            s.emplace_back(str[i]);
            while (j < temp) {
                s.emplace_back(")");
                j++;
            }
            flag = 0;
            continue;
        } else if (flag && str[i][0] != '-') {
            while (j < temp) {
                s.emplace_back(")");
                j++;
            }
            flag = 0;
        } else if (flag) {
            temp++;
        }
        if ((isOperator(str[i - 1][0]) || str[i - 1] == "(") && str[i][0] == '-') {
            s.emplace_back("(");
            s.emplace_back("0");
            if (str[i].size() > 1) {
                s.emplace_back("-");
                s.emplace_back(str[i].substr(1, str[i].size()));
            } else {
                s.emplace_back(str[i]);
            }
            flag = 1;
        } else {
            s.emplace_back(str[i]);
        }
    }
    int j = 0;
    if (flag) {
        while (j < temp) {
            s.emplace_back(")");
            j++;
        }
        s.emplace_back(")");
    }
    return s;
}

ShuntingYard::~ShuntingYard() {
    for (auto expression: toBeDeleted) {
        delete (expression);
    }
}
