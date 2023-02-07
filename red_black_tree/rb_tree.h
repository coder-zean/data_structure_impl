#pragma once

#include <iostream>
#include <deque>

enum Color { Black = 0, Red};

template<typename T>
struct RBTreeNode {
    Color color = Black;
    T key;
    RBTreeNode<T>* left;
    RBTreeNode<T>* right;
    RBTreeNode<T>* parent;
};

template<typename T>
class RBTree {
public:
  RBTree() : nil_node_(new RBTreeNode<T>), root_node_(nil_node_) {} 
  ~RBTree() = default;

  RBTreeNode<T>& operator[](T key) {
    RBTreeNode<T>* current = Search(key);
    if (current == nullptr) {
      return *nil_node_;
    }
    return *current;
  }

  void Insert(T key) {
    // 红黑树为空时插入情况
    if (Empty()) {
      RBTreeNode<T>* node = NewNode(Black, key, nil_node_, nil_node_, nil_node_);
      root_node_ = node;
      return;
    }

    RBTreeNode<T>* current = NewNode(Red, key, nil_node_, nil_node_, nil_node_);
    RBTreeNode<T>* work = root_node_;
    while (work != nil_node_) {
      if (current->key == work->key) {
        delete current;
        return;
      } else if (current->key > work->key) {
        if (work->right == nil_node_) {
          current->parent = work;
          work->right = current;
          work = nil_node_;
        } else {
          work = work->right;
        }
      } else {
        if (work->left == nil_node_) {
          current->parent = work;
          work->left = current;
          work = nil_node_;
        } else {
          work = work->left;
        }
      }
    }
    InsertFixUp(current);
  }

  void Delete(T key) {
    if (Empty()) {
      return;
    }
    RBTreeNode<T>* current = Search(key);
    if (current == nullptr) {
      return;
    }
    std::cout << current->key << std::endl;
    Remove(current);
  }

  RBTreeNode<T>* Search(T key) {
    RBTreeNode<T>* current = nullptr;
    RBTreeNode<T>* work = root_node_;
    while (work != nil_node_) {
      if (work->key == key) {
        current = work;
        break;
      } else if (work->key > key) {
        work = work->left;
      } else {
        work = work->right;
      }
    }
    return current;
  }

  RBTreeNode<T>* NewNode(Color color, T key, 
            RBTreeNode<T>* left, RBTreeNode<T>* right, RBTreeNode<T>* parent) {
    RBTreeNode<T>* node = new RBTreeNode<T>;
    node->color = color;
    node->key = key;
    node->left = left;
    node->right = right;
    node->parent = parent; 
    return node;   
  }

  bool Empty() {
    return root_node_ == nil_node_;
  }

  void InOrder() {
    InOrderHelper(root_node_);
    std::cout << std::endl;
  }

  void PrintTree() {
    std::cout << "---- tree print begin ----" << std::endl;
    if (root_node_ == nil_node_) {
      std::cout << "tree is empty" << std::endl;
      std::cout << "---- tree print end   ----" << std::endl;
    }
    std::deque<RBTreeNode<T>*> helper = {root_node_};
    while (!helper.empty()) {
      int size = helper.size();
      for (int i = 0; i < size; i++) {
        if (helper[0]->left != nil_node_) {
          helper.push_back(helper[0]->left);
        } 
        if (helper[0]->right != nil_node_) {
          helper.push_back(helper[0]->right);
        }
        std::cout << helper[0]->key << "-" << (helper[0]->color == Red ? "red" : "black") << "\t";
        helper.pop_front();
      }
      std::cout << std::endl;
    }
    std::cout << "---- tree print end   ----" << std::endl;
  }
  
private:
  RBTreeNode<T>* nil_node_;
  RBTreeNode<T>* root_node_;

  // 节点交换函数，将节点dst放到src所在位置上
  // 交换完之后，src及其子节点会变成树外节点，只有src的parent指针还指向树内的某个节点，但是树内已经没有节点指向src了
  void Transplant(RBTreeNode<T>* src, RBTreeNode<T>* dst) {
    if (src == root_node_) {
      root_node_ = dst;
    } else if (src == src->parent->left) {
      src->parent->left = dst;
    } else {
      src->parent->right = dst;
    }
    dst->parent = src->parent;
  }

  RBTreeNode<T>* Minimum(RBTreeNode<T>* node) {
    if (node->left == nil_node_) {
      return node;
    }
    return Minimum(node->left);
  }

  void Remove(RBTreeNode<T>* remove_node) {
    RBTreeNode<T>* replace = nil_node_;
    RBTreeNode<T>* now_remove = remove_node;  // 真正执行删除的节点位置
    Color now_remove_color = now_remove->color;
    // replace可能是nil_node_, 通过调用Transplant方法会隐式给nil_node_设置parent指针
    if (remove_node->left == nil_node_) {
      replace = now_remove->right;
      Transplant(now_remove, now_remove->right);
    } else if (remove_node->right == nil_node_) {
      replace = now_remove->left;
      Transplant(now_remove, now_remove->left);
    } else {  // 被删除节点的左右子树都不为空
      // 删除节点左右子树都不为空时，需要先将删除该节点后，该节点位置的替换节点找到
      // 并将这两个节点进行交换，交换后，再将要删除的节点删除。
      // 替换节点一般有两种策略：
      //      1. 找到要删除节点的左子树的最大值与其替换 
      //      2. 找到要删除节点的右子树的最小值与其替换  (本代码使用该种策略)
      now_remove = Minimum(remove_node->right);
      now_remove_color = now_remove->color;
      // 因为找到的是右子树的最左子树作为实际删除位置，所以
      // 要将该最左子树的右子树作为实际删除节点位置上的替换（可能为nil）
      replace = now_remove->right;
      if (now_remove->parent == remove_node) {
        replace->parent = now_remove;
      } else {
        // 这一步实际上是将实际要删除位置的右子树接到要删除的位置上，即删除节点的操作在这一步完成了
        Transplant(now_remove, now_remove->right);
        now_remove->right = remove_node->right;
        now_remove->right->parent = now_remove;
      }
      // 这一步实际上是将取出来的实际删除位置上的节点放到原先要删除的节点的位置上
      Transplant(remove_node, now_remove);
      now_remove->left = remove_node->left;
      remove_node->left->parent = now_remove;
      now_remove->color = remove_node->color;
    }

    if (now_remove_color == Black) {
      RemoveFixUp(replace);
    }
  }

  void InsertFixUp(RBTreeNode<T>* current) {
    // 只有当前节点的父节点的颜色为红色时才需要进行调整
    while (current != nil_node_ && current->parent->color == Red) {
      RBTreeNode<T>* parent = current->parent;
      RBTreeNode<T>* grandparent = parent->parent;
      RBTreeNode<T>* uncle = 
          (grandparent->left == parent ? grandparent->right : grandparent->left);
      if (uncle->color == Red) {
        parent->color = Black;
        uncle->color = Black;
        grandparent->color = Red;
        current = grandparent;
      } else {
        if (grandparent->left == parent) {  // 父亲节点为左节点
          if (parent->right == current) {   // 新插入节点在右侧
            LeftRotate(parent);
            current = parent;
            parent = current->parent;
            grandparent = parent->parent;
          }
          RightRotate(grandparent);
          grandparent->color = Red;
          parent->color = Black;
        } else {                          // 父亲节点为右节点
          if (parent->left == current) {  // 新插入节点在右侧
            RightRotate(parent);
            current = parent;
            parent = current->parent;
            grandparent = parent->parent;
          }
          LeftRotate(grandparent);
          grandparent->color = Red;
          parent->color = Black;
        }
      }
    }
    root_node_->color = Black;
  }

  void RemoveFixUp(RBTreeNode<T>* current) {
    while (current != root_node_ && current->color == Black) {
      RBTreeNode<T>* parent = current->parent;
      RBTreeNode<T>* brother = (parent->left == current ? parent->right : parent->left);
      if (current == parent->left) {   // current在左子树
        if (brother->color == Red) {   // case 1
          brother->color = Black;
          parent->color = Red;
          LeftRotate(parent);
          brother = parent->right;
        }
        if (brother->left->color == Black && brother->right->color == Black) { // case 2
          brother->color = Red;
          current = parent;
          continue;
        } else if (brother->right->color == Black) {  // case3
          brother->color = Red;
          brother->left->color = Black;
          RightRotate(brother);
          brother = parent->right;
        }  
        brother->color = parent->color;  // case4
        parent->color = Black;
        brother->right->color = Black;
        LeftRotate(parent);
        current = root_node_;
      } else {
        if (brother->color == Red) {
          brother->color = Black;
          parent->color = Red;
          RightRotate(brother);
          brother = parent->left;
        }
        if (brother->left->color == Black && brother->right->color == Black) {
          brother->color = Red;
          current = parent;
          continue;
        } else if (brother->right->color == Black) {
          brother->color = Red;
          brother->right->color = Black;
          LeftRotate(brother);
          brother = parent->left;
        }
        brother->color = parent->color;
        parent->color = Black;
        brother->left->color = Black;
        RightRotate(parent);
        current = root_node_;
      }
    }
    // 做完调整之后，将nil_node_的parent指针置空
    // nil_node_->parent = nullptr;
    current->color = Black;
  }

  /**
  *  左旋、右旋操作示意：
  * 
  *       |                                       |
  *       x           left_rotate(T, x)           y
  *      / \        --------------------->       / \
  *     α   y       <---------------------      x   γ 
  *        / \        right_rotate(T, y)       / \
  *       β   γ                               α   β
  *   
  *  注：x, y指的是单个节点，α, β, γ指的是整个子树
  */
  void RightRotate(RBTreeNode<T>* node) {
    RBTreeNode<T>* parent = node->parent;
    RBTreeNode<T>* left_child = node->left;
    RBTreeNode<T>* right_grandchild = left_child->right;
    node->left = right_grandchild;
    if (right_grandchild != nil_node_) {
      right_grandchild->parent = node;
    }
    if (parent->left == node) {
      parent->left = left_child;
    } else {
      parent->right = left_child;
    }
    left_child->parent = parent;
    node->parent = left_child;
    left_child->right = node;
    if (node == root_node_) {
      root_node_ = left_child;
    }
  }

  void LeftRotate(RBTreeNode<T>* node) {
    RBTreeNode<T>* parent = node->parent;
    RBTreeNode<T>* right_child = node->right;
    RBTreeNode<T>* left_grandchild = right_child->left;
    node->right = left_grandchild;
    if (left_grandchild != nil_node_) {
      left_grandchild->parent = node;
    } 
    if (parent->left == node) {
      parent->left = right_child;
    } else {
      parent->right = right_child;
    }
    right_child->parent = parent;
    node->parent = right_child;
    right_child->left = node;
    if (node == root_node_) {
      root_node_ = right_child;
    }
  }

  void InOrderHelper(RBTreeNode<T>* root) {
    if (root != nil_node_) {
      InOrderHelper(root->left);
      std::cout << root->key << " ";
      InOrderHelper(root->right);
    }
  }
};