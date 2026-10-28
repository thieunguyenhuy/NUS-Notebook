/**
 * Author: Thieu Nguyen Huy
 * Description: Splay tree to find add element, remove element and get the k-th element, 1-indexed
 * Time: Amortized O(\log N) on average for each operation
 * Status: Tested on SPOJ
 */

struct Node {
    Node *parent, *child[2];
    int sz = 0, value;

    Node(int val = 0) {
        parent = nullptr, sz = 1, value = val;
        child[0] = child[1] = nullptr;
    }

    int side() {
        return parent ? parent->child[1] == this : -1;
    }

    void pushUp() {
        sz = 1;
        for (int i = 0; i < 2; ++i)
            if (child[i]) sz += child[i]->sz;
    }
};
const int NUM_NODES = 1e6 + 5;
Node nodes[NUM_NODES];
int numNode = 0;

Node *newNode(int value = 0) {
    nodes[numNode] = Node(value);
    return &nodes[numNode++];
}

struct SplayTree {
    Node *root;

    SplayTree() {
        root = newNode(0);
        link(root, newNode(inf), 1);
        root->pushUp();
    }

    Node *oneDir(int dir) {
        Node *p = root;
        while (p && p->child[dir]) p = p->child[dir];
        return p;
    }

    void link(Node *a, Node *b, int dir) {
        if (a == nullptr) {
            root = b;
            if (root) root->parent = nullptr;
            return;
        }
        a->child[dir] = b;
        if (b) b->parent = a;
    }

    void rotate(Node *a) {
        Node *p = a->parent;
        int dir = a->side();
        link(p->parent, a, p->side());
        link(p, a->child[!dir], dir);
        link(a, p, !dir);
        p->pushUp(), a->pushUp();
    }

    void splay(Node *a, Node *s = nullptr) {
        while (a->parent != s) {
            Node *p = a->parent;

            if (p->parent == s) rotate(a);
            else if (a->side() == p->side()) rotate(p), rotate(a); // zig-zig
            else rotate(a), rotate(a);
        }
    }

    void find(int k, Node *s = nullptr) { // assume tree has at least k vertices
        Node *p = root;
        while (true) {
            int cntLeft = (p->child[0] ? p->child[0]->sz : 0);
            if (cntLeft > k) p = p->child[0];
            else if (cntLeft + 1 > k) {
                splay(p, s); return;
            }
            else {
                k -= cntLeft + 1;
                p = p->child[1];   
            }
        }
    }

    // Insert before the current k-th element. 1 <= k <= n + 1
    void insert(int k, int val) {
        find(k);
        find(k - 1, root);

        Node *foo = newNode(val);
        link(foo, root->child[0], 0);
        link(root, foo, 0);
        foo->pushUp(), root->pushUp();
    }

    // 1 <= k <= n
    void remove(int k) {
        find(k + 1);
        find(k - 1, root);

        link(root->child[0], nullptr, 1);
        root->child[0]->pushUp();
        root->pushUp();
    }

    // 1 <= k <= n
    int get(int k) {
        find(k);
        return root->value;
    }
} tree;