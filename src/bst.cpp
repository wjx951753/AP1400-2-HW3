#include "bst.h"


Node*& BST::get_root() {
    return root;
}

void BST::bfs(std::function<void(Node*& node)> func) {
    if (root == nullptr) {
        return;
    }

    std::queue<Node*> nodeQueue;
    nodeQueue.push(root);
    while (!nodeQueue.empty()) {
        Node* node = nodeQueue.front();

        func(node);

        if (node->left != nullptr) {
            nodeQueue.push(node->left);
        }

        if (node->right != nullptr) {
            nodeQueue.push(node->right);
        }
    }
}

size_t BST::length() {
    size_t count = 0;
    bfs([&count](Node* node) {
        count++;
    });
    return count;
}

bool BST::add_node(int value) {
    if (find_node(value)) {
        return false;
    }
    root = addSubTree(root, value);
    return true;

}


Node* BST::addSubTree(Node* root, int value) {
    if (root == nullptr) {
        return new Node(value);
    }

    if (value > root->value) {
        root->right = addSubTree(root->right, value);
    } else if (value > root->value) {
        root->left = addSubTree(root->left, value);
    }

    return root;
}

Node** BST::find_node(int value) {
    Node** current = &root;
    while (*current != nullptr)
    {
        if (value == (*current)->value) {
            return current;
        } else if (value < (*current)->value) {
            current = &((*current)->left);
        } else {
            current = &((*current)->right);
        }
    }
    return nullptr;
}

Node** BST::find_parrent(int value) {
    Node** current = &root;
    Node** parrent = nullptr;
    while (*current != nullptr)
    {
        if (value == (*current)->value) {
            return parrent;
        } else if (value < (*current)->value) {
            parrent = current;
            current = &((*current)->left);
        } else {
            parrent = current;
            current = &((*current)->right);
        }
    }
    return nullptr;
}

Node** BST::find_successor(int value) {
    Node** current = &root;
    Node** successer = nullptr;
    while (*current != nullptr) {
        if (value == (*current)->value) {
            if (((*current)->right) != nullptr) {
                Node** temp = &((*current)->right);
                while ((*temp)->left != nullptr) {
                    temp = &((*temp)->left);
                }
                return temp;
            }
            return successer;
        } else if (value < (*current)->value) {
            successer = current;
            current = &((*current)->left);
        } else {
            current = &((*current)->right);
        }
    }
    return nullptr;
}

bool BST::delete_node(int value) {
    Node** toDelete = find_node(value);

    if (!*toDelete) {
        return false;
    }

    Node* node = *toDelete;

    if (node->left == nullptr && node->right == nullptr) {
        delete node;
        *toDelete = nullptr;
    } else if (node->left && node->right) {
        Node** succ = find_successor(value);
        node->value = (*succ)->value;
        delete_node((*succ)->value);
    } else {
        Node* child = node->left? node->left : node->right;
        delete node;
        *toDelete = child;
    }
    return true;
}

Node* BST::copyTree(Node* node) {
    if (!node) {
        return nullptr;
    }

    Node* newNode = new Node(node->value);
    newNode = copyTree(node->left);
    newNode = copyTree(node->right);
    return newNode;
        
}

void BST::destroyTree(Node* node) {
    if (!node) {
        return;
    }

    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
}

BST& BST::operator=(const BST& other) {
    if (this != &other) {
        destroyTree(root);
        root = copyTree(other.root);
    }

    return *this;
}


BST::~BST() {
    std::vector<Node*> nodes;
    bfs([&nodes](BST::Node*& node) {nodes.push_back(node);});
    for(auto& node: nodes)
        delete node;
}




Node::Node(int value, Node* left, Node* right) : value(value), left(left), right(right){}
Node::Node() : value(0),left(nullptr),right(nullptr) {}
Node::Node(const Node& node): value(node.value),left(node.left),right(node.right) {}