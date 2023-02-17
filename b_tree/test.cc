#include "b_tree.h"

int main() {
    BTree<int, 3> tree;
    tree.Insert(53);
    tree.Insert(139);
    tree.Insert(75);
    tree.Insert(49);
    tree.Insert(145);
    tree.Insert(36);
    tree.Insert(101);
    tree.PrintTree();
    return 0;
}