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
    Page *next;
    bool empty;
    Page()
    {
        next = nullptr;
        empty = false;
    }
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
                Pages[Pages.size() - 1]->next = ptr;
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
    void print()
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
class Memory
{
private:
public:
    vector<Page *> A;
    int memPages;
    Memory(int n)
    {
        memPages = n;
        for (int i = 0; i < n; i++)
        {
            Page *x = new Page();
            A.push_back(x);
        }
        
    }
    void SortSinglePage(vector<Page *> &Pages)
    {
        if (Pages.size() == 0)
        {
            return;
        }
        for (int i = 0; i < Pages.size(); i++)
        {
            sort(Pages[i]->Data.begin(), Pages[i]->Data.end());
        }
        return;
    }
    void Sort(vector<Page *> &Pages)
    {
        vector<int> T(memPages+1,0);
        // pass 0
        SortSinglePage(Pages);
        // pass 1
        // for (int i = 0; i < Pages.size(); i++)
        // {
        //     cout << i << " : " << endl;
        //     for (int j = 0; j < Pages[i]->Data.size(); j++)
        //     {
        //         cout << Pages[i]->Data[j] << " ";
        //     }
        //     cout << endl;
        // }
        Pass(Pages, memPages, 1);
        // for (int i = 0; i < Pages.size(); i++)
        // {
        //     cout << i << " : " << endl;
        //     for (int j = 0; j < Pages[i]->Data.size(); j++)
        //     {
        //         cout << Pages[i]->Data[j] << " ";
        //     }
        //     cout << endl;
        // }
        Pass(Pages,memPages,memPages-1);
        // for (int i = 0; i < Pages.size(); i++)
        // {
        //     cout << i << " : " << endl;
        //     for (int j = 0; j < Pages[i]->Data.size(); j++)
        //     {
        //         cout << Pages[i]->Data[j] << " ";
        //     }
        //     cout << endl;
        // }
        return;
    }
    void Pass(vector<Page *> &Pages, int B, int z)
    {
        // B Capacity of Memory Buffer
        // NOW EXTERNAL MEMORY IS SORTED IN GROUP OF z PAGES
        // B-1 TIMES COMBINE z -> z*(B-1) after this program
        // X and Z two arrays
        // X -> DATA SIZE //COUNTER
        // Z -> PAGES TILL NOW SORTED
        // // //
        vector<int> Storage;
        int n = ceil(Pages.size() * 1.0 / (z * (B - 1)));
        cout << n << endl;
        for (int i = 0; i < Pages.size(); i++)
        {
            cout << i << " : " << endl;
            for (int j = 0; j < Pages[i]->Data.size(); j++)
            {
                cout << Pages[i]->Data[j] << " ";
            }
            cout << endl;
        }
        for (int i = 0; i < n; i++)
        {
            vector<int> X(B - 1, 0);
            vector<int> Z(B - 1, 0);
            for (int j = 0; j < B - 1; j++)
            {
                // cout<<j<<endl<<endl<<endl;
                if ((j + i*(B - 1))*z>= Pages.size())
                {
                    cout<<"null "<<endl;
                    A[j] = nullptr;
                }
                else
                {
                    // " "<<Pages[j + i * (B - 1)]->Data.size()
                    cout<<i<<" "<<j<<endl;
                    cout<<"notnull "<<(j + i * (B - 1))*z<<endl;
                    if(i>1)
                    {
                        cout<<"Hello"<<endl;
                        // for (int h = 0; h < Pages[j + i * (B - 1)]->Data.size() ; h++)
                        // {
                        //     cout<<Pages[j + i * (B - 1)]->Data[h]<<endl;
                        // }
                    }
                    A[j] = new Page();
                    A[j]->Data.insert(A[j]->Data.begin(),Pages[(j + i * (B - 1))*z]->Data.begin(),Pages[(j + i * (B - 1))*z]->Data.end());
                }
            }
            // cout<<endl;
            // cout<<"Reached"<<endl;
            // for (int j = 0; j < A.size(); j++)
            // {
            //     cout << i << " ";
            //     if (A[j] == nullptr)
            //     {
            //         cout << "nullptr"
            //              << " ";
            //              continue;
            //     }
            //     for (int k = 0; k < A[j]->Data.size(); k++)
            //     {
            //         cout << A[j]->Data[k] << " ";
            //     }
            //     cout << endl;
            // }
            int alpha = i;
            // cout<<"Reached";
            int r = findminm(Pages, X, Z, z, alpha);
            int n = 0;
            while (r != INT_MAX)
            {
                // cout <<r <<" ";
                Storage.push_back(r);
                r = findminm(Pages, X, Z, z, alpha);
                n++;
            }
            // cout<<endl;
        }
        cout<<endl<<"Storage: ";
        for (int i = 0; i < Storage.size(); i++)
        {
            cout << Storage[i] << " ";
        }
        cout << endl;
        int k = 0;
        for (int i = 0; i < Pages.size(); i++)
        {
            Pages[i]->Data.clear();
            for(int j = 0; j<PageSize; j++)
            {
                if(k<Storage.size())
                {
                   Pages[i]->Data.push_back(Storage[k]);
                   k++;
                }
            }
        }
    }
    int findminm(vector<Page *> &Pages, vector<int> &X, vector<int> &Z, int z, int alpha)
    {
        int minm = INT_MAX;
        cout << "X "
             << " ";
        for (int i = 0; i < X.size(); i++)
        {
            cout << X[i] << " ";
        }
        cout << endl;
        cout << "Z "
             << " ";
        for (int i = 0; i < Z.size(); i++)
        {
            cout << Z[i] << " ";
        }
        cout << endl;
        for (int i = 0; i < A.size(); i++)
        {
            if (A[i] == nullptr)
            {
                continue;
            }
            if (X[i] >= A[i]->Data.size())
            {
                continue;
            }
            else
            {   
                cout<<A[i]->Data[X[i]]<<" ";
                minm = min(minm, A[i]->Data[X[i]]);
            }
        }
        cout<<endl;
        increment_counter(Pages, X, Z, minm, z, alpha);
        cout << minm<<endl;
        cout << "X "<< " ";
        for (int i = 0; i < X.size(); i++)
        {
            cout << X[i] << " ";
        }
        cout << endl;
        cout << "Z "<< " ";
        for (int i = 0; i < Z.size(); i++)
        {
            cout << Z[i] << " ";
        }
        cout << endl;
        return minm;
    }
    
    void increment_counter(vector<Page *> &Pages, vector<int> &X, vector<int> &Z, int minm, int z, int alpha)
    {
        if (minm == INT_MAX)
        {
            return;
        }
        for (int i = 0; i < A.size(); i++)
        {
            if(A[i]==nullptr)
            {
                continue;
            }
            if (A[i]->Data[X[i]] == minm)
            {
                if (X[i] < A[i]->Data.size())
                {
                    X[i]++;
                    if (X[i] == A[i]->Data.size() && Z[i] < z)
                    {
                        X[i] = 0;
                        Z[i] = Z[i] + 1;
                        if (Z[i] == z)
                        {
                            A[i] = nullptr;
                            return;
                        }
                        else
                        {
                            A[i] = Pages[(alpha * (A.size()-1)+i)*z] ;
                            // problem
                        }
                    }
                    return;
                }
                else
                {
                    if (Z[i] == z)
                    {
                        A[i] = nullptr;
                        return;
                    }
                }
            }
        }
        return;
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
    // dataFile->print();
    B.Sort(dataFile->Pages);
    // dataFile->print();
    return 0;
}
