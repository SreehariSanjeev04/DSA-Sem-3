#include<bits/stdc++.h>
using namespace std;
struct Node {
    int val;
    Node* left;
    Node* right;
    Node(int value) : val(value), left(nullptr), right(nullptr) {}
};
string ContructParathesis(Node* root) {
    if(!root) return "";
    string ans = "";
    ans.append(to_string(root->val));
    string leftSubtree = ContructParathesis(root->left);
    string rightSubtree = ContructParathesis(root->right);
    if(!leftSubtree.empty()) ans.append("(" + leftSubtree + ")");
    if(!rightSubtree.empty()) ans.append("(" + rightSubtree + ")");
    return ans;
}
void add(Node** root, Node* node) {
    if(!root) {
        *root = node;
        return;
    }
    Node* parent = NULL;
    Node* current = *root;
    while(current) {
        parent = current;
        if(current->val < node->val) current=current->right;
        else if(current->val > node->val) current=current->left;
    }
    //current is NULl;
    if(node->val > parent->val) parent->right = node;
    else parent->left = node;
}
int main() {
    return 0;
}