#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100 // Maximum number of vertices

// Structure for adjacency list node
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

// Structure for adjacency list
typedef struct Graph {
    int numVertices;
    Node* adjLists[MAX];
    bool visited[MAX];
} Graph;

// Queue structure for BFS
typedef struct Queue {
    int items[MAX];
    int front;
    int rear;
} Queue;

// Function to create a new node
Node* createNode(int vertex) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph
Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = vertices;
    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = false;
    }
    return graph;
}

// Function to add an edge to the graph
void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    // Since the graph is undirected, add an edge from dest to src as well
    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

// Function for DFS traversal
void DFS(Graph* graph, int vertex) {
    graph->visited[vertex] = true;
    printf("%d ", vertex);

    Node* temp = graph->adjLists[vertex];
    while (temp) {
        int adjVertex = temp->vertex;
        if (!graph->visited[adjVertex]) {
            DFS(graph, adjVertex);
        }
        temp = temp->next;
    }
}

// Function to create a queue
Queue* createQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = -1;
    queue->rear = -1;
    return queue;
}

// Check if the queue is empty
bool isEmpty(Queue* queue) {
    return queue->rear == -1;
}

// Add an element to the queue
void enqueue(Queue* queue, int value) {
    if (queue->rear == MAX - 1) {
        printf("Queue is full\n");
        return;
    }
    if (queue->front == -1) {
        queue->front = 0;
    }
    queue->rear++;
    queue->items[queue->rear] = value;
}

// Remove an element from the queue
int dequeue(Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty\n");
        return -1;
    }
    int item = queue->items[queue->front];
    queue->front++;
    if (queue->front > queue->rear) {
        queue->front = queue->rear = -1;
    }
    return item;
}

// Function for BFS traversal
void BFS(Graph* graph, int startVertex) {
    Queue* queue = createQueue();

    graph->visited[startVertex] = true;
    enqueue(queue, startVertex);

    while (!isEmpty(queue)) {
        int currentVertex = dequeue(queue);
        printf("%d ", currentVertex);

        Node* temp = graph->adjLists[currentVertex];

        while (temp) {
            int adjVertex = temp->vertex;
            if (!graph->visited[adjVertex]) {
                graph->visited[adjVertex] = true;
                enqueue(queue, adjVertex);
            }
            temp = temp->next;
        }
    }
}

// Reset visited array for re-traversal
void resetVisited(Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        graph->visited[i] = false;
    }
}

int main() {
    int vertices, edges, src, dest, startVertex;
    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);

    Graph* graph = createGraph(vertices);

    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    for (int i = 0; i < edges; i++) {
        printf("Enter edge (source destination): ");
        scanf("%d %d", &src, &dest);
        addEdge(graph, src, dest);
    }

    printf("Enter the starting vertex for DFS: ");
    scanf("%d", &startVertex);
    printf("DFS Traversal: ");
    DFS(graph, startVertex);

    resetVisited(graph);

    printf("\nEnter the starting vertex for BFS: ");
    scanf("%d", &startVertex);
    printf("BFS Traversal: ");
    BFS(graph, startVertex);

    return 0;
}


// output //

// Enter the number of vertices: 5
// Enter the number of edges: 6
// Enter edge (source destination): 0 1
// Enter edge (source destination): 0 2
// Enter edge (source destination): 1 3
// Enter edge (source destination): 1 4
// Enter edge (source destination): 2 4
// Enter edge (source destination): 3 4
// Enter the starting vertex for DFS: 0
// DFS Traversal: 0 2 4 3 1 
// Enter the starting vertex for BFS: 0
// BFS Traversal: 0 2 1 4 3 