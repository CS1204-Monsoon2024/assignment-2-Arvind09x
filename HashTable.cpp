#include <iostream>
using namespace std;
class HashTable
{
    int *table;//hashtable underlaying data structure
    int m;
    int t_vals;//total number of values inserted into the table
    double load_factor;
    public: HashTable(int cap)
        {
            load_factor = 0.8;
            t_vals = 0;
            m = cap;
            table = new int[m];
            for(int i = 0;i<m;i++)
            table[i] = -1;
        }
    private:
        int hash(int key)
        {
            return (key%m);
        }
        bool isprime(int n)
        {
            if(n == 2)
            return true;
            if(n%2 == 0)
            return false;
            int i = 3;
            while(i*i<=n)
            {
                if(n%i == 0)
                return false;

                i = i+2;
            }
            return true;
        }
        void resize()
        {
            int new_m = 2*m + 1;
            while(!isprime(new_m))
            {
                new_m = new_m+2;
            }
            int *new_table = new int[new_m];
            for(int i = 0;i<new_m;i++)
            {
                new_table[i] = -1;
            }
            for (int i = 0; i < m; i++) 
            {
                if (table[i] != -1) 
                {
                    // Rehash the existing values into the new table
                    int index = table[i] % new_m;
                    int j = 1; // Quadratic probing variable
                    while (new_table[index] != -1) 
                    {
                        index = (index + j * j) % new_m; // Quadratic probing
                        j++;
                    }
                    new_table[index] = table[i];
                }
            }
            delete[] table;
            table = new_table;
            m = new_m;
            
        }
        bool isEmpty()
        {
            if(t_vals == 0)
            return true;
            return false;
        }
    public:
        void insert(int value)
        {
            if(t_vals/(double)m > load_factor)
            {
                resize();
            }
            if(search(value)!=-1)
            {
                cout << "Duplicate key insertion is not allowed" << endl;
                return;
            }
            int visited = 0;//number of indices visited
            int i = 1;
            int index = hash(value);
            int ind = index;
            if(table[index] == -1)
            {
                table[index] = value;
                t_vals++;
            }
            else
            {
                while(table[ind]!=-1 && visited<m)
                {
                    visited++; 
                    ind = (index + i*i)%m;
                    i++;
                }
                if(visited==m)
                {
                    cout << "Max probing limit reached!" << endl;
                    return;
                }
                else
                {
                    table[ind] = value;
                    t_vals++;
                    return;
                }
            }
        }
        void remove(int value)
        {
            if(isEmpty())
            {
                cout<<"Element not found"<<endl;
                return;
            }
            int index = hash(value);
            int ind = index;
            int visited = 0;//number of indices visited
            int i = 1;
            while(visited<m)
            {
                visited++;
                if(table[ind] == value)
                {
                    table[ind] = -1;
                    t_vals--;
                    return;
                }
                ind = (index + i*i)%m;
                i++;
            }
            cout<<"Element not found"<<endl;
            return;
        }
        int search(int value)
        {
            if(isEmpty())
            {
                return -1;
            }
            int index = hash(value);
            int ind = index;
            int visited = 0;//number of indices visited
            int i = 1;
            while(visited<m)
            {
                visited++;
                if(table[ind] == value)
                {
                    return ind;
                }
                ind = (index + i*i)%m;
                i++;
            }
            return -1;
        }
        void printTable()
        {
            for(int i = 0;i<m;i++)
            {
                if(table[i] == -1)
                cout << "- ";
                else
                cout << table[i] << " ";
            }
            cout << endl;
        }
};