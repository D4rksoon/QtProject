#include "HashTable.h"
#include<vector>
#include<iostream>
#include <math.h>

HashTable::HashTable(int size) :
    m_size(size + 1),
    Nodes(m_size, nullptr)
{}

HashTable::~HashTable()
{
    for (Node* node : Nodes) {
        delete node;
    }

}

std::vector<HashTable::Node*> HashTable::getNodes()
{
    return Nodes;
}

void HashTable::resize(int size)
{
    if(size > m_size)
    {
        Nodes.resize(size);
        for (int i = m_size; i < size; i++)
            Nodes[i] = nullptr;
        m_size = size;
    }
    else
        if(size < m_size)
        {
            for (int i = size; i < m_size; i++)
                delete Nodes[i];

            Nodes.resize(size);
            m_size = size;
        }
}

void HashTable::clearTable()
{
    for (int i = 0; i < m_size; i++) {
        delete Nodes[i];
        Nodes[i] = nullptr;
    }
}

int HashTable::hashCode(int key)
{
    const double a = -(1 - sqrt(5)) / 2; // const a = 0.618034
    int N = m_size; // Table size
    int hashCode = int((key % N) * a * N) % N;
    //int hashCode2 = fmod(fmod(key, N) * a * N, N);
    return hashCode;
}

bool HashTable::insert(int key, std::string value)
{
    int index = hashCode(key);
    Node* newNode = new Node(key, value);
    if (Nodes[index] == NULL) {
        Nodes[index] = newNode;
        return true;
    }
    else {
        Node* tmp = Nodes[index];
        for (int i = 0; i < m_size; i++) {
            if (Nodes[i] == NULL) {
                Nodes[i] = newNode;
                while (tmp->next) {
                    tmp = tmp->next;
                }
                tmp->next = newNode;
                return true;
            }
        }
        return false;
        std::cerr << "Error: Table is full\n";
    }
}

void HashTable::remove(int key)
{
    int index = hashCode(key);
    Node* tmp = Nodes[index];
    if (tmp == nullptr) {
        return;
    }
    // No collision
    if (tmp->next == nullptr and tmp->key() == key) {
        Nodes[index] = nullptr;
        delete tmp;
        return;
    }
    // If does collision
    else if (tmp->next != nullptr){

        if (tmp->key() == key) {
            tmp = nullptr;
            delete tmp;
            return;
        }

        else {
            Node* prev = tmp;
            Node* curr = tmp->next;
            while (curr != nullptr) {
                if (curr->key() == key) {
                    prev->next = curr->next;
                    delete curr;
                    return;
                }
                else {
                    prev = curr;
                    curr = curr->next;
                }
            }
        }
    }
}

bool HashTable::searchKey(int key)
{
    int index = hashCode(key);
    Node* tmp = Nodes[index];
    while (tmp) {
        if (tmp->key() == key) {
            return true;
        }
        tmp = tmp->next;
    }
    return false;
}

