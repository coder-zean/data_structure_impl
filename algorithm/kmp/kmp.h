#pragma once

#include <string>
#include <vector>

class KmpUtil {
public:
  static int DoKmp(std::string s, std::string p) {
    int sLen = s.size();
    int pLen = p.size();

    std::vector<int> next(pLen, -1);
    GetNext(p, next);
    int i = 0, j = 0;
    while (i < sLen && j < pLen) {
      if (j == -1 || s[i] == p[j]) {
        i++;
        j++;
      } else {
      // 匹配失败，只将j回溯
        j = next[j];
      }
    }
    if (j == pLen)  return i - j;
    return -1;
  }

private:
  static void GetNext(std::string p, std::vector<int>& next) {
    int pLen = p.size();
	int k = -1;
	int j = 0;
	while (j < pLen - 1) {
	  //p[k]表示前缀，p[j]表示后缀
	  if (k == -1 || p[j] == p[k]) {
	    ++k;
	    ++j;
	    if (p[j] != p[k]) {
		  next[j] = k;
		} else {
	      next[j] = next[k];
		}
	  } else {
	    k = next[k];
	  }
    }
  }
};