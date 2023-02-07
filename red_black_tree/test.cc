#include "rb_tree.h"

int main() {
    RBTree<int> rb_tree;
    int arr[] = {10, 2, 3, 9, 12, 21};
    for (int i : arr) {
        rb_tree.Insert(i);
    }

    rb_tree.InOrder();
    rb_tree.Delete(10);
    rb_tree.InOrder();
    rb_tree.Delete(21);
    rb_tree.InOrder();
    rb_tree.Delete(3);
    rb_tree.InOrder();
    std::cout << rb_tree[2].key << std::endl;
    return 0;
}