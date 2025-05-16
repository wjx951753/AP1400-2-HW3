#ifndef BST_H
#define BST_H

#include <functional>
#include <queue>

class Node
{
public:
	Node(int value, Node* left, Node* right);
	Node();
	Node(const Node& node);

	int value;
	Node* left;
	Node* right;
};


class BST
{
public:
    Node*& get_root();
    void bfs(std::function<void(Node*& node)> func);
    size_t length();
    bool add_node(int value);
    Node** find_node(int value);
    Node** find_parrent(int value);
    Node** find_successor(int value);
    bool delete_node(int value);

    BST() noexcept = default;
    BST(BST&& other) noexcept;
    ~BST();
    BST(const BST& other) : root(copyTree(other.root)) {};
    BST& operator=(const BST& other);
    BST& operator=(BST&& other) noexcept;

private:
    Node* addSubTree(Node* root, int value); 
    Node* copyTree(Node* node);
    void destroyTree(Node* node);
    Node* root; 
};
#endif //BST_H