//
// Created by Zebin Guo on 1/5/25.
//
#include <Vector.hpp>
#include <Stack.hpp>

class DirectedGraphPath {
public:

    static Vector<int> FindDirectedGraphPathDFSRecursive(const Vector<Vector<int>>& graph, int src, int dest, Vector<bool> visited, Vector<int> &result) {
        result.push_back(src);
        visited[src] = true;
        if (src == dest) return result;
        for (const int& neighbour : graph[src]) {
            if (!visited[neighbour]) {
                Vector<int> res= FindDirectedGraphPathDFSRecursive(graph, neighbour, dest, visited, result);
                if (!res.empty()) return res;
            }
        }
        result.pop_back();
        return {};
    }

    static Vector<int> FindDirectedGraphPathDFSIterative(const Vector<Vector<int>>& graph, int src, int dest, Vector<bool> visited) {
        Stack<std::pair<int, Vector<int>>> DFSStack;
        DFSStack.push({src, {src}});

        while (!DFSStack.isEmpty()) {
            auto [node, currentPath] = DFSStack.top();
            DFSStack.pop();

            if (visited[node]) continue;
            visited[node] = true;

            if (node == dest) return currentPath;
            for (const int& neighbour : graph[node]) {
                if (!visited[neighbour]) {
                    Vector<int> path = currentPath;
                    path.push_back(neighbour);
                    DFSStack.push({neighbour, path});
                }
            }
        }

        return {};
    }

    static Vector<int> FindDirectedGraphPath(const Vector<Vector<int>>& graph, int src, int dest, int method) {
        // method 1 is DFS recursive
        // method 2 is DFS iterative
        // method 3 is BFS recursive
        // method 4 is BFS iterative
        Vector<bool> visited(graph.size(),false);
        Vector<int> result;
        if (src == dest) return {};
        if (method == 1) {
            return FindDirectedGraphPathDFSRecursive(graph, src, dest, visited, result);
        } else if (method == 2) {
            return FindDirectedGraphPathDFSIterative(graph, src, dest, visited);
        }

    }
};
