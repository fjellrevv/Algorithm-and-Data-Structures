#include <iostream>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

struct edge {
    int from_edge, to_edge, weight;
};

void insertionSortByWeight(edge arr[], int n) {
    int key, j;
    for (int i = 0  ; i < n; i++) {
        int x = arr[i].from_edge, y = arr[i].to_edge;
        key = arr[i].weight;
        j = i - 1;

        while (j >= 0 && arr[j].weight > key) {
            arr[j + 1].from_edge = arr[j].from_edge;
            arr[j + 1].to_edge = arr[j].to_edge;
            arr[j + 1].weight = arr[j].weight;
            j = j - 1;
        }
        arr[j + 1].from_edge = x;
        arr[j + 1].to_edge = y;
        arr[j + 1].weight = key;
    }
}

int r[50], parent[50];
edge arr[50];
string name[50];
int max_weight = 0;

bool cmp(edge a, edge b) {
    return a.weight < b.weight;
}

int find(int x) {
    if (x != parent[x]) parent[x] = find(parent[x]);
    return parent[x];
}

int main() {

    string data;
    int size = 0, index = 0, ans = 0;

    
    ifstream in("hello.txt");
    if (in.is_open())
    {
        getline(in, data);
        stringstream ss(data);
        string edge;
        while (ss >> edge) {
            name[size] = edge;
            size++;
        }
        for (int i = 0; i < size; ++i) {
            getline(in, data);
            int str_index = 0;
            stringstream ss(data);
            string w;
            while (ss >> w) {
                if (stoi(w) != 0) {
                    bool flag = 0;
                    for (int z = 0; z < index; ++z) {
                        if (arr[z].from_edge == str_index && arr[z].to_edge == i) {
                            flag = 1;
                            break;
                        }
                    }
                    if (flag) {
                        str_index++;
                        continue;
                    }
                    arr[index].from_edge = i;
                    arr[index].to_edge = str_index;
                    arr[index].weight = stoi(w);
                    str_index++;
                    index++;

                }
                else {
                    str_index++;
                }
            }
        }
    }
    in.close();
    insertionSortByWeight(arr, index);

    for (int i = 0; i < size; i++) {
        r[i] = 0;
        parent[i] = i;
    }

    for (int i = 0; i < size; ++i) {

        int edge_1 = arr[i].from_edge;
        int edge_2 = arr[i].to_edge;
        int find_edge_1 = find(edge_1);
        int find_edge_2 = find(edge_2);

        if (find_edge_1 != find_edge_2) {

            ans += arr[i].weight;
            arr[i].weight *= -1;
            
            if (r[find_edge_1] > r[find_edge_2]) parent[find_edge_2] = find_edge_1;

            else {
                parent[find_edge_1] = find_edge_2;
            }
            if (r[find_edge_1] == r[find_edge_2]) r[find_edge_2]++;
        }
    }

    for (int i = 0; i < size; ++i) {
        if (arr[i].weight < 0) {
            cout << name[arr[i].from_edge] << " " << name[arr[i].to_edge] << "\n";
        }
    }

    cout << ans << "\n";
    return 0;
}