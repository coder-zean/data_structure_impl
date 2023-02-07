#include "rb_tree.h"

int main() {
    RBTree<int> rb_tree;
    int arr[] = {10, 2, 3, 9, 12, 21};
    for (int i : arr) {
        rb_tree.Insert(i);
    }

    rb_tree.PrintTree();
    rb_tree.Delete(10);
    rb_tree.PrintTree();
    rb_tree.Delete(21);
    rb_tree.PrintTree();
    rb_tree.Delete(2);
    rb_tree.PrintTree();
    return 0;
}