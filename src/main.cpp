// Copyright 2022 NNTU-CS
#include "tree.h"

#include <chrono>
#include <iostream>
#include <random>
#include <vector>

int main() {
    std::vector<char> in = {'1', '2', '3'};
    PMTree tree(in);

    std::vector<std::vector<char>> perms = tree.getAllPerms();
    std::cout << "Все перестановки для 1,2,3:" << std::endl;
    for (size_t i = 0; i < perms.size(); ++i) {
        std::cout << i + 1 << ": ";
        for (size_t j = 0; j < perms[i].size(); ++j) {
            std::cout << perms[i][j];
        }
        std::cout << std::endl;
    }

    std::vector<char> p1 = tree.getPerm1(1);
    std::vector<char> p2 = tree.getPerm2(2);
    std::cout << "\ngetPerm1(1) = ";
    for (size_t i = 0; i < p1.size(); ++i) std::cout << p1[i];
    std::cout << "\ngetPerm2(2) = ";
    for (size_t i = 0; i < p2.size(); ++i) std::cout << p2[i];
    std::cout << std::endl;

    std::cout << "\nзамеры времени" << std::endl;
    std::cout << "n\tgetAllPerms\tgetPerm1\tgetPerm2" << std::endl;

    for (int n = 3; n <= 7; ++n) {
        std::vector<char> sym;
        for (int i = 1; i <= n; ++i) {
            sym.push_back('0' + i);
        }

        PMTree myTree(sym);

        auto start = std::chrono::high_resolution_clock::now();
        myTree.getAllPerms();
        auto end = std::chrono::high_resolution_clock::now();
        int64_t t1 = std::chrono::duration_cast<
            std::chrono::microseconds>(end - start).count();

        int fact = 1;
        for (int i = 1; i <= n; ++i) fact = fact * i;

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, fact);
        int rnum = dis(gen);

        start = std::chrono::high_resolution_clock::now();
        myTree.getPerm1(rnum);
        end = std::chrono::high_resolution_clock::now();
        int64_t t2 = std::chrono::duration_cast<
            std::chrono::microseconds>(end - start).count();

        start = std::chrono::high_resolution_clock::now();
        myTree.getPerm2(rnum);
        end = std::chrono::high_resolution_clock::now();
        int64_t t3 = std::chrono::duration_cast<
            std::chrono::microseconds>(end - start).count();

        std::cout << n << "\t" << t1 << "\t\t" << t2 << "\t\t" << t3
                  << std::endl;
    }

    return 0;
}
