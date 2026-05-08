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

// ==========================================================
// BST CLASS
// ==========================================================

class BST{
public:

    Node *root;

    BST(){
        root = NULL;
    }

    // ==========================================================
    // Insert Book In BST
    // ==========================================================

    Node* insert(Node *node, Book item){

        if(node == NULL)
            return new Node(item);

        if(item.id < node->data.id)
            node->left = insert(node->left, item);

        else
            node->right = insert(node->right, item);

        return node;
    }

    void insert(Book item){
        root = insert(root, item);
    }

    // ==========================================================
    // Find Minimum Node
    // ==========================================================

    Node *findmin(Node *node){

        while(node->left != NULL){
            node = node->left;
        }

        return node;
    }

    // ==========================================================
    // Delete Book From BST
    // ==========================================================

    Node *Delete(Node *node, Book item){

        if(node == NULL)
            return NULL;

        if(item.id < node->data.id)
            node->left = Delete(node->left, item);

        else if(item.id > node->data.id)
            node->right = Delete(node->right, item);

        else{

            // Leaf Node
            if(node->left == NULL && node->right == NULL){

                delete node;
                return NULL;
            }

            // Left Child Only
            else if(node->right == NULL){

                Node *temp = node->left;

                delete node;
                return temp;
            }

            // Right Child Only
            else if(node->left == NULL){

                Node *temp = node->right;

                delete node;
                return temp;
            }

            // Two Children
            else{

                Node *temp = findmin(node->right);

                node->data = temp->data;

                node->right = Delete(node->right, temp->data);
            }
        }

        return node;
    }

    // ==========================================================
    // Search In BST
    // ==========================================================

    Node* search(Node *node, int item){

        if(node == NULL)
            return NULL;

        if(item < node->data.id)
            return search(node->left, item);

        else if(item > node->data.id)
            return search(node->right, item);

        return node;
    }

    bool search(int item){

        Node *result = search(root, item);

        if(result == NULL){

            cout << "Book Not Found\n";
            return false;
        }

        else{

            cout << "Book Found\n";
            cout << "ID: " << result->data.id << endl;
            cout << "Title: " << result->data.title << endl;
            cout << "Author: " << result->data.author << endl;

            return true;
        }
    }

    // ==========================================================
    // Inorder Traversal
    // ==========================================================

    void inorder(Node *node){

        if(node != NULL){

            inorder(node->left);

            cout << "ID: " << node->data.id
                 << "\tTitle: " << node->data.title
                 << "\tAuthor: " << node->data.author
                 << endl;

            inorder(node->right);
        }
    }

    // ==========================================================
    // Calculate Height Of BST
    // ==========================================================

    int getHeight(Node* root){

        if(root == NULL)
            return 0;

        return 1 + max(
            getHeight(root->left),
            getHeight(root->right)
        );
    }

    // ==========================================================
    // Count Search Steps In BST
    // ==========================================================

    int searchSteps(Node* root, int id){

        int steps = 0;

        while(root != NULL){

            steps++;

            if(id == root->data.id)
                return steps;

            else if(id < root->data.id)
                root = root->left;

            else
                root = root->right;
        }

        return steps;
    }
};

// ==========================================================
// AVL CLASS
// ==========================================================

class AVL {
public:

    Node* root;

    AVL() {
        root = NULL;
    }

    // ==========================================================
    // Get Height
    // ==========================================================

    int getHeight(Node* root) {

        if (root == NULL)
            return 0;

        return root->height;
    }

    // ==========================================================
    // Get Balance Factor
    // ==========================================================

    int getBalance(Node* root) {

        if (root == NULL)
            return 0;

        return getHeight(root->left) - getHeight(root->right);
    }

    // ==========================================================
    // Left Rotation
    // ==========================================================

    Node* leftRotation(Node* root) {

        Node* temp = root->right;
        Node* temp2 = temp->left;

        temp->left = root;
        root->right = temp2;

        root->height = 1 + max(getHeight(root->left), getHeight(root->right));
        temp->height = 1 + max(getHeight(temp->left), getHeight(temp->right));

        return temp;
    }

    // ==========================================================
    // Right Rotation
    // ==========================================================

    Node* rightRotation(Node* root) {

        Node* temp = root->left;
        Node* temp2 = temp->right;

        temp->right = root;
        root->left = temp2;

        root->height = 1 + max(getHeight(root->left), getHeight(root->right));
        temp->height = 1 + max(getHeight(temp->left), getHeight(temp->right));

        return temp;
    }

    // ==========================================================
    // Insert In AVL
    // ==========================================================

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

        // Left Left
        if (balance > 1 && book.id < root->left->data.id)
            return rightRotation(root);

        // Right Right
        if (balance < -1 && book.id > root->right->data.id)
            return leftRotation(root);

        // Left Right
        if (balance > 1 && book.id > root->left->data.id){

            root->left = leftRotation(root->left);
            return rightRotation(root);
        }

        // Right Left
        if (balance < -1 && book.id < root->right->data.id){

            root->right = rightRotation(root->right);
            return leftRotation(root);
        }

        return root;
    }

    void insert(Book book) {
        root = insert(root, book);
    }

    // ==========================================================
    // Find Minimum Node
    // ==========================================================

    Node* findmin(Node *root){

        while(root->left != NULL){
            root = root->left;
        }

        return root;
    }

    // ==========================================================
    // Delete From AVL
    // ==========================================================

    Node* Delete(Node* root, Book book){

        if(root == NULL)
            return NULL;

        if(book.id < root->data.id)
            root->left = Delete(root->left, book);

        else if(book.id > root->data.id)
            root->right = Delete(root->right, book);

        else{

            // Leaf
            if(root->left == NULL && root->right == NULL){

                delete root;
                return NULL;
            }

            // Left Child
            else if(root->right == NULL){

                Node *temp = root->left;

                delete root;
                return temp;
            }

            // Right Child
            else if(root->left == NULL){

                Node *temp = root->right;

                delete root;
                return temp;
            }

            // Two Children
            else{

                Node *temp = findmin(root->right);

                root->data = temp->data;

                root->right = Delete(root->right, temp->data);
            }
        }

        root->height = 1 + max(getHeight(root->left), getHeight(root->right));

        int balance = getBalance(root);

        // Left Left
        if(balance > 1 && getBalance(root->left) >= 0)
            return rightRotation(root);

        // Right Right
        if(balance < -1 && getBalance(root->right) <= 0)
            return leftRotation(root);

        // Left Right
        if(balance > 1 && getBalance(root->left) < 0){

            root->left = leftRotation(root->left);
            return rightRotation(root);
        }

        // Right Left
        if(balance < -1 && getBalance(root->right) > 0){

            root->right = rightRotation(root->right);
            return leftRotation(root);
        }

        return root;
    }

    // ==========================================================
    // Search In AVL
    // ==========================================================

    Node* search(Node* root , int id){

        if(root == NULL)
            return NULL;

        else if(id == root->data.id)
            return root;

        else if(id < root->data.id)
            return search(root->left , id);

        else
            return search(root->right ,id);
    }

    void search(int id){

        Node* result = search(root , id);

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

    // ==========================================================
    // Inorder Traversal
    // ==========================================================

    void inorder(Node* root){

        if(root == NULL)
            return ;

        inorder(root->left);

        cout << "Book Id: " << root->data.id << endl;
        cout << "Book Title: " << root->data.title << endl;
        cout << "Book Author: " << root->data.author << endl;
        cout << "----------------------------\n";

        inorder(root->right);
    }

    // ==========================================================
    // Count Search Steps In AVL
    // ==========================================================

    int searchSteps(Node* root, int id){

        int steps = 0;

        while(root != NULL){

            steps++;

            if(id == root->data.id)
                return steps;

            else if(id < root->data.id)
                root = root->left;

            else
                root = root->right;
        }

        return steps;
    }

    // ==========================================================
    // Print Books In Range
    // ==========================================================

    void printInRange(Node* root, int minID, int maxID){

        if (root == NULL)
            return ;

        if (root->data.id > minID)
            printInRange(root->left, minID, maxID);

        if (root->data.id >= minID && root->data.id <= maxID){

            cout << "Book Id: " << root->data.id << endl;
            cout << "Book Title: " << root->data.title << endl;
            cout << "Book Author: " << root->data.author << endl;
            cout << "-------------------\n";
        }

        if (root->data.id < maxID)
            printInRange(root->right, minID, maxID);
    }

    void printInRange(int minID, int maxID){

        printInRange(root, minID, maxID);
    }

    // ==========================================================
    // Find Closest ID
    // ==========================================================

    int closestID(Node* root, int target){

        if(root == NULL)
            return -1;

        int closest = root->data.id;

        while (root != NULL){

            if (abs(root->data.id - target) < abs(closest - target)){
                closest = root->data.id;
            }

            if (target < root->data.id)
                root = root->left;

            else if (target > root->data.id)
                root = root->right;

            else
                return root->data.id;
        }

        return closest;
    }

    void closestID(int target){

        int result = closestID(root, target);

        cout << "Closest ID to "
             << target
             << " is: "
             << result
             << endl;
    }
};

    // ==========================================================
    // MAIN FUNCTION
    // ==========================================================

int main(){

    AVL avl;
    BST bst;

    // ==========================================================
    // Random IDs Books
    // ==========================================================

    Book b1(10, "C++ Basics", "Menna");
    Book b2(20, "Data Structures", "Nada");
    Book b3(5, "Algorithms", "Mahmoud");
    Book b4(15, "OOP", "Mina");
    Book b5(4, "CS", "Seif");
    Book b6(3, "Networks", "Mai");

    // Extra Books
    Book b7(25, "Database", "Ali");
    Book b8(30, "AI", "Omar");
    Book b9(12, "Math", "Sara");
    Book b10(18, "Physics", "Ahmed");
    Book b11(7, "Biology", "Nour");
    Book b12(50, "Machine Learning", "Youssef");
    Book b13(45, "Operating Systems", "Mona");
    Book b14(60, "Cyber Security", "Karim");
    Book b15(1, "Web Development", "Hana");
    Book b16(8, "Discrete Math", "Adham");
    Book b17(90, "Cloud Computing", "Laila");
    Book b18(55, "Computer Vision", "Khaled");
    Book b19(13, "Software Engineering", "Salma");
    Book b20(33, "Compiler Design", "Mostafa");

    // ==========================================================
    // Insert In AVL
    // ==========================================================

    avl.insert(b1);
    avl.insert(b2);
    avl.insert(b3);
    avl.insert(b4);
    avl.insert(b5);
    avl.insert(b6);
    avl.insert(b7);
    avl.insert(b8);
    avl.insert(b9);
    avl.insert(b10);
    avl.insert(b11);
    avl.insert(b12);
    avl.insert(b13);
    avl.insert(b14);
    avl.insert(b15);
    avl.insert(b16);
    avl.insert(b17);
    avl.insert(b18);
    avl.insert(b19);
    avl.insert(b20);

    // ==========================================================
    // Insert In BST
    // ==========================================================

    bst.insert(b1);
    bst.insert(b2);
    bst.insert(b3);
    bst.insert(b4);
    bst.insert(b5);
    bst.insert(b6);
    bst.insert(b7);
    bst.insert(b8);
    bst.insert(b9);
    bst.insert(b10);
    bst.insert(b11);
    bst.insert(b12);
    bst.insert(b13);
    bst.insert(b14);
    bst.insert(b15);
    bst.insert(b16);
    bst.insert(b17);
    bst.insert(b18);
    bst.insert(b19);
    bst.insert(b20);

    // ==========================================================
    // AVL Traversal
    // ==========================================================

    cout << "===== AVL Inorder Traversal =====\n";
    avl.inorder(avl.root);

    // ==========================================================
    // Search
    // ==========================================================

    cout << "\n===== Search =====\n";
    avl.search(15);

    // ==========================================================
    // Delete
    // ==========================================================

    cout << "\n===== Delete Book =====\n";

    avl.root = avl.Delete(avl.root, b5);

    avl.inorder(avl.root);

    // ==========================================================
    // Print Books In Range
    // ==========================================================

    cout << "\n===== Books In Range =====\n";

    avl.printInRange(4, 30);

    // ==========================================================
    // Closest ID
    // ==========================================================

    cout << "\n===== Closest ID =====\n";

    avl.closestID(14);

    // ==========================================================
    // Random IDs Comparison
    // ==========================================================

    cout << "\n===== Random IDs Comparison =====\n";

    cout << "BST Height: "
         << bst.getHeight(bst.root)
         << endl;

    cout << "AVL Height: "
         << avl.getHeight(avl.root)
         << endl;

    cout << "BST Search Steps: "
         << bst.searchSteps(bst.root, 50)
         << endl;

    cout << "AVL Search Steps: "
         << avl.searchSteps(avl.root, 50)
         << endl;

    // ==========================================================
    // Sorted IDs Test
    // ==========================================================

    BST bst2;
    AVL avl2;

    bst2.insert(Book(10,"A","A"));
    bst2.insert(Book(20,"B","B"));
    bst2.insert(Book(30,"C","C"));
    bst2.insert(Book(40,"D","D"));
    bst2.insert(Book(50,"E","E"));

    avl2.insert(Book(10,"A","A"));
    avl2.insert(Book(20,"B","B"));
    avl2.insert(Book(30,"C","C"));
    avl2.insert(Book(40,"D","D"));
    avl2.insert(Book(50,"E","E"));

    cout << "\n===== Sorted IDs Comparison =====\n";

    cout << "BST Height: "
         << bst2.getHeight(bst2.root)
         << endl;

    cout << "AVL Height: "
         << avl2.getHeight(avl2.root)
         << endl;

    cout << "BST Search Steps: "
         << bst2.searchSteps(bst2.root, 50)
         << endl;

    cout << "AVL Search Steps: "
         << avl2.searchSteps(avl2.root, 50)
         << endl;

    return 0;
}
