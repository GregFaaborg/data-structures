/*
Greg Faaborg
avl.cpp
Implementation of an avl tree, which is a bst that does not allow subtrees heights to differe by more than 1.
If they do you have to rotate the tree to follow this balancing factor
*/
#include <stdio.h>
#include <iostream>
#include "avl.hpp"
using namespace std;

#define IS_ROOT 0
#define IS_LEFT 1
#define IS_RIGHT 2

//returns the maximum height of two nodes
int max_height(int height1, int height2)
{
    if(height1 > height2)
        return height1;
    else
        return height2;
}


//return the height of the current node
int height(AvlNode *node)
{
    if(node == nullptr)
        return -1;
    else 
        return node->height;
}

//single rotate left 
void srl(AvlNode *&node)
{
    //set temp to be the left child of the inserted node
    AvlNode *temp = node->left;
    //set the current nodes left child to be temps right child
    node->left = temp->right;
    //temps right is now the current node
    temp->right = node;
    //adjust heights for each node
    node->height = 1 + max_height(height(node->left),height(node->right));
    temp->height = 1 + max_height(height(temp->left), node->height);
    //setting the node to have the temps node data
    node = temp;
}

//single rotate right
void srr(AvlNode *&node)
{
    //set temp to be the right child of the inserted node
    AvlNode *temp = node->right;
    //set the nodes right child to be temps left child
    node->right = temp->left;
    //temps left is now the current node
    temp->left = node;
    //adjusting heights of the nodes
    node->height = 1 + max_height(height(node->right),height(node->left));
    temp->height = 1 + max_height(height(temp->right),node->height);
    //setting the node to be have the temps node data 
    node = temp;
}

//returns the smallest node for the remove function
int min(AvlNode *&node)
{
    AvlNode *temp = node;

    while(temp->left != nullptr)
        temp = temp->left;
    return temp->element;
}


//function that balances the tree
void balance(AvlNode *&node)
{
    //empty tree
    if(node == nullptr)
        return;
    //tree is unbalanced on left side 
    if(height(node->left) - height(node->right) > 1)
    {
        //left left height is larger than or equal to the 
        if(height(node->left->left) >= height(node->left->right))
        {
            //single rotate w/ left child
            srl(node);
        }
        //left right height is larger
        else
        {   
            //rotate right w/ left child
            srr(node->left);
            //then rotate left with current node
            srl(node);
        }
    }
    //tree is unbalanced on the right side
    else if(height(node->right) - height(node->left) > 1)
    { 
        if(height(node->right->right) >= height(node->right->left))
        { 
            //single rotate w/ right child
            srr(node);
        }
        else
        {
            //rotate left w/ right child 
            srl(node->right);
            //then rotate right at current node
            srr(node);
        }
    }
    //set new height for node
    node->height = 1 + max_height(height(node->left), height(node->right));
}



/**
 * Internal method to insert into a subtree.
 * info is the item to insert.
 * root is the node that roots the subtree.
 * Set the new root of the subtree.
 */
void insert( const int &info, AvlNode *&root )
{
    if (root == nullptr)
    {
        root = new AvlNode (info, nullptr, nullptr);
    }
    //insert into left subtree if info is smaller than the current node
    else if (info < root->element)
    {
        insert( info, root->left );
    }  
    //insert into the right subtree if the info is larger than the current node
    else if(info > root->element)
    {
        insert( info, root->right );       
    }
    //do nothing because it is a duplicate
    else 
    ;

    //balancing tree
    balance(root);
}

/**
 * Internal method to remove from a subtree.
 * info is the item to remove.
 * root is the node that roots the subtree.
 * Set the new root of the subtree.
 */
void remove( const int &info, AvlNode *&root) 
{
    if(root == nullptr)
        return;
    //if the node to be removed is smaller than the current node traverse the left subtree
    if(info < root->element)
        remove(info,root->left);
    //else the node is larger traverse the 
    else if(info > root->element)
        remove(info, root->right);
    //two children
    else if(root->left != nullptr && root->right != nullptr)
    {
        // find the smallest node in the right subtree
        root->element = min(root->right);
        remove(root->element,root->right);
    }
    //one child
    else
    {   
        
        AvlNode *temp = root;
        //left child 
        if(root->left != nullptr)
            root = root->left;
        //right child
        else
            root = root->right;
        //delete node
        delete temp;
    }
    //balance tree 
    balance(root);
}


/*
 * Print methods, do not change
 */
void print(AvlNode *root, int level, int type) {
  if (root == NULL) {
    return;
  }
  if (type == IS_ROOT) {
    std::cout << root -> element << "\n";
  } else {
    for (int i = 1; i < level; i++) {
      std::cout << "| ";
    }
    if (type == IS_LEFT) {
      std::cout << "|l_" << root -> element << "\n";
    } else {
      std::cout << "|r_" << root -> element << "\n";
    }
  }
  if (root -> left != NULL) {
    print(root -> left, level + 1, IS_LEFT);
  }
  if (root -> right != NULL) {
    print(root -> right, level + 1, IS_RIGHT);
  }
}
void print(AvlNode *root) {
  print(root, 0, IS_ROOT);
}
/*
 * END Print methods, do not change
 */


/* 
 * Main method, do not change
 */
int main(int argc, const char * argv[]) {
  AvlNode *root = NULL;
  std::string filename = argv[1];
  freopen(filename.c_str(), "r", stdin);
  std::string input;
  int data;
  while(std::cin >> input){
    if (input == "insert"){
      std::cin>>data;
      insert(data, root);
    } else if(input == "delete"){
      std::cin>>data;
      remove(data, root);
    } else if(input == "print"){
      print(root);
      std::cout << "\n";
    } else{
      std::cout<<"Data not consistent in file";
      break;
    }
  }
  return 0;
}
/*
 * END main method
 */
