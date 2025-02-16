#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>

using namespace std;


struct Node {
    char data;
    int freq;
    Node *left, *right;

    Node(char data, int freq) {
        this->data = data;
        this->freq = freq;
        left = right = nullptr;
    }
};


struct Compare {
    bool operator()(Node* left, Node* right) {
        return left->freq > right->freq;
    }
};


void thegenerateHuffmanCodes(Node* root, string code) {
    if (root == nullptr) return;

    
    if (root->data != '$') {
        cout << code << " ";
    }

    
    thegenerateHuffmanCodes(root->left, code + "0");
    thegenerateHuffmanCodes(root->right, code + "1");
}


void thehuffmanCodes(const string& S, const vector<int>& f) {
    priority_queue<Node*, vector<Node*>, Compare> minHeap;

    
    for (int i = 0; i < S.size(); i++) {
        minHeap.push(new Node(S[i], f[i]));
    }

    
    while (minHeap.size() > 1) {
        Node* left = minHeap.top(); minHeap.pop();
        Node* right = minHeap.top(); minHeap.pop();

        Node* internalNode = new Node('$', left->freq + right->freq);
        internalNode->left = left;
        internalNode->right = right;

        minHeap.push(internalNode);
    }

    
    Node* root = minHeap.top();
    thegenerateHuffmanCodes(root, "");
    cout << endl;
}

int main() {
    string S;
    int n;

   
    cout << "Enter the string of distinct characters: ";
    cin >> S;
    n = S.size();

    vector<int> f(n);
    cout << "Enter the frequencies of the characters: \n";
    for (int i = 0; i < n; i++) {
        cout << "Frequency of '" << S[i] << "': ";
        cin >> f[i];
    }

   
    thehuffmanCodes(S, f);

    return 0;
}
