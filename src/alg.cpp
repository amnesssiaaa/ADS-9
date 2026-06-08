// Copyright 2022 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  "tree.h"

std::vector<std::vector<char>> getAllPerms(PMTree& tree) {
    std::vector<std::vector<char>> result;
    std::vector<char> current;
    tree.collectPermutations(tree.getRoot(), current, result);
    return result;
}
std::vector<char> getPerm1(PMTree& tree, int num) {
    if (num <= 0) return {};
    int totalPerms = tree.countPermutationsInSubtree(tree.getRoot());
    if (num > totalPerms) return {};
    std::vector<char> result;
    int counter = 0;
    bool found = false;
    tree.getPermByCounting(tree.getRoot(), counter, num, result, found);
    return found ? result : std::vector<char>{};
}

std::vector<char> getPerm2(PMTree& tree, int num) {
    if (num <= 0) return {};
    Node* current = tree.getRoot();
    std::vector<char> result;
    while (current != nullptr && !current->children.empty()) {
        for (Node* child : current->children) {
            int count = tree.countPermutationsInSubtree(child);
            if (num <= count) {
                if (child->value != '\0') {
                    result.push_back(child->value);
                }
                current = child;
                break;
            } else {
                num -= count;
            }
        }
    }
    return result;
}
