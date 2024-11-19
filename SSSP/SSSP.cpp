#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

std::vector<int> dijkstra(const std::vector<std::vector<std::pair<int, int>>> &graph, int start)
{
    int N = graph.size();
    std::vector<int> distances(N, INT_MAX);
    //std::vector<bool> visited(N, false);
    distances[start] = 0;
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> pq;

    pq.emplace(0, start);
    while (!pq.empty())
    {
        std::pair<int,int> pq_elem = pq.top();
        int cur_dist = pq_elem.first;
        int cur_node = pq_elem.second;
        pq.pop();

        if (cur_dist > distances[cur_node]) continue;
        // visited[cur_node] = true;

        for (const std::pair<int, int> &neighbour : graph[cur_node])
        {
            int new_dist = cur_dist + neighbour.second;
            if (new_dist < distances[neighbour.first])
            {
                distances[neighbour.first] = new_dist;
                pq.emplace(new_dist, neighbour.first);
            }
        }
    }

    return distances;
}

std::vector<int> generate_landmarks(const std::vector<int> &degrees, int N)
{
    std::vector<std::pair<int, int>> enumerated_degrees(N);
    for (int i = 0; i < N; i++)
    {
        enumerated_degrees[i] = {i, degrees[i]};
    }

    // std::sort(enumerated_degrees.begin(), enumerated_degrees.end(), [](const std::pair<int, int> &a, const std::pair<int, int> &b)
    //           { return a.second > b.second; });

    std::vector<int> landmarks;
    int n_landmarks;// = N/3000;
    if(N == 30000){
        n_landmarks = 10;
    }
    else if(N == 50000){
        n_landmarks = 15;
    }
    else{
        n_landmarks = 20;
    }

    std::nth_element(enumerated_degrees.begin(), enumerated_degrees.begin() + n_landmarks, enumerated_degrees.end(),
                 [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
                     return a.second > b.second;
                 });

    for (int i = 0; i < n_landmarks; i++)
    {
        landmarks.push_back(enumerated_degrees[i].first);
    }

    return landmarks;
}

int get_approx_dist(const std::vector<std::vector<int>> &landmark_distances, int start, int end)
{
    int dist = 0;
    for (int i = 0; i < landmark_distances.size(); i++)
    {
        dist = std::max(dist, std::abs(landmark_distances[i][start] - landmark_distances[i][end]));
        //dist += std::abs(landmark_distances[i][start] - landmark_distances[i][end]);
    }
    return dist;
}

int astar(const std::vector<std::vector<std::pair<int, int>>> &graph, const std::vector<std::vector<int>> &landmark_distances, int start, int end)
{
    int N = graph.size();
    std::vector<int> g_cost(N, INT_MAX);
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> pq;

    g_cost[start] = 0;
    pq.emplace(get_approx_dist(landmark_distances, start, end), start);

    while (!pq.empty())
    {
        int cur_node = pq.top().second;
        pq.pop();

        if (cur_node == end)
        {
            return g_cost[end];
        }
        for (const std::pair<int, int> &neighbour : graph[cur_node])
        {
            int neighbour_node = neighbour.first;
            int neighbour_weight = neighbour.second;
            int new_g_cost = g_cost[cur_node] + neighbour_weight;
            if (new_g_cost < g_cost[neighbour_node])
            {
                g_cost[neighbour_node] = new_g_cost;
                int h_cost = get_approx_dist(landmark_distances, neighbour.first, end);
                pq.emplace((new_g_cost + h_cost), neighbour_node);
            }
        }
    }

    return 1000000000;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);  

    int N, M;
    scanf("%d %d", &N, &M);  

    std::vector<std::vector<std::pair<int, int>>> graph(N);
    std::vector<int> degrees(N, 0);

    for (int i = 0; i < N; i++)
    {
        int n_neighbours;
        scanf("%d", &n_neighbours);  
        degrees[i] = n_neighbours;

        for (int k = 0; k < n_neighbours; k++)
        {
            int neighbour, weight;
            scanf("%d %d", &neighbour, &weight);
            graph[i].emplace_back(neighbour, weight);
            degrees[neighbour]++;
        }
    }

    int Q;
    scanf("%d", &Q);  
    std::vector<std::pair<int, int>> queries(Q);

    for (int i = 0; i < Q; i++)
    {
        scanf("%d %d", &queries[i].first, &queries[i].second);  
    }

    std::vector<int> landmarks = generate_landmarks(degrees, N);

    std::vector<std::vector<int>> landmark_distances;
    for (int landmark : landmarks)
    {
        landmark_distances.push_back(dijkstra(graph, landmark));
    }

    for (const auto &query : queries)
    {
        int result = astar(graph, landmark_distances, query.first, query.second);
        printf("%d\n", result);  
    }

    return 0;
}