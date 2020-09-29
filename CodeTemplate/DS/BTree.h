//
// Created by wangdh on 2020/9/28.
//

#ifndef CONTEST_BTREE_H
#define CONTEST_BTREE_H

#include <iostream>
#include <vector>
using namespace std;

class Node {

public:
    int deg;
    vector<int> key;
    vector<Node*> child;
    Node(int de) : deg(de), key(vector<int>(de)), child(vector<Node*>(de)) {}

};

class BTree {

};


#endif //CONTEST_BTREE_H
