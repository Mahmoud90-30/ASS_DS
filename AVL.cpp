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

class BST{
public:
    Node *root;
    BST(){root=NULL;}
    Node* insert(Node *node,Book item){
        if(node==NULL) return new Node(item);
        if(item.id<node->data.id) node->left=insert(node->left,item);
        else node->right=insert(node->right,item);
        return node;
    }
    void insert(Book item){
        root=insert(root,item);
    }
    Node *findmin(Node *node){
        while(node->left!=NULL){
            node=node->left;
        }
        return node;
    }
    Node *Delete(Node *node,Book item){
        if(node==NULL) return NULL;
        if(item.id<node->data.id) node->left=Delete(node->left,item);
        else if(item.id>node->data.id) node->right=Delete(node->right,item);
        else{
            if(node->left==NULL && node->right==NULL){ //leaf
                delete node;
                return NULL;
            }
            else if(node->right==NULL){ //child on left
                Node *temp=node->left;
                delete node;
                return temp;
            }
            else if(node->left==NULL){ //child on right
                Node *temp=node->right;
                node->data=temp->data;
                delete node;
                return temp;
            }
            else{
                Node *temp=findmin(node->right);
                node->data=temp->data;
                node->right=Delete(node->right,temp->data.id);
            }
        }
        return node;
    }
    Node* search(Node *node,int item){
        if(node==NULL) return NULL;
        if(item<node->data.id) return search(node->left,item);
        else if(item>node->data.id) return search(node->right,item);
        return node;
    }
    bool search(int item){
        Node *result=search(root,item);
        if(result==NULL){
            cout<<"Book Not Found\n";
            return false;
        }
        else{
            cout<<"Book found And ID:"<<result->data.id<<
            " Title: "<<result->data.title
            <<" Author: "<<result->data.author<<endl;
            return true;
        }
    }
    void inorder(Node *node){
        if(node!=NULL){
            inorder(node->left);
            cout<<"Id: "<<node->data.id<<"\tTitle: "<<
            node->data.title<<"\tAuthor: "<<node->data.author<<endl;
            inorder(node->right);
        }
    }
};

class AVL {
public:
    Node* root;

    AVL() { root = NULL; }

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
        if (balance > 1 && book.id > root->left->data.id){
            root->left = leftRotation(root->left);
            return rightRotation(root);
        }

        // right left
        if (balance < -1 && book.id < root->right->data.id){
            root->right = rightRotation(root->right);
            return leftRotation(root);
        }

        return root;
    }

    void insert(Book book) {
        root = insert(root, book);
    }

    Node* findmin(Node *root){
        while(root->left!=NULL){
            root=root->left;
        }
        return root;
    }

    Node* Delete(Node* root,Book book){
        if(root==NULL) return NULL;
        if(book.id<root->data.id) root->left=Delete(root->left,book);
        else if(book.id>root->data.id) root->right=Delete(root->right,book);
        else{
            if(root->left==NULL && root->right==NULL){ //leaf
                delete root;
                return NULL;
            }
            else if(root->right==NULL){ //child on left
                Node *temp=root->left;
                delete root;
                return temp;
            }
            else if(root->left==NULL){ //child on right
                Node *temp=root->right;
                root->data=temp->data;
                delete root;
                return temp;
            }
            else{
                Node *temp=findmin(root->right);
                root->data=temp->data;
                root->right=Delete(root->right,temp->data.id);
            }
        }
        root->height = 1 + max(getHeight(root->left), getHeight(root->right));
        int balance = getBalance(root);
        //left left
        if(balance>1 && getBalance(root->left)>=0)
            return rightRotation(root);
        //right right
        if(balance<-1 && getBalance(root->right)<=0)
            return leftRotation(root);
        //left right
        if(balance>1 && getBalance(root->right)==-1){
            root->left=leftRotation(root->left);
            return rightRotation(root);
        }
        //right left
        if(balance < -1 && getBalance(root->right)==1){
            root->right=rightRotation(root->right);
            return leftRotation(root);
        }

        return root;
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
        cout<<"----------------------------\n";
        inorder(root->right);
    }

    //==========================================================================
    //Functional Fuotures 
    //==========================================================================

    void printInRange(Node* root, int minID, int maxID) 
    {

        if (root == NULL) return ;

        if (root->data.id > minID)
            printInRange(root->left, minID, maxID);

        if (root->data.id >= minID && root->data.id <= maxID) {

            cout << "Book Id: " << root->data.id << endl;
            cout << "Book Title: " << root->data.title << endl;
            cout << "Book Author: " << root->data.author << endl;
            cout << "-------------------\n";
        }

       
        if (root->data.id < maxID)
            printInRange(root->right, minID, maxID);
    }

    void printInRange(int minID, int maxID) 
    {

    printInRange(root, minID, maxID);

    }

    //closest ID to target

    int closestID(Node* root, int target) 
    {
        if(root == NULL) return ;

    int closest = root->data.id;

    while (root != NULL) {

       
        if (abs(root->data.id - target) < abs(closest - target)) {
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

    void closestID(int target) {
        int result = closestID(root, target);
        cout << "Closest ID to " << target << " is: " << result << endl;
    }


};

int main(){
    Book b1(10, "C++ Basics", "Menna"),b2(20, "Data Structures", "Nada"),b3(5, "Algorithms", "Mahmoud"),
    b4(15, "OOP", "Mina"),b5(4,"CS" , "Seif"),b6(3,"CS" , "Mai");
    AVL tree;
    //BST tree;
    tree.insert(b1);
    tree.insert(b2);
    tree.insert(b3);
    tree.insert(b4);
    tree.insert(b5);
    tree.insert(b6);
    cout << "===== Inorder Traversal (Sorted Books) =====\n";
    //tree.inorder(tree.root);
    
    cout << "\n===== Search for Data Structures =====\n";
    tree.search(15);
    
    cout<<"\n===== Inorder Traversal (Sorted Books) After Delete =====\n";
    tree.root=tree.Delete(tree.root,b5);
    tree.inorder(tree.root);
    
    cout << "===== Books with IDs between 4 and 15 =====\n";
    tree.printInRange(4, 15);

    cout << "===== Closest ID to 12 =====\n";
    tree.closestID(12);
}
