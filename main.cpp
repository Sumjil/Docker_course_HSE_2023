#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <list>
#include <cstring>
#include <algorithm>
#include <utility>

const int INF = 1000 * 1000 * 1000; // 1e+9;
int num_city, m_roads;
std::vector<std::pair<int, int>> g[100017];
bool vis[100017];
int tin[100017];
int lownlink[100017];
int timer = 0;
std::vector<std::pair<int, int>> ans;
std::vector<int> costs;

std::vector<std::pair<int, int>> &dfs(int node, int parent)
{
    timer++;
    tin[node] = timer;
    vis[node] = true;
    lownlink[node] = timer;
    // cout << "v = " << node << "\n";
    // cout << "tin[node]  = " << tin[node] << "\n";
    // cout << "lownlink[node]  = " << lownlink[node] << "\n";

    for (const auto &edge : g[node]) // look at adj
    {
        int adj = edge.first;
        int we = edge.second;
        // cout << "adj = " << adj << " w = " << w << "\n";
        if (adj == parent)
        {
            continue;
        }
        if (vis[adj])
        {
            lownlink[node] = std::min(lownlink[node], tin[adj]);
        }
        else
        {
            dfs(adj, node);
            lownlink[node] = std::min(lownlink[node], lownlink[adj]);
            if (lownlink[adj] > tin[node])
            {
                std::cout << "Bridge " << node + 1 << ' ' << adj + 1 << std::endl;

                ans.emplace_back(std::make_pair(node + 1, adj + 1));
                costs.push_back(we);
            }
        }
    }
    // cout << "v = " << node << "\n";
    // cout << "tin[node]  = "<<tin[node] <<"\n";
    // cout << "lownlink[node]  = " << lownlink[node] << "\n";
    return ans;
};

int main()
{
    std::cout << "Enter the number of vertices and edges of the graph" << std::endl;
    std::cin >> num_city >> m_roads;
    std::cout << "Enter edges with weights" << std::endl;
    for (int i = 0; i < m_roads; ++i)
    {
        int node_f, node_s, weight;
        std::cin >> node_f >> node_s >> weight;
        g[node_f - 1].emplace_back(std::make_pair(node_s - 1, weight));
        g[node_s - 1].emplace_back(std::make_pair(node_f - 1, weight));
    }

    memset(vis, 0, sizeof(vis));
    memset(tin, 0, sizeof(tin));
    memset(lownlink, 0, sizeof(lownlink));
    ans.reserve(m_roads);
    costs.reserve(m_roads);
    dfs(0, -1);
    // std::cout << "Bridges " << std::endl;
    if (ans.size() == 0)
    {
        // cout << "ans " << -1 << "\n";
        std::cout << -1 << "\n";
        return 0;
    }
    // for (int i = 0; i < ans.size(); ++i)
    // {
    //     std::cout << ans[i].first << " " << ans[i].second << " " << costs[i] << "\n";
    // }
    auto min_value = *std::min_element(costs.begin(), costs.end());
    // cout << "ans " << min_value << "\n";
    // std::cout << min_value << "\n";
    return 0;
}
