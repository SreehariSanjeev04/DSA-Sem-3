#include <iostream>
#include <stack>
#include <string>

using namespace std;

struct Node {
    int val;
    Node* left;
    Node* right;
    Node(int value) : val(value), left(nullptr), right(nullptr) {}
};

Node* constructBinaryTree(const string& s, int *start) {
    if (s.empty() || *start >= s.size()) return nullptr;

    // Parsing the number
    int num = 0;
    while (*start < s.size() && s[*start] != '(' && s[*start] != ')') {
        num = num * 10 + s[*start] - '0';
        ++*start;
    }

    Node* root = new Node(num);

    // Process the left subtree
    if (*start < s.size() && s[*start] == '(') {
        ++*start;
        root->left = constructBinaryTree(s, start);
    }

    // Process the right subtree
    if (*start < s.size() && s[*start] == ')') {
        ++*start;
    }
    if (*start < s.size() && s[*start] == '(') {
        ++*start;
        root->right = constructBinaryTree(s, start);
    }
    
    if (*start < s.size() && s[*start] == ')') {
        ++*start;
    }

    return root;
}

void preorder(Node* root) {
    if (root == nullptr) return;
    cout << root->val << " ";
    preorder(root->left);
    preorder(root->right);
}

int main() {
    string str = "4(2(3)(1))(6(5))";
    int start = 0;
    Node* root = constructBinaryTree(str, &start);
    preorder(root);
    cout << endl;
    return 0;
}
