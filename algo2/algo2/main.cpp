#include <iostream>
#include <conio.h>
#include <stack>
#include <vector>
#include <string>

using namespace std;

// сортировка вставкой
void insertionSort(vector<int>&arr)
{
    int i, key, j;
    for (i = 1; i < arr.size(); i++) 
    {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) 
        {
            arr[j + 1] = arr[j];
            j -= 1;
        }
        arr[j + 1] = key;
    }
}

// minrun
int getMinrun(int n)
{
    int r = 0;           
    while (n >= 64) 
    {
        r |= n & 1; // получаем младший бит числа n
        n >>= 1;
    }
    return n + r;
}

// runs
vector<vector<int>> getRun(vector<int>arr, vector<vector<int>>runs, int minrun)
{
    int i = -1, j = 0, curr = 0;
    while (i != arr.size() - 1)
    {
        runs.push_back(vector<int>()); runs[j].push_back(arr[++i]);
        while (runs[j].size() < minrun && i != arr.size() - 1)
        {
            runs[j].push_back(arr[++i]);
            curr++;
            if (runs[j][curr - 1] > runs[j][curr])
            {
                if (runs[j].size() > minrun) break;
                swap(runs[j][curr - 1], runs[j][curr]);
            }
        }
        insertionSort(runs[j]);
        j++;
        curr = 0;
    }
    return runs;
}

// слияние
vector<vector<int>> merge(vector<vector<int>>runs)
{
    vector<vector<int>>pair;
    int i = 0, j = -1, x = 0, y = 0, z = 0; // i - индекс подмассива, j = номер подмассива

    while (1)
    {
        if (runs.size() == 1) break;
        if (j == -1)
        {
            j++;
        }

        x = runs[j].size(); 

        if (j > 0 && runs.size() > 1)
        {
            y = runs[j - 1].size();
        }
        if (j > 1 && runs.size() > 2)
        {
            z = runs[j - 2].size();
        }

        if (j > 0 && ((j == 1 && x <= y) || (j > 1 && (y <= z || x <= y + z))))
        {
            // временный массив
            vector<int>temp; 
            if (j == 1)
            {
                temp.resize(runs[j].size());
                copy(runs[j].begin(), runs[j].end(), temp.begin());
            }
            else
            {
                if (x <= z)
                {
                    temp.resize(runs[j].size());
                    copy(runs[j].begin(), runs[j].end(), temp.begin());
                }
                else
                {
                    temp.resize(runs[j - 2].size());
                    copy(runs[j - 2].begin(), runs[j - 2].end(), temp.begin());
                }
            }

            // проверка на убывание
            bool flag = 0;
            for (int k = 1; k < temp.size(); k++)
            {
                if (temp[k - 1] > temp[k])
                {
                    flag = 1;
                    break;
                }
            }
            if (flag) reverse(temp.begin(), temp.end());

            // галоп
            vector<int>merge_arr;
            int temp_x = 0, y_x = 0, cnt_temp_x = 0, cnt_y_x = 0, deg = 1;

            // пока размер массива слияния не равен сумме двух массивов
            while (merge_arr.size() != y + temp.size())
            {
                if (y_x == y)
                {
                    if (cnt_temp_x == 0) deg = 1;
                    merge_arr.push_back(temp[temp_x]);
                    cnt_temp_x++;
                    temp_x++;
                } 
                else if (y_x < y && temp_x < temp.size() && temp[temp_x] < runs[j - 1][y_x])
                {
                    if (cnt_temp_x == 0) deg = 1;
                    merge_arr.push_back(temp[temp_x]);
                    cnt_temp_x++;
                    cnt_y_x = 0;

                    if (cnt_temp_x == 7 && temp_x + pow(2, deg) < temp.size())
                    {
                        temp_x += pow(2, deg);

                        while ((temp_x < temp.size() && temp[temp_x] < runs[j - 1][y_x]))
                        {
                            for (int v = pow(2, deg); v > 0; v--)
                            {
                                merge_arr.push_back(temp[temp_x - v + 1]);
                                cnt_temp_x++;
                            }
                            deg++;
                            temp_x += pow(2, deg);
                        }
                        temp_x -= pow(2, deg);
                        temp_x++;
                        deg = 0;
                    }
                    else
                    {
                        if (temp_x < temp.size()) temp_x++;
                    }
                }
                else if (temp_x == temp.size())
                {
                    if (cnt_y_x == 0) deg = 1;
                    merge_arr.push_back(runs[j - 1][y_x]);
                    cnt_y_x++;
                    cnt_temp_x = 0;
                    y_x++;
                }
                else if (y_x < y && temp_x < temp.size() && temp[temp_x] >= runs[j - 1][y_x])
                {
                    if (cnt_y_x == 0) deg = 1;
                    merge_arr.push_back(runs[j - 1][y_x]);
                    cnt_y_x++;
                    cnt_temp_x = 0;

                    if (cnt_y_x == 7 && y_x + pow(2, deg) < y)
                    {
                        y_x += pow(2, deg);

                        while ((y_x < y && temp[temp_x] > runs[j - 1][y_x]))
                        {
                            for (int v = pow(2, deg); v > 0; v--)
                            {
                                merge_arr.push_back(runs[j - 1][y_x - v + 1]);
                                cnt_y_x++;
                            }
                            deg++;
                            y_x += pow(2, deg);

                        }
                        y_x -= pow(2, deg);
                        y_x++;
                        deg = 0;
                    }
                    else
                    {
                        if (y_x + 1 <= y) y_x++;
                    }
                }
            }

            if (temp.size() == x)
            {
                runs[j].resize(merge_arr.size());
                copy(merge_arr.begin(), merge_arr.end(), runs[j].begin());
                runs.erase(runs.begin() + j - 1);
                j--;
            }

            else
            {
                runs[j - 1].resize(merge_arr.size());
                copy(merge_arr.begin(), merge_arr.end(), runs[j - 1].begin());
                runs.erase(runs.begin() + j - 2);
                j--;
            }

        }
        else
        {
                j++;
        }
    }
    return runs;
}

vector<int> TimSort(vector<int>arr)
{
    vector<vector<int>>runs;

    int minrun = getMinrun(arr.size());
    runs = getRun(arr, runs, minrun);
    runs = merge(runs);

    copy(runs[0].begin(), runs[0].end(), arr.begin());
    return arr;
}

int main()
{
    setlocale(LC_ALL, "Rus");
    vector<int>vec; int exit = 1; string str = "", tmp;

    system("cls"); 
    vec.clear(); str.clear(); tmp.clear();
    cout << "Введите элементы последовательности через пробел и нажмите Enter: ";
    while (str == "") getline(cin, str);
    if (str[str.length() - 1] != ' ') str += ' ';
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] == ' ')
        {
            vec.push_back(stoi(tmp));
            tmp.clear();
        }
        else tmp += str[i];
    }

    vec = TimSort(vec);

    cout << "\nОтсортированный массив: ";
    for (int i = 0; i < vec.size(); i++)
    {
        cout << vec[i] << " ";
    }

    exit = _getch();
    return 0;
}