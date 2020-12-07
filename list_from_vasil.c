// Примеры функций для работы с однонаправленными списками
// для занятий со студентами 1 курса (на C)
// Автор: Васильчиков В.В.

#include <stdio.h>
#include <stdlib.h>

#define OK		1
#define NotOK	0

typedef struct s_Node {
	int Info;
	struct s_Node *Next;
} t_Node;

typedef struct s_Store {
	int N_Pack; /* Размер выделяемой пачки вершин */
	t_Node *AllocatedBlocks; /* Прицеплять будем в начало */
	t_Node *FirstFree; /* Прицеплять будем в начало */
	int FreeCount; /* Текущее количество свободных - опционально */
} t_Store;

typedef struct s_List {
	t_Store *pS; /* Склад для получения вершин */
	t_Node *First;
	t_Node *Last; /* опционально */
	int Count; /* опционально */
} t_List;

t_Node *MyAlloc(t_Store *pS)
{
	t_Node *temp;
	int i;

	if (!pS)
	{
		printf("\nMyAlloc: Store does not exist!");
		return NULL;
	}

	if (pS->FirstFree)
	{
		temp = pS->FirstFree;
		pS->FirstFree = temp->Next;
		pS->FreeCount--; /* опционально */
		return temp;
	}

	/* Выделяем новый кусок */
	if (pS->N_Pack < 2)
	{
		printf("\nMyAlloc: Packet size is too small!");
		return NULL;
	}

	if (!(temp = (t_Node *)malloc(pS->N_Pack * sizeof(*temp))))/*удвоение пасяти*/
		return NULL;

	for (i = 1; i < pS->N_Pack; i++) /* нулевую не трогаем */
		temp[i].Next = temp + i + 1;
	temp[pS->N_Pack - 1].Next = NULL; /* последняя */

	/* Запоминаем для дальнейшего освобождения */
	temp->Next = pS->AllocatedBlocks;
	pS->AllocatedBlocks = temp;

	pS->FirstFree = temp + 1;
	pS->FreeCount = pS->N_Pack - 1; /* опционально */

	return MyAlloc(pS); /* чтобы не повторяться */
}

int MyFree(t_Store *pS, t_Node *Node)
{
	if (!pS)
	{
		printf("\nMyFree: Store does not exist!");
		return NotOK;
	}

	Node->Next = pS->FirstFree;
	pS->FirstFree = Node;
	pS->FreeCount++; /* опционально */

	return OK;
}

int MyFinishFree(t_Store *pS)
{
	t_Node *temp;

	if (!pS)
	{
		printf("\nMyFinishFree: Store does not exist!");
		return NotOK;
	}

	for (; pS->AllocatedBlocks;)
	{
		pS->AllocatedBlocks = (temp = pS->AllocatedBlocks)->Next;
		free(temp);
	}

	pS->FirstFree = NULL;
	pS->FreeCount = 0; /* опционально */

	return OK;
}

int InsertAfter(t_List *pL, t_Node *Node, int Info)
{
	t_Node *New;

	if (!pL)
	{
		printf("\nInsertAfter: List does not exist!");
		return NotOK;
	}

	if (!(New = MyAlloc(pL->pS)))
	{
		printf("\nInsertAfter: Can't allocate new node!");
		return NotOK;
	}

	New->Info = Info;

	if (!Node) /* Insert first */
	{
		New->Next = pL->First; pL->First = New;
	}
	else
	{
		New->Next = Node->Next; Node->Next = New;
	}

	pL->Count++; /* опционально */
	if (!New->Next)/*если вставляли в конец*/
		pL->Last = New; /* опционально */
	return OK;
}

int InsertToTail(t_List *pL, int Info) /* опционально */
{
	if (!pL)
	{
		printf("\nInsertToTail: List does not exist!");
		return NotOK;
	}

	return InsertAfter(pL, pL->Last, Info);
}

int DeleteAfter(t_List *pL, t_Node *Node)
{
	t_Node *temp;

	if (!pL)
	{
		printf("\nDeleteAfter: List does not exist!");
		return NotOK;
	}

	if (!pL->First)
	{
		printf("\nDeleteAfter: List is empty!");
		return NotOK;
	}

	if (!Node) /* Delete first */
	{
		pL->First = (temp = pL->First)->Next;

		pL->Count--; /* опционально */
		if (!pL->First)
			pL->Last = NULL; /* опционально */

		return MyFree(pL->pS, temp);
	}

	if (!(temp = Node->Next))
	{
		printf("\nDeleteAfter: Nothing to delete!");
		return NotOK;
	}

	Node->Next = temp->Next;

	pL->Count--; /* опционально */
	if (!Node->Next)
		pL->Last = Node; /* опционально */

	return MyFree(pL->pS, temp);
}

int DeleteNode(t_List *pL, t_Node *Node)
{
	t_Node *cur, *pr;

	if (!pL)
	{
		printf("\nDeleteNode: List does not exist!");
		return NotOK;
	}

	for (pr = NULL, cur = pL->First; cur; cur = (pr = cur)->Next)
		if (cur == Node)
			return DeleteAfter(pL, pr);

	printf("\nDeleteNode: Can't find the Node!");
	return NotOK;
}

int ClearList(t_List *pL)
{
	t_Node *cur, *next;

	if (!pL)
	{
		printf("\nClearList: List does not exist!");
		return NotOK;
	}

	for (cur = pL->First; cur; cur = next)
	{
		next = cur->Next;
		MyFree(pL->pS, cur);
	}

	pL->First = pL->Last = NULL;
	pL->Count = 0;

	return OK;
}

void PrintList(t_List *pL)
{
	t_Node *cur;

	if (!pL)
	{
		printf("\nPrintList: List does not exist!");
		return;
	}

	printf("\nList info: First=%p, Count=%d, Last=%p, Store=%p",
		pL->First, pL->Count, pL->Last, pL->pS);
	if (pL->Count > 0)
		printf("\nNodes:");
	for (cur = pL->First; cur; cur = cur->Next)
		printf("\nAddr=%p, Info=%d, Next=%p", cur, cur->Info, cur->Next);
}


// для примера все переменные глобальные 
t_List MyList;
t_Store MyStore;

int main(int argc, char* argv[])
{
	printf("\nList testing");

	/* инициализация */
	MyList.pS = &MyStore;
	MyStore.N_Pack = 3;

	printf("\n*******************************************");
	printf("\nInitial value");
	PrintList(&MyList);

	InsertAfter(&MyList, NULL, 1);
	printf("\n*******************************************");
	printf("\nInsertAfter(&MyList, NULL, 1)");
	PrintList(&MyList);

	InsertAfter(&MyList, NULL, 2);
	printf("\n*******************************************");
	printf("\nInsertAfter(&MyList, NULL, 2)");
	PrintList(&MyList);

	InsertAfter(&MyList, NULL, 3);
	printf("\n*******************************************");
	printf("\nInsertAfter(&MyList, NULL, 3)");
	PrintList(&MyList);

	InsertAfter(&MyList, NULL, 4);
	printf("\n*******************************************");
	printf("\nInsertAfter(&MyList, NULL, 4)");
	PrintList(&MyList);

	InsertAfter(&MyList, NULL, 5);
	printf("\n*******************************************");
	printf("\nInsertAfter(&MyList, NULL, 5)");
	PrintList(&MyList);

	DeleteAfter(&MyList, MyList.First);
	printf("\n*******************************************");
	printf("\nDeleteAfter(&MyList, MyList.First)");
	PrintList(&MyList);

	DeleteAfter(&MyList, NULL);
	printf("\n*******************************************");
	printf("\nDeleteAfter(&MyList, NULL)");
	PrintList(&MyList);

	DeleteNode(&MyList, MyList.First);
	printf("\n*******************************************");
	printf("\nDeleteNode(&MyList, MyList.First)");
	PrintList(&MyList);

	InsertToTail(&MyList, 6);
	printf("\n*******************************************");
	printf("\nInsertToTail(&MyList, 6)");
	PrintList(&MyList);

	MyFinishFree(&MyStore);
	return 0;
}

/**** для примера с длинными числами */
#define Radix 10000

int AddLong(t_List *pL1, t_List *pL2, t_List *pLr)
{
	int v1, v2, vr, vost = 0;
	t_Node *p1 = pL1->First, *p2 = pL2->First;

	ClearList(pLr);

	for (;;)
	{
		if (p1)
		{
			v1 = p1->Info;
			p1 = p1->Next;
		}
		else
			v1 = 0;

		if (p2)
		{
			v2 = p2->Info;
			p2 = p2->Next;
		}
		else
			v2 = 0;

		vr = v1 + v2 + vost;
		if (vr == 0 && p1 == NULL && p2 == NULL)
			break;

		vost = vr / Radix;
		vr = vr % Radix;

		if (!InsertToTail(pLr, vr))
			return NotOK;
	}

	return OK;
}

/*****/
