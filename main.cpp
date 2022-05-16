/*
This is a class that emulates a Binary Search Tree
By: Kushal Rao
Last Modified: 4/22/22
*/
//Imports
#include <iostream>
#include <fstream>
#include <cstring>
#include <math.h>
#include<stdio.h>
#include<stdlib.h>

using namespace std;

struct node{//Create a node struct
  int value;
  struct node *left = NULL;
  struct node *right = NULL;
  struct node *parent = NULL;
};

//Methods
void add(node* &head);
void display(node* head, int depth);
void fadd(node* curr, node* n, int input);
void manadd(node* &head);
void remove(node* &head, int goal);
bool search(node* head, int goal, node* &goaln);

int main(){
  srand(time(0));
  bool quit = false;//bool to check when user wants to quit
  node* head = NULL;
  while(!quit){//Main while
    cout << "Type a valid command(ADD, REMOVE, MADD, SEARCH, DISPLAY, QUIT)" << endl;//Prompt user for input
    char input[10];//Get input from user
    cin >> input;
    if(strcmp(input, "MADD") == 0){//if user wants to manually add
      manadd(head);
    }
    if(strcmp(input,"ADD") == 0){//If user wants to add students
      add(head);
    }
    if(strcmp(input,"SEARCH") == 0){//If user wants to search students
      int num;
      cout << "What number do you want to look for" << endl;
      cin >> num;
      cin.clear();
      node* temp;
      bool n = search(head, num, temp);
      if(n){
	cout << "Present" << endl;
      }
      else{
	cout << "Not there" << endl;
      }
    }
    if(strcmp(input,"REMOVE") == 0){//If user wants to remove
      int num;
      cout << "What number do you want to look for" << endl;
      cin >> num;
      cin.clear();
      remove(head, num);
    }
    else if(strcmp(input, "DISPLAY")==0){//Dislay as a tree
      display(head, 0);
    }
    else if(strcmp(input,"QUIT") == 0){//If user wants to quit
      quit = true;
    }
  }
  return 0;
}

void remove(node* &head, int goal){
  node* goaln;//pointer to hold the goal node's adress
  bool n;
  if(!search(head, goal, goaln)){//Check if a node with that value exists and find the pointer for it
    cout << "Input a valid number" << endl;
    return;
  }
  node* parent = goaln->parent;
  if(goaln != head){//If the node that is to be removed is the not the root
    if(parent->left == goaln){
      n = true;
    }
    else{
      n = false;
    }//If n is ture curr is left of parent
  }
  if(goaln == head){//If there is nothing but the root remove the root
    if(goaln ->right == NULL && goaln->left == NULL){
      head = NULL;
      return;
    }
    else if(goaln->right != NULL && goaln->left != NULL){//If there is a right and left
      node * temp = goaln->right;
      while(temp->left != NULL){
	temp = temp->left;
      }
      goaln->value = temp->value;
      if(temp == goaln->right){
        goaln->right = goaln->right->right;
      }
      if(temp->parent->left == temp){
        temp->parent->left = NULL;
      }
      return;
    }
    if(head->right == NULL){//If there only is a right
      head = head->left;
    }
    else{//If there only is a left
      head = head->right;
    }
  }
  else{//If the goal node is not the root
    if(goaln->right == NULL && goaln->left == NULL){//If both are null set the parents pointer that would point to the goal node to NULL
      if(n){
	parent->left = NULL;
      }
      else{
	parent->right = NULL;
      }
      return;
    }
    else if(goaln->right != NULL && goaln->left != NULL){//If there is a both right and left
      node * temp = goaln->right;
      while(temp->left != NULL){
	temp = temp->left;
      }
      goaln->value = temp->value;
      if(temp == goaln->right){
        goaln->right = goaln->right->right;
      }
      if(temp->parent->left == temp){
        temp->parent->left = NULL;
      }
      return;
    }
    else{//If there is only one child
      if(n){
	if(goaln->left == NULL){
	  parent->left = goaln->right;
	}
	else{
	  parent->left = goaln->left;
	}
      }
      else{
	if(goaln->left == NULL){
	  parent->right = goaln->right;
	}
	else{
	  parent->right = goaln->left;
	}
      }
      return;
    } 
  }
}

void display(node* head, int depth){//Display method
  if(head->right != NULL){//If there is a right call print on the right
    display(head->right, depth + 1);
  }
  for(int i =0; i < depth; i++){//print tabs then yourself
    cout << "\t";
  }
  cout << head->value << endl;
  if(head->left != NULL){//If there is a right call print on the right
    display(head->left, depth + 1);
  }
}

bool search(node* head, int goal, node* &goaln){//Look for the node that has a certain value
  bool n = false;
  if(head->value == goal){//If current is the goal node
    goaln = head;
    return true;
  }
  else{
    if(head->right != NULL && goal > head->value){//If there is a right call search on the right
      n = search(head->right, goal, goaln);
    }
    else if(head->left != NULL && goal <= head->value){//If there is a right call search on the right
      n = search(head->left, goal, goaln);
    }
    if(n){//If the node has been found
      return true;
    }
  }
  return false;
}



void add(node* &head){//Add using file
  cout << "How many numbers do you want to add?" << endl;
  int ninput;
  cin >> ninput;
  cin.clear();
  for(int i = 0; i < ninput; i ++){//Create how many numbers the user wants
    fstream file("nums.txt");//Import the number file
    char input[100];
    int count = 0;
    int num = (rand() % 50) + 1;
    int num2;
    char temp[100];
    //Get random number and add it 
    while (file.getline(input, 100, ' ')) {
      if (count == num) {
	strcpy(temp,input);
	count++;
      }
      count++;
    }
    num2 = atoi(temp);
    node* n = new node();
    n->value = num2; 
    if(head == NULL){
      n->parent = NULL;
      head = n;
    }
    else{
      fadd(head, n, num2);
    }
  }
}

void manadd(node* &head){//Add manually
  cout << "Waht is the number you want to add(1-1000)" << endl;
  int input;
  cin >> input;
  cin.clear();
  node* n = new node();
  n->value = input; 
  if(head == NULL){
    head = n;
    return;
  }
  fadd(head, n, input);
}

void fadd(node* curr, node* n, int input){//Add into the right spot
  if(curr->right != NULL && input > curr->value){
    fadd(curr->right, n, input);
  }
  else if(curr->left != NULL && input <= curr->value){
    fadd(curr->left, n, input);
  }
  else{
    if(input > curr->value){
      n->parent = curr;
      curr->right = n;
    }
    if(input <= curr->value){
      n->parent = curr;
      curr->left = n;
    }
  }
}
