#include <bits/stdc++.h>
typedef long long int ll;
using namespace std;
int PageSize;
int BufferPages;
int findmin(vector<vector<int>> &X,vector<int> &Y)
{
    int minm = INT_MAX;
    for (int i = 0; i < Y.size(); i++)
    {
        if(Y[i]>=X[i].size())
        {
            continue;
        }
        minm = min(X[i][Y[i]],minm);
    }
    return minm;
}
int main()
{
    vector<vector<int>> X;
    vector<int> A;
    A.push_back(10);
    A.push_back(24);
    A.push_back(2);
    A.push_back(12);
    A.push_back(20);
    vector<int> B ;
    B.push_back(1);
    B.push_back(2);
    B.push_back(4);
    B.push_back(6);
    B.push_back(22);
    vector<int> C;
    C.push_back(5);
    C.push_back(7);
    C.push_back(9);
    C.push_back(8);
    C.push_back(6);
    vector<int> D;
    D.push_back(0);
    D.push_back(2);
    D.push_back(1);
    D.push_back(12);
    D.push_back(120);
    vector<int> E;
    E.push_back(1);
    E.push_back(4);
    E.push_back(2);
    E.push_back(12);
    E.push_back(0);
    sort(A.begin(),A.end());
    sort(B.begin(),B.end());
    sort(C.begin(),C.end());
    sort(D.begin(),D.end());
    sort(E.begin(),E.end());
    X.push_back(A);
    X.push_back(B);
    X.push_back(C);
    X.push_back(D);
    X.push_back(E);
    vector<int> Y(X.size(),0);
    while (1)
    {
        int y = findmin(X,Y);
        if(y==INT_MAX)
        {
            break;
        }
        // for (int i = 0; i < Y.size(); i++)
        // {
        //     cout<<Y[i]<<" ";
        // }
        for (int i = 0; i < Y.size(); i++)
        {
            if(Y[i]>=X[i].size())
            {
                continue;
            }
            if(y==X[i][Y[i]])
            {
                Y[i]++;
                break;
            }
        }
        // cout<<endl;
        // cout<<y<<endl;
        cout<<y<<" ";
    }
}