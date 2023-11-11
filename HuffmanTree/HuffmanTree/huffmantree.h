#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H



#include<string>
#include<list>

class Node
{
public:
    Node():
        m_frequency(0),
        m_left(nullptr),
        m_right(nullptr),
        m_symbols("")
    {}
    Node(std::string symbols)
    {
        m_symbols = symbols;
    }
    Node(Node* left, Node* right)
    {
        m_symbols = left->m_symbols + right->m_symbols;
        m_frequency = left->m_frequency + right->m_frequency;
        m_left = left;
        m_right = right;
    }
    ~Node() = default;
    int frequency() const
    {
        return m_frequency;
    }
    Node* left()
    {
        return m_left;
    }
    Node* right()
    {
        return m_right;
    }
    std::string symbols()
    {
        return m_symbols;
    }
    void setFrequency(const int frequency)
    {
        m_frequency = frequency;
    }


private:
    Node* m_left = nullptr;
    Node* m_right = nullptr;
    int m_frequency = 0;
    std::string m_symbols;
};

class HuffmanTree:public Node
{
public:
    HuffmanTree() = default;
    ~HuffmanTree() = default;
    void build(const std::string text);
    double encode(std::string text, std::string& encodedText);
    bool decode(const std::string encodedText, std::string& decodedText);
    void clear(Node* root);
    void clear();
    int heightTree(Node* root) const;
    void Table(const std::string& text, int* Tab);
    void createAndSortList(const std::string& text, std::list<Node*>& nodes);
    bool isLeaf(Node* root);
    Node* root();

private:
    Node* m_root = nullptr;


};

#endif // HUFFMANTREE_H
