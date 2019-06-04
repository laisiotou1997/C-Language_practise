/*
;|**********************************************************************;
;* Project           : Data Structure & Algorithm
;*
;* Program name      : CircularLinkedList.c
;*
;* Author            : SIO TOU LAI (laisiotou1997@gmail.com)
;*
;* Date created      : 04/06/2019
;*
;* Version           : Internal
;*
;* Copyright         : GNU GENERAL PUBLIC LICENSE Version 3
;*
;* Purpose           : Circular Linked List
;*
;* Revision History  :
;*
;* Date        Author      Ref    Revision (Date in DDMMYYYY format)
;* 04062019    lst97       1      First release
;*
;* Known Issue       :
;* No input validate and exception handle
;*
;|**********************************************************************;
*/

#include <stdio.h>
#include <stdlib.h>

#define LENGTH 10

struct CircularLinkedList{
	int iData;
	struct CircularLinkedList* pNext;
};

typedef struct CircularLinkedList CLL;

CLL* fnCLL_Create(CLL *);
void fnCLL_Print(CLL *);
void fnCLL_Append(CLL *, int);
CLL* fnCLL_Delete(CLL *, int);
void fnCLL_Value(CLL *, int);
void fnCLL_Free(CLL*);

int main(void) {
	int iUserInput = 0;
	CLL* pHead = 0;
	printf("= = = = = Menu = = = = =\n1. Create Linked List\n2. Insert Number\n3. Delete Number\n4. Index of the value\n5. Print Linked List\n0. Exit\n\n");
	while (1) {
		printf("@Circular_Linked_List>");
		scanf_s("%d", &iUserInput);
		switch (iUserInput) {
		case 0:
			fnCLL_Free(pHead);
			system("pause");
			return 0;
		case 1:
			pHead = (CLL*)malloc(sizeof(CLL));
			pHead = fnCLL_Create(pHead);
			fnCLL_Print(pHead);
			continue;
		case 2:
			printf("Insert to where:\n");
			scanf_s("%d", &iUserInput);
			fnCLL_Append(pHead, iUserInput -1);
			fnCLL_Print(pHead);
			continue;
		case 3:
			printf("What number you want to delete:\n");
			scanf_s("%d", &iUserInput);
			pHead = fnCLL_Delete(pHead, iUserInput);
			fnCLL_Print(pHead);
			continue;
		case 4:
			printf("What number you want to search:\n");
			scanf_s("%d", &iUserInput);
			fnCLL_Value(pHead, iUserInput);
			continue;
		case 5:
			fnCLL_Print(pHead);
			continue;
		default:
			printf("Invalide Input!\n\n");
			continue;
		}
	}
}

CLL* fnCLL_Create(CLL *pCLL_Head) {
	CLL *pCLL = pCLL_Head, *pTempCLL = 0;

	pCLL->iData = 0;
	pCLL->pNext = pCLL_Head;
	for (int iLoop = 1; iLoop < LENGTH; iLoop++) {
		pTempCLL = (CLL*)malloc(sizeof(CLL));
		pTempCLL->iData = iLoop;
		pTempCLL->pNext = pCLL_Head;
		pCLL->pNext = pTempCLL;
		pCLL = pTempCLL;
	}
	return pCLL_Head;
}

void fnCLL_Print(CLL *pCLL) {
	CLL* pHead = pCLL;
	while (pCLL->pNext != pHead) {
		printf("%d ", pCLL->iData);
		pCLL = pCLL->pNext;
	}
	printf("%d\n\n", pCLL->iData);
}

void fnCLL_Append(CLL* pCLL, int iIndex) {
	int iUserInput = 0;
	CLL *pTempCLL = 0, *newCLL = 0;

	printf("What number you want to put:\n");
	scanf_s("%d", &iUserInput);
	for (int iLoop = 0; iLoop < iIndex; iLoop++) {
		pTempCLL = pCLL;
		pCLL = pCLL->pNext;
	}
	newCLL = (CLL*)malloc(sizeof(CLL));
	newCLL->iData = iUserInput;
	pTempCLL->pNext = newCLL;
	newCLL->pNext = pCLL;
}

CLL* fnCLL_Delete(CLL* pCLL, int iNumber) {
	CLL* pCLL_Head = pCLL, *pTempCLL = pCLL_Head;

	if (pCLL->iData == iNumber && pCLL == pCLL_Head) {
		while (1) {
			if (pCLL->pNext == pCLL_Head) {
				pCLL->pNext = pCLL_Head->pNext;
				free(pCLL_Head);
				return pCLL->pNext;
			} else pCLL = pCLL->pNext;
		}
	} else {
		while (pCLL->pNext != pCLL_Head) {
			if (pCLL->iData == iNumber) {
				pTempCLL->pNext = pCLL->pNext;
				free(pCLL);
				return pCLL_Head;
			} else {
				pTempCLL = pCLL;
				pCLL = pCLL->pNext;
			}
		}
		if (pCLL->iData == iNumber) {
			pTempCLL->pNext = pCLL_Head;
			free(pCLL);
			return pCLL_Head;
		}
	}

	printf("No Found!\n\n");
	return pCLL_Head;
}

void fnCLL_Value(CLL *pCLL, int iIndex) {
	CLL* pCLL_Head = pCLL;
	int iCounter = 1;

	while (pCLL->pNext != pCLL_Head) {
		if (pCLL->iData == iIndex) {
			printf("The number is in index[%d]\n\n", iCounter);
			return;
		}
		iCounter++;
		pCLL = pCLL->pNext;
	}
	if (pCLL->iData == iIndex) printf("The number is in index[%d]\n\n", iCounter);
	else printf("No Found!\n\n");
}

void fnCLL_Free(CLL* pCLL) {
	CLL* pTempCLL = pCLL, * pHead = pCLL;

	while (pCLL->pNext != pHead) {
		pTempCLL = pCLL->pNext;
		free(pCLL);
		pCLL = pTempCLL;
	}
	free(pCLL);
	printf("Freeing the heap - SUCCESS!\n\n");
}
