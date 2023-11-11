#ifndef SEARCHTREE_H
#define SEARCHTREE_H
#include <vector>



class SearchTree
{
public:
    //class Node;
    struct Node;
    SearchTree();
    ~SearchTree();

    bool isEmpty();
    Node* root();
    void clearTree();
    Node* addNode(int key);
    Node* searchNode(int key);
    bool deleteNode(const int key);
    bool deleteNode(Node* root);
    int heightTree(Node* root);

protected:
    void clearTree(Node* root);
    Node* addNode(Node* root, int key);
    Node* maxNode(Node* root);
    Node* searchNode(Node* root, int key);
    Node* searchParent(Node* root);
    bool deleteNode(Node* root, const int key);


protected:
    Node* m_root = nullptr;
};

class SearchTree::Node
{
public:
    Node(int key = 0, Node* left = nullptr, Node* right = nullptr)
    {
        m_key = key;
        m_left = left;
        m_right = right;
    }
    ~Node() = default;
public:
    int m_key = 0;
    Node* m_left = nullptr;
    Node* m_right = nullptr;


};
#endif // SEARCHTREE_H
