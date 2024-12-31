#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <cstdlib>
#include <algorithm>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::to_string;
using std::ifstream;
using std::ofstream;
using std::map;

typedef struct _heapNode
{
    string to;
    int weight;

    _heapNode(string t, int w)
    {
        to = t;
        weight = w;
    }

    _heapNode()
    {
        to = "";
        weight = 0;
    }

    _heapNode& operator=(const _heapNode h)
    {
        to = h.to;
        weight = h.weight;
        return *this;
    }

    bool operator<(const _heapNode h)
    {
        return weight < h.weight;
    }

    bool operator>(const _heapNode h)
    {
        return weight > h.weight;
    }

    bool operator==(const _heapNode h)
    {
        return weight == h.weight;
    }

    bool operator!=(const _heapNode h)
    {
        return weight != h.weight;
    }
} HeapNode;

void InitHeap(HeapNode*& heap, int size)
{
    heap = new HeapNode[size];
}

HeapNode MinOfHeap(HeapNode*& heap)
{
    return heap[1];
}

void DeleteHeap(HeapNode*& heap, int& heapSize)
{
    if (heapSize < 1)
    {
        return;
    }

    heap[1] = heap[heapSize];
    heap[heapSize] = HeapNode();
    heapSize--;

    int index = 1;
    bool check = true;
    while (index * 2 <= heapSize && check)
    {
        HeapNode tmpNode;
        if (heap[index] > heap[index * 2] && heap[index] > heap[(index * 2) + 1])
        {
            int nextIndex = (heap[index * 2] > heap[index * 2 + 1]) ? (index * 2) : (index * 2 + 1);
            tmpNode = heap[nextIndex];
            heap[nextIndex] = heap[index];
            heap[index] = tmpNode;
            index = nextIndex;
        }
        else if (heap[index] > heap[index * 2 + 1])
        {
            int nextIndex = (index * 2 + 1);
            tmpNode = heap[nextIndex];
            heap[nextIndex] = heap[index];
            heap[index] = tmpNode;
            index = nextIndex;
        }
        else if (heap[index] > heap[index * 2])
        {
            int nextIndex = (index * 2);
            tmpNode = heap[nextIndex];
            heap[nextIndex] = heap[index];
            heap[index] = tmpNode;
            index = nextIndex;
        }
        else
        {
            check = false;
        }
    }
}

void InsertHeap(HeapNode*& heap, int& heapSize, HeapNode node)
{
    heapSize++;
    heap[heapSize] = node;

    int index = heapSize;

    while (index > 1 && heap[index] < heap[index / 2])
    {
        HeapNode tmpNode = heap[index / 2];
        heap[index / 2] = heap[index];
        heap[index] = tmpNode;
        index = index / 2;
    }
}

int main(int args, char* argv[])
{
    ifstream ifs(string(argv[1]) + ".txt");
    if (!ifs.is_open())
    {
        cout << "Graph File (" << argv[1] << ".txt) has not founded. Check your directory and try again." << endl;
        return 0;
    }

    map<string, map<string, int>> graph;
    string start, end;

    while (ifs)
    {
        string from, to, w;
        getline(ifs, from, '\t');
        getline(ifs, to, '\t');
        getline(ifs, w);

        if (from.compare("") == 0 && to.compare("") == 0 && w.compare("") == 0)
        {
            break;
        }

        int weight = atoi(w.c_str());

        if (w.compare("STARTING") == 0)
        {
            start = from;
            continue;
        }
        if (w.compare("FINISHING") == 0)
        {
            end = from;
            continue;
        }

        if (w.compare(to_string(weight)))
        {
            cout << "File Input failed... Check Files and Try Again" << endl;
            return 0;
        }
        graph[from][to] = weight;
    }
    ifs.close();

    map<string, string> dad, status;
    map<string, int> dist;
    map<string, bool> allVertexInfo;

    int edgeCount = 0, heapSize = 0;
    HeapNode* heap;

    for (auto iter = graph.begin(); iter != graph.end(); iter++)
    {
        for (auto iter2 = graph[iter->first].begin(); iter2 != graph[iter->first].end(); iter2++)
        {
            allVertexInfo[iter->first] = true;
            allVertexInfo[iter2->first] = true;
            edgeCount++;
        }
    }

    for (auto iter = allVertexInfo.begin(); iter != allVertexInfo.end(); iter++)
    {
        status[iter->first] = "other";
        dist[iter->first] = 0;
        dad[iter->first] = iter->first;
    }

    InitHeap(heap, edgeCount + 2);
    status[start] = string("in-tree");
    dist[start] = 0;

    for (auto iter = graph[start].begin(); iter != graph[start].end(); iter++)
    {
        status[iter->first] = "fringe";
        dist[iter->first] = graph[start][(string)iter->first];
        dad[iter->first] = start;
        InsertHeap(heap, heapSize, HeapNode(iter->first, graph[start][iter->first]));
    }

    while (heapSize > 0)
    {
        HeapNode v = MinOfHeap(heap);
        status[v.to] = "in-tree";
        DeleteHeap(heap, heapSize);
        for (auto iter = graph[v.to].begin(); iter != graph[v.to].end(); iter++)
        {
            if (status[iter->first].compare("other") == 0)
            {
                status[iter->first] = "fringe";
                dist[iter->first] = dist[v.to] + graph[v.to][iter->first];
                dad[iter->first] = v.to;

                InsertHeap(heap, heapSize, HeapNode(iter->first, dist[iter->first]));
            }
            else if (status[iter->first].compare("fringe") == 0)
            {
                if (dist[iter->first] > dist[v.to] + graph[v.to][iter->first])
                {
                    dist[iter->first] = dist[v.to] + graph[v.to][iter->first];
                    dad[iter->first] = v.to;
                    InsertHeap(heap, heapSize, HeapNode(iter->first, dist[iter->first]));
                }
            }
        }
    }

    string graphString;
    graphString = ("digraph G {\n\n\t" + start + " [color=lightGrey, style=filled, shape=doublecircle]\n\t" + end +
        " [color=lightGrey, style=filled, shape=doublecircle]\n\tnode [shape=circle];\n\n\t");

    map<string, string> shortistLine;
    string prev = end;

    while (prev.compare(start) != 0)
    {
        shortistLine[dad[prev]] = prev;
        prev = dad[prev];
    }

    for (auto iter = graph.begin(); iter != graph.end(); iter++)
    {
        for (auto iter2 = graph[iter->first].begin(); iter2 != graph[iter->first].end(); iter2++)
        {
            if (!shortistLine[iter->first].compare(iter2->first))
            {
                graphString += iter->first + " -> " + iter2->first + " [label=" + to_string(graph[iter->first][iter2->first]) + ", color=blue];\n\t";
            }
            else
            {
                graphString += iter->first + " -> " + iter2->first + " [label=" + to_string(graph[iter->first][iter2->first]) + "];\n\t";
            }
        }
    }
    graphString += "\n\n}";

    cout << "Graphviz .dot file output : \n" << graphString << endl;

    ofstream ofs(string(argv[2]) + ".dot");
    ofs << graphString;
    ofs.close();
    system(("dot -Tpdf " + string(argv[2]) + ".dot > " + string(argv[2]) + ".pdf").c_str());

    delete[] heap;

    return 0;
}