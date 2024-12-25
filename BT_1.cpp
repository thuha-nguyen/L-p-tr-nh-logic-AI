#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
#include <cctype>
#include <stdexcept>

using namespace std;

// ham kiem tra tinh hop le cua bieu thuc logic
bool isValidExpression(const string &expr) {
    stack<char> s;
    for (char c : expr) {
        if (c == '(') {
            s.push(c);
        } else if (c == ')') {
            if (s.empty()) {
                return false; // sai do dong ngoac ma khong co mo ngoac
            }
            s.pop();
        }
    }
    return s.empty(); 
}

// Hàm tính giá tr? bi?u th?c logic
bool evaluateExpression(const string &expr, const unordered_map<char, bool> &variables) {
    stack<bool> operands;
    stack<char> operators;

    auto applyOperator = [](char op, bool b1, bool b2 = false) {
        switch (op) {
        case '!':
            return !b1;
        case '&':
            return b1 && b2;
        case '|':
            return b1 || b2;
        default:
            throw invalid_argument("Invalid operator");
        }
    };

    for (size_t i = 0; i < expr.size(); ++i) {
        char c = expr[i];
        if (isspace(c)) continue;

        if (isalpha(c)) {
            // them gia tri bien vao stack
            if (variables.find(c) == variables.end()) {
                throw invalid_argument(string("Variable ") + c + " not found in values.");
            }
            operands.push(variables.at(c));
        } else if (c == '(') {
            operators.push(c);
        } else if (c == ')') {
            while (!operators.empty() && operators.top() != '(') {
                char op = operators.top();
                operators.pop();

                bool b1 = operands.top(); operands.pop();
                if (op == '!') {
                    operands.push(applyOperator(op, b1));
                } else {
                    bool b2 = operands.top(); operands.pop();
                    operands.push(applyOperator(op, b2, b1));
                }
            }
            operators.pop(); // Lo?i b? '('
        } else if (c == '&' || c == '|' || c == '!') {
            while (!operators.empty() && operators.top() != '(') {
                char op = operators.top();
                operators.pop();

                bool b1 = operands.top(); operands.pop();
                if (op == '!') {
                    operands.push(applyOperator(op, b1));
                } else {
                    bool b2 = operands.top(); operands.pop();
                    operands.push(applyOperator(op, b2, b1));
                }
            }
            operators.push(c);
        }
    }

    // xu ly cac toan tu con lai
    while (!operators.empty()) {
        char op = operators.top();
        operators.pop();

        bool b1 = operands.top(); operands.pop();
        if (op == '!') {
            operands.push(applyOperator(op, b1));
        } else {
            bool b2 = operands.top(); operands.pop();
            operands.push(applyOperator(op, b2, b1));
        }
    }

    return operands.top();
}

int main() {
    string expression;
    cout << "Nhap bieu thuc logic: ";
    getline(cin, expression);

    // kiem tra tinh hop le
    if (!isValidExpression(expression)) {
        cout << "Bieu thuc khong hop le!" << endl;
        return 1;
    }

    unordered_map<char, bool> variables;
    cout <<"Bieu thuc hop le! ";
    cout << "Nhap cac bien logic va gia tri cua chung : false 0, true 1 " << endl;
    cout << "Nhap 'x' de ket thuc." << endl;

    while (true) {
        char var;
        int val;
        cin >> var;
        if (var == 'x') break;
        cin >> val;
        variables[var] = (val != 0);
    }

    try {
        bool result = evaluateExpression(expression, variables);
        cout << "Ket qua cua bieu thuc: " << (result ? "True" : "False") << endl;
    } catch (const exception &e) {
        cout << "Loi: " << e.what() << endl;
    }

    return 0;
}

