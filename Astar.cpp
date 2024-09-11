#include <iostream>
#include <vector>
#include <cstring>
#include <limits>
#include <algorithm> 
using namespace std;

#define ROW 10
#define COL 10

#define ZXDJ 10
#define XXDJ 14
enum dirent { p_up, p_down, p_left, p_right, p_lup, p_ldown, p_rup, p_rdown };

struct mypoint {
    int row;
    int col;     // 记录当前的位置
    int f, g, h; // 量化评估
};

struct treeNode {
    mypoint pos;
    vector<treeNode*> child;
    treeNode* parent;  // 找父亲
};

// 创建树节点的函数
treeNode* creattreenode(int row, int col) {
    treeNode* pnew = new treeNode;
    memset(pnew, 0, sizeof(treeNode)); //void* memset(void* ptr, int value, size_t num);
    pnew->pos.row = row;
    pnew->pos.col = col;
    return pnew;
}

int getH(mypoint pos, mypoint endpos) {
    int x = abs(endpos.row - pos.row);
    int y = abs(endpos.col - pos.col);
    return 10 * (x + y);
}

int main() {
    int map[ROW][COL] = {
        {0,0,0,0,1,0,0,0,0,0},
        {0,0,0,0,1,0,0,0,0,0},
        {0,0,0,0,1,0,0,0,0,0},
        {0,0,0,0,1,0,0,0,0,0},
        {0,0,0,0,1,0,0,0,0,0},
        {0,0,0,0,1,0,0,0,0,0},
        {0,0,0,0,1,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,1,0,0,0,0,0},
        {0,0,0,0,1,0,0,0,0,0}
    };
    bool path[ROW][COL] = {0}; // 0 没有走过  1：走过
    mypoint beginpos = {2, 1};
    mypoint endpos = {6, 9};

    // 准备一棵树  起点就是树根
    treeNode* proot = creattreenode(beginpos.row, beginpos.col);
    vector<treeNode*> buff;
    path[beginpos.row][beginpos.col] = true;
    treeNode* pcurrent = proot;
    treeNode* pchild = nullptr;
    bool findend = false;

    // 从起点开始寻路
    while (true) {
        // 生成子节点
        for (int i = 0; i < 8; i++) {
            pchild = creattreenode(pcurrent->pos.row, pcurrent->pos.col);
            switch (i) {
                case p_up:
                    pchild->pos.row--;
                    pchild->pos.g += ZXDJ;
                    break;
                case p_down:
                    pchild->pos.row++;
                    pchild->pos.g += ZXDJ;
                    break;
                case p_left:
                    pchild->pos.col--;
                    pchild->pos.g += ZXDJ;
                    break;
                case p_right:
                    pchild->pos.col++;
                    pchild->pos.g += ZXDJ;
                    break;
                case p_lup:
                    pchild->pos.row--;
                    pchild->pos.col--;
                    pchild->pos.g += XXDJ;
                    break;
                case p_ldown:
                    pchild->pos.row++;
                    pchild->pos.col--;
                    pchild->pos.g += XXDJ;
                    break;
                case p_rup:
                    pchild->pos.row--;
                    pchild->pos.col++;
                    pchild->pos.g += XXDJ;
                    break;
                case p_rdown:
                    pchild->pos.row++;
                    pchild->pos.col++;
                    pchild->pos.g += XXDJ;
                    break;
            }

            // 检查新位置是否在范围内且未被阻塞
            if (pchild->pos.row >= 0 && pchild->pos.row < ROW &&
                pchild->pos.col >= 0 && pchild->pos.col < COL &&
                map[pchild->pos.row][pchild->pos.col] == 0 &&
                !path[pchild->pos.row][pchild->pos.col]) {

                // 计算 H 和 F
                pchild->pos.h = getH(pchild->pos, endpos);
                pchild->pos.f = pchild->pos.g + pchild->pos.h;

                // 添加到树和缓冲区
                pcurrent->child.push_back(pchild);
                pchild->parent = pcurrent;
                buff.push_back(pchild);
                path[pchild->pos.row][pchild->pos.col] = true;
            } else {
                delete pchild;
            }
        }

        // 检查缓冲区是否为空
        if (buff.empty()) {
            break;
        }

        // 查找最小 F 值的节点
        auto it = min_element(buff.begin(), buff.end(),
            [](const treeNode* a, const treeNode* b) {
                return a->pos.f < b->pos.f;
            });
        pcurrent = *it;
        buff.erase(it);

        // 检查是否找到终点
        if (pcurrent->pos.row == endpos.row && pcurrent->pos.col == endpos.col) {
            findend = true;
            break;
        }
    }

    // 打印结果
    if (findend) {
        cout << "找到终点了" << endl;
        vector<mypoint> pathToPrint;
        while (pcurrent) {
            pathToPrint.push_back(pcurrent->pos);
            pcurrent = pcurrent->parent;
        }
        for (auto it = pathToPrint.rbegin(); it != pathToPrint.rend(); ++it) {
            cout << "(" << it->row << "," << it->col << ")";
        }
        cout << endl;
    } else {
        cout << "没找到终点" << endl;
    }

    // 清理
    for (auto node : buff) {
        delete node;
    }

    return 0;
}
