#include <algorithm>
#include <array>
#include <gtest/gtest.h>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution1 {
  public:
    vector<string> findWords(const vector<vector<char>> &board,
                             const vector<string> &words) {
        int rows = board.size();
        int cols = board.front().size();

        unordered_set<string> foundWords;
        Trie dict;
        vector<vector<bool>> visited(rows, vector<bool>(cols, false));
        string word;

        for (const string &w : words) {
            dict.insert(w);
        }

        for (int y = 0; y < board.size(); y++) {
            for (int x = 0; x < board.front().size(); x++) {
                backtrack(board, words, foundWords, dict, visited, word,
                          {y, x});
            }
        }

        return vector<string>(foundWords.begin(), foundWords.end());
    }

  private:
    class Trie {
      public:
        Trie() { root = new Node(); }

        ~Trie() { deleteNode(root); }

        void insert(const string &word) {
            Node *current = root;

            for (const char &val : word) {
                int index = val - 'a';
                Node *next = current->children[index];

                if (next != nullptr) {
                    current = next;
                } else {
                    current->children[index] = new Node(val);
                    current = current->children[index];
                }
            }

            current->terminal = true;
        }

        bool search(const string &word) const {
            Node *current = root;

            for (const char &val : word) {
                int index = val - 'a';
                Node *next = current->children[index];

                if (next == nullptr) {
                    return false;
                }

                current = next;
            }

            return current->terminal;
        }

        bool startsWith(const string &prefix) const {
            Node *current = root;

            for (const char &val : prefix) {
                int index = val - 'a';
                Node *next = current->children[index];

                if (next == nullptr) {
                    return false;
                }

                current = next;
            }

            return true;
        }

      private:
        static constexpr int ALPHABET_SIZE = 26;

        struct Node {
            char val;
            array<Node *, ALPHABET_SIZE> children;
            bool terminal;

            Node() : val('\0'), children(), terminal() {}
            Node(char val) : val(val), children(), terminal() {}
        };

        Node *root;

        void deleteNode(Node *node) {
            for (Node *next : node->children) {
                if (next != nullptr) {
                    deleteNode(next);
                }
            }
            delete node;
        }
    };

    void backtrack(const vector<vector<char>> &board,
                   const vector<string> &words,
                   unordered_set<string> &foundWords, const Trie &dict,
                   vector<vector<bool>> &visited, string &word,
                   pair<int, int> pos) {
        int rows = board.size();
        int cols = board.front().size();

        if (pos.first < 0 || pos.first >= rows || pos.second < 0 ||
            pos.second >= cols) {
            return;
        }

        if (visited[pos.first][pos.second]) {
            return;
        }

        word += board[pos.first][pos.second];

        if (!dict.startsWith(word)) {
            word.pop_back();
            return;
        }

        if (dict.search(word)) {
            foundWords.insert(word);
        }

        visited[pos.first][pos.second] = true;

        static const vector<pair<int, int>> directions = {
            {-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        for (const auto &dir : directions) {
            pair<int, int> next = {pos.first + dir.first,
                                   pos.second + dir.second};
            backtrack(board, words, foundWords, dict, visited, word, next);
        }

        visited[pos.first][pos.second] = false;
        word.pop_back();
    }
};

class Solution1Test : public ::testing::Test {
  protected:
    Solution1 solution;
};

TEST_F(Solution1Test, TestCase1) {
    vector<vector<char>> board = {{'o', 'a', 'a', 'n'},
                                  {'e', 't', 'a', 'e'},
                                  {'i', 'h', 'k', 'r'},
                                  {'i', 'f', 'l', 'v'}};
    vector<string> words = {"oath", "pea", "eat", "rain"};

    vector<string> actual = solution.findWords(board, words);
    vector<string> expected = {"eat", "oath"};

    sort(actual.begin(), actual.end());
    sort(expected.begin(), expected.end());
    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase2) {
    vector<vector<char>> board = {{'a', 'b'}, {'c', 'd'}};
    vector<string> words = {"abcb"};

    vector<string> actual = solution.findWords(board, words);
    vector<string> expected = {};

    sort(actual.begin(), actual.end());
    sort(expected.begin(), expected.end());
    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase3) {
    vector<vector<char>> board = {
        {'a', 'b', 'c', 'e'}, {'s', 'f', 'c', 's'}, {'a', 'd', 'e', 'e'}};
    vector<string> words = {"see", "abcced", "abcf", "sae"};

    vector<string> actual = solution.findWords(board, words);
    vector<string> expected = {"see", "abcced"};

    sort(actual.begin(), actual.end());
    sort(expected.begin(), expected.end());
    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase4) {
    vector<vector<char>> board = {{'t', 'h', 'i', 's'},
                                  {'i', 's', 'a', 't'},
                                  {'a', 't', 'e', 's'},
                                  {'s', 'a', 'm', 'p'}};
    vector<string> words = {"this", "is", "a", "test", "sample"};

    vector<string> actual = solution.findWords(board, words);
    vector<string> expected = {"this", "is", "a", "test"};

    sort(actual.begin(), actual.end());
    sort(expected.begin(), expected.end());
    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase5) {
    vector<vector<char>> board = {
        {'a', 'b', 'c'}, {'d', 'e', 'f'}, {'g', 'h', 'i'}};
    vector<string> words = {"abc", "cfi", "adg", "beh", "defi"};

    vector<string> actual = solution.findWords(board, words);
    vector<string> expected = {"abc", "cfi", "adg", "beh", "defi"};

    sort(actual.begin(), actual.end());
    sort(expected.begin(), expected.end());
    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase6) {
    vector<vector<char>> board = {{'a'}};
    vector<string> words = {"a"};

    vector<string> actual = solution.findWords(board, words);
    vector<string> expected = {"a"};

    sort(actual.begin(), actual.end());
    sort(expected.begin(), expected.end());
    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase7) {
    vector<vector<char>> board = {{'a', 'b'}, {'c', 'd'}};
    vector<string> words = {"ab", "abd"};

    vector<string> actual = solution.findWords(board, words);
    vector<string> expected = {"ab", "abd"};

    sort(actual.begin(), actual.end());
    sort(expected.begin(), expected.end());
    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase8) {
    vector<vector<char>> board = {
        {'b', 'a', 'b', 'a', 'b', 'a', 'b', 'a', 'b', 'a'},
        {'a', 'b', 'a', 'b', 'a', 'b', 'a', 'b', 'a', 'b'},
        {'b', 'a', 'b', 'a', 'b', 'a', 'b', 'a', 'b', 'a'},
        {'a', 'b', 'a', 'b', 'a', 'b', 'a', 'b', 'a', 'b'},
        {'b', 'a', 'b', 'a', 'b', 'a', 'b', 'a', 'b', 'a'},
        {'a', 'b', 'a', 'b', 'a', 'b', 'a', 'b', 'a', 'b'},
        {'b', 'a', 'b', 'a', 'b', 'a', 'b', 'a', 'b', 'a'},
        {'a', 'b', 'a', 'b', 'a', 'b', 'a', 'b', 'a', 'b'},
        {'b', 'a', 'b', 'a', 'b', 'a', 'b', 'a', 'b', 'a'},
        {'a', 'b', 'a', 'b', 'a', 'b', 'a', 'b', 'a', 'b'}};
    vector<string> words = {
        "ababababaa", "ababababab", "ababababac", "ababababad", "ababababae",
        "ababababaf", "ababababag", "ababababah", "ababababai", "ababababaj",
        "ababababak", "ababababal", "ababababam", "ababababan", "ababababao",
        "ababababap", "ababababaq", "ababababar", "ababababas", "ababababat",
        "ababababau", "ababababav", "ababababaw", "ababababax", "ababababay",
        "ababababaz", "ababababba", "ababababbb", "ababababbc", "ababababbd",
        "ababababbe", "ababababbf", "ababababbg", "ababababbh", "ababababbi",
        "ababababbj", "ababababbk", "ababababbl", "ababababbm", "ababababbn",
        "ababababbo", "ababababbp", "ababababbq", "ababababbr", "ababababbs",
        "ababababbt", "ababababbu", "ababababbv", "ababababbw", "ababababbx",
        "ababababby", "ababababbz", "ababababca", "ababababcb", "ababababcc",
        "ababababcd", "ababababce", "ababababcf", "ababababcg", "ababababch",
        "ababababci", "ababababcj", "ababababck", "ababababcl", "ababababcm",
        "ababababcn", "ababababco", "ababababcp", "ababababcq", "ababababcr",
        "ababababcs", "ababababct", "ababababcu", "ababababcv", "ababababcw",
        "ababababcx", "ababababcy", "ababababcz", "ababababda", "ababababdb",
        "ababababdc", "ababababdd", "ababababde", "ababababdf", "ababababdg",
        "ababababdh", "ababababdi", "ababababdj", "ababababdk", "ababababdl",
        "ababababdm", "ababababdn", "ababababdo", "ababababdp", "ababababdq",
        "ababababdr", "ababababds", "ababababdt", "ababababdu", "ababababdv",
        "ababababdw", "ababababdx", "ababababdy", "ababababdz", "ababababea",
        "ababababeb", "ababababec", "ababababed", "ababababee", "ababababef",
        "ababababeg", "ababababeh", "ababababei", "ababababej", "ababababek",
        "ababababel", "ababababem", "ababababen", "ababababeo", "ababababep",
        "ababababeq", "ababababer", "ababababes", "ababababet", "ababababeu",
        "ababababev", "ababababew", "ababababex", "ababababey", "ababababez",
        "ababababfa", "ababababfb", "ababababfc", "ababababfd", "ababababfe",
        "ababababff", "ababababfg", "ababababfh", "ababababfi", "ababababfj",
        "ababababfk", "ababababfl", "ababababfm", "ababababfn", "ababababfo",
        "ababababfp", "ababababfq", "ababababfr", "ababababfs", "ababababft",
        "ababababfu", "ababababfv", "ababababfw", "ababababfx", "ababababfy",
        "ababababfz", "ababababga", "ababababgb", "ababababgc", "ababababgd",
        "ababababge", "ababababgf", "ababababgg", "ababababgh", "ababababgi",
        "ababababgj", "ababababgk", "ababababgl", "ababababgm", "ababababgn",
        "ababababgo", "ababababgp", "ababababgq", "ababababgr", "ababababgs",
        "ababababgt", "ababababgu", "ababababgv", "ababababgw", "ababababgx",
        "ababababgy", "ababababgz", "ababababha", "ababababhb", "ababababhc",
        "ababababhd", "ababababhe", "ababababhf", "ababababhg", "ababababhh",
        "ababababhi", "ababababhj", "ababababhk", "ababababhl", "ababababhm",
        "ababababhn", "ababababho", "ababababhp", "ababababhq", "ababababhr",
        "ababababhs", "ababababht", "ababababhu", "ababababhv", "ababababhw",
        "ababababhx", "ababababhy", "ababababhz", "ababababia", "ababababib",
        "ababababic", "ababababid", "ababababie", "ababababif", "ababababig",
        "ababababih", "ababababii", "ababababij", "ababababik", "ababababil",
        "ababababim", "ababababin", "ababababio", "ababababip", "ababababiq",
        "ababababir", "ababababis", "ababababit", "ababababiu", "ababababiv",
        "ababababiw", "ababababix", "ababababiy", "ababababiz", "ababababja",
        "ababababjb", "ababababjc", "ababababjd", "ababababje", "ababababjf",
        "ababababjg", "ababababjh", "ababababji", "ababababjj", "ababababjk",
        "ababababjl", "ababababjm", "ababababjn", "ababababjo", "ababababjp",
        "ababababjq", "ababababjr", "ababababjs", "ababababjt", "ababababju",
        "ababababjv", "ababababjw", "ababababjx", "ababababjy", "ababababjz",
        "ababababka", "ababababkb", "ababababkc", "ababababkd", "ababababke",
        "ababababkf", "ababababkg", "ababababkh", "ababababki", "ababababkj",
        "ababababkk", "ababababkl", "ababababkm", "ababababkn", "ababababko",
        "ababababkp", "ababababkq", "ababababkr", "ababababks", "ababababkt",
        "ababababku", "ababababkv", "ababababkw", "ababababkx", "ababababky",
        "ababababkz", "ababababla", "abababablb", "abababablc", "ababababld",
        "abababable", "abababablf", "abababablg", "abababablh", "ababababli",
        "abababablj", "abababablk", "ababababll", "abababablm", "ababababln",
        "abababablo", "abababablp", "abababablq", "abababablr", "ababababls",
        "abababablt", "abababablu", "abababablv", "abababablw", "abababablx",
        "abababably", "abababablz", "ababababma", "ababababmb", "ababababmc",
        "ababababmd", "ababababme", "ababababmf", "ababababmg", "ababababmh",
        "ababababmi", "ababababmj", "ababababmk", "ababababml", "ababababmm",
        "ababababmn", "ababababmo", "ababababmp", "ababababmq", "ababababmr",
        "ababababms", "ababababmt", "ababababmu", "ababababmv", "ababababmw",
        "ababababmx", "ababababmy", "ababababmz", "ababababna", "ababababnb",
        "ababababnc", "ababababnd", "ababababne", "ababababnf", "ababababng",
        "ababababnh", "ababababni", "ababababnj", "ababababnk", "ababababnl",
        "ababababnm", "ababababnn", "ababababno", "ababababnp", "ababababnq",
        "ababababnr", "ababababns", "ababababnt", "ababababnu", "ababababnv",
        "ababababnw", "ababababnx", "ababababny", "ababababnz", "ababababoa",
        "ababababob", "ababababoc", "ababababod", "ababababoe", "ababababof",
        "ababababog", "ababababoh", "ababababoi", "ababababoj", "ababababok",
        "ababababol", "ababababom", "ababababon", "ababababoo", "ababababop",
        "ababababoq", "ababababor", "ababababos", "ababababot", "ababababou",
        "ababababov", "ababababow", "ababababox", "ababababoy", "ababababoz",
        "ababababpa", "ababababpb", "ababababpc", "ababababpd", "ababababpe",
        "ababababpf", "ababababpg", "ababababph", "ababababpi", "ababababpj",
        "ababababpk", "ababababpl", "ababababpm", "ababababpn", "ababababpo",
        "ababababpp", "ababababpq", "ababababpr", "ababababps", "ababababpt",
        "ababababpu", "ababababpv", "ababababpw", "ababababpx", "ababababpy",
        "ababababpz", "ababababqa", "ababababqb", "ababababqc", "ababababqd",
        "ababababqe", "ababababqf", "ababababqg", "ababababqh", "ababababqi",
        "ababababqj", "ababababqk", "ababababql", "ababababqm", "ababababqn",
        "ababababqo", "ababababqp", "ababababqq", "ababababqr", "ababababqs",
        "ababababqt", "ababababqu", "ababababqv", "ababababqw", "ababababqx",
        "ababababqy", "ababababqz", "ababababra", "ababababrb", "ababababrc",
        "ababababrd", "ababababre", "ababababrf", "ababababrg", "ababababrh",
        "ababababri", "ababababrj", "ababababrk", "ababababrl", "ababababrm",
        "ababababrn", "ababababro", "ababababrp", "ababababrq", "ababababrr",
        "ababababrs", "ababababrt", "ababababru", "ababababrv", "ababababrw",
        "ababababrx", "ababababry", "ababababrz", "ababababsa", "ababababsb",
        "ababababsc", "ababababsd", "ababababse", "ababababsf", "ababababsg",
        "ababababsh", "ababababsi", "ababababsj", "ababababsk", "ababababsl",
        "ababababsm", "ababababsn", "ababababso", "ababababsp", "ababababsq",
        "ababababsr", "ababababss", "ababababst", "ababababsu", "ababababsv",
        "ababababsw", "ababababsx", "ababababsy", "ababababsz", "ababababta",
        "ababababtb", "ababababtc", "ababababtd", "ababababte", "ababababtf",
        "ababababtg", "ababababth", "ababababti", "ababababtj", "ababababtk",
        "ababababtl", "ababababtm", "ababababtn", "ababababto", "ababababtp",
        "ababababtq", "ababababtr", "ababababts", "ababababtt", "ababababtu",
        "ababababtv", "ababababtw", "ababababtx", "ababababty", "ababababtz",
        "ababababua", "ababababub", "ababababuc", "ababababud", "ababababue",
        "ababababuf", "ababababug", "ababababuh", "ababababui", "ababababuj",
        "ababababuk", "ababababul", "ababababum", "ababababun", "ababababuo",
        "ababababup", "ababababuq", "ababababur", "ababababus", "ababababut",
        "ababababuu", "ababababuv", "ababababuw", "ababababux", "ababababuy",
        "ababababuz", "ababababva", "ababababvb", "ababababvc", "ababababvd",
        "ababababve", "ababababvf", "ababababvg", "ababababvh", "ababababvi",
        "ababababvj", "ababababvk", "ababababvl", "ababababvm", "ababababvn",
        "ababababvo", "ababababvp", "ababababvq", "ababababvr", "ababababvs",
        "ababababvt", "ababababvu", "ababababvv", "ababababvw", "ababababvx",
        "ababababvy", "ababababvz", "ababababwa", "ababababwb", "ababababwc",
        "ababababwd", "ababababwe", "ababababwf", "ababababwg", "ababababwh",
        "ababababwi", "ababababwj", "ababababwk", "ababababwl", "ababababwm",
        "ababababwn", "ababababwo", "ababababwp", "ababababwq", "ababababwr",
        "ababababws", "ababababwt", "ababababwu", "ababababwv", "ababababww",
        "ababababwx", "ababababwy", "ababababwz", "ababababxa", "ababababxb",
        "ababababxc", "ababababxd", "ababababxe", "ababababxf", "ababababxg",
        "ababababxh", "ababababxi", "ababababxj", "ababababxk", "ababababxl",
        "ababababxm", "ababababxn", "ababababxo", "ababababxp", "ababababxq",
        "ababababxr", "ababababxs", "ababababxt", "ababababxu", "ababababxv",
        "ababababxw", "ababababxx", "ababababxy", "ababababxz", "ababababya",
        "ababababyb", "ababababyc", "ababababyd", "ababababye", "ababababyf",
        "ababababyg", "ababababyh", "ababababyi", "ababababyj", "ababababyk",
        "ababababyl", "ababababym", "ababababyn", "ababababyo", "ababababyp",
        "ababababyq", "ababababyr", "ababababys", "ababababyt", "ababababyu",
        "ababababyv", "ababababyw", "ababababyx", "ababababyy", "ababababyz",
        "ababababza", "ababababzb", "ababababzc", "ababababzd", "ababababze",
        "ababababzf", "ababababzg", "ababababzh", "ababababzi", "ababababzj",
        "ababababzk", "ababababzl", "ababababzm", "ababababzn", "ababababzo",
        "ababababzp", "ababababzq", "ababababzr", "ababababzs", "ababababzt",
        "ababababzu", "ababababzv", "ababababzw", "ababababzx", "ababababzy",
        "ababababzz"};

    vector<string> actual = solution.findWords(board, words);
    vector<string> expected = {"ababababab"};

    sort(actual.begin(), actual.end());
    sort(expected.begin(), expected.end());
    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase9) {
    vector<vector<char>> board = {
        {'m', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l'},
        {'n', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a'},
        {'o', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a'},
        {'p', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a'},
        {'q', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a'},
        {'r', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a'},
        {'s', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a'},
        {'t', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a'},
        {'u', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a'},
        {'v', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a'},
        {'w', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a'},
        {'x', 'y', 'z', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a'}};
    vector<string> words = {
        "aaaaaaaaaa", "aaaaaaaaab", "aaaaaaaaac", "aaaaaaaaad", "aaaaaaaaae",
        "aaaaaaaaaf", "aaaaaaaaag", "aaaaaaaaah", "aaaaaaaaai", "aaaaaaaaaj",
        "aaaaaaaaak", "aaaaaaaaal", "aaaaaaaaam", "aaaaaaaaan", "aaaaaaaaao",
        "aaaaaaaaap", "aaaaaaaaaq", "aaaaaaaaar", "aaaaaaaaas", "aaaaaaaaat",
        "aaaaaaaaau", "aaaaaaaaav", "aaaaaaaaaw", "aaaaaaaaax", "aaaaaaaaay",
        "aaaaaaaaaz", "aaaaaaaaba", "aaaaaaaabb", "aaaaaaaabc", "aaaaaaaabd",
        "aaaaaaaabe", "aaaaaaaabf", "aaaaaaaabg", "aaaaaaaabh", "aaaaaaaabi",
        "aaaaaaaabj", "aaaaaaaabk", "aaaaaaaabl", "aaaaaaaabm", "aaaaaaaabn",
        "aaaaaaaabo", "aaaaaaaabp", "aaaaaaaabq", "aaaaaaaabr", "aaaaaaaabs",
        "aaaaaaaabt", "aaaaaaaabu", "aaaaaaaabv", "aaaaaaaabw", "aaaaaaaabx",
        "aaaaaaaaby", "aaaaaaaabz", "aaaaaaaaca", "aaaaaaaacb", "aaaaaaaacc",
        "aaaaaaaacd", "aaaaaaaace", "aaaaaaaacf", "aaaaaaaacg", "aaaaaaaach",
        "aaaaaaaaci", "aaaaaaaacj", "aaaaaaaack", "aaaaaaaacl", "aaaaaaaacm",
        "aaaaaaaacn", "aaaaaaaaco", "aaaaaaaacp", "aaaaaaaacq", "aaaaaaaacr",
        "aaaaaaaacs", "aaaaaaaact", "aaaaaaaacu", "aaaaaaaacv", "aaaaaaaacw",
        "aaaaaaaacx", "aaaaaaaacy", "aaaaaaaacz", "aaaaaaaada", "aaaaaaaadb",
        "aaaaaaaadc", "aaaaaaaadd", "aaaaaaaade", "aaaaaaaadf", "aaaaaaaadg",
        "aaaaaaaadh", "aaaaaaaadi", "aaaaaaaadj", "aaaaaaaadk", "aaaaaaaadl",
        "aaaaaaaadm", "aaaaaaaadn", "aaaaaaaado", "aaaaaaaadp", "aaaaaaaadq",
        "aaaaaaaadr", "aaaaaaaads", "aaaaaaaadt", "aaaaaaaadu", "aaaaaaaadv",
        "aaaaaaaadw", "aaaaaaaadx", "aaaaaaaady", "aaaaaaaadz", "aaaaaaaaea",
        "aaaaaaaaeb", "aaaaaaaaec", "aaaaaaaaed", "aaaaaaaaee", "aaaaaaaaef",
        "aaaaaaaaeg", "aaaaaaaaeh", "aaaaaaaaei", "aaaaaaaaej", "aaaaaaaaek",
        "aaaaaaaael", "aaaaaaaaem", "aaaaaaaaen", "aaaaaaaaeo", "aaaaaaaaep",
        "aaaaaaaaeq", "aaaaaaaaer", "aaaaaaaaes", "aaaaaaaaet", "aaaaaaaaeu",
        "aaaaaaaaev", "aaaaaaaaew", "aaaaaaaaex", "aaaaaaaaey", "aaaaaaaaez",
        "aaaaaaaafa", "aaaaaaaafb", "aaaaaaaafc", "aaaaaaaafd", "aaaaaaaafe",
        "aaaaaaaaff", "aaaaaaaafg", "aaaaaaaafh", "aaaaaaaafi", "aaaaaaaafj",
        "aaaaaaaafk", "aaaaaaaafl", "aaaaaaaafm", "aaaaaaaafn", "aaaaaaaafo",
        "aaaaaaaafp", "aaaaaaaafq", "aaaaaaaafr", "aaaaaaaafs", "aaaaaaaaft",
        "aaaaaaaafu", "aaaaaaaafv", "aaaaaaaafw", "aaaaaaaafx", "aaaaaaaafy",
        "aaaaaaaafz", "aaaaaaaaga", "aaaaaaaagb", "aaaaaaaagc", "aaaaaaaagd",
        "aaaaaaaage", "aaaaaaaagf", "aaaaaaaagg", "aaaaaaaagh", "aaaaaaaagi",
        "aaaaaaaagj", "aaaaaaaagk", "aaaaaaaagl", "aaaaaaaagm", "aaaaaaaagn",
        "aaaaaaaago", "aaaaaaaagp", "aaaaaaaagq", "aaaaaaaagr", "aaaaaaaags",
        "aaaaaaaagt", "aaaaaaaagu", "aaaaaaaagv", "aaaaaaaagw", "aaaaaaaagx",
        "aaaaaaaagy", "aaaaaaaagz", "aaaaaaaaha", "aaaaaaaahb", "aaaaaaaahc",
        "aaaaaaaahd", "aaaaaaaahe", "aaaaaaaahf", "aaaaaaaahg", "aaaaaaaahh",
        "aaaaaaaahi", "aaaaaaaahj", "aaaaaaaahk", "aaaaaaaahl", "aaaaaaaahm",
        "aaaaaaaahn", "aaaaaaaaho", "aaaaaaaahp", "aaaaaaaahq", "aaaaaaaahr",
        "aaaaaaaahs", "aaaaaaaaht", "aaaaaaaahu", "aaaaaaaahv", "aaaaaaaahw",
        "aaaaaaaahx", "aaaaaaaahy", "aaaaaaaahz", "aaaaaaaaia", "aaaaaaaaib",
        "aaaaaaaaic", "aaaaaaaaid", "aaaaaaaaie", "aaaaaaaaif", "aaaaaaaaig",
        "aaaaaaaaih", "aaaaaaaaii", "aaaaaaaaij", "aaaaaaaaik", "aaaaaaaail",
        "aaaaaaaaim", "aaaaaaaain", "aaaaaaaaio", "aaaaaaaaip", "aaaaaaaaiq",
        "aaaaaaaair", "aaaaaaaais", "aaaaaaaait", "aaaaaaaaiu", "aaaaaaaaiv",
        "aaaaaaaaiw", "aaaaaaaaix", "aaaaaaaaiy", "aaaaaaaaiz", "aaaaaaaaja",
        "aaaaaaaajb", "aaaaaaaajc", "aaaaaaaajd", "aaaaaaaaje", "aaaaaaaajf",
        "aaaaaaaajg", "aaaaaaaajh", "aaaaaaaaji", "aaaaaaaajj", "aaaaaaaajk",
        "aaaaaaaajl", "aaaaaaaajm", "aaaaaaaajn", "aaaaaaaajo", "aaaaaaaajp",
        "aaaaaaaajq", "aaaaaaaajr", "aaaaaaaajs", "aaaaaaaajt", "aaaaaaaaju",
        "aaaaaaaajv", "aaaaaaaajw", "aaaaaaaajx", "aaaaaaaajy", "aaaaaaaajz",
        "aaaaaaaaka", "aaaaaaaakb", "aaaaaaaakc", "aaaaaaaakd", "aaaaaaaake",
        "aaaaaaaakf", "aaaaaaaakg", "aaaaaaaakh", "aaaaaaaaki", "aaaaaaaakj",
        "aaaaaaaakk", "aaaaaaaakl", "aaaaaaaakm", "aaaaaaaakn", "aaaaaaaako",
        "aaaaaaaakp", "aaaaaaaakq", "aaaaaaaakr", "aaaaaaaaks", "aaaaaaaakt",
        "aaaaaaaaku", "aaaaaaaakv", "aaaaaaaakw", "aaaaaaaakx", "aaaaaaaaky",
        "aaaaaaaakz", "aaaaaaaala", "aaaaaaaalb", "aaaaaaaalc", "aaaaaaaald",
        "aaaaaaaale", "aaaaaaaalf", "aaaaaaaalg", "aaaaaaaalh", "aaaaaaaali",
        "aaaaaaaalj", "aaaaaaaalk", "aaaaaaaall", "aaaaaaaalm", "aaaaaaaaln",
        "aaaaaaaalo", "aaaaaaaalp", "aaaaaaaalq", "aaaaaaaalr", "aaaaaaaals",
        "aaaaaaaalt", "aaaaaaaalu", "aaaaaaaalv", "aaaaaaaalw", "aaaaaaaalx",
        "aaaaaaaaly", "aaaaaaaalz", "aaaaaaaama", "aaaaaaaamb", "aaaaaaaamc",
        "aaaaaaaamd", "aaaaaaaame", "aaaaaaaamf", "aaaaaaaamg", "aaaaaaaamh",
        "aaaaaaaami", "aaaaaaaamj", "aaaaaaaamk", "aaaaaaaaml", "aaaaaaaamm",
        "aaaaaaaamn", "aaaaaaaamo", "aaaaaaaamp", "aaaaaaaamq", "aaaaaaaamr",
        "aaaaaaaams", "aaaaaaaamt", "aaaaaaaamu", "aaaaaaaamv", "aaaaaaaamw",
        "aaaaaaaamx", "aaaaaaaamy", "aaaaaaaamz", "aaaaaaaana", "aaaaaaaanb",
        "aaaaaaaanc", "aaaaaaaand", "aaaaaaaane", "aaaaaaaanf", "aaaaaaaang",
        "aaaaaaaanh", "aaaaaaaani", "aaaaaaaanj", "aaaaaaaank", "aaaaaaaanl",
        "aaaaaaaanm", "aaaaaaaann", "aaaaaaaano", "aaaaaaaanp", "aaaaaaaanq",
        "aaaaaaaanr", "aaaaaaaans", "aaaaaaaant", "aaaaaaaanu", "aaaaaaaanv",
        "aaaaaaaanw", "aaaaaaaanx", "aaaaaaaany", "aaaaaaaanz", "aaaaaaaaoa",
        "aaaaaaaaob", "aaaaaaaaoc", "aaaaaaaaod", "aaaaaaaaoe", "aaaaaaaaof",
        "aaaaaaaaog", "aaaaaaaaoh", "aaaaaaaaoi", "aaaaaaaaoj", "aaaaaaaaok",
        "aaaaaaaaol", "aaaaaaaaom", "aaaaaaaaon", "aaaaaaaaoo", "aaaaaaaaop",
        "aaaaaaaaoq", "aaaaaaaaor", "aaaaaaaaos", "aaaaaaaaot", "aaaaaaaaou",
        "aaaaaaaaov", "aaaaaaaaow", "aaaaaaaaox", "aaaaaaaaoy", "aaaaaaaaoz",
        "aaaaaaaapa", "aaaaaaaapb", "aaaaaaaapc", "aaaaaaaapd", "aaaaaaaape",
        "aaaaaaaapf", "aaaaaaaapg", "aaaaaaaaph", "aaaaaaaapi", "aaaaaaaapj",
        "aaaaaaaapk", "aaaaaaaapl", "aaaaaaaapm", "aaaaaaaapn", "aaaaaaaapo",
        "aaaaaaaapp", "aaaaaaaapq", "aaaaaaaapr", "aaaaaaaaps", "aaaaaaaapt",
        "aaaaaaaapu", "aaaaaaaapv", "aaaaaaaapw", "aaaaaaaapx", "aaaaaaaapy",
        "aaaaaaaapz", "aaaaaaaaqa", "aaaaaaaaqb", "aaaaaaaaqc", "aaaaaaaaqd",
        "aaaaaaaaqe", "aaaaaaaaqf", "aaaaaaaaqg", "aaaaaaaaqh", "aaaaaaaaqi",
        "aaaaaaaaqj", "aaaaaaaaqk", "aaaaaaaaql", "aaaaaaaaqm", "aaaaaaaaqn",
        "aaaaaaaaqo", "aaaaaaaaqp", "aaaaaaaaqq", "aaaaaaaaqr", "aaaaaaaaqs",
        "aaaaaaaaqt", "aaaaaaaaqu", "aaaaaaaaqv", "aaaaaaaaqw", "aaaaaaaaqx",
        "aaaaaaaaqy", "aaaaaaaaqz", "aaaaaaaara", "aaaaaaaarb", "aaaaaaaarc",
        "aaaaaaaard", "aaaaaaaare", "aaaaaaaarf", "aaaaaaaarg", "aaaaaaaarh",
        "aaaaaaaari", "aaaaaaaarj", "aaaaaaaark", "aaaaaaaarl", "aaaaaaaarm",
        "aaaaaaaarn", "aaaaaaaaro", "aaaaaaaarp", "aaaaaaaarq", "aaaaaaaarr",
        "aaaaaaaars", "aaaaaaaart", "aaaaaaaaru", "aaaaaaaarv", "aaaaaaaarw",
        "aaaaaaaarx", "aaaaaaaary", "aaaaaaaarz", "aaaaaaaasa", "aaaaaaaasb",
        "aaaaaaaasc", "aaaaaaaasd", "aaaaaaaase", "aaaaaaaasf", "aaaaaaaasg",
        "aaaaaaaash", "aaaaaaaasi", "aaaaaaaasj", "aaaaaaaask", "aaaaaaaasl",
        "aaaaaaaasm", "aaaaaaaasn", "aaaaaaaaso", "aaaaaaaasp", "aaaaaaaasq",
        "aaaaaaaasr", "aaaaaaaass", "aaaaaaaast", "aaaaaaaasu", "aaaaaaaasv",
        "aaaaaaaasw", "aaaaaaaasx", "aaaaaaaasy", "aaaaaaaasz", "aaaaaaaata",
        "aaaaaaaatb", "aaaaaaaatc", "aaaaaaaatd", "aaaaaaaate", "aaaaaaaatf",
        "aaaaaaaatg", "aaaaaaaath", "aaaaaaaati", "aaaaaaaatj", "aaaaaaaatk",
        "aaaaaaaatl", "aaaaaaaatm", "aaaaaaaatn", "aaaaaaaato", "aaaaaaaatp",
        "aaaaaaaatq", "aaaaaaaatr", "aaaaaaaats", "aaaaaaaatt", "aaaaaaaatu",
        "aaaaaaaatv", "aaaaaaaatw", "aaaaaaaatx", "aaaaaaaaty", "aaaaaaaatz",
        "aaaaaaaaua", "aaaaaaaaub", "aaaaaaaauc", "aaaaaaaaud", "aaaaaaaaue",
        "aaaaaaaauf", "aaaaaaaaug", "aaaaaaaauh", "aaaaaaaaui", "aaaaaaaauj",
        "aaaaaaaauk", "aaaaaaaaul", "aaaaaaaaum", "aaaaaaaaun", "aaaaaaaauo",
        "aaaaaaaaup", "aaaaaaaauq", "aaaaaaaaur", "aaaaaaaaus", "aaaaaaaaut",
        "aaaaaaaauu", "aaaaaaaauv", "aaaaaaaauw", "aaaaaaaaux", "aaaaaaaauy",
        "aaaaaaaauz", "aaaaaaaava", "aaaaaaaavb", "aaaaaaaavc", "aaaaaaaavd",
        "aaaaaaaave", "aaaaaaaavf", "aaaaaaaavg", "aaaaaaaavh", "aaaaaaaavi",
        "aaaaaaaavj", "aaaaaaaavk", "aaaaaaaavl", "aaaaaaaavm", "aaaaaaaavn",
        "aaaaaaaavo", "aaaaaaaavp", "aaaaaaaavq", "aaaaaaaavr", "aaaaaaaavs",
        "aaaaaaaavt", "aaaaaaaavu", "aaaaaaaavv", "aaaaaaaavw", "aaaaaaaavx",
        "aaaaaaaavy", "aaaaaaaavz", "aaaaaaaawa", "aaaaaaaawb", "aaaaaaaawc",
        "aaaaaaaawd", "aaaaaaaawe", "aaaaaaaawf", "aaaaaaaawg", "aaaaaaaawh",
        "aaaaaaaawi", "aaaaaaaawj", "aaaaaaaawk", "aaaaaaaawl", "aaaaaaaawm",
        "aaaaaaaawn", "aaaaaaaawo", "aaaaaaaawp", "aaaaaaaawq", "aaaaaaaawr",
        "aaaaaaaaws", "aaaaaaaawt", "aaaaaaaawu", "aaaaaaaawv", "aaaaaaaaww",
        "aaaaaaaawx", "aaaaaaaawy", "aaaaaaaawz", "aaaaaaaaxa", "aaaaaaaaxb",
        "aaaaaaaaxc", "aaaaaaaaxd", "aaaaaaaaxe", "aaaaaaaaxf", "aaaaaaaaxg",
        "aaaaaaaaxh", "aaaaaaaaxi", "aaaaaaaaxj", "aaaaaaaaxk", "aaaaaaaaxl",
        "aaaaaaaaxm", "aaaaaaaaxn", "aaaaaaaaxo", "aaaaaaaaxp", "aaaaaaaaxq",
        "aaaaaaaaxr", "aaaaaaaaxs", "aaaaaaaaxt", "aaaaaaaaxu", "aaaaaaaaxv",
        "aaaaaaaaxw", "aaaaaaaaxx", "aaaaaaaaxy", "aaaaaaaaxz", "aaaaaaaaya",
        "aaaaaaaayb", "aaaaaaaayc", "aaaaaaaayd", "aaaaaaaaye", "aaaaaaaayf",
        "aaaaaaaayg", "aaaaaaaayh", "aaaaaaaayi", "aaaaaaaayj", "aaaaaaaayk",
        "aaaaaaaayl", "aaaaaaaaym", "aaaaaaaayn", "aaaaaaaayo", "aaaaaaaayp",
        "aaaaaaaayq", "aaaaaaaayr", "aaaaaaaays", "aaaaaaaayt", "aaaaaaaayu",
        "aaaaaaaayv", "aaaaaaaayw", "aaaaaaaayx", "aaaaaaaayy", "aaaaaaaayz",
        "aaaaaaaaza", "aaaaaaaazb", "aaaaaaaazc", "aaaaaaaazd", "aaaaaaaaze",
        "aaaaaaaazf", "aaaaaaaazg", "aaaaaaaazh", "aaaaaaaazi", "aaaaaaaazj",
        "aaaaaaaazk", "aaaaaaaazl", "aaaaaaaazm", "aaaaaaaazn", "aaaaaaaazo",
        "aaaaaaaazp", "aaaaaaaazq", "aaaaaaaazr", "aaaaaaaazs", "aaaaaaaazt",
        "aaaaaaaazu", "aaaaaaaazv", "aaaaaaaazw", "aaaaaaaazx", "aaaaaaaazy",
        "aaaaaaaazz"};

    vector<string> actual = solution.findWords(board, words);
    vector<string> expected = {
        "aaaaaaaaij", "aaaaaaaaih", "aaaaaaaaaj", "aaaaaaaaaa", "aaaaaaaaah",
        "aaaaaaaagh", "aaaaaaaagf", "aaaaaaaaaf", "aaaaaaaaap", "aaaaaaaaon",
        "aaaaaaaaop", "aaaaaaaaef", "aaaaaaaaed", "aaaaaaaaar", "aaaaaaaaqp",
        "aaaaaaaaqr", "aaaaaaaaad", "aaaaaaaaat", "aaaaaaaasr", "aaaaaaaast",
        "aaaaaaaacd", "aaaaaaaacb", "aaaaaaaaav", "aaaaaaaaut", "aaaaaaaauv",
        "aaaaaaaajk", "aaaaaaaaji", "aaaaaaaaak", "aaaaaaaaai", "aaaaaaaahi",
        "aaaaaaaahg", "aaaaaaaaag", "aaaaaaaaao", "aaaaaaaafg", "aaaaaaaafe",
        "aaaaaaaaaq", "aaaaaaaapo", "aaaaaaaapq", "aaaaaaaabc", "aaaaaaaabm",
        "aaaaaaaanm", "aaaaaaaano", "aaaaaaaaae", "aaaaaaaaas", "aaaaaaaarq",
        "aaaaaaaars", "aaaaaaaade", "aaaaaaaadc", "aaaaaaaaau", "aaaaaaaats",
        "aaaaaaaatu", "aaaaaaaakl", "aaaaaaaakj", "aaaaaaaaal", "aaaaaaaaab",
        "aaaaaaaaan", "aaaaaaaalk", "aaaaaaaaac", "aaaaaaaaay", "aaaaaaaaaw",
        "aaaaaaaavu", "aaaaaaaavw", "aaaaaaaaaz", "aaaaaaaayz", "aaaaaaaayx",
        "aaaaaaaawv", "aaaaaaaawx", "aaaaaaaaza", "aaaaaaaazy"};

    sort(actual.begin(), actual.end());
    sort(expected.begin(), expected.end());
    EXPECT_EQ(actual, expected);
}

TEST_F(Solution1Test, TestCase10) {
    vector<vector<char>> board = {{'o', 'a', 'b', 'n'},
                                  {'o', 't', 'a', 'e'},
                                  {'a', 'h', 'k', 'r'},
                                  {'a', 'f', 'l', 'v'}};
    vector<string> words = {"oa", "oaa"};

    vector<string> actual = solution.findWords(board, words);
    vector<string> expected = {"oa", "oaa"};

    sort(actual.begin(), actual.end());
    sort(expected.begin(), expected.end());
    EXPECT_EQ(actual, expected);
}