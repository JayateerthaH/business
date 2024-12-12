#include <bits/stdc++.h>
using namespace std;

class kruskal {
public:
    int n, m, cnt = 0;
    vector<tuple<int, int, int>> temp, ans;
    int *arr;

    kruskal() {
        cout << "Enter no of vertices: ";
        cin >> n;
        cout << "Enter no. of edges you are entering: ";
        cin >> m;

        temp.resize(m);
        cout << "Enter values for u, v, w one by one:\n";
        for (int i = 0; i < m; i++) {
            cin >> get<0>(temp[i]) >> get<1>(temp[i]) >> get<2>(temp[i]);
        }

        mergesort(temp);

        arr = (int *)malloc(sizeof(int) * n);
        for (int i = 0; i < n; i++) {
            arr[i] = i;
        }
    }

    void merge(vector<tuple<int, int, int>> &b, vector<tuple<int, int, int>> &c, vector<tuple<int, int, int>> &a) {
        int i = 0, j = 0, k = 0, p = b.size(), q = c.size();
        while (i < p && j < q) {
            if (get<2>(b[i]) <= get<2>(c[j])) {
                a[k++] = b[i++];
            } else {
                a[k++] = c[j++];
            }
        }
        while (i < p) a[k++] = b[i++];
        while (j < q) a[k++] = c[j++];
    }

    void mergesort(vector<tuple<int, int, int>> &a) {
        int n = a.size();
        if (n > 1) {
            vector<tuple<int, int, int>> b(a.begin(), a.begin() + n / 2);
            vector<tuple<int, int, int>> c(a.begin() + n / 2, a.end());
            mergesort(b);
            mergesort(c);
            merge(b, c, a);
        }
    }

    void Union(int u, int v) {
        int temp1 = arr[u];
        for (int i = 0; i < n; i++) {
            if (arr[i] == temp1) arr[i] = arr[v];
        }
    }

    int Find(int u, int v) {
        return arr[u] == arr[v];
    }

    void ops() {
        int i = 0;
        while (cnt < n - 1 && i < m) { 
            if (!Find(get<0>(temp[i]), get<1>(temp[i]))) {
                Union(get<0>(temp[i]), get<1>(temp[i]));
                ans.push_back(temp[i]);
                cnt++;
            }
            i++;
        }
    }
};

signed main() {
    kruskal k;
    k.ops();

    cout << "Edges in the Minimum Spanning Tree:\n";
    for (auto [u, v, w] : k.ans) {
        cout << u << " " << v << " " << w << endl;
    }

    return 0;
}
