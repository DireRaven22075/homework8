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
	//학번 출력
	printf("[----------------------2023041004 - 한윤수----------------------]\n");
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


//중위순회 함수 (left-> root -> right)
void inorderTraversal(Node* ptr)
{
	//만약 좌측에 노드가 존재한다면
	if (ptr->left != NULL)
		//좌측으로 제귀함수 호출
		inorderTraversal(ptr->left);
	//현재 노드의 값 출력
	printf("[%d] ", ptr->key);
	//만약 우측에 노드가 존재한다면
	if (ptr->right != NULL)
		//우측으로 제귀함수 호출
		inorderTraversal(ptr->right);
	//함수 종료
	return;
}

//전위순회 함수 (root -> left -> right)
void preorderTraversal(Node* ptr)
{
	//현재 노드의 값 출력
	printf("[%d] ", ptr->key);
	//만약 좌측에 노드가 존재한다면
	if (ptr->left != NULL)
		//좌측으로 제귀함수 호출
		preorderTraversal(ptr->left);
	//만약 우측에 노드가 존재한다면
	if (ptr->right != NULL)
		//우측으로 제귀함수 호출
		preorderTraversal(ptr->right);
	//함수 종료
	return;
}

//후위순회 함수 (left -> right -> root)
void postorderTraversal(Node* ptr)
{
	//만약 좌측에 노드가 존재한다면
	if (ptr->left != NULL)
		//좌측으로 제귀함수 호출
		postorderTraversal(ptr->left);
	//만약 우측에 노드가 존재한다면
	if (ptr->right != NULL)
		//우측으로 제귀함수 호출
		postorderTraversal(ptr->right);
	//현재 노드의 값 출력
	printf("[%d] ", ptr->key);
	//함수 종료
	return;
}

//노드 추가함수
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

//리프노드 삭제함수
int deleteLeafNode(Node* head, int key)
{
	//현재 탐색위치 저장용 변수 선언
	Node* current = head->left;
	//부모노드 저장용 변수 선언
	Node* parent = head;
	//탐색 무한반복
	while (1) {
		//만약 현재 탐색위치의 키값이 찾으려는 키값과 다르다면
		if (current->key != key) {
			//만약 현재 탐색위치의 키값이 찾으려는 키값보다 작다면
			if (current->key < key) {
				//만약 우측에 노드가 존재한다면 우측으로 이동
				if (current->right != NULL) {
					parent = current;
					current = current->right;
				}
				//찾지 못하면 출력후 함수 종료
				else {
					printf("the node [%d] is not found.\n", key);
					return 0;
				} 
			}
			//만약 현재 탐색위치의 키값이 찾으려는 키값보다 크다면
			else {
				//만약 좌측에 노드가 존재한다면 좌측으로 이동
				if (current->left != NULL) {
					parent = current;
					current = current->left;
				}
				//찾지 못하면 출력후 함수 종료
				else {
					printf("the node [%d] is not found.\n", key);
					return 0;
				}
			}
		}
		//만약 현재 탐색위치의 키값이 찾으려는 키값과 같다면
		else {
			//만약 현재 탐색위치가 리프노드라면
			if (current->left == NULL && current->right == NULL) {
				//부모노드의 좌측이 현재 탐색위치라면, 좌측을 NULL로 초기화
				if (parent->left == current) {
					parent->left = NULL;
				}
				//부모노드의 우측이 현재 탐색위치라면, 우측을 NULL로 초기화
				else {
					parent->right = NULL;
				}
				//현재 탐색위치 메모리 해제후 함수 종료
				free(current);
				return 0;
			}
			//리프노드가 아니라면 출력후 함수 종료
			else {
				printf("the node [%d] is not a leaf node.\n", key);
				return 0;
			}
		}
	}
}

//제귀함수를 이용한 탐색 함수
Node* searchRecursive(Node* ptr, int key)
{
	//만약 현재 탐색위치의 키값이 찾으려는 키값과 다르다면
	if (ptr->key != key) {
		//만약 현재 탐색위치의 키값이 찾으려는 키값보다 작다면
		if (ptr->key < key) {
			//만약 우측에 노드가 존재한다면 우측으로 이동
			if (ptr->right != NULL) searchRecursive(ptr->right, key);
			//없으면 NULL 반환
			else return NULL;
		}
		//만약 현재 탐색위치의 키값이 찾으려는 키값보다 크다면
		else {
			//만약 좌측에 노드가 존재한다면 좌측으로 이동
			if (ptr->left != NULL) searchRecursive(ptr->left, key);
			//없으면 NULL 반환
			else return NULL;
		}
	}
	//만약 현재 탐색위치의 키값이 찾으려는 키값과 같다면
	else {
		return ptr;
	}
}

//반복문을 이용한 탐색 함수
Node* searchIterative(Node* head, int key)
{
	//현재 탐색위치 저장용 변수 선언
	Node* current = head->left;
	//탐색 무한반복
	while (1) {
		//만약 현재 탐색위치의 키값이 찾으려는 키값과 다르다면
		if (current->key != key) {
			//만약 현재 탐색위치의 키값이 찾으려는 키값보다 작다면
			if (current->key < key) {
				//만약 우측에 노드가 존재한다면 우측으로 이동
				if (current->right != NULL) current = current->right;
				//없으면 NULL 반환
				else return NULL;
			}
			else {
				//만약 좌측에 노드가 존재한다면 좌측으로 이동
				if (current->left != NULL) current = current->left;
				//없으면 NULL 반환
				else return NULL;
			}
		}
		//만약 현재 탐색위치의 키값이 찾으려는 키값과 같다면
		else {
			//현재 탐색위치 반환
			return current;
		}
	}
}

//메모리 해제 함수
int freeBST(Node* head)
{
	//만약 우측에 노드가 존재한다면
	if (head->right != NULL)
		//우측 노드로 제귀함수 호출
		freeBST(head->right);
	//만약 좌측에 노드가 존재한다면
	if (head->left != NULL)
		//좌측 노드로 제귀함수 호출
		freeBST(head->left);
	//현재 노드 메모리 해제
	free(head);
	return 0;
}





