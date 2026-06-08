// Copyright 2022 NNTU-CS
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <locale>
#include <vector>

#include "tree.h"


    for (Node* child : children) {
        delete child;
    }
}

PMTree::PMTree(const std::vector<char>& elements) : initialElements(elements) {
    root = new Node('\0');
    buildTree(root, elements);
}

PMTree::~PMTree() {
    delete root;
}

Node* PMTree::getRoot() const {
    return root;
}

std::vector<char> PMTree::getInitialElements() const {
    return initialElements;
}

void PMTree::buildTree(Node* node, std::vector<char> remaining) {
    if (remaining.empty()) return;

    std::sort(remaining.begin(), remaining.end());
    node->neighbors = remaining;

    for (char elem : remaining) {
        Node* child = new Node(elem);
        node->children.push_back(child);

        std::vector<char> newRemaining;
        for (char c : remaining) {
            if (c != elem) newRemaining.push_back(c);
        }
        buildTree(child, newRemaining);
    }
}

void PMTree::collectPermutations(Node* node, std::vector<char>& current,
                                   std::vector<std::vector<char>>& result) {
    if (node->value != '\0') current.push_back(node->value);

    if (node->children.empty()) {
        result.push_back(current);
    } else {
        for (Node* child : node->children) {
            collectPermutations(child, current, result);
        }
    }

    if (node->value != '\0') current.pop_back();
}

int PMTree::countPermutations(Node* node) {
    if (node->children.empty()) return 1;
    int count = 0;
    for (Node* child : node->children) {
        count += countPermutations(child);
    }
    return count;
}

void PMTree::getPermByOrder(Node* node, int& counter, int target,
                             std::vector<char>& result, bool& found) {
    if (found) return;

    if (node->value != '\0') result.push_back(node->value);

    if (node->children.empty()) {
        counter++;
        if (counter == target) found = true;
        return;
    }

    for (Node* child : node->children) {
        getPermByOrder(child, counter, target, result, found);
        if (found) return;
    }

    if (node->value != '\0') result.pop_back();
}

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
    return getPerm1(num);
}

std::vector<std::vector<char>> getAllPerms(PMTree& tree) {
    return tree.getAllPerms();
}

std::vector<char> getPerm1(PMTree& tree, int num) {
    return tree.getPerm1(num);
}

std::vector<char> getPerm2(PMTree& tree, int num) {
    return tree.getPerm2(num);
}
