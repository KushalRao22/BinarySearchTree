#include <iostream>
#include <fstream>
#include <cstring>
#include <math.h>
#include<stdio.h>
#include<stdlib.h>

using namespace std;

struct node{//Create a student struct
  int value;
  struct node *left = NULL;
  struct node *right = NULL;
};

void add(node* &head);
void fadd(node* curr, node* n, int input);
void display(node* head, int depth);
void manadd(node* &head);
bool search(node* head, int goal, node* &goaln);
void remove(node* curr, int goal);

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
    if(strcmp(input,"SEARCH") == 0){//If user wants to add students
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
    if(strcmp(input,"REMOVE") == 0){//If user wants to remove from heap, printing it out in the process
      int num;
      cout << "What number do you want to look for" << endl;
      cin >> num;
      cin.clear();
      remove(head, num);
    }
    else if(strcmp(input, "DISPLAY")==0){//Dislay the heap as a tree
      display(head, 0);
    }
    else if(strcmp(input,"QUIT") == 0){//If user wants to quit
      quit = true;
    }
  }
  return 0;
}

void remove(node* curr, int goal){
  node* goaln;//pointer to hold the goal node's adress
  if(!search(curr, goal, goaln)){
    cout << "Input a valid number" << endl;
    return;
  }
  goaln->value = -10;
  
}




void display(node* head, int depth){
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

bool search(node* head, int goal, node* &goaln){
  bool n = false;
  node* temp;
  if(head->value == goal){
    goaln = head;
    return true;
  }
  else{
    if(head->right != NULL && goal > head->value){//If there is a right call print on the right
      n = search(head->right, goal, temp);
    }
    else if(head->left != NULL && goal <= head->value){//If there is a right call print on the right
      n = search(head->left, goal, temp);
    }
    if(n){
      return true;
    }
  }
  return false;
}



void add(node* &head){
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
    //Get random number and add it to the array
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

void fadd(node* curr, node* n, int input){
  if(curr->right != NULL && input > curr->value){
    fadd(curr->right, n, input);
  }
  else if(curr->left != NULL && input <= curr->value){
    fadd(curr->left, n, input);
  }
  else{
    if(input > curr->value){
      curr->right = n;
    }
    if(input <= curr->value){
      curr->left = n;
    }
  }
}
