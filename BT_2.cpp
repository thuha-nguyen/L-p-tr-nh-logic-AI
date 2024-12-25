#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <cmath>
#include <stack>

using namespace std;

// kiem tra tinh hop le cua bieu thuc
bool isValidExpression(const string &expr) {
    stack<char> s;
    for (char c : expr) {
        if (c == '(') {
            s.push(c);
        } else if (c == ')') {
            if (s.empty()) return false;
            s.pop();
        }
    }
    return s.empty();
}

// ham tim tat ca cac bien trong bieu thuc
unordered_set<char> getVariables(const string &expr) {
    unordered_set<char> variables;
    for (char c : expr) {
        if (isalpha(c)) {
            variables.insert(c);
        }
    }
    return variables;
}

//ham tinh gia tri cua bieu thuc logic
bool evaluateExpression(const string &expr, const unordered_map<char, bool> &values) {
    stack<bool> operands;
    stack<char> operators;

    auto applyOperator = [](bool a, bool b, char op) -> bool {
        if (op == '&') return a && b;
        if (op == '|') return a || b;
        if (op == '-') return !a; 
        return false;
    };

    for (size_t i = 0; i < expr.size(); ++i) {
        char c = expr[i];
        
        if (isspace(c)) continue; // bo khoang trang

        if (isalpha(c)) {
            operands.push(values.at(c));
        } else if (c == '(') {
            operators.push(c);
        } else if (c == ')') {
            while (!operators.empty() && operators.top() != '(') {
                char op = operators.top(); operators.pop();
                bool b = operands.top(); operands.pop();
                bool a = operands.top(); operands.pop();
                operands.push(applyOperator(a, b, op));
            }
            operators.pop(); // Bo dau ( khoi stack
        } else if (c == '&' || c == '|') {
            while (!operators.empty() && operators.top() != '(') {
                char op = operators.top(); operators.pop();
                bool b = operands.top(); operands.pop();
                bool a = operands.top(); operands.pop();
                operands.push(applyOperator(a, b, op));
            }
            operators.push(c);
        } else if (c == '-') { // toan tu NOT
            bool a = operands.top(); operands.pop();
            operands.push(!a);
        }
    }

    while (!operators.empty()) {
        char op = operators.top(); operators.pop();
        bool b = operands.top(); operands.pop();
        bool a = operands.top(); operands.pop();
        operands.push(applyOperator(a, b, op));
    }

    return operands.top();
}

// ham tao bang chan tri
void generateTruthTable(const string &expr) {
    if (!isValidExpression(expr)) {
        cout << "Bieu thuc khong hop le!" << endl;
        return;
    }

    unordered_set<char> variables = getVariables(expr);
    vector<char> varList(variables.begin(), variables.end());

size_t numVars = varList.size();
    size_t numRows = pow(2, numVars);

    // In bang
    for (char var : varList) {
        cout << var << " ";
    }
    cout << "KetQua" << endl;

    // To hop cac gia tri
    for (size_t i = 0; i < numRows; ++i) {
        unordered_map<char, bool> values;
        for (size_t j = 0; j < numVars; ++j) {
            bool value = (i & (1 << (numVars - j - 1))) != 0;
            values[varList[j]] = value;
            cout << (value ? "T " : "F ");
        }

        // tinh ket qua bieu thuc
        bool result = evaluateExpression(expr, values);
        cout << (result ? "T" : "F") << endl;
    }
}

int main() {
    string expression;

    cout << "Nhap bieu thuc logic: ";
    getline(cin, expression);

    generateTruthTable(expression);

    return 0;
}
