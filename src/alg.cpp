// Copyright 2022 NNTU-CS
#include  "tree.h"

#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include <algorithm>
#include <vector>

std::vector<std::vector<char>> PMTree::getAllPerms() {
    std::vector<std::vector<char>> result;
    std::vector<char> current;
    collectPermutations(root, current, result);
    return result;
}

std::vector<char> PMTree::getPerm1(int num) {
    if (num <= 0) return {};

    int total = countPermutations(root);
    if (num > total) return {};

    std::vector<char> result;
    int counter = 0;
    bool found = false;
    getPermByOrder(root, counter, num, result, found);

    return result;
}

std::vector<char> PMTree::getPerm2(int num) {
    if (num <= 0) return {};

    Node* cur = root;
    std::vector<char> result;

    while (cur != nullptr && !cur->children.empty()) {
        for (Node* child : cur->children) {
            int cnt = countPermutations(child);

            if (num <= cnt) {
                if (child->value != '\0') {
                    result.push_back(child->value);
                }
                cur = child;
                break;
            } else {
                num -= cnt;
            }
        }
    }

    return result;
}
