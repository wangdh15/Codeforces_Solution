/**
 *
 * 使用DLX解数独问题
 *
 * 将行看做决策，列看做约束。
 * 约束有四类，每个决策当做一行
 * 
 * https://www.acwing.com/problem/content/description/171/
 * 
 */

#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;

class DancingLinks {
public:
    //!! 构造函数，接收一个bool类型的矩阵，以及矩阵中最大的1的个数
    explicit DancingLinks(const vector<vector<bool>> &_matrix,  int _max_nodes) :
            cols(_matrix[0].size()),
            data(vector<Node>(_max_nodes)),
            col_size(vector<int>(_matrix[0].size() + 1)),
            free_idx(cols + 1) {
        for (int i = 0; i <= cols; i ++) {
            data[i].left = i - 1;
            data[i].right = i + 1;
            data[i].up = data[i].down = i;
        }
        data[0].left = cols;
        data[cols].right = 0;
        _init_with_matrix(_matrix);
    }

    ~DancingLinks() = default;

    //!! 对传入的矩阵进行求解，返回是否找到一个解
    bool solve() {return _solve();}

    //!! 如果存在解，则返回求得的解
    vector<int> get_one_solution() const {return one_solution;}


private:

    class Node {
    public:
        int left, right, down, up;
        int col, row;
    };

    int cols;
    vector<Node> data;  // 存储所有开好的节点
    vector<int> col_size;  // 存储每一类当前的1的个数
    int free_idx;  // 记录当前没有用到的节点下标
    vector<int> one_solution;  // 存储解得的一个解

    // 插入函数
    void _insert(int &head, int &tail, int x, int y) {
        data[free_idx].col = y;
        data[free_idx].row = x;
        data[free_idx].left = tail;
        data[free_idx].right = head;
        data[free_idx].up = y;
        data[free_idx].down = data[y].down;
        data[data[free_idx].left].right = free_idx;
        data[data[free_idx].right].left = free_idx;
        data[data[free_idx].up].down = free_idx;
        data[data[free_idx].down].up = free_idx;
        col_size[y] ++;
        tail = free_idx ++;
    }

    // 初始化函数
    void _init_with_matrix(const vector<vector<bool>> &_matrix) {
        int n = _matrix.size(), m = _matrix[0].size();
        for (int i = n - 1; i >= 0; i --) {
            int head = free_idx, tail = free_idx;
            for (int j = 0; j < m; j ++) {
                if (_matrix[i][j]) {
                    _insert(head, tail, i + 1, j + 1);
                }
            }
        }
    }


    // 删除某一列的函数
    void _remove(int p) {

        data[data[p].left].right = data[p].right;
        data[data[p].right].left = data[p].left;  // 将这一列从哨兵中删除

        // 找到这一列中的包含1的行，然后将每一行的所有元素都删掉，按行删除是将这一行的元素从它对应的列中删除
        for (int i = data[p].down; i != p; i = data[i].down) {
            for (int j = data[i].right; j != i; j = data[j].right) {
                data[data[j].up].down = data[j].down;
                data[data[j].down].up = data[j].up;
                col_size[data[j].col] --;
            }
        }
    }

    // 恢复某一列。和上面的删除操作是互逆操作
    void _resume(int p) {

        for (int i = data[p].up; i != p; i = data[i].up) {
            for (int j = data[i].left; j != i; j = data[j].left) {
                data[data[j].down].up = j;
                data[data[j].up].down = j;
                col_size[data[j].col] ++;
            }
        }
        data[data[p].right].left = p;
        data[data[p].left].right = p;
    }


    // 返回当前十字链表是否为空
    bool _empty() const {return !data[0].right;}


    // 得到列方向1最少的列
    int get_min_one_column() const {
        int ans = data[0].right;
        for (int i = data[0].right; i ; i = data[i].right) {
            if (col_size[i] < col_size[ans]) ans = i;
        }
        return ans;
    }

    // 求解函数
    bool _solve() {

        if (_empty()) return true;
        int p = get_min_one_column();
        _remove(p);
        for (int i = data[p].down; i != p; i = data[i].down) {  // 枚举当前列中包含一的每一行

            one_solution.push_back(data[i].row);
            for (int j = data[i].right; j != i; j = data[j].right) _remove(data[j].col);  // 将这一行中包含一的对应列都删除
            if (_solve()) return true;
            for (int j = data[i].left; j != i; j = data[j].left) _resume(data[j].col);
            one_solution.pop_back();
        }
        _resume(p);
        return false;
    }
};

char board[20][20];
const int N = 16 * 16 * 16 + 10;
int row[N], col[N], pl[N];

int main() {

    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    // cout.tie(nullptr);

    
    while (~scanf("%s", board[0])) {
        for (int i = 1; i <= 15; i ++) scanf("%s", board[i]);
        
        int cnt = 0;
        for (int i = 0; i < 16; i ++) {
            for (int j = 0; j < 16; j ++) {
                if (board[i][j] == '-') cnt ++;
            }
        }
        
        vector<vector<bool>> rec(cnt * 15 + 16 * 16, vector<bool>(16 * 16 * 4));
        int idx = 0;
        for (int i = 0; i < 16; i ++) {
            for (int j = 0; j < 16; j ++) {
                int a = 0, b = 15;
                if (board[i][j] != '-') a = b = board[i][j] - 'A';
                for (int k = a; k <= b; k ++) {
                    rec[idx][i * 16 + j] = true;
                    rec[idx][256 + i * 16 + k] = true;
                    rec[idx][256 * 2 + j * 16 + k] = true;
                    rec[idx][256 * 3 + (i  / 4 * 4 + j / 4) * 16 + k] = true;
                    row[idx + 1] = i;
                    col[idx + 1] = j;
                    pl[idx + 1] = k;
                    idx ++;
                }
            }
        }
        DancingLinks d(rec, 16 * 16 * 16 * 4);
        bool res = d.solve();
    
        for (auto x : d.get_one_solution()) {
            board[row[x]][col[x]] = pl[x] + 'A';
        }
        for (int i = 0; i < 16; i ++) {
            for (int j = 0; j < 16; j ++) {
                cout << board[i][j];
            }
            cout << '\n';
        }
        cout << '\n';
    }
    return 0;

}
