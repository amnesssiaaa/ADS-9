// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_
#include <vector>

struct Node {
    char value;
    std::vector<Node*> children;
    std::vector<char> neighbors;     
    
    Node(char val) : value(val) {}
    ~Node();
};

class PMTree {
private:
    Node* root;
    std::vector<char> initialElements;
    void buildTree(Node* node, std::vector<char> remaining);
    void collectPermutations(Node* node, std::vector<char>& current, 
                              std::vector<std::vector<char>>& result);
    int countPermutations(Node* node);
    void getPermByOrder(Node* node, int& counter, int target, 
                        std::vector<char>& result, bool& found);
public:
    PMTree(const std::vector<char>& elements);
    ~PMTree();
    Node* getRoot() const;
    std::vector<char> getInitialElements() const;
    std::vector<std::vector<char>> getAllPerms();
    std::vector<char> getPerm1(int num);
    std::vector<char> getPerm2(int num);
};
#endif  // INCLUDE_TREE_H_
