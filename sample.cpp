#include <iostream>
#include <stack>
#include <string>
using namespace std;

struct Node {
    int data;
    Node *left, *right;
};

// A function that allocates a new node 
Node* newNode(int data) {
    Node* node = new Node(); // Use new instead of malloc
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

// A function to find the index of the matching closing parenthesis
int checkIndex(const string& str, int si, int ei) {
    if (si > ei) return -1;
    stack<char> s;
    for (int i = si; i <= ei; i++) {
        if (str[i] == '(')
            s.push(str[i]);
        else if (str[i] == ')') {
            if (!s.empty() && s.top() == '(')
                s.pop();
        }
        if (s.empty())
            return i;
    }
    return -1;
}

// Function to construct the binary tree from the given string
Node* tree(const string& str, int si, int ei) {
    if (si > ei) return NULL;
    
    // Create the root node
    int num = 0;
    while (si < str.size() && (str[si]-'0') < 10 && (str[si]-'0') > 0)
    {
        num = num*10 + (str[si++] - '0');
    }
    Node* root = newNode(num); 
    // Check for left subtree
    if (si <= ei && str[si] == '(') {
        int index = checkIndex(str, si, ei);
        if (index != -1) {
            root->left = tree(str, si + 1, index - 1);
            root->right = tree(str, index + 1, ei - 1);
        }
    }
    
    return root;
}

// Inorder traversal of the tree
void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

int main() {
    string s =  "23(10(9(7)())(15(11)(17)))(45(30)(67))";
    Node* root = tree(s, 0, s.size() - 1);
    inorder(root);
    cout << endl;
    return 0;
}
