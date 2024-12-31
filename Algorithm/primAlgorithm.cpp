#include <iostream>
#include <map>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::map;

typedef struct _heapnode
{
    string toVertex;
    int weight;

    _heapnode(string to, int w)
    {
        toVertex = to;
        weight = w;
    }

    _heapnode()
    {
        toVertex = "";
        weight = 0;
    }

    _heapnode& operator=(_heapnode& h)
    {
        this->toVertex = h.toVertex;
        this->weight = h.weight;
        return *this;
    }

    bool operator==(_heapnode& h)
    {
        return (weight == h.weight);
    }

    bool operator>(_heapnode& h)
    {
        return (weight > h.weight);
    }

    bool operator<(_heapnode& h)
    {
        return (weight < h.weight);
    }
} HeapNode;

void HeapInit(HeapNode*& heap, int size)
{
    heap = new HeapNode[size];
}

HeapNode MinofHeap(HeapNode*& heap)
{
    return heap[1];
}

void AddHeap(HeapNode*& heap, int& heapSize, HeapNode addNode)
{
    heapSize++;
    heap[heapSize] = addNode;

    int nextIndex = heapSize;

    while ((heap[nextIndex] < heap[nextIndex / 2] || heap[nextIndex] == heap[nextIndex / 2]) && nextIndex > 1)
    {
        HeapNode tmpNode = heap[nextIndex];
        heap[nextIndex] = heap[nextIndex / 2];
        heap[nextIndex / 2] = tmpNode;
        nextIndex /= 2;
    }
}

void DeleteHeap(HeapNode*& heap, int& heapSize)
{
    if (heapSize == 0)
    {
        return;
    }
    else if (heapSize == 1)
    {
        HeapNode tmpNode;
        heap[1] = tmpNode;
        heapSize--;
        return;
    }

    HeapNode tmpNode;
    heap[1] = heap[heapSize];
    heap[heapSize] = tmpNode;
    int nextIndex = 1;

    while (nextIndex * 2 < heapSize && (heap[nextIndex] > heap[nextIndex * 2] || heap[nextIndex] > heap[nextIndex * 2 + 1]))
    {
        int nextMin = -1;

        if (nextIndex * 2 + 1 < heapSize && heap[nextIndex] > heap[nextIndex * 2] && heap[nextIndex] > heap[nextIndex * 2 + 1])
        {
            nextMin = (heap[nextIndex * 2] < heap[nextIndex * 2 + 1]) ? (nextIndex * 2) : (nextIndex * 2 + 1);
        }
        else if (heap[nextIndex] > heap[nextIndex * 2 + 1] && nextIndex * 2 + 1 < heapSize)
        {
            nextMin = nextIndex * 2 + 1;
        }
        else if (heap[nextIndex] > heap[nextIndex * 2])
        {
            nextMin = nextIndex * 2;
        }

        if (nextMin == -1)
        {
            break;
        }

        HeapNode tmpNode = heap[nextIndex];
        heap[nextIndex] = heap[nextMin];
        heap[nextMin] = tmpNode;
        nextIndex = nextMin;
    }
    heapSize--;
}

int main()
{
    int weight = 0;
    string startVertex, endVertex, start;

    map<string, map<string, int>> graph;
    int edgeCount = 0;

    HeapNode* heap;
    int heapCount = 0;
    map<string, string> status, dad;
    map<string, int> dist;

    while (true)
    {
        cout << "Input data[vertex, vertex, weight] : ";
        cin >> startVertex >> endVertex >> weight;

        if (weight == 0)
        {
            start = startVertex;
            break;
        }

        graph[startVertex][endVertex] = weight;
        graph[endVertex][startVertex] = weight;
        edgeCount++;
        status[startVertex] = "others";
        status[endVertex] = "others";
    }

    HeapInit(heap, edgeCount + 2);

    cout << endl << "Initial Graph: " << endl;
    for (auto iter = status.begin(); iter != status.end(); iter++)
    {
        static map<string, bool> printed;
        for (auto iter2 = graph[iter->first].begin(); iter2 != graph[iter->first].end(); iter2++)
        {
            if (printed.count(iter2->first) == 1)
            {
                continue;
            }
            cout << iter->first << " - " << iter2->first << " : " << iter2->second << endl;
        }
        printed[iter->first] = true;
    }
    cout << endl;

    status[start] = "in-tree";
    for (auto iter = graph[start].begin(); iter != graph[start].end(); iter++)
    {
        status[iter->first] = "fringe";
        dist[iter->first] = iter->second;
        dad[iter->first] = start;
        AddHeap(heap, heapCount, HeapNode(iter->first, iter->second));
    }

    while (heapCount > 0)
    {
        HeapNode vertex = MinofHeap(heap);
        DeleteHeap(heap, heapCount);
        if (status[vertex.toVertex].compare("in-tree") == 0)
        {
            continue;
        }
        status[vertex.toVertex] = "in-tree";

        for (auto iter = graph[vertex.toVertex].begin(); iter != graph[vertex.toVertex].end(); iter++)
        {
            if (status[iter->first].compare("others") == 0)
            {
                status[iter->first] = "fringe";
                dist[iter->first] = iter->second;
                dad[iter->first] = vertex.toVertex;
                AddHeap(heap, heapCount, HeapNode(iter->first, iter->second));
            }
            else if (status[iter->first].compare("fringe") == 0)
            {
                if (dist[iter->first] > iter->second)
                {
                    dist[iter->first] = iter->second;
                    dad[iter->first] = vertex.toVertex;
                    AddHeap(heap, heapCount, HeapNode(iter->first, iter->second));
                }
            }
        }
    }

    cout << "Prim result: " << endl;

    for (auto iter = graph.begin(); iter != graph.end(); iter++)
    {
        bool isFounded = false;
        for (auto iter2 = dad.begin(); iter2 != dad.end(); iter2++)
        {
            if (iter2->second == iter->first)
            {
                isFounded = true;
                break;
            }
        }

        if (!isFounded)
        {
            if (start.compare(iter->first) == 0)
            {
                cout << start << endl;
                continue;
            }

            string end = iter->first;
            map<string, string> shortist;
            while (end.compare(start) != 0)
            {
                shortist[dad[end]] = end;
                end = dad[end];
            }

            cout << start;
            end = shortist[end];
            while (end.compare(iter->first) != 0)
            {
                cout << " - " << end << "(" << dist[end] << ")";
                end = shortist[end];
            }
            cout << " - " << iter->first << "(" << dist[iter->first] << ")" << endl;
        }
    }

    return 0;
}