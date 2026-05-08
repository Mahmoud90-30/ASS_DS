#include <iostream>
#include <algorithm>
using namespace std;

struct Book {
    int id;
    string title;
    string author;

    Book(int i = 0, string t = "", string a = "") {
        id = i;
        title = t;
        author = a;
    }
};

class Node {
public:
    Book data;
    int height;
    Node* left;
    Node* right;

    Node(Book value) {
        data = value;
        left = right = NULL;
        height = 1;
    }
};

class AVL {
public:
    Node* root;

    AVL() {
        root = NULL;
    }

    int getHeight(Node* root) {
        if (root == NULL) return 0;
        return root->height;
    }

    int getBalance(Node* root) {
        if (root == NULL) return 0;
        return getHeight(root->left) - getHeight(root->right);
    }

    Node* leftRotation(Node* root) {
        Node* temp = root->right;
        Node* temp2 = temp->left;

        temp->left = root;
        root->right = temp2;

        root->height = 1 + max(getHeight(root->left), getHeight(root->right));
        temp->height = 1 + max(getHeight(temp->left), getHeight(temp->right));

        return temp;
    }

    Node* rightRotation(Node* root) {
        Node* temp = root->left;
        Node* temp2 = temp->right;

        temp->right = root;
        root->left = temp2;

        root->height = 1 + max(getHeight(root->left), getHeight(root->right));
        temp->height = 1 + max(getHeight(temp->left), getHeight(temp->right));

        return temp;
    }

    Node* left_rightRotation(Node* root) {
        root->left = leftRotation(root->left);
        return rightRotation(root);
    }

    Node* right_leftRotation(Node* root) {
        root->right = rightRotation(root->right);
        return leftRotation(root);
    }

    Node* insert(Node* root, Book book) {
        if (root == NULL)
            return new Node(book);

        if (book.id < root->data.id)
            root->left = insert(root->left, book);
        else if (book.id > root->data.id)
            root->right = insert(root->right, book);
        else
            return root;

        root->height = 1 + max(getHeight(root->left), getHeight(root->right));

        int balance = getBalance(root);

        // left left
        if (balance > 1 && book.id < root->left->data.id)
            return rightRotation(root);

        // right right
        if (balance < -1 && book.id > root->right->data.id)
            return leftRotation(root);

        // left right
        if (balance > 1 && book.id > root->left->data.id)
            return left_rightRotation(root);

        // right left
        if (balance < -1 && book.id < root->right->data.id)
            return right_leftRotation(root);

        return root;
    }

    void insert(Book book) {
        root = insert(root, book);
    }

    Node* search(Node* root , int id){
        if(root == NULL) return NULL;
        else if(id == root->data.id) return root;
        else if(id < root->data.id) return search(root->left , id);
        else return search(root->right ,id);
    }  

    void search(int id){
        Node* result= search(root , id);
        if(result != NULL){
            cout << "Book Found:\n";
            cout << "Book Id: " << result->data.id << endl;
            cout << "Book Title: " << result->data.title << endl;
            cout << "Book Author: " << result->data.author << endl;
        }
        else{
            cout << "Book Not Found\n";
        }

    }

    void inorder(Node* root){
        if(root == NULL) return ;

        inorder(root->left);
        cout << "Book Id: " << root->data.id << endl;
        cout << "Book Title: " << root->data.title << endl;
        cout << "Book Author: " << root->data.author << endl;
        inorder(root->right);
    }
};

int main(){
    AVL tree;

    tree.insert(Book(10, "C++ Basics", "Menna"));
    tree.insert(Book(20, "Data Structures", "Nada"));
    tree.insert(Book(5, "Algorithms", "Mahmoud"));
    tree.insert(Book(15, "OOP", "Mina"));
    tree.insert(Book(4,"CS" , "Seif"));
    tree.insert(Book(3,"CS" , "Mai"));
    cout << "===== Inorder Traversal (Sorted Books) =====\n";
    //tree.inorder(tree.root);
    tree.search(15);
}