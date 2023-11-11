#include <algorithm>
#include<vector>
#include<list>
#include<algorithm>
#include "HuffmanTree.h"

int max(int a, int b){
    if(a > b)
        return a;
    else
        return b;
}

bool checkRepeatString(const std::string text, char symb) {
    for (int i = 0; i < text.length(); i++) {
        if (text[i] == symb) {
            return false;
        }
    }
    return true;
}

bool checkRepeatInt(std::vector<int> mas, int val) {
    for (int i = 0; i < mas.size(); i++) {
        if (mas[i] == val) {
            return false;
        }
    }
    return true;
}

void HuffmanTree::build(const std::string text)
{
    std::list<Node*> nodes;
    createAndSortList(text, nodes);
    while (nodes.size() > 1) {
        Node* subTreeRoot1 = nodes.front();
        nodes.pop_front();
        Node* subTreeRoot2 = nodes.front();
        nodes.pop_front();
        Node* sumNode = new Node(subTreeRoot1, subTreeRoot2);

        std::list<Node*>::iterator seeker = nodes.begin();
        while (seeker != nodes.end() && (*seeker)->frequency() <= sumNode->frequency()) {
            seeker++;
        }

        nodes.insert(seeker, sumNode);

    }
    m_root = nodes.back();

}

double HuffmanTree::encode(std::string text, std::string &encodedText)
{
    if (!m_root) {
        return -1;
    }
    double encodeSum = 0;
    for (int i = 0; i < text.size(); i++) {
        Node* tmp = m_root;
        while (!isLeaf(tmp)) {
            std::string nodeSymbols = tmp->left()->symbols();
            if (nodeSymbols.find(text[i]) <= nodeSymbols.size()) {
                tmp = tmp->left();
                encodedText += "0";
            }
            else {
                tmp = tmp->right();
                encodedText += "1";
            }
            encodeSum++;
        }
    }
    if(m_root->left() == nullptr and m_root->right() == nullptr){
        for(int i = 0; i < text.size(); i++){
            encodedText += "0";
            encodeSum += 1;
        }

    }
    double compressionRatio = text.size() * 8 / encodeSum;
    return compressionRatio;
}

bool HuffmanTree::decode(const std::string encodedText, std::string &decodedText)
{
    if (!m_root) {
        return false;
    }
    Node* tmp = m_root;
    for (int i = 0; i < encodedText.size(); i++) {
        if (encodedText[i] == '0' and tmp->left()) {
            tmp = tmp->left();
        }
        else if (encodedText[i] == '1' and tmp->right()) {
            tmp = tmp->right();
        }

        if (isLeaf(tmp)) {
            decodedText += tmp->symbols();
            tmp = m_root;
        }
    }
    return true;
}

void HuffmanTree::clear(Node* root)
{
    if (root)
    {
        clear(root->left());
        clear(root->right());
        root = nullptr;
        delete root;
    }
}

void HuffmanTree::clear()
{
    clear(m_root);
}

int HuffmanTree::heightTree(Node* root) const
{
    if (!root){
        return 0;
    }

    if (root->left() == nullptr and root->right() == nullptr ){
        return 1;
    }

    int leftHeight = 0;
    int rightHeight = 0;

    if (root->left())
        leftHeight = heightTree(root->left());

    if (root->right())
        rightHeight = heightTree(root->right());

    return max(rightHeight, leftHeight) + 1;
}

void HuffmanTree::Table(const std::string& text, int* Tab)
{
    int n = text.length();
    for (int i = 0; i < n; i++) {
        Tab[text[i]]++;
    }
}

void HuffmanTree::createAndSortList(const std::string& text, std::list<Node*>& nodes)
{
    int Tab[256] = { 0 };
    Table(text, Tab);

    std::string withoutRepeat;
    for (int i = 0; i < text.size(); i++) {
        if (checkRepeatString(withoutRepeat, text[i])) {
            withoutRepeat.push_back(text[i]);
        }
    }
    int lenString = withoutRepeat.length();

    std::vector<int> masWithoutRepeat;
    for (int i = 0; i < lenString; i++) {
        if (checkRepeatInt(masWithoutRepeat, Tab[withoutRepeat[i]])) {
            masWithoutRepeat.push_back(Tab[withoutRepeat[i]]);
        }
    }
    std::sort(masWithoutRepeat.begin(), masWithoutRepeat.end());
    int lenMas = masWithoutRepeat.size();

    for (int i = 0; i < lenMas; i++) {
        for (int j = 0; j < lenString; j++) {
            if (Tab[withoutRepeat[j]] == masWithoutRepeat[i]) {
                std::string symbl;

                Node* tmp = new Node(std::string(1, withoutRepeat[j]));
                tmp->setFrequency(masWithoutRepeat[i]);
                nodes.push_back(tmp);

            }
        }
    }
}

bool HuffmanTree::isLeaf(Node* root)
{
    if (root == nullptr) {
        return false;
    }
    if (root->left() == nullptr and root->right() == nullptr) {
        return true;
    }
    return false;
}

HuffmanTree::Node* HuffmanTree::root()
{
    return m_root;
}




