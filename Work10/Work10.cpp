#include <iostream>
#include <vector>

using namespace std;

template<class T>
class Edge
{
public:
	int Start;
	int End;
	Edge<T>* Next_Edge;

	Edge(const int start, const int end)
	{
		Start = start;
		End = end;
		Next_Edge = nullptr;
	}

	~Edge()
	{
		if (Next_Edge != nullptr)
			delete Next_Edge;
	}

	Edge* NextEdge()
	{
		return this->Next_Edge;
	}
};

template<class T>
class Node
{

public:
	Edge<T>* OutEdge;
	T value;
	int in_edge_count = 0;
	bool is_visited = false;

	Node(T value)
	{
		this->value = value;
		OutEdge = nullptr;
	}

	void SetOutEdge(Edge<T>* edge)
	{
		this->OutEdge = edge;
	}

	bool has_out_edge()
	{
		return OutEdge != nullptr;
	}

	~Node()
	{
		if (has_out_edge())
		{
			delete OutEdge;
		}
	}

};



int main()
{
	int n, m;
	cin >> n >> m;
	vector<Node<int>> nodes;
	for (int i = 0; i < n; ++i)
	{
		nodes.push_back(Node<int>(i + 1));
	}

	for (int i = 0; i < m; i++)
	{
		int p1, p2;
		cin >> p1 >> p2;
		p1--;
		p2--;
		Node<int>* ptr_p1 = &nodes[p1];
		if (!ptr_p1->has_out_edge())
		{
			ptr_p1->SetOutEdge(new Edge<int>(p1, p2));
			nodes[p2].in_edge_count++;
			continue;
		}
		Edge<int>* edge_p1 = ptr_p1->OutEdge;

		while (edge_p1->NextEdge() != nullptr)
			edge_p1 = edge_p1->NextEdge();

		edge_p1->Next_Edge = new Edge<int>(p1, p2);

		nodes[p2].in_edge_count++;
	}


	while (true)
	{
		int min_node = -1;
		for (int i = 0; i < n; i++)
		{
			if (!nodes[i].is_visited && nodes[i].in_edge_count == 0)
			{
				if (min_node == -1 || min_node > i)
				{
					min_node = i;
				}
			}
		}
		if (min_node == -1)
			break;

		nodes[min_node].is_visited = true;

		cout << nodes[min_node].value << '\t';

		Edge<int>* edge = nodes[min_node].OutEdge;
		while (edge != nullptr)
		{
			nodes[edge->End].in_edge_count--;
			edge = edge->NextEdge();
		}
	}

	return 0;
}