#pragma once
#include <vector>
#include <string>


/**
 * 只支持26个小写英文字母的前缀树
*/
class Trie {
public:
  Trie() : children_(26, nullptr), is_end_(false) {}

  void Insert(std::string word) {
    int sz = word.size();
    Trie* cur = this;
    for (int i = 0; i < sz; i++) {
        int idx = word[i] - 'a';
        if (cur->children_[idx]) {
            cur = cur->children_[idx];
        } else {
            Trie* new_node = new Trie;
            cur->children_[idx] = new_node;
            cur = new_node;
        }
    }
    cur->is_end_ = true;
  }

  bool Search(std::string word) {
    Trie* res = SearchPrefix(word);
    return res && res->is_end_;

  }

  bool StartsWith(std::string prefix) {
    return !!SearchPrefix(prefix);
  }

private:
  std::vector<Trie*> children_;
  bool is_end_;

  Trie* SearchPrefix(std::string prefix) {
    int sz = prefix.size();
    Trie* cur = this;
    for (int i = 0; i < sz; i++) {
        int idx = prefix[i] - 'a';
        if (cur->children_[idx]) {
            cur = cur->children_[idx];
        } else {
            return nullptr;
        }
    }
    return cur;
  }
};