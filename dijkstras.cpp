#include <bits/stdc++.h>
using namespace std;
#define inf INT_MAX / 2

class dijkstras{

    public: 
    int vertices;
    vector<int> dist, path, vis;
    int src, re, cnt = 0;
    vector<vector<int>> cost;

    void read()
    {
        cost.resize(vertices);
        for(int i = 0; i < vertices; i++)
        {
            vector<int> temp1(vertices);
            fill(temp1.begin(), temp1.end(), inf);
            
            cost[i] = temp1;            
            cost[i][i] = 0;
        }


        cout << "No. of edges: ";
        int edges;
        cin >> edges;
        for(int i  = 0; i < edges; i++)
        {
            //cout << "u v w: ";
            int u, v, w;
            cin >> u >> v >> w;
            cost[u][v] = w;
        }        

    }
    void init()
    {
        vis.resize(vertices);
        fill(vis.begin(), vis.end(), 0);

        cout << "Enter the source: ";
        cin >> src;
        vis[src] = 1;

        path.resize(vertices);
        dist.resize(vertices);

        for(int i = 0; i < vertices; i++)
        {
            path[i] = src;
            dist[i] = cost[src][i]; 
        }
        re = src;
    }



    void shortest_path()
    {

        int min_i = 0;

        for(int i = 0; i < vertices; i++)
        {
            if(vis[i] == 0)
            {
                if(dist[min_i] > dist[i]) min_i = i;
            }
        }

        re = min_i;
        vis[re] = 1;

        for(int i = 0; i < vertices; i++)
        {
            if(vis[i] == 0)
            {
                if(dist[i] > dist[re] + cost[re][i] && dist[re] < inf)
                {
                    path[i] = re;
                    dist[i] = dist[re] + cost[re][i];
                }
            }
        }
        
    }

    void print_path(int  x)
    {
        vector<int> ans;
        ans.push_back(x);
        for(int i = 0; i < vertices; i++)
        {
            ans.push_back(path[ans.back()]);
            if(ans.back() == src)
            break;
        }

        for(int i = ans.size() - 1; i > 0; i--) cout << ans[i] << "->";
        cout << ans.front();
        
        cout << "\ttotal cost: " << dist[x];
        cout << endl;
  
        
    }



};

signed main()
{

    dijkstras d;
    cout << "Enter the no. of vertices: ";
    cin >> d.vertices;
    d.read();
    d.init();
    for(int i = 0; i < d.vertices - 1; i++) d.shortest_path();
    for(int i = 0; i < d.vertices - 1; i++ ) d.print_path(i);
}
