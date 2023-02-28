#pragma once
#include <vector>
#include <random>
#include <cmath>
#include <iostream>

template<typename Index_t>
struct IndexNode {
  IndexNode<Index_t>* down;
  IndexNode<Index_t>* next;
  Index_t index_val;
};

template<typename Data_t, typename Index_t>
struct DataNode {
  IndexNode<Index_t>* index;
  Data_t data;
  DataNode<Data_t, Index_t>* next;
};



template<typename Data_t, typename Index_t, unsigned int MAX_LEVEL = 5, float SKIPLISTZ = 0.5>
class SkipList {
public:

  Data_t* Find(Index_t key) {
    return FindByIndex(key);
  }

  Data_t* FindByIndex(Index_t key) {
    IndexNode<Index_t>* work = nullptr; 
    for (int i = 1; i <= MAX_LEVEL; i++) {
      work = index_level_head_node_set_[MAX_LEVEL - i];
      if (work != nullptr)  break;
    }
    // 还没有建立索引，直接从data里面找
    if (work == nullptr) {
      DataNode<Data_t, Index_t>* data_work = data_head_node_;
      while (data_work != nullptr) {
        if (data_work->index->index_val == key)  return &(data_work->data);
        data_work = data_work->next;
      }
      return nullptr;
    }

    while (true) {
      if (work->index_val == key) {
        work = work->down;
      } else if (work->next == nullptr || work->next->index_val > key) {
        work = work->down;
      }
    }
  }


  // 这个方法一般需要Data_t重载了operator==才有效，使用该方法会导致索引失效
  Data_t* FindByData(Data_t data) {

  }


private:
  DataNode<Data_t, Index_t>* data_head_node_;
  std::vector<IndexNode<Index_t>*> index_level_head_node_set_;

  int RandomLevel() {
    
  }
};

