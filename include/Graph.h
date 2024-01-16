//
// Created by HORIA on 10.01.2024.
//

#ifndef DATA_STRUCTURES_GRAPH_H
#define DATA_STRUCTURES_GRAPH_H
#include <iostream>
#include <string>
#include <list>
#include <algorithm>
#include <deque>

struct Vertex {
    explicit Vertex(const std::list<int>& _connections={}) : connections{_connections} {
        unique_id = id;
        ++id;
    }
    static int id;
    int unique_id;
    std::list<int> connections {};
};
int Vertex::id = 1;

//connects u to v
//assumes v is include in vertices
void add_edge(std::list<Vertex>& vertices, int u, int v) {
    auto it = std::find_if(vertices.begin(),vertices.end(),[u](auto& vert){return (vert.unique_id == u);});
    if (it == vertices.end()) {
        std::cerr << "Vert not in vertices!\n";
        exit(1);
    }
    it->connections.push_back(v);
    it->connections.sort();
}

std::list<Vertex>::iterator get_vert(std::list<Vertex>& verts, int u) {
    return std::find_if(verts.begin(),verts.end(),[u](auto& v){return (v.unique_id==u);});
}

void cauta_in_latime(std::list<Vertex>& vertices, int s, std::vector<std::string>& colors, std::vector<int>& d,std::vector<int>& pi) {

    for (int i=1;i<=vertices.size();++i) {
        colors[i] = "alb";
        d[i] = INT_MAX;
        pi[i] = 0;
    }

    colors[s] = "gri";
    d[s] = 0;
    std::deque<int> q {s};

    while (!q.empty()) {
        int u = q.front();
        q.pop_front();
        for (auto vert : get_vert(vertices, u)->connections) {
            if (colors[vert] == "alb") {
                colors[vert] = "gri";
                d[vert] = d[u] + 1;
                pi[vert] = u;
                q.push_back(vert);
            }
        }
        colors[u] = "negru";
    }
}

void afiseaza_drum(std::list<Vertex>& G, int s, int v, std::vector<int>& pi) {
    if (v == s) {
        std::cout << s << " ";
    } else if (!pi[v]) {
        std::cout << "Nu exista drum de la s la v!\n";
    } else {
        afiseaza_drum(G,s,pi[v],pi);
        std::cout << v << " ";
    }
}

void visit(int u,int& timp,std::vector<int>& d,std::vector<int>& f,std::vector<std::string>& colors,std::list<Vertex>& G, std::vector<int>& pi,std::list<int>& l) {
    colors[u] = "gri";
    timp += 1;
    d[u] = timp;
    for (auto v : get_vert(G,u)->connections) {
        if (colors[v]=="alb") {
            pi[v] = u;
            visit(v,timp,d,f,colors,G,pi,l);
        }
    }
    colors[u] = "negru";
    timp += 1;
    f[u] = timp;
    l.push_front(u);
}

void cauta_in_adancime(std::list<Vertex>& G) {
    std::vector<int> pi (G.size()+1);
    std::vector<std::string> colors (G.size()+1);
    std::vector<int> d (G.size()+1);
    std::vector<int> f (G.size()+1);
    for (int i=1;i<=G.size();++i) {
        colors[i] = "alb";
        pi[i] = 0;
    }
    std::list<int> l {};
    int timp {};
    for (int i=1;i<=G.size();++i) {
        if (colors[i]=="alb") {
            visit(i, timp,d,f,colors,G,pi,l);
        }
    }
    for (auto elem : l) {
        std::cout << elem << " ";
    }
}
void dfs(const std::vector<Varf>& verts,std::vector<bool>& visited, int node) {
    visited[node] = true;
    for (auto elem : verts[node].cons) {
        if (!visited[elem]) {
            dfs(verts,visited,elem);
        }
    }
}
#endif //DATA_STRUCTURES_GRAPH_H
