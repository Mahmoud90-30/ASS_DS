#include <iostream>
#include <string>
#include <vector>
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

class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        int n = nums.size();
        vector<int> res(n, -1);

        Stack st; 

        for (int i = 2 * n - 1; i >= 0; i--) {

            int idx = i % n;

            while (!st.empty() && nums[st.peek()] <= nums[idx]) {
                st.pop();
            }

            if (i < n) {
                if (!st.empty()) {
                    res[idx] = nums[st.peek()];
                }
            }

            st.push(idx);
        }

        return res;
    }
};

class ExpressionEvaluator {
private:
    Stack st;
    int result;
    int sign;
    int num;

public:
    ExpressionEvaluator() {
        result = 0;
        sign = 1;
        num = 0;
    }

    int evaluate(string s) {

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
};

int main() {
// ========================================================Q1

    // ExpressionEvaluator Ex;
    // string str;
    // getline(cin, str);
    // cout << Ex.evaluate(str) << endl;
    
    // ========================================================Q2
    
    // Solution sol;

    // vector<int> nums1 = {1, 2, 1};
    // vector<int> ans1 = sol.nextGreaterElements(nums1);

    // for (int x : ans1) cout << x << " ";
    // cout << endl;

    // vector<int> nums2 = {1, 2, 3, 4, 3};
    // vector<int> ans2 = sol.nextGreaterElements(nums2);

    // for (int x : ans2) cout << x << " ";
    // cout << endl;
    
    return 0;
}
