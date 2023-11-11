#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include <string>
class HashTable
{
protected:
    class Node;

public:
    HashTable(int size = 0);
    std::vector<Node*> getNodes();
    ~HashTable();
    void resize(int size);
    void clearTable();
    int hashCode(int key);
    bool insert(int key, std::string value);
    void remove(int key);
    bool searchKey(int key);
private:
    int m_size;
    std::vector<Node*> Nodes;

protected:
    class Node
    {
        friend class HashTable;
    public:
        Node() = default;
        Node(int key, std::string value)
        {
            m_key = key;
            m_value = value;
            next = nullptr;
        }
        ~Node() = default;
        int key()
        {
            return m_key;
        }
        void setKey(int key)
        {
            m_key = key;
        }
        std::string value()
        {
            return m_value;
        }
        void setValue(std::string value)
        {
            m_value = value;
        }


    private:
        int m_key = 0;
        std::string m_value;
        Node* next = nullptr;

    };




};

#endif // HASHTABLE_H
