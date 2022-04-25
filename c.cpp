#include <bits/stdc++.h>
typedef long long int ll;
using namespace std;
int PageSize;
int BufferPages;
class Page
{
private:
public:
    vector<int> Data;
};
class ExternalData
{
private:
public:
    vector<Page *> Pages;
    void add(int x)
    {
        if (Pages.size() == 0)
        {
            Page *head = new Page();
            head->Data.push_back(x);
            Pages.push_back(head);
            return;
        }
        else
        {
            if (Pages[Pages.size() - 1]->Data.size() == PageSize)
            {
                Page *ptr = new Page();
                ptr->Data.push_back(x);
                Pages.push_back(ptr);
            }
            else
            {
                Pages[Pages.size() - 1]->Data.push_back(x);
            }
        }
        return;
    }
};
class Memory
{
private:
public:
    vector<Page *> A;
    Memory(int n)
    {
        for (int i = 0; i < n; i++)
        {
            Page *x = new Page();
            A.push_back(x);
        }
    }
    void Sort(vector<Page *> &Pages)
    {
        for (int i = 0; i < Pages.size(); i++)
        {
            sort(Pages[i]->Data.begin(), Pages[i]->Data.end());
        }
        // cout<<" Naman ";
        return;
    }
    void CompleteSort(vector<Page *> &Pages)
    {
        for (int i = 2; i <= Pages.size(); i = i * 2)
        {
            for (int k = 0; k < Pages.size(); k = k + i)
            {
                vector<int> C;
                for (int j = k; j < k + i / 2; j++)
                {
                    if (j >= Pages.size())
                    {
                        break;
                    }
                    else
                    {
                        C.insert(C.end(), Pages[j]->Data.begin(), Pages[j]->Data.end());
                    }
                }
                for (int j = k + i / 2; j < k + i; j++)
                {
                    if (j >= Pages.size())
                    {
                        break;
                    }
                    else
                    {
                        C.insert(C.end(), Pages[j]->Data.begin(), Pages[j]->Data.end());
                    }
                }
                sort(C.begin(), C.end());
                int y = 0;
                for (int j = 0; j<C.size(); j++)
                {
                    Pages[y+k]->Data.clear();
                    int o = 0;
                    while (o<3)
                    {
                        Pages[y+k]->Data.push_back(C[j]);
                        o++;
                    }
                }
            }
        }

        return;
    }
    void print(vector<Page *> &Pages)
    {
        for (int i = 0; i < Pages.size(); i++)
        {
            cout << i << " : " << endl;
            for (int j = 0; j < Pages[i]->Data.size(); j++)
            {
                cout << Pages[i]->Data[j] << " ";
            }
            cout << endl;
        }
    }
};
int main()
{
    cin >> BufferPages;
    cin >> PageSize;
    int dataRecords;
    cin >> dataRecords;
    ExternalData *dataFile = new ExternalData();
    for (int i = 0; i < dataRecords; i++)
    {
        int x;
        cin >> x;
        dataFile->add(x);
    }
    Memory B(BufferPages);
    B.Sort(dataFile->Pages);

    return 0;
}