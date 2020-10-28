### KD Tree 原理

KD Tree是一个较为简单的数据结构。其维护高维点集信息。通过对输入的数据进行预处理，在之后能够高效地查询输入点距离最近的点，距离最远的点。在查询的过程中使用优先级队列进行记录，可以查询距离最近的K个点，距离最远的K个点。

如下是一个示例。

![](KDTree/1.png)

![](KDTree/2.png)

#### 建树

为了保证树的高度极可能低，在当前点集中，选择某一维度的中位数来进行划分。选择的维度为当前点集中最分散的一维。这里涉及到将一个数据划分为两部分，存在高效地算法，STL已经实现了`nth_element`函数。具体实现思想是基于快速排序的划分函数。

```c++
    // 构建KDtree
    int _build(int l, int r) {
        if (l > r) return NULL_CHILD;
        int mid = l + r >> 1;
       	// 统计各个维度的方差
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
      	
      	// 按照方差最大的一维进行划分
        if (vax >= vay) {
            data[mid].dim = 1;
            nth_element(data.begin(), data.begin() + mid, data.end(), cmp1);
        } else {
            data[mid].dim = 2;
            nth_element(data.begin(), data.begin() + mid, data.end(), cmp2);
        }
				
      	// 递归创建左右子树
        data[mid].lc = _build(l, mid - 1);
        data[mid].rc = _build(mid + 1, r);
      
      	// 利用子树的信息更新父节点信息
        pushup(mid);
        return mid;
    }

```

#### 查询

输入一个点时，希望查询当前子树中距离最近的点和最远的点。

如果直接在KDTree上进行遍历的话，时间复杂度过高，希望有些方法可以进行剪枝。

我们在每个节点维护其子树的所有点的各个维度的最大值和最小值，也就得到了一个矩形的边界。

然后我们求输入点和这个矩形内任意一点的最大值和最小值，用作估价函数。

当求最小值的时候，发下到矩形内的任意一点的最小值都大于当前已经找到的值，则直接回溯。求最大值同理。

这样平均查询复杂度可以达到`log N`。

```c++
    // 在某棵子树中查询最小值
    void _get_min_dis(const Node& a, int l, int r) {
        if (l > r) return ;
        int mid = l + r >> 1;
        min_dis = min(min_dis, get_dis(a, data[mid]));
        double l_min_dis = estimage_min_dis(a, data[data[mid].lc].x_min, data[data[mid].lc].x_max, data[data[mid].lc].y_min, data[data[mid].lc].x_max);
        double r_min_dis = estimage_min_dis(a, data[data[mid].rc].x_min, data[data[mid].rc].x_max,data[data[mid].rc].y_min, data[data[mid].rc].x_max);
        if (l_min_dis < min_dis && r_min_dis < min_dis) {
            if (l_min_dis < r_min_dis) {  // 先从最小的里面开始查，启发式搜索
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
```

#### 插入与删除

按照当前节点划分的维度来判断进入左子树还是有子树。最终在树中创建一个新的节点。

可以引入平衡因子，但左子树和右子树的节点数超过平衡因子的阈值之后，就对这个子树进行重构。

删除的操作类似。



