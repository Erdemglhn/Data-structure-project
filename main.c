//Osman Erdem Gülhan 150123008
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#define MAX 16

typedef struct Node{
	char data[MAX];
	struct Node* next;
}Node;

typedef struct Stack{
	int data;
	struct Stack* next;
}Stack;

typedef struct VarNode{
	char var[3];
	int varCount;
	char assign[3][MAX];
	Node* MainNode;
}VarNode;

void push(Stack** top, int x){
	Stack* n = (Stack*)malloc(sizeof(Stack));
	n->data = x;
	n->next = *top;
	*top = n;
}

int pop(Stack** top){
	if(!*top){
		return -1;
	}
	Stack* t = *top;
	int value = t->data;
	*top=t->next;
	free(t);
	return value;
}

Node* createNode(char* s){
	Node* n = (Node*)malloc(sizeof(Node));
	strcpy(n->data,s);
	n->next = NULL;
	return n;
}

void Add(Node** head,char* s){
	Node* n = createNode(s);
	if(!*head){
		*head = n;
		return;
	}
	Node* t = *head;
	while(t->next !=NULL){
		t = t->next;
	}
	t->next = n;
}

Node* copyList(Node* h){
	Node* newHead=NULL;
	while(h!=NULL){
		Add(&newHead,h->data);
		h = h->next;
	}
	return newHead;
}

int isOp(char* s){
	return (!strcmp(s,"+") || !strcmp(s,"-") || !strcmp(s,"/") || !strcmp(s,"*") || !strcmp(s,"^"));
}

int evaluate(Node* h){
	Stack* s = NULL;
	while(h!=NULL){
		if(!isOp(h->data)){
			push(&s,atoi(h->data));
		}
		else{
			int b = pop(&s);
			int a = pop(&s);
			int result = 0;
			if(!strcmp(h->data,"+")){
				result = a+b;
			}
			else if(!strcmp(h->data,"-")){
				result = a-b;
			}
			else if(!strcmp(h->data,"*")){
				result = a*b;
			}
			else if(!strcmp(h->data,"/")){
				if(b==0 || a%b!=0){
					return 9938948;
				}
				result = a/b;
			}
			else if(!strcmp(h->data,"^")){
				result = (int)pow(a,b);
			}
			push(&s,result);
		}
		h = h->next;
	}
	return pop(&s);
}

void tryValues(VarNode* varNd,int num){
	int k,l,m;
	if(num==varNd->varCount){
		Node* c =copyList(varNd->MainNode);
		Node* t = c;
		while(t!=NULL){
			for(k=0;k<varNd->varCount;k++){
				if(strlen(t->data)==1 && t->data[0]==varNd->var[k]){
					strcpy(t->data,varNd->assign[k]);
				}
			}
			t = t->next;
		}
		int result= evaluate(c);
		if(result==0){
			printf("(");
			for(k=0;k<varNd->varCount;k++){
				printf("%s",varNd->assign[k]);
				if(k<varNd->varCount-1){
					printf(",");
				}
			}
			printf(") = 0\n");
		}
		while(c!=NULL){
			Node* f = c->next;
			free(c);
			c=f;
		}
		return;
	}
	char* ops[]={"+","-","*","/","^"};
	for(l=0;l<5;l++){
		strcpy(varNd->assign[num],ops[l]);
		tryValues(varNd,num+1);
	}
	for(m=1;m<=20;m++){
		sprintf(varNd->assign[num],"%d",m);
		tryValues(varNd,num+1);
	}
}

void evaluateFirst(Node* node){
	int k;
	VarNode varNd;
	varNd.MainNode=node;
	varNd.varCount=0;
	Node* t = node;
	while(t !=NULL){
		if(isalpha(t->data[0])){
			int tmp=0;
			for(k=0;k<varNd.varCount;k++){
				if(varNd.var[k]==t->data[0]){
					tmp=1;
				}
			}
			if(!tmp){
				varNd.var[varNd.varCount++] = t->data[0];
			}	
		}
		t = t->next;	
	}
	tryValues(&varNd,0);
}

Node* fileToList(char* fileName){
	FILE* f = fopen(fileName,"r");
	if(!f){
		printf("file cannot open!\n");
		return NULL;
	}
	char text[1000];
	fread(text,1,999,f);
	fclose(f);
	text[999]=0;
	Node* head=NULL;
	char* token = strtok(text," \n\t");
	while(token){
		if(!strcmp(token,"="))
			break;
		Add(&head,token);
		token = strtok(NULL," \n\t");
	}
	return head;
}

int main() {
	FILE* f = fopen("DataStructureInput.txt","w");
	fprintf(f,"3 1 + 2 3 2 ^ a 2 / 4 3 - b - c * 2 4 1 + ^ 3 4 * 2 2 * - / 6 2 * - + = 0");
	fclose(f);
	Node* list = fileToList("DataStructureInput.txt");
	evaluateFirst(list);
	
}
