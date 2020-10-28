/**
 * KD Tree 较为工程化的实现
 *
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Node {
public:
    double x, y; // 存储点坐标
    int lc, rc; // 存储左右孩子
    int dim; // 存储当前节点划分的维度
    double x_min, x_max, y_min, y_max; // 记录当前节点代表的子树中的矩形的范围
    Node(double _x=0, double _y=0) : x(_x), y(_y){}
};


class KDTree {

public:
    explicit KDTree(vector<Node> &&points) {
        build(move(points));
    }

    // 通过输入一个vector来重新创建一颗树
    void build(vector<Node> &&points) {
        data = points;
        _build(0, data.size() - 1);
    }

    // 输入一个点，查询现有点到这个点的最近距离
    double query_min_dis(const Node &q) {
        min_dis = INF;
        _get_min_dis(q, 0, data.size() - 1);
        return min_dis;
    }

    // 输入一个点，查询现在点到这个点的最远距离
    double query_max_dis(const Node &q)  {
        max_dis = -INF;
        _get_max_dis(q, 0, data.size() - 1);
        return max_dis;
    }

private:

    constexpr static int NULL_CHILD = -1;
    constexpr static double INF = 2e18;
    vector<Node> data;

    // 两个维度的比较函数
    function<bool(const Node&, const Node&)> cmp1 = [](const Node &a, const Node &b) -> bool {return a.x < b.x;};
    function<bool(const Node&, const Node&)> cmp2 = [](const Node &a, const Node &b) -> bool {return a.y < b.y;};

    // 查询的时候作为全局变量来使用
    double min_dis = INF;
    double max_dis = -INF;


    template<class T>
    T sqr(T a) {return a * a;}


    // 得到点a到矩形范围内所有点的最小值
    double estimage_min_dis(const Node& a, double x_min, double x_max, double y_min, double y_max) {
        double res = 0;
        if (a.x < x_min) res += sqr(a.x - x_min);
        if (a.x > x_max) res += sqr(a.x - x_max);
        if (a.y < y_min) res += sqr(a.y - y_min);
        if (a.y > y_max) res += sqr(a.y - y_max);
        return res;
    }

    // 得到点a到矩形范围内所有点的最ax大值
    double estimage_max_dis(const Node& a, double x_min, double x_max, double y_min, double y_max) {
        double res = 0;
        res += max(sqr(a.x - x_max), sqr(a.x - x_min));
        res += max(sqr(a.y - y_max), sqr(a.y - y_min));
        return res;
    }


    double get_dis(const Node&a, const Node &b) {
        return sqr(a.x - b.x) + sqr(a.y - b.y);
    }


    // 利用孩子节点代表的矩形的范围更新自己的矩形的范围
    void pushup(int mid) {
        data[mid].x_min = data[mid].x_max = data[mid].x;
        data[mid].y_min = data[mid].y_max = data[mid].y;
        if (data[mid].lc != NULL_CHILD) {
            data[mid].x_min = min(data[mid].x_min, data[data[mid].lc].x_min);
            data[mid].x_max = max(data[mid].x_max, data[data[mid].lc].x_max);
            data[mid].y_min = min(data[mid].y_min, data[data[mid].lc].y_min);
            data[mid].y_max = max(data[mid].y_max, data[data[mid].lc].y_max);
        }
        if (data[mid].rc != NULL_CHILD) {
            data[mid].x_min = min(data[mid].x_min, data[data[mid].rc].x_min);
            data[mid].x_max = max(data[mid].x_max, data[data[mid].rc].x_max);
            data[mid].y_min = min(data[mid].y_min, data[data[mid].rc].y_min);
            data[mid].y_max = max(data[mid].y_max, data[data[mid].rc].y_max);
        }
    }



    // 构建KDtree
    int _build(int l, int r) {
        if (l > r) return NULL_CHILD;
        int mid = l + r >> 1;
        double avx = 0, avy = 0, vax = 0, vay = 0;
        for (int i = l; i <= r; i ++) {
            avx += data[i].x;
            avy += data[i].y;
        }
        avx /= static_cast<double>(r - l + 1);
        avy /= static_cast<double>(r - l + 1);
        for (int i = l; i <= r; i ++) {
            vax += sqr<double>(avx - data[i].x);
            vay += sqr<double>(avy - data[i].y);
        }
        if (vax >= vay) {
            data[mid].dim = 1;
            nth_element(data.begin(), data.begin() + mid, data.end(), cmp1);
        } else {
            data[mid].dim = 2;
            nth_element(data.begin(), data.begin() + mid, data.end(), cmp2);
        }

        data[mid].lc = _build(l, mid - 1);
        data[mid].rc = _build(mid + 1, r);
        pushup(mid);
        return mid;
    }


    // 在某棵子树中查询最小值
    void _get_min_dis(const Node& a, int l, int r) {
        if (l > r) return ;
        int mid = l + r >> 1;
        min_dis = min(min_dis, get_dis(a, data[mid]));
        double l_min_dis = estimage_min_dis(a, data[data[mid].lc].x_min, data[data[mid].lc].x_max, data[data[mid].lc].y_min, data[data[mid].lc].x_max);
        double r_min_dis = estimage_min_dis(a, data[data[mid].rc].x_min, data[data[mid].rc].x_max,data[data[mid].rc].y_min, data[data[mid].rc].x_max);
        if (l_min_dis < min_dis && r_min_dis < min_dis) {
            if (l_min_dis < r_min_dis) {
                _get_min_dis(a, l, mid - 1);
                if (r_min_dis < min_dis) _get_min_dis(a, mid + 1, r);
            } else {
                _get_min_dis(a, mid + 1, r);
                if (l_min_dis < min_dis) _get_min_dis(a, l, mid - 1);
            }
        } else {
            if (l_min_dis < min_dis) _get_min_dis(a, l, mid - 1);
            if (r_min_dis < min_dis) _get_min_dis(a, mid + 1, r);
        }
    }

    // 在某棵子树中查询最大值
    void _get_max_dis(const Node &a, int l, int r) {
        if (l > r) return ;
        int mid = l + r >> 1;
        max_dis = max(max_dis, get_dis(a, data[mid]));
        double l_max_dis = estimage_max_dis(a, data[data[mid].lc].x_min, data[data[mid].lc].x_max, data[data[mid].lc].y_min, data[data[mid].lc].x_max);
        double r_max_dis = estimage_max_dis(a, data[data[mid].rc].x_min, data[data[mid].rc].x_max,data[data[mid].rc].y_min, data[data[mid].rc].x_max);
        if (l_max_dis > max_dis && r_max_dis > max_dis) {
            if (l_max_dis > r_max_dis) {
                _get_max_dis(a, l, mid - 1);
                if (r_max_dis > max_dis) _get_max_dis(a, mid + 1, r);
            } else {
                _get_max_dis(a, mid + 1, r);
                if (l_max_dis > max_dis) _get_max_dis(a, l, mid - 1);
            }
        } else {
            if (l_max_dis > max_dis) _get_max_dis(a, l, mid - 1);
            if (r_max_dis > max_dis) _get_max_dis(a, mid + 1, r);
        }
    }

};


int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<Node> data(n);
    for (int i = 0; i < n; i ++) cin >> data[i].x >> data[i].y;
    KDTree kdTree(move(data));
    while (m --) {
        double x, y;
        cin >> x >> y;
        cout << kdTree.query_min_dis(Node(x, y)) << " " << kdTree.query_max_dis(Node(x, y)) << endl;
    }
    return 0;
}
