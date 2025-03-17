#include "ladder.h"

using namespace std;

void error(string word1, string word2, string msg) {
    cout << msg << " " << word1 << " " << word2 << endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
  int slen1 = str1.length();
  int slen2 = str2.length();
  if (slen1 == slen2) {
    int diff = 0;
    for (int i = 0; i < slen1; ++i) {
      if (str1[i] != str2[i])
        ++diff;
    }
    return diff <= d;
  }
  string shorter = (slen1 < slen2) ? str1 : str2;
  string longer = (shorter == str1) ? str2 : str1;
  int shorterLen = shorter.length();
  int longerLen = longer.length();
  if (longerLen - shorterLen == 1) {
    int i = 0, j = 0, edit = 0;
    while (i < shorterLen && j < longerLen) {
      if (shorter[i] != longer[j]) {
        ++edit;
        if (edit > d) return false;
        ++j;
      } else {
        ++i;
        ++j;
      }
    }
    if (i < shorterLen || j < longerLen)
      ++edit;
    return edit <= d;
  }
  return false;
}

bool is_adjacent(const string& word1, const string& word2) {
  int wlen1 = word1.length();
  int wlen2 = word2.length();
  if (wlen1 == wlen2) {
    int diff = 0;
    for (int i = 0; i < wlen1; ++i) {
      if (word1[i] != word2[i])
        ++diff;
    }
    return diff <= 1;
  }
  string shorter = (wlen1 < wlen2) ? word1 : word2;
  string longer = (shorter == word1) ? word2 : word1;
  int shorterLen = shorter.length();
  int longerLen = longer.length();
  if (longerLen - shorterLen == 1) {
    int i = 0, j = 0, diff = 0;
    while (i < shorterLen && j < longerLen) {
      if (shorter[i] != longer[j]) {
        ++diff;
        if (diff > 1) return false;
        ++j;
      } else {
        ++i;
        ++j;
      }
    }
    return true;
  }
  return false;
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
  queue<vector<string>> ladder_queue;
  ladder_queue.push({begin_word});
  set<string> visited;
  visited.insert(begin_word);
  while (!ladder_queue.empty()) {
    vector<string> ladder = ladder_queue.front();
    ladder_queue.pop();
    string last_word = ladder.back();
    for (const string & word : word_list) {
      if (is_adjacent(last_word, word) && visited.find(word) == visited.end()) {
        visited.insert(word);
        vector<string> new_ladder = ladder;
        new_ladder.push_back(word);
        if (word == end_word) {
          return new_ladder;
        }
        ladder_queue.push(new_ladder);
      }
    }
  }
  return {};
}

void load_words(set<string> & word_list, const string& file_name) {
  ifstream file(file_name);
  string word;
  while (file >> word) {
    transform(word.begin(), word.end(), word.begin(), ::tolower);
    word_list.insert(word);
  }
  file.close();
}

void print_word_ladder(const vector<string>& ladder) {
  if (!ladder.empty()) {
    cout << "Word ladder found: ";
    for (const string & word : ladder)
      cout << word << " ";
    cout << endl;
  } else {
    cout << "No word ladder found." << endl;
  }
}

#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}

void verify_word_ladder() {
  set<string> word_list;
  load_words(word_list, "src/words.txt");
  my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
  my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
  my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
  my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
  my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
  my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}
