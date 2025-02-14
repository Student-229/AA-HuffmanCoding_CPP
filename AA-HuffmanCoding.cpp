#include <iostream>
#include <queue>
#include <vector>
#include <map>

using namespace std;

// Huffman Tree Node Structure
class HuffmanNode {
public:
    char symbol;
    int frequency;
    HuffmanNode *leftChild, *rightChild;

    // Constructor for HuffmanNode
    HuffmanNode(char s, int f) {
        symbol = s;
        frequency = f;
        leftChild = rightChild = nullptr;
    }
};

// Custom comparator for priority queue
struct CompareNodes {
    bool operator()(HuffmanNode* first, HuffmanNode* second) {
        return first->frequency > second->frequency;  // Min-Heap (smallest frequency first)
    }
};

// Function to construct the Huffman Tree
HuffmanNode* constructHuffmanTree(const string &symbols, const vector<int> &freqList) {
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, CompareNodes> minHeap;

    // Insert all characters into the priority queue
    for (size_t i = 0; i < symbols.length(); i++) {
        minHeap.push(new HuffmanNode(symbols[i], freqList[i]));
    }

    // Constructing the Huffman Tree
    while (minHeap.size() > 1) {
        HuffmanNode* leftNode = minHeap.top(); minHeap.pop();
        HuffmanNode* rightNode = minHeap.top(); minHeap.pop();

        // Merge two nodes
        HuffmanNode* parentNode = new HuffmanNode('#', leftNode->frequency + rightNode->frequency);
        parentNode->leftChild = leftNode;
        parentNode->rightChild = rightNode;

        minHeap.push(parentNode);
    }

    // The root of the Huffman Tree
    return minHeap.top();
}

// Function to generate Huffman Codes using Preorder Traversal
void generateCodes(HuffmanNode* rootNode, string currentCode, map<char, string> &huffmanCodes) {
    if (!rootNode) return;

    // If leaf node, assign the Huffman Code
    if (!rootNode->leftChild && !rootNode->rightChild) {
        huffmanCodes[rootNode->symbol] = currentCode;
    }

    // Recursive Traversal (Preorder)
    generateCodes(rootNode->leftChild, currentCode + "0", huffmanCodes);
    generateCodes(rootNode->rightChild, currentCode + "1", huffmanCodes);
}

// Function to print Huffman codes in Preorder Traversal
void printHuffmanCodes(HuffmanNode* rootNode) {
    map<char, string> huffmanMap;
    generateCodes(rootNode, "", huffmanMap);

    cout << "Huffman Codes (Preorder Traversal Order):" << endl;
    for (const auto &entry : huffmanMap) {
        cout << entry.first << ": " << entry.second << endl;
    }
}

// Main function
int main() {
    string inputSymbols = "abcdef";
    vector<int> frequencyList = {5, 9, 12, 13, 16, 45};

    // Build Huffman Tree
    HuffmanNode* huffmanRoot = constructHuffmanTree(inputSymbols, frequencyList);

    // Print Huffman Codes in Preorder Traversal Order
    printHuffmanCodes(huffmanRoot);

    return 0;
}
