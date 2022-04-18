#include <iostream>
#include <fstream>
#include <cstring>
#include <math.h>
#include<stdio.h>
#include<stdlib.h>

using namespace std;

struct node{//Create a student struct
  char value;
  struct node *left = NULL;
  struct node *right = NULL;
};

void add(node* head);
void check(node* head, node* n);
void display(node* head, int depth);
void manadd(int* table);
void remove(node* head);

int main(){
  srand(time(0));
  bool quit = false;//bool to check when user wants to quit
  node* head = new node();
  while(!quit){//Main while
    cout << "Type a valid command(ADD, REMOVE, MADD, PRINT, DISPLAY, QUIT)" << endl;//Prompt user for input
    char input[10];//Get input from user
    cin >> input;
    if(strcmp(input, "MADD") == 0){//if user wants to manually add
      manadd(head);
    }
    if(strcmp(input,"ADD") == 0){//If user wants to add students
      add(head);
    }
    if(strcmp(input,"REMOVE") == 0){//If user wants to remove from heap, printing it out in the process
      remove(head);
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

void manadd(node* head){//Add manually
  cout << "Waht is the number you want to add(1-1000)" << endl;
  int input;
  cin >> input;
  cin.clear();
  node* n = new node();
  n->value = input; 
  check(head, n);
}

void check(node* head, node* n){
  if()
}
