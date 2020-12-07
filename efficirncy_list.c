#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
typedef struct s_node {
	int info;/*main info part*/
	struct s_node *next;/*next node*/
	struct s_node *prev;/*previous node*/
}t_node;
typedef struct s_storage {
	int cap;/*num of all nodes*/
	t_node* allocblocks;/*first node*/
	t_node *firstfree;/*first free node*/
	int numfree;/*num of free nodes*/
}t_storage;
typedef struct s_list {
	t_storage* ps;/*storage with nodes*/
	t_node* first;/*"head" of list*/
	t_node* last;/*"tail" of list*/
	int size;/*number of nodes in list*/
}t_list;
t_node* myalloc(t_storage* pS) {
	t_node* temp;
	int i;
	if (!pS) {
		/*error */
		return NULL;
	}
	if (pS->firstfree) {
		temp = pS->firstfree;
		pS->firstfree = pS->firstfree->next;
		pS->numfree--;
		temp->next = pS->firstfree->prev = NULL;
		return temp;
	}
	if (pS->cap < 2) {
		/*error with too small packet*/
		return NULL;
	}
	if (!(temp = (t_node*)calloc(pS->cap, sizeof(t_node))))/*alloc more memory*/
		return NULL;
	for (i = 1; i < pS->cap; i++) {/*connect all nodes*/
		temp[i].next = temp + i + 1;
		temp[i].next = temp + i - 1;
	}
	temp[1].prev = temp[pS->cap - 1].next = NULL;
	temp->next = pS->allocblocks;
	pS->allocblocks = temp;

	pS->firstfree = temp + 1;
	pS->numfree = pS->cap - 1;

	return myalloc(pS);
}
int FreeNode(t_storage* pS, t_node* node) {
	if (!pS)
		return 0;
	node->next = pS->firstfree;
	pS->firstfree->prev = node;
	pS->firstfree = node;
	pS->numfree++;
	return 1;
}
int FinFree(t_storage* pS) {
	t_node* temp;
	if (!pS)
		return 0;
	while (pS->allocblocks) {
		temp = pS->allocblocks;
		pS->allocblocks = pS->allocblocks->next;
		free(temp);
	}
	pS->firstfree = NULL;
	pS->numfree = 0;
	return 1;
}
int AddAfter(t_list* pl, t_node* after, int info) {
	t_node* newN=NULL;
	if (!pl){
		/*error*/
		return 0;
	}

	if (!(newN = myalloc(pl->ps))) {
		/*error*/
		return 0;
	}
	newN->info = info;
	if (!after) {
		if(pl->first)pl->first->prev = newN;
		newN->next = pl->first;
		pl->first = newN;
	}
	else{
		newN->next = after->next;
		if (after->next)
			after->next->prev = newN;
		after->next = newN;
		newN->prev = after;
	}
	pl->size++;
	if (newN->next)
		pl->last = newN;
	return 1;
}
int AddLast(t_list* pl, int info) {
	if (!pl) {
		/*error*/
		return 0;
	}
	return AddAfter(pl, pl->last, info);
}
int DeleteAfter(t_list* pl, t_node* after) {
	t_node* temp;
	if (!pl) {
		/*error have no list*/
		return 0;
	}
	if (!pl->first) {
		/*error empty list*/
		return 0;
	}
	if (!after) {
		temp = pl->first;
		pl->first = pl->first->next;
		if (!pl->first)
			pl->last = NULL;
		else
			pl->first->prev = NULL;
		pl->size--;
		return FreeNode(pl->ps, temp);	
	}
	if (!after->next) {
		/*error nothing to delete*/
		return 0;
	}
	temp = after->next;
	after->next = temp->next;
	if (after->next)
		after->next->prev = after;
	else
		pl->last = NULL;
	pl->size--;
	return FreeNode(temp);
}
int DeleteNode(t_list* pL, t_node* Node){
	t_node* cur, * pr;
	if (!pL)	{
		/*error have no list*/
		return 0;
	}
	for (pr = NULL, cur = pL->first; cur; cur = (pr = cur)->next)
		if (cur == Node)
			return DeleteAfter(pL, pr);
	/*error node does not exist*/
	return 0;
}
int ClearList(t_list* pL){
	t_node* cur, * next;
	if (!pL){
		/*error list does not exist*/
		return 0;
	}
	for (cur = pL->first; cur; cur = next){
		next = cur->next;
		MyFree(pL->ps, cur);
	}
	pL->first = pL->last = NULL;
	pL->size = 0;
	return 1;
}
void PrintList(t_list* pL){
	t_node* cur;
	if (!pL){
		/*error list does not exixt*/
		return;
	}
	printf("\nList info: First=%p, Count=%d, Last=%p, Store=%p",
		pL->first, pL->size, pL->last, pL->ps);
	if (pL->size > 0)
		printf("\nNodes:");
	for (cur = pL->first; cur; cur = cur->next)
		printf("\nAddr=%p, Info=%d, Next=%p", cur, cur->info, cur->next);
}
int main() {


}
