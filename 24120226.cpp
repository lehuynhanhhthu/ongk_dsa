#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <sstream>
#include <cctype>
#include <algorithm>

using namespace std;

// ------------------- HÀM XỬ LÝ SỐ LỚN -------------------

string removeLeadingZeros(const string& num) {
    int i = 0;
    while (i < num.size() - 1 && num[i] == '0') i++;
    return num.substr(i);
}

string add(string a, string b) {
    string result = "";
    int carry = 0, sum;
    int n1 = a.size(), n2 = b.size();
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());

    for (int i = 0; i < max(n1, n2); ++i) {
        int digit1 = i < n1 ? a[i] - '0' : 0;
        int digit2 = i < n2 ? b[i] - '0' : 0;
        sum = digit1 + digit2 + carry;
        carry = sum / 10;
        result += (sum % 10) + '0';
    }
    if (carry) result += carry + '0';
    reverse(result.begin(), result.end());
    return removeLeadingZeros(result);
}

bool isSmaller(string a, string b) {
    a = removeLeadingZeros(a);
    b = removeLeadingZeros(b);
    if (a.size() != b.size()) return a.size() < b.size();
    return a < b;
}

string subtract(string a, string b) {
    // xử lý số âm
    if (a[0] == '-' && b[0] != '-') return "-" + add(a.substr(1), b);
    if (a[0] != '-' && b[0] == '-') return add(a, b.substr(1));
    if (a[0] == '-' && b[0] == '-') return subtract(b.substr(1), a.substr(1));

    if (isSmaller(a, b)) return "-" + subtract(b, a);

    string result = "";
    int carry = 0;
    int n1 = a.size(), n2 = b.size();
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());

    for (int i = 0; i < n1; ++i) {
        int digit1 = a[i] - '0';
        int digit2 = i < n2 ? b[i] - '0' : 0;
        int sub = digit1 - digit2 - carry;
        if (sub < 0) {
            sub += 10;
            carry = 1;
        }
        else carry = 0;
        result += sub + '0';
    }
    reverse(result.begin(), result.end());
    return removeLeadingZeros(result);
}

string multiply(string a, string b) {
    bool negative = false;
    if (a[0] == '-') {
        negative = !negative;
        a = a.substr(1);
    }
    if (b[0] == '-') {
        negative = !negative;
        b = b.substr(1);
    }

    int n = a.size(), m = b.size();
    vector<int> res(n + m, 0);

    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            res[i + j] += (a[i] - '0') * (b[j] - '0');

    for (int i = 0; i < res.size(); ++i) {
        if (res[i] >= 10) {
            if (i + 1 < res.size())
                res[i + 1] += res[i] / 10;
            res[i] %= 10;
        }
    }

    while (res.size() > 1 && res.back() == 0) res.pop_back();

    string result;
    for (int i = res.size() - 1; i >= 0; --i)
        result += res[i] + '0';

    return negative ? "-" + result : result;
}

string divide(string a, string b) {
    if (removeLeadingZeros(b) == "0") return "DIVIDE_BY_ZERO";

    bool negative = false;
    if (a[0] == '-') {
        negative = !negative;
        a = a.substr(1);
    }
    if (b[0] == '-') {
        negative = !negative;
        b = b.substr(1);
    }

    string result, remainder;
    for (char digit : a) {
        remainder += digit;
        remainder = removeLeadingZeros(remainder);
        int q = 0;
        while (!isSmaller(remainder, b)) {
            remainder = subtract(remainder, b);
            q++;
        }
        result += (q + '0');
    }

    result = removeLeadingZeros(result);
    return negative && result != "0" ? "-" + result : result;
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

vector<string> tokenize(const string& expr) {
    vector<string> tokens;
    int i = 0, n = expr.length();
    while (i < n) {
        if (isspace(expr[i])) {
            i++;
        }
        else if (expr[i] == '-' && (i == 0 || expr[i-1] == '(' || isOperator(expr[i-1]))) {
            // Dấu âm đứng đầu, sau '(' hoặc sau toán tử
            string num = "-";
            i++;
            while (i < n && isdigit(expr[i])) num += expr[i++];
            tokens.push_back(num);
        }
        else if (isdigit(expr[i])) {
            string num;
            while (i < n && isdigit(expr[i])) num += expr[i++];
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


vector<string> infixToPostfix(const vector<string>& tokens) {
    vector<string> output;
    stack<string> opStack;

    for (const string& token : tokens) {
        if (isdigit(token[0]) || (token[0] == '-' && token.size() > 1)) {
            output.push_back(token);
        }
        else if (token == "(") {
            opStack.push(token);
        }
        else if (token == ")") {
            while (!opStack.empty() && opStack.top() != "(") {
                output.push_back(opStack.top());
                opStack.pop();
            }
            if (!opStack.empty()) opStack.pop();
        }
        else if (isOperator(token[0])) {
            while (!opStack.empty() && precedence(opStack.top()[0]) >= precedence(token[0])) {
                output.push_back(opStack.top());
                opStack.pop();
            }
            opStack.push(token);
        }
    }

    while (!opStack.empty()) {
        output.push_back(opStack.top());
        opStack.pop();
    }

    return output;
}

string evalPostfix(const vector<string>& tokens) {
    stack<string> s;

    for (const string& token : tokens) {
        if (isdigit(token[0]) || (token[0] == '-' && token.size() > 1)) {
            s.push(token);
        }
        else if (isOperator(token[0])) {
            if (s.size() < 2) return "ERROR";
            string b = s.top(); s.pop();
            string a = s.top(); s.pop();
            string res;

            if (token == "+") res = add(a, b);
            else if (token == "-") res = subtract(a, b);
            else if (token == "*") res = multiply(a, b);
            else if (token == "/") res = divide(a, b);

            if (res == "DIVIDE_BY_ZERO") return "ERROR";
            s.push(res);
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
        string result = evalPostfix(postfix);
        
        outfile << result << "\n";
    }
    cout <<"Open output file!" <<endl;

    return 0;
}
