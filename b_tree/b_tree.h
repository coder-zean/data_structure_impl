#pragma once
#include <algorithm>
#include <deque>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

template <typename T, uint8_t M>
struct BTreeNode {
  uint32_t key_num;
  T* keys;
  BTreeNode<T, M>* parent;
  BTreeNode<T, M>** childs;

  BTreeNode() {
    key_num = 0;
    keys = new T[M];  // 最后一个位置只用于分裂时用
    parent = nullptr;
    childs = new BTreeNode<T, M>*[M + 1];  // 最后一个位置只用于分裂时用
  }
};

// 性质：
// 1. 根节点至少有两个孩子
// 2. 每个分支节点有k个孩子和k-1个关键字

template <typename T, uint8_t M>
class BTree {
public:
  BTree() { root_ = new BTreeNode<T, M>; }

  std::pair<BTreeNode<T, M>*, int> Search(T key) {
    if (root_->key_num == 0) return {root_, -1};
    BTreeNode<T, M>* work = root_;
    BTreeNode<T, M>* work_parent = nullptr;
    while (work != nullptr) {
      int num = work->key_num;
      for (int i = 0; i < num; i++) {
        if (key == work->keys[i]) {
          return {work, i};
        } else if (key < work->keys[i]) {
          work_parent = work;
          work = work->childs[i];
          break;
        }
        if (i == work->key_num - 1) {
          work_parent = work;
          work = work->childs[i + 1];
        }
      }
    }
    return {work_parent, -1};
  }

  void Insert(T key) {
    if (Search(key).second != -1) return;
    BTreeNode<T, M>* insert_place = Search(key).first;
    if (insert_place->key_num == 0) {
      insert_place->keys[0] = key;
      insert_place->key_num++;
      return;
    }
    for (int i = insert_place->key_num - 1; i >= 0; i--) {
      if (insert_place->keys[i] > key) {
        insert_place->keys[i + 1] = insert_place->keys[i];
      } else {
        insert_place->keys[i + 1] = key;
        break;
      }
      if (i == 0) {
        insert_place->keys[0] = key;
      }
    }
    insert_place->key_num++;
    if (insert_place->key_num == M) {  // 需要进行分裂
      fission(insert_place);
    }
  }

  void PrintTree() {
    deque<BTreeNode<T, M>*> bfs = {root_};
    while (!bfs.empty()) {
      int sz = bfs.size();
      for (int i = 0; i < sz; i++) {
        BTreeNode<T, M>* node = bfs.front();
        bfs.pop_front();
        for (int j = 0; j < node->key_num; j++) {
          cout << node->keys[j] << " ";
          if (node->childs[j] != nullptr) {
            bfs.push_back(node->childs[j]);
          }
        }
        if (node->childs[node->key_num] != nullptr) {
          bfs.push_back(node->childs[node->key_num]);
        }
        cout << " |==| ";
      }
      cout << endl;
    }
  }

private:
  BTreeNode<T, M>* root_;

  // 分裂操作
  void fission(BTreeNode<T, M>* node) {
    // 将原始节点分裂成两个节点
    int new_node_key_num = M - M / 2 - 1;
    BTreeNode<T, M>* new_node = new BTreeNode<T, M>;
    for (int i = M / 2 + 1, j = 0; i < M; i++, j++) {
      new_node->keys[j] = node->keys[i];
      new_node->childs[j] = node->childs[i];
    }
    new_node->childs[new_node_key_num] = node->childs[M];
    new_node->key_num = new_node_key_num;
    node->key_num = M / 2;

    BTreeNode<T, M>* parent = node->parent;
    // 没有父节点时，新建父节点作为分裂出来的两个节点的父节点
    if (parent == nullptr) {
      BTreeNode<T, M>* new_parent_node = new BTreeNode<T, M>;
      new_parent_node->keys[0] = node->keys[M / 2];
      new_parent_node->key_num = 1;
      new_parent_node->childs[0] = node;
      new_parent_node->childs[1] = new_node;
      root_ = new_parent_node;
      node->parent = root_;
      new_node->parent = root_;
      return;
    }
    uint32_t parent_key_num = parent->key_num;
    new_node->parent = parent;
    for (int i = parent_key_num - 1; i >= 0; --i) {
      if (parent->keys[i] > node->keys[M / 2]) {
        parent->keys[i + 1] = parent->keys[i];
        parent->childs[i + 2] = parent->childs[i + 1];
      } else {
        parent->keys[i + 1] = node->keys[M / 2];
        parent->childs[i + 2] = new_node;
        break;
      }
      if (i == 0) {
        parent->keys[0] = node->keys[M / 2];
        parent->childs[1] = new_node;
      }
    }
    parent->key_num++;
    if (parent->key_num == M) {
      fission(parent);
    }
  }
};