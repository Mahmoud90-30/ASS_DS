#include <iostream>
#include <string>
#include <cctype>
using namespace std;

class Node {
public:
    int data;
    Node* next;
};

class Stack {
private:
    Node* top;

public:
    Stack() {
        top = NULL;
    }

    void push(int val) {
        Node* newNode = new Node;
        newNode->data = val;
        newNode->next = top;
        top = newNode;
    }

    int pop() {
        if (empty()) {
            cout << "Stack is empty!\n";
            return -1;
        }
        int val = top->data;
        Node* temp = top;
        top = top->next;
        delete temp;
        return val;
    }

    bool empty() {
        return top == NULL;
    }

    int peek() {
    if (empty()) {
        cout << "Stack is empty!\n";
        return -1;
    }
    return top->data;
    }
};


int evaluate(string s) {
    Stack st;

    int result = 0;
    int sign = 1;
    int num = 0;

    for (char c : s) {

        if (isdigit(c)) {
            num = num * 10 + (c - '0');
        }

        else if (c == '+') {
            result += sign * num;
            num = 0;
            sign = 1;
        }

        else if (c == '-') {
            result += sign * num;
            num = 0;
            sign = -1;
        }

        else if (c == '(') {
            st.push(result);
            st.push(sign);

            result = 0;
            sign = 1;
        }

        else if (c == ')') {
            result += sign * num;
            num = 0;

            result *= st.pop();
            result += st.pop(); 
        }
    }

    result += sign * num;
    return result;
}

int main() {

    string str;
    getline(cin, str);
    cout << evaluate(str) << endl;           

    return 0;
}