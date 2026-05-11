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
    // Books Array (20 Books)
    // ==========================================================

    Book books[20] = {

        {10, "C++ Basics", "Menna"},
        {20, "Data Structures", "Nada"},
        {5, "Algorithms", "Mahmoud"},
        {15, "OOP", "Mina"},
        {4, "CS", "Seif"},
        {3, "Networks", "Mai"},
        {25, "Database", "Ali"},
        {30, "AI", "Omar"},
        {12, "Math", "Sara"},
        {18, "Physics", "Ahmed"},
        {7, "Biology", "Nour"},
        {50, "Machine Learning", "Youssef"},
        {45, "Operating Systems", "Mona"},
        {60, "Cyber Security", "Karim"},
        {1, "Web Development", "Hana"},
        {8, "Discrete Math", "Adham"},
        {90, "Cloud Computing", "Laila"},
        {55, "Computer Vision", "Khaled"},
        {13, "Software Engineering", "Salma"},
        {33, "Compiler Design", "Mostafa"}
    };

    // ==========================================================
    // Insert Books In AVL And BST Using Loop
    // ==========================================================

    for(int i = 0; i < 20; i++){

        avl.insert(books[i]);

        bst.insert(books[i]);
    }

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

    // // ==========================================================
    // // Delete
    // // ==========================================================

    // cout << "\n===== Delete Book =====\n";

    // avl.root = avl.Delete(avl.root, books[4]);

    // avl.inorder(avl.root);

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

    cout << "BST Height: "<< bst.getHeight(bst.root)<< endl;
    cout << "AVL Height: "<< avl.getHeight(avl.root)<< endl;

    cout << "BST Search Steps: "<< bst.searchSteps(bst.root, 50)<< endl;
    cout << "AVL Search Steps: "<< avl.searchSteps(avl.root, 50)<< endl;

    // ==========================================================
    // Sorted IDs Test
    // ==========================================================

    BST bst2;
    AVL avl2;

Book sortedBooks[20] = {

    {10, "A", "A"},
    {20, "B", "B"},
    {30, "C", "C"},
    {40, "D", "D"},
    {50, "E", "E"},
    {60, "F", "F"},
    {70, "G", "G"},
    {80, "H", "H"},
    {90, "I", "I"},
    {100, "J", "J"},
    {110, "K", "K"},
    {120, "L", "L"},
    {130, "M", "M"},
    {140, "N", "N"},
    {150, "O", "O"},
    {160, "P", "P"},
    {170, "Q", "Q"},
    {180, "R", "R"},
    {190, "S", "S"},
    {200, "T", "T"}
};

for(int i = 0; i < 20; i++) {

    bst2.insert(sortedBooks[i]);
    avl2.insert(sortedBooks[i]);
}

    // ==========================================================
    // Sorted IDs Comparison
    // ==========================================================

    cout << "\n===== Sorted IDs Comparison =====\n";

    cout << "BST Height: "<< bst2.getHeight(bst2.root)<< endl;
    cout << "AVL Height: "<< avl2.getHeight(avl2.root)<< endl;
    cout << "BST Search Steps: "<< bst2.searchSteps(bst2.root, 50)<< endl;
    cout << "AVL Search Steps: "<< avl2.searchSteps(avl2.root, 50)<< endl;

    return 0;
}
