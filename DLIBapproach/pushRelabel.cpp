
// code original authors Siddharth Lalwani and Utkarsh Trivedi 
// URLhttps://www.geeksforgeeks.org/push-relabel-algorithm-set-1-introduction-and-illustration/
// code modified by dpe22 for EC504 Group Project URLhttps://github.com/Flymindo/EC504_FinalProject



/****************************************************************************************************************************************************************************************/
// Push-Relabel Algorithm Overview

// (1) Inititalize PreFlow
//		- Initialize height and flow of all nodes to 0
//		- Initialize height of source to n = total # of nodes
//		- Initialize flow of every arc to 0
//		- For all neighbors of source, flow and excess flow are equal to initial capacity

// (2) Perform Push() or Relabel() until all nodes have 0 excess flow
//		- Push(): If a node has excess flow and there is a neighber with smaller height, push the flow (i.e., min of excess flow and arc capacity) from the node to the neighbor. 
//		- Relabel(): If a node has excess flow, but no neighbor with smaller height, increase the height of the min height neighbor node by 1 so it becomes possible to push() to it. 

// (3) Return flow
/****************************************************************************************************************************************************************************************/

#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>
#include <dlib/image_transforms.h>
#include <fstream>
#include <iostream>
#include <vector>

using namespace dlib;
using namespace std;

struct Node {
	int h;		// node height
	int e_flow; // excess flow

	Node(int h, int e_flow) {
		this->h = h;
		this->e_flow = e_flow;
	}
};

struct Edge {
	int u, v;	// endpoints of arc
	int flow;	// current flow
	int capacity;

	Edge(int flow, int capacity, int u, int v) {
		this->flow = flow;
		this->capacity = capacity;
		this->u = u;
		this->v = v;
	}

};

class Graph {
	int N;		// number of nodes
	std::vector<Node> node;
	std::vector<Edge> edge;

	// function to push excess flow from u
	bool push(int u);

	// function to relabel a vertex u
	void relabel(int u);

	// initialize preflow
	void preflow(int s);

	// function to update reverse arc
	void updateReverseEdgeFlow(int i, int flow);

public:
	Graph(int N); // constructor

	// function to add an arc to the graph
	void addEdge(int u, int v, int w);

	// function to return maximum flow from s to t
	int getMaxFlow(int s, int t);
};

Graph::Graph(int N) {
	this->N = N;

	// initialize all nodes with height 0 and 0 excess flow
	for (int i = 0; i < N; i++) {
		node.push_back(Node(0, 0));
	}
}

void Graph::addEdge(int u, int v, int capacity) {
	edge.push_back(Edge(0, capacity, u, v));
}

void Graph::preflow(int s) {

	// height of node = number of nodes
	node[s].h = node.size();

	for (int i = 0; i < edge.size(); i++) {

		// if current arc is from the origin
		if (edge[i].u == s) {
			// flow = capacity
			edge[i].flow = edge[i].capacity;
			// initialize e_flow for neighboring nodes
			node[edge[i].v].e_flow += edge[i].flow;
			// add an arc from v to origin (s) with capacity = 0
			edge.push_back(Edge(-edge[i].flow, 0, edge[i].v, s));
		}
	}
}

// returns the index of overflowing node
int overFlowNode(std::vector<Node>& node) {
	for (int i = 1; i < node.size() - 1; i++) {
		if (node[i].e_flow > 0) return i;
	}
	return -1;
}

// update reverese flow for flow added on ith arc
void Graph::updateReverseEdgeFlow(int i, int flow) {
	int u = edge[i].v, v = edge[i].u;

	for (int j = 0; j < edge.size(); j++) {
		if (edge[j].v == v && edge[j].u == u) {
			edge[j].flow -= flow;
			return;
		}
	}

	// add reverse arc
	Edge a = Edge(0, flow, u, v);
	edge.push_back(a);
}

// function to push flow from overflowing vertex u
bool Graph::push(int u) {

	// loop through all arcs to fin a neighbor of u to push flow
	for (int i = 0; i < edge.size(); i++) {
		if (edge[i].u == u) {

			// if flow == capacity then no push is possilbe
			if (edge[i].flow == edge[i].capacity)
				continue;

			// push is only possible if the height of the neighbor is smaller than the heigh of the overflowing node
			if (node[u].h > node[edge[i].v].h) {
				// flow to push = min of remaining flow on arc and excess flow
				int flow = std::min(edge[i].capacity - edge[i].flow, node[u].e_flow);
				// reduce excess flow for the overflowing node
				node[u].e_flow -= flow;
				// increase flow for the neighboring node
				node[edge[i].v].e_flow += flow;
				// add residual flow
				edge[i].flow += flow;
				updateReverseEdgeFlow(i, flow);
				return true;
			}
		}
	}
	return false;
}

// function to relabel node u
void Graph::relabel(int u) {
	//initialize min height of neighbor
	int mh = INT_MAX;

	//find neighbor with min height
	for (int i = 0; i < edge.size(); i++) {
		if (edge[i].u == u) {
			// if flow == capacity, no relabel
			if (edge[i].flow == edge[i].capacity)
				continue;
			// update min height and height of u
			if (node[edge[i].v].h < mh) {
				mh = node[edge[i].v].h;
				node[u].h = mh + 1;
			}
		}
	}
}

int Graph::getMaxFlow(int s, int t) {
	preflow(s);

	// loop until no nodes overflow
	while (overFlowNode(node) != -1) {
		int u = overFlowNode(node);
		if (!push(u)) relabel(u);
	}

	// return the last node, whose e_flow will be the max flow of the graph
	return node.back().e_flow;
}

int main(int argc, char** argv) {
	
	int T = 6; 
	Graph t(T);

	// Creating flow network shown in CLRS CH 26 pg 726 (a)
	t.addEdge(0, 1, 16);
	t.addEdge(0, 2, 13);
	t.addEdge(1, 2, 10);
	t.addEdge(2, 1, 4);
	t.addEdge(1, 3, 12);
	t.addEdge(2, 4, 14);
	t.addEdge(3, 2, 9);
	t.addEdge(3, 5, 20);
	t.addEdge(4, 3, 7);
	t.addEdge(4, 5, 4);

	int a = 0, b = 5;
	cout << "Max flow is " << t.getMaxFlow(a, b) << endl;

	try
	{
		// make sure the user entered an argument to this program
		if (argc != 2)
		{
			std::cout << "error, you have to enter a BMP file as an argument to this program" << std::endl;
			return 1;
		}

		// Here we declare an image object that can store rgb_pixels.  Note that in 
		// dlib there is no explicit image object, just a 2D array and
		// various pixel types.  
		array2d<rgb_pixel> img;
		//array2d<short> horz_gradient, vert_gradient;
		//array2d<unsigned char> edge_image;

		// Now load the image file into our image.  If something is wrong then
		// load_image() will throw an exception.  Also, if you linked with libpng
		// and libjpeg then load_image() can load PNG and JPEG files in addition
		// to BMP files.
		load_image(img, argv[1]);
		array2d<unsigned char> img_gray;
		assign_image(img_gray, img);
		// make a window to display the original image
		image_window my_window2(img, "Original Image");

		// number of pixels aka nodes aka vertices
		int V = img.nr() * img.nc();
		int capacity = 0;
		int sigma = 100;
		int capacityBlue = 0;
		int capacityRed = 0;
		int capacityGreen = 0;

		// initialize a graph with V nodes + source and sink nodes
		std::cout << "initializing graph" << endl;
		Graph g(V+2);
		std::cout << "graph initialized with " << V << " nodes, a source node (s), and a sink node (t)." << endl;

		// This loop executes every time the user double clicks on some image pixel and it
		// will terminate once the user closes the window or clicks on two pixels
		int counter = 0;
		point p;
		std::vector<point> userInput;

		while (my_window2.get_next_double_click(p))
		{
			counter++;
			userInput.push_back(p);
			std::cout << "User double clicked on pixel:         " << p << endl;
			if (counter == 2) break;
		}

		// add edges
		for (int i = 0; i < img.nr(); i++) {

			//the capacity of each edge should be higher for similar pixels and smaller for different pictures (could use grayscale for simplicity)
			for (int j = 0; j < img.nc(); j++) {

				//add edge to source (grayscale)
				//capacity = 100 * exp(-(img_gray[i][j] - img_gray[userInput[0].y()][userInput[0].x()]) ^ 2 / (2*sigma^2));
				//capacity = max(capacity, 0);
				//std::cout << "capacity from edge to source at [" << i << "][" << j << "] = " << capacity << endl;

				//add edge to source
				capacityBlue = 100 * exp(-pow(img[i][j].blue - img[userInput[0].y()][userInput[0].x()].blue, 2) / (2 * pow(sigma,2)));
				capacityRed = 100 * exp(-pow(img[i][j].red - img[userInput[0].y()][userInput[0].x()].red, 2) / (2 * pow(sigma,2)));
				capacityGreen = 100 * exp(-pow(img[i][j].green - img[userInput[0].y()][userInput[0].x()].green, 2) / (2 * pow(sigma,2)));
				//cout << img[i][j].red - img[userInput[0].y()][userInput[0].x()].red << endl;
				//cout << img[i][j].green - img[userInput[0].y()][userInput[0].x()].green << endl;
				//cout << img[i][j].blue - img[userInput[0].y()][userInput[0].x()].blue << endl;
				capacity = capacityRed + capacityGreen + capacityBlue;
				//capacity = max(capacity, 0);
				g.addEdge((i)*img.nc() + j, V + 1, capacity);
				
				//add edge to sink
				capacityBlue = 100 * exp(-pow(img[i][j].blue - img[userInput[1].y()][userInput[1].x()].blue, 2) / (2 * pow(sigma,2)));
				capacityRed = 100 * exp(-pow(img[i][j].red - img[userInput[1].y()][userInput[1].x()].red, 2) / (2 * pow(sigma,2)));
				capacityGreen = 100 * exp(-pow(img[i][j].green - img[userInput[1].y()][userInput[1].x()].green, 2) / (2 * pow(sigma, 2)));
				capacity = capacityRed + capacityGreen + capacityBlue;
				capacity = max(capacity, 0);
				g.addEdge((i) * img.nc() + j, V + 2, capacity);
				//std::cout << "capacity from edge to sink at [" << i << "][" << j << "] = " << capacity << endl;
				
				//add edge right unless in the right-most column
				if (j < img.nc() - 1) {
					capacityBlue = 100 * exp(-pow(img[i][j].blue - img[i][j + 1].blue, 2) / (2 * pow(sigma, 2)));
					capacityRed = 100 * exp(-pow(img[i][j].red - img[i][j + 1].red, 2) / (2 * pow(sigma, 2)));
					capacityGreen = 100 * exp(-pow(img[i][j].green - img[i][j + 1].green, 2) / (2 * pow(sigma, 2)));
					capacity = capacityRed + capacityGreen + capacityBlue;
					capacity = max(capacity, 0);
					g.addEdge((i) * img.nc() + j, (i) * img.nc() + (j + 1), capacity);
					std::cout << "capacity from edge to right at [" << i << "][" << j << "] = " << capacity << endl;
				}

				//add edge left unless in the left-most column
				if (j > 0) {
					capacityBlue = 100 * exp(-pow(img[i][j].blue - img[i][j - 1].blue, 2) / (2 * pow(sigma,2)));
					capacityRed = 100 * exp(-pow(img[i][j].red - img[i][j - 1].red, 2) / (2 * pow(sigma, 2)));
					capacityGreen = 100 * exp(-pow(img[i][j].green - img[i][j - 1].green, 2) / (2 * pow(sigma, 2)));
					capacity = capacityRed + capacityGreen + capacityBlue;
					capacity = max(capacity, 0);
					g.addEdge((i) * img.nc() + j, (i) * img.nc() + (j - 1), capacity);
					//std::cout << "capacity from edge to left at [" << i << "][" << j << "] = " << capacity << endl;
				}

				//add edge up unless in the top row
				if (i > 0) {
					capacityBlue = 100 * exp(-pow(img[i][j].blue - img[i - 1][j].blue, 2) / (2 * pow(sigma, 2)));
					capacityRed = 100 * exp(-pow(img[i][j].red - img[i - 1][j].red, 2) / (2 * pow(sigma, 2)));
					capacityGreen = 100 * exp(-pow(img[i][j].green - img[i - 1][j].green, 2) / (2 * pow(sigma, 2)));
					capacity = capacityRed + capacityGreen + capacityBlue;
					capacity = max(capacity, 0);
					g.addEdge((i) * img.nc() + j, (i - 1) * img.nc() + j, capacity);
					//std::cout << "capacity from edge to up at [" << i << "][" << j << "] = " << capacity << endl;
				}

				//add edge down unless in the bottom row
				if (i < img.nr() - 1) {
					capacityBlue = 100 * exp(-pow(img[i][j].blue - img[i + 1][j].blue, 2) / (2 * pow(sigma,2)));
					capacityRed = 100 * exp(-pow(img[i][j].red - img[i + 1][j].red, 2) / (2 * pow(sigma,2)));
					capacityGreen = 100 * exp(-pow(img[i][j].green - img[i + 1][j].green, 2) / (2 * pow(sigma,2)));
					capacity = capacityRed + capacityGreen + capacityBlue;
					capacity = max(capacity, 0);
					g.addEdge(i * img.nc() + j, (i + 1) * img.nc() + j, capacity);
					//std::cout << "capacity from edge to down at [" << i << "][" << j << "] = " << capacity << endl;
				}
				//std::cout << "Added edges for column " << j << " in row " << i << endl;
			}
		}

		int s = V + 1;
		int t = V + 2;
		std::cout << "Maximum flow is " << g.getMaxFlow(s, t);

		// terminate the program when the user closes the image
		my_window2.wait_until_closed();

		// Finally, note that you can access the elements of an image using the normal [row][column]
		// operator like so:
		//std::cout << horz_gradient[0][3] << std::endl;
		//std::cout << "number of rows in image:    " << horz_gradient.nr() << std::endl;
		//std::cout << "number of columns in image: " << horz_gradient.nc() << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << "exception thrown: " << e.what() << std::endl;
	}
	return 0;
}