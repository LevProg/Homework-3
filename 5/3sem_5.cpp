#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> matrix;
struct Node {
    int key;
    int nodesCount;
    Node* left;
    Node* right;

    Node(int k) : key(k), nodesCount(0), left(nullptr), right(nullptr) {}
};

class BinaryTree {
public:
    int x;
    BinaryTree() : root(nullptr) {}
    void insert(vector<int> keys) {
        for(auto key: keys) root = insertRecursive(root, key);
    }
    void remove(int key) {
        root = removeRecursive(root, key);
    }
    void print() {
        x = 0;
        matrix = vector < vector<int >>(10, vector<int>(10, 0));
        fillMartix(root, 0);
        printMatrix();
    }
private:
    Node* root;

    Node* insertRecursive(Node* node, int value) {
        if (node == nullptr) {
            return new Node(value);
        }
        if (value < node->key) {
            node->left = insertRecursive(node->left, value);
        }
        else {
            node->right = insertRecursive(node->right, value);
        }
        node->nodesCount = 1 + getNodeCount(node->left) + getNodeCount(node->right);
        return node;
    }

    Node* removeRecursive(Node* node, int value) {
        if (node == nullptr) {
            return nullptr;
        }
        if (value < node->key) {
            node->left = removeRecursive(node->left, value);
        }
        else if (value > node->key) {
            node->right = removeRecursive(node->right, value);
        }
        else {
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            Node* temp = findMin(node->right);
            node->key = temp->key;
            node->right = removeRecursive(node->right, temp->key);
        }
        node->nodesCount = 1 + getNodeCount(node->left) + getNodeCount(node->right);
        return node;
    }

    Node* findMin(Node* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    int getNodeCount(Node* node) const {
        return (node != nullptr) ? node->nodesCount : 0;
    }
    void fillMartix(Node* node, int y)
    {
        if (node != NULL)
        {
            fillMartix(node->left, y + 1);
            matrix[y][x] = node->key;
            x++;
            fillMartix(node->right, y + 1);
        }
    }
    void printMatrix()
    {
        for (auto i : matrix) {
            for (int j = 0; j < i.size(); j++) {
                if (i[j] != 0) {
                    cout << i[j];
                }
                for (int k = 0; k < matrix.size(); k++)cout << ' ';
            }
            cout << endl << endl;
        }
    }
};

int main() {
    system("chcp 1251");
    BinaryTree tree;
    vector<int> keys{ 5, 4, 8, 1, 71, 9 };
    tree.insert(keys);
    cout << "Дерево после вставки: 5, 4, 8, 1, 71, 9\n";
    tree.print();
    tree.remove(9);
    cout << "Дерево после удаления узла со значением 9\n";
    tree.print();
    tree.remove(71);
    cout << "Дерево после удаления узла со значением 71\n";
    tree.print();
    return 0;
}
