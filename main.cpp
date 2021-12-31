#include <iostream>
#include <string>
#include <stack>
#include <cmath>

using namespace std;
struct type {
    char xxx;
    double value;
};

bool foo(stack<type> &num, stack<type> &operations, type &result) {
    double x, y, z;
    y = num.top().value;
    num.pop();
    switch (operations.top().xxx) {
        case '+':
            if (!num.empty()) {
                x = num.top().value;
                num.pop();
                z = x + y;
                result.xxx = 'n';
                result.value = z;
            } else {
                result = {'n', y};
            }
            num.push(result);
            break;
        case '*':
            x = num.top().value;
            num.pop();
            z = x * y;
            result.xxx = 'n';
            result.value = z;
            num.push(result);
            break;
        case '-':
            z = y * -1;
            result.xxx = 'n';
            result.value = z;
            num.push(result);
            break;
        case '/':
            x = num.top().value;
            if (x == 0) {
                cerr << "Error: you can't divide by 0...";
                return false;
            }
            num.pop();
            z = x / y;
            result.xxx = 'n';
            result.value = z;
            num.push(result);
            break;
        case '^':
            x = num.top().value;
            if (x == 0 && y == 0) {
                cerr << "Error: you can't raise 0 to the power of 0...";
                return false;
            }
            num.pop();
            z = pow(x, y);
            result.xxx = 'n';
            result.value = z;
            num.push(result);
            break;
        case 'c':
            result.xxx = 'n';
            result.value = cos(y);
            num.push(result);
            break;
        case 's':
            result.xxx = 'n';
            result.value = sin(y);
            num.push(result);
            break;
        case 't':
            if (cos(y) == 0) {
                cerr << "Error: invalid argument for tg...";
                return false;
            }
            result.xxx = 'n';
            result.value = sin(y) / cos(y);
            num.push(result);
            break;
        case 'g':
            if (sin(y) == 0) {
                cerr << "Error: invalid argument for ctg...";
                return false;
            }
            result.xxx = 'n';
            result.value = cos(y) / sin(y);
            num.push(result);
            break;
        case 'e':
            result.xxx = 'n';
            result.value = exp(y);
            num.push(result);
            break;
        default:
            cerr << "Error operation...";
            return false;
    }
    operations.pop();
    return true;
}

int priority(char ch) {
    if (ch == '+') return 1;
    if (ch == '*' || ch == '/') return 2;
    if (ch == '^') return 3;
    if (ch == 'c' || ch == 's') return 5;
    if (ch == '-') return 4;
    return 0;
}

int main() {
    stack<type> operations;
    stack<type> num;
    char ch;
    double value;
    type n = {};
    cout << "Enter expression:\n";
    string str;
    getline(cin, str);
    double x;
    for (size_t i = 0; i < str.size(); i++) {
        if (str[i] == 'x' && str[i + 1] != 'p') {
            cout << "Enter x: ";
            cin >> x;
            break;
        }
    }
    while (!str.empty()) {
        ch = str[0];
        if (str[0] == 'x' && str[1] != 'p') {
            num.push({'n', x});
            str.erase(str.begin());
            continue;
        } else if (ch >= '0' && ch <= '9') {
            value = stod(str);
            n.xxx = 'n';
            n.value = value;
            num.push(n);
            while (str[0] >= '0' && str[0] <= '9' || str[0] == '.') {
                str.erase(str.begin());
            }
            continue;
        } else if (ch == '-') {
            if (str[1] == '*' || str[1] == '^' || str[1] == '-' || str[1] == '+' || str[1] == '/') {
                cout << "Error expression...";
                return -11;
            }
            while (!operations.empty() && operations.top().xxx != '+' && operations.top().xxx != '(')
                foo(num, operations, n);
            while (str[0] == '-' || str[0] == ' ') {
                str.erase(str.begin());
            }
            operations.push({'+', 0});
            operations.push({'-', 0});
            continue;
        } else if (str.substr(0, 3) == "cos") {
            if (str[3] == '*' || str[3] == '^' || str[3] == '-' || str[3] == '+' || str[3] == '/') {
                cout << "Error expression...";
                return -11;
            }
            n.xxx = 'c';
            n.value = 0;
            operations.push(n);
            str.erase(str.begin(), str.begin() + 3);
            continue;
        } else if (str.substr(0, 3) == "sin") {
            if (str[3] == '*' || str[3] == '^' || str[3] == '+' || str[3] == '/') {
                cout << "Error expression...";
                return -11;
            }
            n.xxx = 's';
            n.value = 0;
            operations.push(n);
            str.erase(str.begin(), str.begin() + 3);
            continue;
        } else if (str.substr(0, 2) == "tg") {
            if (str[2] == '*' || str[2] == '^' || str[2] == '-'  || str[2] == '+' || str[2] == '/') {
                cout << "Error expression...";
                return -11;
            }
            n.xxx = 't';
            n.value = 0;
            operations.push(n);
            str.erase(str.begin(), str.begin() + 2);
            continue;
        } else if (str.substr(0, 3) == "ctg"){
            if (str[3] == '*' || str[3] == '^' || str[3] == '+' || str[3] == '/') {
                cout << "Error expression...";
                return -11;
            }
            n.xxx = 'g';
            n.value = 0;
            operations.push(n);
            str.erase(str.begin(), str.begin() + 3);
            continue;
        } else if (str.substr(0, 3) == "exp") {
            if (str[3] == '*' || str[3] == '^' || str[3] == '-' || str[3] == '+' || str[3] == '/') {
                cout << "Error expression...";
                return -11;
            }
            n.xxx = 'e';
            n.value = 0;
            operations.push(n);
            str.erase(str.begin(), str.begin() + 3);
            continue;
        } else if (ch == '+' || ch == '*' || ch == '/' || ch == '(' || ch == '^') {
            if (ch != '(' && str[1] == '*' || str[0] == '-' || str[1] == '^' || str[1] == '+' || str[1] == '/') {
                cout << "Error expression...";
                return -11;
            }
            if (ch == '(' && str[1] == ')' || str[1] == '*' || str[1] == '^' || str[1] == '+' || str[1] == '/') {
                cout << "Error expression...";
                return -11;
            }
            while (!operations.empty() && priority(ch) <= priority(operations.top().xxx) && ch != '(') {
                foo(num, operations, n);
            }
            n.xxx = ch;
            n.value = 0;
            operations.push(n);
            str.erase(str.begin());
            continue;
        } else if (ch == ')') {
            while (operations.top().xxx != '(') {
                if (foo(num, operations, n) == 0) return -11;
            }
            str.erase(str.begin());
            operations.pop();
        } else if (ch == ' ') str.erase(str.begin());
        else {
            cerr << "Error expression...";
            return -3;
        }
    }
    while (!operations.empty()) {
        if (foo(num, operations, n) == 0) return -11;
    }
    cout << "Ans: " << num.top().value;
    return 0;
}

