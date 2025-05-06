#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <sstream>
#include <cctype>
#include <algorithm>

using namespace std;

// ------------------- HÀM XỬ LÝ SỐ LỚN -------------------

string deleteleading0(const string& numb) {
    int i = 0;
    while (i < numb.size() - 1 && numb[i] == '0') {
        i++;
    }
    return numb.substr(i);
}

string add(string a, string b) {
    string kq = "";
    int remb = 0;
    int dig_sum;
    int d_a = a.size();
    int d_b = b.size();

    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());

    for (int i = 0; i < max(d_a, d_b); i++) {
        int dig_a = 0;
        int dig_b = 0;
        if (i < d_a) {
            dig_a = a[i] - '0';
        }
        if (i < d_b) {
            dig_b = b[i] - '0';
        }
        dig_sum = dig_a + dig_b + remb;
        remb = dig_sum / 10;
        kq += (dig_sum % 10) + '0';
    }

    if (remb != 0) {
        kq += remb + '0';
    }

    reverse(kq.begin(), kq.end());

    return deleteleading0(kq);
}

bool isSmaller(string a, string b) {
    a = deleteleading0(a);
    b = deleteleading0(b);
    if (a.size() != b.size()) {
        return a.size() < b.size();
    }
    return a < b;
}

string subtract(string a, string b) {
    if (a[0] == '-' && b[0] != '-') {
        return "-" + add(a.substr(1), b);
    }
    if (a[0] != '-' && b[0] == '-') {
        return add(a, b.substr(1));
    }
    if (a[0] == '-' && b[0] == '-') {
        return subtract(b.substr(1), a.substr(1));
    }

    if (isSmaller(a, b)) {
        return "-" + subtract(b, a);
    }

    string kq = "";
    int remb = 0;
    int d_a = a.size();
    int d_b = b.size();

    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());

    for (int i = 0; i < d_a; i++) {
        int dig_a = a[i] - '0';
        int dig_b = 0;
        if (i < d_b) {
            dig_b = b[i] - '0';
        }
        int dig_sub = dig_a - dig_b - remb;
        if (dig_sub < 0) {
            dig_sub += 10;
            remb = 1;
        }
        else {
            remb = 0;
        }
        kq += dig_sub + '0';
    }

    reverse(kq.begin(), kq.end());

    return deleteleading0(kq);
}

string multiply(string a, string b) {
    bool isNeg = false;

    if (a[0] == '-') {
        isNeg = !isNeg;
        a = a.substr(1);
    }

    if (b[0] == '-') {
        isNeg = !isNeg;
        b = b.substr(1);
    }

    int d_a = a.size();
    int d_b = b.size();
    vector<int> kq(d_a + d_b, 0);

    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());

    for (int i = 0; i < d_a; i++) {
        for (int j = 0; j < d_b; j++) {
            kq[i + j] += (a[i] - '0') * (b[j] - '0');
        }
    }

    for (int i = 0; i < kq.size(); i++) {
        if (kq[i] >= 10) {
            if (i + 1 < kq.size()) {
                kq[i + 1] += kq[i] / 10;
            }
            kq[i] %= 10;
        }
    }

    while (kq.size() > 1 && kq.back() == 0) {
        kq.pop_back();
    }

    string kqStr;
    for (int i = kq.size() - 1; i >= 0; i--) {
        kqStr += kq[i] + '0';
    }

    if (isNeg) {
        return "-" + kqStr;
    }
    else {
        return kqStr;
    }
}

string divide(string a, string b) {
    if (deleteleading0(b) == "0") {
        return "DIVIDE_BY_ZERO";
    }

    bool isNeg = false;

    if (a[0] == '-') {
        isNeg = !isNeg;
        a = a.substr(1);
    }

    if (b[0] == '-') {
        isNeg = !isNeg;
        b = b.substr(1);
    }

    string kq = "";
    string cl = "";

    for (int i = 0; i < a.size(); i++) {
        cl += a[i];
        cl = deleteleading0(cl);
        int count = 0;
        while (!isSmaller(cl, b)) {
            cl = subtract(cl, b);
            count++;
        }
        kq += (count + '0');
    }

    kq = deleteleading0(kq);

    if (isNeg && kq != "0") {
        return "-" + kq;
    }
    else {
        return kq;
    }
}

// ------------------- BIỂU THỨC VÀ HẬU TỐ -------------------

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

vector<string> tokenize(string expr) {
    vector<string> tokens;
    int i = 0;
    int n = expr.length();

    while (i < n) {
        if (isspace(expr[i])) {
            i++;
        }
        else if (expr[i] == '-' && (i == 0 || expr[i - 1] == '(' || isOperator(expr[i - 1]))) {
            string num = "-";
            i++;
            while (i < n && isdigit(expr[i])) {
                num += expr[i++];
            }
            tokens.push_back(num);
        }
        else if (isdigit(expr[i])) {
            string num;
            while (i < n && isdigit(expr[i])) {
                num += expr[i++];
            }
            tokens.push_back(num);
        }
        else if (isOperator(expr[i]) || expr[i] == '(' || expr[i] == ')') {
            tokens.push_back(string(1, expr[i]));
            i++;
        }
        else {
            tokens.push_back("INVALID");
            break;
        }
    }
    return tokens;
}

vector<string> infixToPostfix(vector<string> tokens) {
    vector<string> output;
    stack<string> operators;

    for (int i = 0; i < tokens.size(); i++) {
        string token = tokens[i];

        if (isdigit(token[0]) || (token[0] == '-' && token.size() > 1)) {
            output.push_back(token);
        }
        else if (token == "(") {
            operators.push(token);
        }
        else if (token == ")") {
            while (!operators.empty() && operators.top() != "(") {
                output.push_back(operators.top());
                operators.pop();
            }
            if (!operators.empty()) {
                operators.pop();
            }
        }
        else if (isOperator(token[0])) {
            while (!operators.empty() && precedence(operators.top()[0]) >= precedence(token[0])) {
                output.push_back(operators.top());
                operators.pop();
            }
            operators.push(token);
        }
    }

    while (!operators.empty()) {
        output.push_back(operators.top());
        operators.pop();
    }

    return output;
}

string evalPostfix(vector<string> tokens) {
    stack<string> s;

    for (int i = 0; i < tokens.size(); i++) {
        string token = tokens[i];

        if (isdigit(token[0]) || (token[0] == '-' && token.size() > 1)) {
            s.push(token);
        }
        else if (isOperator(token[0])) {
            if (s.size() < 2) return "ERROR";

            string b = s.top();
            s.pop();
            string a = s.top();
            s.pop();
            string kq;

            if (token == "+") kq = add(a, b);
            else if (token == "-") kq = subtract(a, b);
            else if (token == "*") kq = multiply(a, b);
            else if (token == "/") kq = divide(a, b);

            if (kq == "DIVIDE_BY_ZERO") return "ERROR";
            s.push(kq);
        }
    }

    return s.size() == 1 ? s.top() : "ERROR";
}

// ------------------- HÀM MAIN -------------------

int main() {
    ifstream infile("tests.txt");
    ofstream outfile("output_24120226.txt");

    if (!infile) {
        cerr << "Failed to open input file: tests.txt\n";
        return 1;
    }

    if (!outfile) {
        cerr << "Failed to open output file: output_24120226.txt\n";
        return 1;
    }

    string line;
    while (getline(infile, line)) {
        vector<string> tokens = tokenize(line);
        if (tokens.empty() || tokens[0] == "INVALID") {
            cout << "ERROR\n";
            outfile << "ERROR\n";
            continue;
        }

        vector<string> postfix = infixToPostfix(tokens);
        string kq = evalPostfix(postfix);

        outfile << kq << "\n";
    }
    cout << "Open output file!" << endl;

    return 0;
}
