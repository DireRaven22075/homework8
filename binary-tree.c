/*
 * Binary Search Tree #1
 *
 * Data Structures
 *
 * School of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


int main()
{
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Node                  = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}



void inorderTraversal(Node* ptr)
{
	if (ptr->left != NULL)
		inorderTraversal(ptr->left);
	printf("[%d] ", ptr->key);
	if (ptr->right != NULL)
		inorderTraversal(ptr->right);
	return;
}

void preorderTraversal(Node* ptr)
{
	printf("[%d] ", ptr->key);
	if (ptr->left != NULL)
		preorderTraversal(ptr->left);
	if (ptr->right != NULL)
		preorderTraversal(ptr->right);
	return;
}

void postorderTraversal(Node* ptr)
{
	if (ptr->left != NULL)
		postorderTraversal(ptr->left);
	if (ptr->right != NULL)
		postorderTraversal(ptr->right);
	printf("[%d] ", ptr->key);
	return;
}


int insert(Node* head, int key)
{
	//새로운 노드 동적할당
	Node* node = (Node*)malloc(sizeof(Node));
	//새로운 노드에 key값 저장
	node->key = key;
	//새로운 노드의 포인터 초기화
	node->left = NULL;
	node->right = NULL;
	//현재 탐색위치 저장용 변수 선언
	Node* current = head;
	//만약 트리가 비어있다면 (루트의 좌측에 할당)
	if (head->left == NULL) {
		head->left = node;
		return 0;
	}
	current = head->left;
	//탐색 무한반복
	while (1) {
		//만약 추가할 노드의 키값이 현재 탐색위치의 키값보다 크다면
		if (current->key < node->key) {
			//만약 우측이 비어있다면, 우측에 배치후 함수 종료
			if (current->right == NULL) {
				current->right = node;
				break;
			}
			else {
				//우측이 비어있지 않다면, 우측으로 이동
				current = current->right;
			}
		}
		//만약 추가할 노드의 키값이 현재 탐색위치의 키값보다 작다면
		else if (current->key > node->key) {
			//만약 좌측이 비어있다면, 좌측에 배치후 함수 종료
			if (current->left == NULL) {
				current->left = node;
				break;
			}
			else {
				//좌측이 비어있지 않다면, 좌측으로 이동
				current = current->left;
			}
		}
		//만약 추가할 노드의 키값과 현재 탐색위치의 키값이 같다면
		else {
			//이미 존재하는 키값이므로 함수 종료
			printf("현재 존재하는 키값입니다.");
			return EOF;
		}
	}
	return 0;
}

int deleteLeafNode(Node* head, int key)
{
	
}

Node* searchRecursive(Node* ptr, int key)
{
	if (ptr->key != key) {
		if (ptr->key < key) {
			if (ptr->right != NULL) searchRecursive(ptr->right, key);
			else return NULL;
		}
		else {
			if (ptr->left != NULL) searchRecursive(ptr->left, key);
			else return NULL;
		}
	}
	else {
		return ptr;
	}
}

Node* searchIterative(Node* head, int key)
{
	Node* current = head->left;
	while (1) {
		if (current->key != key) {
			if (current->key < key) {
				if (current->right != NULL) current = current->right;
				else return NULL;
			}
			else {
				if (current->left != NULL) current = current->left;
				else return NULL;
			}
		}
		else {
			return current;
		}
	}
}


int freeBST(Node* head)
{

}





