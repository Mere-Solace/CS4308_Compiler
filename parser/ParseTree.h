#include <string>
#include <vector>
#include <iostream>

class ParseTreeNode {
public:
    std::string value;
    std::vector<ParseTreeNode*> children;

    ParseTreeNode(std::string val) : value(val) {}

    void addChild(ParseTreeNode* child) {
        children.push_back(child);
    }
};

class ParseTree {
public:
    ParseTreeNode* root;

    ParseTree() : root(nullptr) {}

    void setRoot(ParseTreeNode* node) {
        root = node;
    }

    void printTree(ParseTreeNode* node, int depth = 0) {
        if (node == nullptr) return;
        for (int i = 0; i < depth; i++) {
            std::cout << "   ";
        }
        std::cout << node->value << std::endl;
        for (ParseTreeNode* child : node->children) {
            printTree(child, depth + 1);
        }
    }
};