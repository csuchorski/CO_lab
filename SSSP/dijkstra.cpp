#include <iostream>
#include <vector>
#include <queue>
#include <climits>

std::vector<int> dijkstra(const std::vector<std::vector<std::pair<int, int>>> &graph, int start)
{
    int N = graph.size();
    std::vector<int> distances(N, INT_MAX);
    distances[start] = 0;
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> pq;

    pq.emplace(0, start);
    while (!pq.empty())
    {
        int cur_dist = pq.top().first;
        int cur_node = pq.top().second;
        pq.pop();

        if (cur_dist > distances[cur_node])
        {
            continue;
        }
        for (const std::pair<int, int> &neighbour : graph[cur_node])
        {
            if (distances[cur_node] + neighbour.second < distances[neighbour.first])
            {
                distances[neighbour.first] = distances[cur_node] + neighbour.second;
                pq.emplace(distances[neighbour.first], neighbour.first);
            }
        }
    }

    return distances;
}

int bi_dijkstra(const std::vector<std::vector<std::pair<int, int>>> &graph, int start, int end)
{
    std::vector<int> dist1 = dijkstra(graph, start);
    std::vector<int> dist2 = dijkstra(graph, end);

    int res = INT_MAX;
    for (int i = 0; i < graph.size(); i++)
    {
        if (dist1[i] != INT_MAX && dist2[i] != INT_MAX)
        {
            res = std::min(res, dist1[i] + dist2[i]);
        }
    }

    if (res == INT_MAX)
    {
        return 1000000000;
    }
    return res;
}
int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N, M;
    std::cin >> N >> M;
    std::vector<std::vector<std::pair<int, int>>> graph(N);

    for (int i = 0; i < N; i++)
    {
        int n_neighbours;
        std::cin >> n_neighbours;
        for (int k = 0; k < n_neighbours; k++)
        {
            int neighbour, weight;
            std::cin >> neighbour >> weight;
            graph[i].emplace_back(neighbour, weight);
        }
    }

    int Q;
    std::cin >> Q;
    std::vector<std::pair<int, int>> queries(Q);
    for (int i = 0; i < Q; i++)
    {
        int start, end;
        std::cin >> start >> end;
        queries[i] = std::make_pair(start, end);
    }

    // std::vector<int> results;
    for (auto &query : queries)
    {
        std::cout << bi_dijkstra(graph, query.first, query.second) << std::endl;
    }
    // for (auto &res : results)
    // {
    //     std::cout << res << std::endl;
    // }

    return 0;
}
