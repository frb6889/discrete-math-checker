#include <iostream>
#include <utility> // 包含 std::pair
#include <vector>
using namespace std;
// 实验1:邻接矩阵/权矩阵，关联矩阵，邻接表，正向表，逆向表
//  g++ -o cha1 cha1.cpp

/* 
输入格式：
第一行四个正整数n,m, type1 和type2 。
其中 n 和m 分别表示图的点数和边数。 
type1=0 表示该图为无向图，type1=1 表示该图为有向图。 
type2=0 表示该图不是赋权图，type2=1 表示该图是赋权图。

如果 type2=0 ，接下来 m 行，每行两个正整数 u 和 v 表示一条边。
如果 type2=1 ，接下来 m 行，每行三个正整数 u, v 和 d 表示一条边，其中 d 为这条边的边权。 */

/* 
2020.1.
5 9 1 0
1 2
1 3
1 4
5 1
3 2
2 3
2 5
3 4
5 4
 */
int main()
{
    int n[4];
    for (int i = 0; i < 4; i++)
    {
        cin >> n[i];
    }
    int mnum = n[1];

    // --m储存边信息--
    int x;
    if (n[3] == 0)
        x = 2;
    else if (n[3] == 1)
        x = 3;
    int m[mnum][x];

    for (int i = 0; i < n[1]; i++)
    {
        if (n[3] == 0)
            cin >> m[i][0] >> m[i][1];
        else if (n[3] == 1)
            cin >> m[i][0] >> m[i][1] >> m[i][2];
    }

    // -------声明-------
    int g1[n[0]][n[0]];
    /* 1.邻接矩阵或权矩阵.*/

    int g2[n[0]][n[0]];
    /* 2.关联矩阵.*/

    vector<vector<int> > g3(n[0]);

    vector<vector<int> > g31(n[0]);
    vector<vector<int> > g32(n[0]);
    /*3.邻接表。4.正向表。*/

    vector<vector<int> > g4(n[0]);
    vector<vector<int> > g41(n[0]);
    vector<vector<int> > g42(n[0]);
    /*5.逆向表。*/

    for (int i = 0; i < n[0]; ++i)
    {
        for (int j = 0; j < n[0]; ++j)
            g1[i][j] = 0;
        if (n[3] == 0)
        {
            for (int k = 0; k < n[1]; ++k)
                g2[i][k] = 0;
        }
    }
    // 检查重边或自环
    bool has_Chongbian = false;
    bool has_Zihuan = false;
    for (int h = 0; h < mnum; h++)
    {
        for (int h2 = h + 1; h2 < mnum; h2++)
        {
            if ((m[h][0] == m[h2][0]) && (m[h][1] == m[h2][1]))
            {
                has_Chongbian = true;
                // cout << "有重边!";
            }
        }
        if (m[h][0] == m[h][1])
        {
            has_Zihuan = true;
            // cout << "有自环!";
        }
    }

    //-------录入数据-------

    // --邻接矩阵--
    for (int h = 0; h < mnum; h++)
    {

        // 如果无向,则 1 or 0.
        if (n[2] == 0)
        {
            if (n[3] == 0)
            {
                //--无向无权图--
                // 1.无权图,邻接矩阵
                if (has_Chongbian == false)
                {
                    g1[m[h][0] - 1][m[h][1] - 1] = 1;
                    g1[m[h][1] - 1][m[h][0] - 1] = 1;
                }
                // 2.无权图,关联矩阵
                if (has_Zihuan == false && n[3] == 0)
                {
                    g2[m[h][0] - 1][h] = 1;
                    g2[m[h][1] - 1][h] = 1;
                }
                // 无向无权图,邻接表添加所有邻接点
                g3[m[h][0] - 1].push_back(m[h][1]);
                g3[m[h][1] - 1].push_back(m[h][0]);
            }
            else if (n[3] == 1)
            {
                //--无向权图--
                // 1.权图,邻接矩阵记录权
                if (has_Chongbian == false)
                {
                    g1[m[h][0] - 1][m[h][1] - 1] = m[h][2];
                    g1[m[h][1] - 1][m[h][0] - 1] = m[h][2];
                }
                // 2.权图,不用输出关联矩阵

                // 3.邻接表
                // 无向权图,添加权值.
                /* g3[m[h][0] - 1].push_back(m[h][2]);
                g3[m[h][1] - 1].push_back(m[h][2]); */
                // 正向表
                // 先记录B, 链接的点;再记录Z,边权
                g31[m[h][0] - 1].push_back(m[h][1]);
                g32[m[h][0] - 1].push_back(m[h][2]);
                g31[m[h][1] - 1].push_back(m[h][0]);
                g32[m[h][1] - 1].push_back(m[h][2]);
            }
            // 无向图,不用生成逆向表
        }
        // 如果有向,则 1 -1 0.
        if (n[2] == 1)
        {
            if (n[3] == 0)
            {
                if (has_Chongbian == false)
                {
                    g1[m[h][0] - 1][m[h][1] - 1] = 1;
                }
                if (has_Zihuan == false)
                {

                    g2[m[h][0] - 1][h] = 1;
                    g2[m[h][1] - 1][h] = -1;
                }
                // 有向图,邻接表,只添加后继
                // g3[m[h][0]-1].insert(g3[m[h][0]-1].begin(), m[h][1]);
                g3[m[h][0] - 1].push_back(m[h][1]);
                // 输出两行, 表示向量A和向量B

                // 有向图,逆向表,后继点储存前驱
                g4[m[h][1] - 1].push_back(m[h][0]);
            }
            else if (n[3] == 1)
            {
                //--有向权图--
                // 1.权图,邻接矩阵记录权
                if (has_Chongbian == false)
                {
                    g1[m[h][0] - 1][m[h][1] - 1] = m[h][2];
                }
                // 2.权图,不用输出关联矩阵

                // 3.邻接表
                // 有向权图,添加权值.
                /* g3[m[h][0] - 1].push_back(m[h][2]);
                g3[m[h][1] - 1].push_back(m[h][2]); */
                // 正向表
                // 先记录B, 链接的点;再记录Z,边权
                g31[m[h][0] - 1].push_back(m[h][1]);
                g32[m[h][0] - 1].push_back(m[h][2]);
                g41[m[h][1] - 1].push_back(m[h][0]);
                g42[m[h][1] - 1].push_back(m[h][2]);
            }
        }
    }

    // -------输出-------
    cout << "邻接矩阵/权矩阵：" << endl;
    if (has_Chongbian == false)
    {
        for (int i = 0; i < n[0]; i++)
        {
            for (int j = 0; j < n[0]; j++)
            {
                cout << g1[i][j] << " ";
            }
            cout << endl;
        }
    }
    cout << endl;

    cout << "关联矩阵：" << endl;
    if (has_Zihuan == false && n[3] == 0)
    {
        for (int i = 0; i < n[0]; i++)
        {
            for (int j = 0; j < n[1]; j++)
            {
                cout << g2[i][j] << " ";
            }
            cout << endl;
        }
    }
    cout << endl;

    //--邻接表
    cout << "邻接表：" << endl;
    for (int i = 0; i < n[0]; ++i)
    {
        if (n[3] == 0)
        {
            for (int j = 0; j < g3[i].size(); ++j)
            {
                cout << g3[i][j] << " ";
            }

            cout << "\n";
        }
        else if (n[3] == 1)
        {
            for (int j = 0; j < g31[i].size(); ++j)
            {
                cout << g31[i][j] << " ";
                cout << g32[i][j] << " ";
            }
            cout << "\n";
        }
    }
    cout << endl;

    //--正向表: 将无向图中的每个点的邻接点/有向图中每个点的直接后继在一起存放,因此可以直接输出和?
    cout << "正向表:" << endl;
    if (n[3] == 0)
    {
        int pos = 1;
        cout << "正向表A:" << endl;
        // 正向表A就直接把邻接表的大小排在一起就可以了?
        cout << pos << " ";
        for (int i = 0; i < n[0]; ++i)
        {
            pos += g3[i].size();
            cout << pos << " ";
        }
        cout << endl;
        cout << "正向表B:" << endl;
        // 正向表B就把邻接表输出的内容放到一排就可以了?
        for (int i = 0; i < n[0]; ++i)
        {
            for (int j = 0; j < g3[i].size(); ++j)
            {
                cout << g3[i][j] << " ";
            }
        }
        cout << endl;
    }
    else if (n[3] == 1)
    {
        int pos_quan = 1;

        // 正向表A就直接把邻接表的大小排在一起就可以了?
        cout << "正向表A:" << endl;
        cout << pos_quan << " ";
        for (int i = 0; i < n[0]; ++i)
        {
            pos_quan += g31[i].size();
            cout << pos_quan << " ";
        }
        cout << endl;
        // 正向表B就把邻接表输出的内容放到一排就可以了?
        cout << "正向表B:" << endl;
        for (int i = 0; i < n[0]; ++i)
        {
            for (int j = 0; j < g31[i].size(); ++j)
            {
                cout << g31[i][j] << " ";
            }
        }
        cout << endl;
        for (int i = 0; i < n[0]; ++i)
        {
            for (int j = 0; j < g32[i].size(); ++j)
            {
                cout << g32[i][j] << " ";
            }
        }
        cout << endl;
    }
    cout << endl;

    //--逆向表: 当 有向n[2]==1 时候, 将点的直接前驱放在一起存放
    cout << "逆向表:" << endl;
    if (n[2] == 1)
    {
        if (n[3] == 0)
        {
            int pos_ni = 1;
            cout << pos_ni << " ";
            for (int i = 0; i < n[0]; ++i)
            {
                pos_ni += g4[i].size();
                cout << pos_ni << " ";
            }
            cout << endl;
            for (int i = 0; i < n[0]; ++i)
            {
                for (int j = 0; j < g4[i].size(); ++j)
                {
                    cout << g4[i][j] << " ";
                }
            }
            cout << endl;
        }
        else if (n[3] == 1)
        {
            int pos_ni_quan = 1;
            cout << pos_ni_quan << " ";
            for (int i = 0; i < n[0]; ++i)
            {
                pos_ni_quan += g41[i].size();
                cout << pos_ni_quan << " ";
            }
            cout << endl;
            // 正向表B就把邻接表输出的内容放到一排就可以了?
            for (int i = 0; i < n[0]; ++i)
            {
                for (int j = 0; j < g41[i].size(); ++j)
                {
                    cout << g41[i][j] << " ";
                }
            }
            cout << endl;
            for (int i = 0; i < n[0]; ++i)
            {
                for (int j = 0; j < g42[i].size(); ++j)
                {
                    cout << g42[i][j] << " ";
                }
            }
        }
    }
}