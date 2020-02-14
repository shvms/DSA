#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct vertexTag {
    char tag;                   // name of the node
    bool visited;               // is visited. To be used for searching
    struct edgeTag *edges;      // points to the linked list of edges
    struct vertexTag *next;     // points to the next vertex in the list of vertices
} Vertex;

typedef struct edgeTag {
    struct vertexTag *connectsTo;   // connects to which vertex
    struct edgeTag *next;           // next edge
} Edge;

typedef struct GraphTag {
    struct vertexTag *vertices;     // pointer to the initial vertex of the vertices
} Graph;

Graph* createGraph();
Graph* addVertex(Graph* g, char vertex);
Graph* addEdge(Graph* g, char vertex1, char vertex2);
void destroyGraph(Graph* g);
void dfs(Graph* g, Vertex* v);
void bfs(Graph* g, Vertex* v);
void resetGraph(Graph* g);

/* utility functions */
void addNode(Vertex** vertices, char item) {
    Vertex *new_vertex = (Vertex*) malloc(sizeof(Vertex));
    new_vertex -> tag = item;
    new_vertex -> visited = false;
    new_vertex -> edges = NULL;
    new_vertex -> next = NULL;

    if (*vertices == NULL)
        *vertices = new_vertex;
    else {
        Vertex* curr = *vertices;
        while (curr -> next != NULL) {
            curr = curr -> next;
        }
        curr -> next = new_vertex;
    }
}
Vertex* findVertex(Vertex* head, char val) {
    while (head != NULL && (head -> tag) != val) {
        head = head -> next;
    }
    return head;
}
Edge* findEdge(Edge* head, char val) {
    while (head != NULL && (head -> connectsTo) -> tag != val) {
        head = head -> next;
    }
    return head;
}

// queue
typedef struct Node {
    struct vertexTag* val;
    struct Node* next;
} node;

typedef struct Q {
    node* front;
    node* rear;
    int curr_size;
} queue;

node* createNode(struct vertexTag* val) {
    node* n = (node*) malloc(sizeof(node));
    n -> next = NULL;
    n -> val = val;
    return n;
}

queue* initialiseQueue() {
    queue* qu = (queue*) malloc(sizeof(queue));
    qu -> front = NULL;
    qu -> rear = NULL;
    qu -> curr_size = 0;
}

void enqueue(queue* qu, struct vertexTag* val) {
    node* new_node = createNode(val);
    if (qu -> front == NULL) {
        qu -> front = new_node;
        qu -> rear = qu -> front;
    } else {
        (qu -> rear) -> next = new_node;
        qu -> rear = new_node;
    }
    (qu -> curr_size)++;
}

struct vertexTag* dequeue(queue* qu) {
    node* to_be_deleted;
    if (qu -> curr_size == 0) {
        printf("Queue already empty.\n");
        exit(1);
    }
    if (qu -> curr_size == 1) {
        to_be_deleted = qu -> front;
        qu -> front = NULL;
        qu -> rear = NULL;
    } else {
        to_be_deleted = qu -> front;
        qu -> front = (qu -> front) -> next;
    }
    struct vertexTag* v = to_be_deleted -> val;
    free(to_be_deleted);
    (qu -> curr_size)--;
    return v;
}

bool isEmpty(queue* qu) {
    return qu -> curr_size == 0;
}

/* Assumes no duplicate vertex or edges inserted */
int main() {
    Graph* g = createGraph();
    addVertex(g, 's');
    addVertex(g, 'a');
    addVertex(g, 'b');
    addVertex(g, 'c');
    addVertex(g, 'd');
    addVertex(g, 'e');

    addEdge(g, 's', 'a');
    addEdge(g, 's', 'b');
    addEdge(g, 'a', 'c');
    addEdge(g, 'a', 'd');
    addEdge(g, 'c', 'd');
    addEdge(g, 'c', 'e');
    addEdge(g, 'd', 'e');
    addEdge(g, 'b', 'd');

    Vertex* v = g -> vertices;
    while (v != NULL) {
        printf("%c --> ", v -> tag);
        Edge* e = v -> edges;
        while (e != NULL) {
            printf("%c --> ", (e -> connectsTo) -> tag);
            e = e -> next;
        }
        printf("NULL\n");

        v = v -> next;
    }

    printf("\n");

    char start = 's';
    Vertex* s = findVertex(g -> vertices, start);
    printf("Depth First Search at %c: ", s);
    dfs(g, s);

    resetGraph(g);

    printf("\n");
    printf("Breadth First Search at %c: ", start);
    bfs(g, s);

    return 0;
}

Graph* createGraph() {
    Graph* g = (Graph*) malloc(sizeof(Graph));
    g -> vertices = NULL;
    return g;
}

void resetGraph(Graph* g) {
    Vertex* v = g -> vertices;
    while (v != NULL) {
        v -> visited = false;
        v = v -> next;
    }
}

Graph* addVertex(Graph* g, char vertex) {
    addNode(&(g -> vertices), vertex);
    return g;
}

/*
 * directed from v1 -> v2
 */
Graph* addEdge(Graph* g, char v1, char v2) {
    Vertex* v2_ = g -> vertices;

    // if v2 exists in graph
    v2_ = findVertex(v2_, v2);
    if (v2_ == NULL) {
        printf("Error: No vertex named %c.\n", v2);
        exit(1);
    }

    // searching for v1
    Vertex* v1_ = g -> vertices;
    v1_ = findVertex(v1_, v1);
    if (v1_ == NULL) {
        printf("Error: No vertex named %c.\n", v1);
        exit(1);
    }

    Edge* new_edge12 = (Edge*) malloc(sizeof(Edge));
    new_edge12 -> connectsTo = v2_;

    // adding edge
    Edge* temp = v1_ -> edges;
    v1_ -> edges = new_edge12;
    new_edge12 -> next = temp;

    // undirected
    Edge* new_edge21 = (Edge*) malloc(sizeof(Edge));
    new_edge21 -> connectsTo = v1_;

    temp = v2_ -> edges;
    v2_ -> edges = new_edge21;
    new_edge21 -> next = temp;

    return g;
}

void dfs(Graph* g, Vertex* s) {
    printf("%c\t", s->tag);
    s -> visited = true;
    Edge* e = s -> edges;
    while (e != NULL) {
        if ((e -> connectsTo) -> visited == false) {
            (e -> connectsTo) -> visited = true;
            dfs(g, e -> connectsTo);
        }
        e = e -> next;
    }
}

void bfs(Graph* g, Vertex* s) {
    queue* qu = initialiseQueue();
    s -> visited = true;
    enqueue(qu, s);

    while (!isEmpty(qu)) {
        Vertex* v = dequeue(qu);
        printf("%c\t", v -> tag);

        Edge* e = v -> edges;
        while (e != NULL) {
            if ((e -> connectsTo) -> visited == false) {
                (e -> connectsTo) -> visited = true;
                enqueue(qu, e -> connectsTo);
            }
            e = e -> next;
        }
    }
}