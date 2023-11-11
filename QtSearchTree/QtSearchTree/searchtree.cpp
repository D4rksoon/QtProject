#include "SearchTree.h"
#include <iostream>
#include <vector>

SearchTree::SearchTree()
{

}

SearchTree::~SearchTree()
{
    clearTree();
}

SearchTree::Node* SearchTree::root()
{
    return m_root;
}

void SearchTree::clearTree()
{
    clearTree(m_root);
}

void SearchTree::clearTree(Node* root)
{
    if (root == nullptr)
        return;

    if (root->m_left){
        clearTree(root->m_left);
    }
    if (root->m_right){
        clearTree(root->m_right);
    }

    if (root == m_root){
        m_root = nullptr;
    }

    delete root;
}

bool SearchTree::isEmpty()
{
    return m_root == nullptr;
}

int SearchTree::heightTree(Node* root)
{
    if (root == nullptr)
        return 0;

    if ((root->m_left == nullptr) and (root->m_right == nullptr))
        return 1;

    int leftHeight = 0, rightHeight = 0;

    if (root->m_left)
        leftHeight = heightTree(root->m_left);

    if (root->m_right)
        rightHeight = heightTree(root->m_right);

    int height;

    if (rightHeight > leftHeight)
        height = rightHeight;
    else
        height = leftHeight;

    return height + 1;
}

SearchTree::Node* SearchTree::addNode(Node* root, int key)
{
    if (!root) {
        root = new Node(key);
    }
    else if (key < root->m_key) {
        root->m_left = (addNode(root->m_left, key));
    }
    else {
        root->m_right = (addNode(root->m_right, key));
    }

    return root;
}

SearchTree::Node* SearchTree::addNode(int key)
{
    if (m_root) {
        return addNode(m_root, key);
    }
    else {
        return m_root = new Node(key);
    }
}

SearchTree::Node* SearchTree::maxNode(Node* root)
{
    if (root == nullptr)
        return nullptr;

    if (root->m_right)
        return maxNode(root->m_right);
    else
        return root;
}

SearchTree::Node* SearchTree::searchNode(Node* root, int key)
{
    if (root == nullptr)
        return nullptr;

    if (key == root->m_key)
        return root;

    if (key < root->m_key)
        return searchNode(root->m_left, key);
    else
        return searchNode(root->m_right, key);

}

SearchTree::Node* SearchTree::searchNode(int key)
{
    return searchNode(m_root, key);
}

SearchTree::Node* SearchTree::searchParent(Node* root)
{
    if (root == nullptr || m_root == root)
        return nullptr;

    std::vector<Node*> currLevel;
    currLevel.push_back(m_root);

    while (currLevel.size())
    {

        std::vector<Node*> nextLevel;
        nextLevel.reserve(currLevel.size() * 2);

        for (Node* node : currLevel)
        {
            if (node->m_left)
            {
                if (node->m_left == root)
                {
                    return node;
                }
                nextLevel.push_back(node->m_left);

            }

            if (node->m_right)
            {
                if (node->m_right == root)
                {
                    return node;
                }

                nextLevel.push_back(node->m_right);

            }
        }
        currLevel.swap(nextLevel);
    }
    return nullptr;
}

bool SearchTree::deleteNode(const int key)
{
    return deleteNode(m_root, key);
}

bool SearchTree::deleteNode(Node* root)
{
    deleteNode(root, root->m_key);
}

bool SearchTree::deleteNode(Node* root, const int key)
{
    Node* removeNode = searchNode(root, key);
    if (root == nullptr || removeNode == nullptr){
        return false;
    }


    Node* nodeParent = searchParent(removeNode);

    if (removeNode->m_left == nullptr and removeNode->m_right == nullptr)
    {
        if (nodeParent){
            if (nodeParent->m_left == removeNode){
                nodeParent->m_left = nullptr;
            }
            else{
                nodeParent->m_right = nullptr;
            }
        }
        else{
            m_root = nullptr;
        }
        delete removeNode;
        return true;
    }

    if (removeNode->m_left != nullptr and removeNode->m_right == nullptr)
    {
        Node* replacementNode = removeNode->m_left;
        if (nodeParent){
            if (nodeParent->m_left == removeNode){
                 nodeParent->m_left = replacementNode;
            }
            else{
                 nodeParent->m_right = replacementNode;
            }
        }
        else{
            m_root = m_root->m_left;
        }
        delete removeNode;
        return true;
    }

    if (removeNode->m_left == nullptr and removeNode->m_right != nullptr)
    {
        Node* replacementNode = removeNode->m_right;
        if (nodeParent){
            if (nodeParent->m_left == removeNode){
                 nodeParent->m_left = replacementNode;
            }
            else{
                 nodeParent->m_right = replacementNode;
            }
        }
        else{
            m_root = m_root->m_right;
        }
        delete removeNode;
        return true;
    }

    if (removeNode->m_left != nullptr and removeNode->m_right != nullptr)
    {
        Node* replacementNode = maxNode(removeNode->m_left);
        Node* replacementNodeParent = searchParent(replacementNode);
        if (nodeParent){
            if (nodeParent->m_left == removeNode){
                 nodeParent->m_left = replacementNode;
            }
            else{
                 nodeParent->m_right = replacementNode;
            }
        }
        else{
            m_root = replacementNode;
        }

        if (replacementNode == removeNode->m_left)
            replacementNode->m_right = removeNode->m_right;
        else
        {
            replacementNodeParent->m_right = replacementNode->m_left;
            replacementNode->m_left = removeNode->m_left;
            replacementNode->m_right = removeNode->m_right;
        }
        delete removeNode;
        return true;
    }
}

