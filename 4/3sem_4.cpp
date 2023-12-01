#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

vector<vector<string>> matrix;
struct Node {
    string data;
    Node* left;
    Node* right;

    Node(const string& value) : data(value), left(nullptr), right(nullptr) {}
};
class BinaryTree {
public:
    int x;
    BinaryTree() : root(nullptr) {
        matrix = vector < vector<string >>(10, vector<string>(10, "0"));
        insert("Есть шерсть?");
        insert("медведь");
        insert("свинья");
    }
    void insert(const string& value) {
        root = insertRecursive(root, value);
    }
    void replace(const string& incorectAnswer, const string& corectAnswer, const string& question) {
        replaceRecursive(root, incorectAnswer, corectAnswer, question);
    }
    void print() {
        x = 0;
        matrix = vector < vector<string >>(10, vector<string>(10, "0"));
        fillMartix(root, 0);
        printMatrix();
    }
    void chose() {
        Node* cur = root;
        string value;
        cout << "p-print tree\ts-stop program\ty-yes\tn-no" << endl;
        do {
            cout << cur->data<<" (y/n)" << endl;;//question
            cin >> value;
            if (value == "p") print();
            else if (value == "y") cur = cur->left;
            else if ((value == "n")) cur = cur->right;
            else continue;
            if (cur->left == nullptr) {
                cout << "Это животное " << cur->data << "? (y/n)" << endl;
                cin >> value;
                if (value == "y")  cur = root;
                else {
                    string correctAnswer, question;
                    cout << "Кто это?" << endl; cin >> correctAnswer;
                    cout << "Чем характеризуется?" << endl; cin >> question;
                    cout << "Данные исправлены" << endl;
                    question += '?';
                    replace(cur->data, correctAnswer, question);
                    print();
                    cur = root;
                }
            }
        } while (value != "s");
    }
private:
    Node* root;
    void fillMartix(Node* node, int y) 
    {
        if (node != NULL)
        {
            fillMartix(node->left, y + 1);
            matrix[y][x] = node->data;
            x++;
            fillMartix(node->right, y + 1);
        }
    }
    void printMatrix()
    {
        for (auto i : matrix) {
            for (int j=0; j < i.size(); j++) {
                if (i[j] != "0") {
                    cout << i[j];
                }
                for (int k = 0; k < 10; k++)cout << ' ';
            }
            cout << endl<<endl;
        }
    }
    void replaceRecursive(Node* node, const string& incorectAnswer, const string& corectAnswer, const string& question)
    {
        if (node != NULL)
        {
            if (node->data == incorectAnswer) {
                node->right = new Node(incorectAnswer);
                node->left = new Node(corectAnswer);
                node->data = question;
                return;
            }
            replaceRecursive(node->left, incorectAnswer, corectAnswer, question);
            replaceRecursive(node->right, incorectAnswer, corectAnswer, question);
        }
    }

    Node* insertRecursive(Node* node, const string& value) {
        if (node == nullptr) {
            return new Node(value);
        }
        if (node->left != nullptr && node->right== nullptr) {
            node->right = insertRecursive(node->right, value);
        }
        else {
            node->left = insertRecursive(node->left, value);
        }
        return node;
    }
};

int main() {

    system("chcp 1251");
    cout << endl;
    BinaryTree tree;
    tree.chose();
    return 0;
}
