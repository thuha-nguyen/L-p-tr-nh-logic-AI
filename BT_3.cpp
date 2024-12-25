#include <iostream>
#include <vector>
#include <functional>
#include <sstream>
#include <string>

using namespace std;

// ham kiem tra logic vi tu
bool checkFormula(
    const vector<int>& domain,
    function<bool(int)> P,
    function<bool(int)> Q
) {
    
    for (int x : domain) {
        if (!( !P(x) || Q(x) )) {  // P(x) ? Q(x) là !P(x) || Q(x)
            return false;
        }
    }

    bool existsPart = false;
    for (int y : domain) {
        if (P(y)) {
            existsPart = true;
            break;
        }
    }

   
    return existsPart;
}

function<bool(int)> parseCondition(const string& condition) {
    return [condition](int x) {
        if (condition == "x > 1") return x > 1;
        else if (condition == "x % 2 == 0") return x % 2 == 0;
        else if (condition == "x % 2 != 0") return x % 2 != 0;
        else return false; // dieu kien khong hop le
    };
}

int main() {
    // domain
    vector<int> domain = {1, 2, 3};

    // Nhap dieu kien P(x)
    string p_condition;
    cout << "Nh?p di?u ki?n cho P(x) ";
    getline(cin, p_condition);

    // Nhap dieu kien Q(x)
    string q_condition;
    cout << "Nh?p di?u ki?n cho Q(x)  ";
    getline(cin, q_condition);

    
    function<bool(int)> P = parseCondition(p_condition);
    function<bool(int)> Q = parseCondition(q_condition);

    //cong thuc logic: ?x (P(x) ? Q(x)) ? ?y P(y)
    bool result = checkFormula(domain, P, Q);

    // ket qua
    if (result) {
        cout << "Công th?c dúng (True)" << endl;
    } else {
        cout << "Công th?c sai (False)" << endl;
    }

    return 0;
}
