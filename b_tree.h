#pragma once

#include <iostream>
#include <vector>
#include <algorithm>

template<typename T, uint8_t M>
struct BTreeNode {
  uint8_t key_num;
  T keys[M - 1];
  BTreeNode<T, M>* parent;
  BTreeNode<T, M>* childs[M];
};

// 性质：
// 1. 根节点至少有两个孩子
// 2. 每个分支节点有k个孩子和k-1个关键字

template<typename T, uint8_t M>
class BTree {
public:

  BTree() {
    T keys[M - 1];
    BTreeNode<T, M>* childs[M];
    root_ = NewNode(0, keys, nullptr, childs);
  }

  static BTreeNode<T, M>* NewNode(uint8_t key_num, T keys[M - 1], BTreeNode<T, M>* parent, BTreeNode<T, M>* childs[M]) {
    return new BTreeNode<T, M>{key_num, keys, parent, childs};
  }

  std::pair<BTreeNode<T, M>*, int> Search(T key) {
    if (root_->key_num == 0) return {root_, -1};
    BTreeNode<T, M>* work = root_;
    BTreeNode<T, M>* work_parent = nullptr;
    while (work != nullptr) {
        for (int i = 0; i < work->key_num; i++) {
            if (key == work->keys[i]) {
                return {work, i};
            } else if (key < work->keys[i]) {
                work_parent = work;
                work = work->childs[i];
                break;
            }
            if (i == work->key_num - 1) {
                work_parent = work;
                work = childs[i + 1];
            }
        }
    }
    return {work_parent, -1};
  }

  void Insert(T key) {
    if (Search(key).second != -1) return;
    BTreeNode<T, M>* insert_place = Search(key).first;
    if (insert_place->key_num < M - 1) {
        insert_place->keys[key_num] = key;
        key_num++;
        std::sort(insert_place->keys.begin(), insert_place->keys.begin() + key_num);
    } else {
        
    }
  }
private:
  BTreeNode<T, M>* root_;

};