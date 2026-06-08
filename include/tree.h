// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_
#include <vector>
#include <algorithm>

struct Node {
    char value;
    std::vector<Node*> children;
    std::vector<char> neighbors;
    Node(char val) : value(val) {}
    ~Node() {
        for (Node* child : children) {
            delete child;
        }
    }
};

class PMTree {
private:
    Node* root;
    std::vector<char> initialElements;
    void buildTree(Node* node, std::vector<char> remaining);
    void collectPermutations(Node* node, std::vector<char>& current, 
                              std::vector<std::vector<char>>& result);
    void getPermByCounting(Node* node, int& counter, int targetNum, 
                           std::vector<char>& result, bool& found);
    int countPermutationsInSubtree(Node* node);

public:
    PMTree(const std::vector<char>& elements);
    ~PMTree();
    Node* getRoot() const { return root; }
    std::vector<char> getInitialElements() const { return initialElements; }
    friend std::vector<std::vector<char>> getAllPerms(PMTree& tree);
    friend std::vector<char> getPerm1(PMTree& tree, int num);
    friend std::vector<char> getPerm2(PMTree& tree, int num);
};
std::vector<std::vector<char>> getAllPerms(PMTree& tree);
std::vector<char> getPerm1(PMTree& tree, int num);
std::vector<char> getPerm2(PMTree& tree, int num);

#endif  // INCLUDE_TREE_H_
