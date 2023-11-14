#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "prototypes.c"

/**
 * struct Node - linked list node for environment variables
 * @var: the environment variable
 * @next: pointer to the next node in the list
 */
typedef struct Node
{
	char *var;
	struct Node *next;
} Node;

/**
 * addNode - adds a new node to the linked list
 * @head: double pointer to the head of the list
 * @var: environment variable to add
 */
void addNode(Node **head, char *var)
{
	Node *newNode = malloc(sizeof(Node));

	if (newNode == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	newNode->var = var;
	newNode->next = *head;
	*head = newNode;
}

/**
 * printList - prints the linked list of environment variables
 * @head: pointer to the head of the list
 */
void printList(Node *head)
{
	while (head != NULL)
	{
		printf("%s\n", head->var);
		head = head->next;
	}

}

/**
 * freeList - frees the memory allocated for the linked list
 * @head: double pointer to the head of the list
 */
void freeList(Node **head)
{
	while (*head != NULL)
	{
		Node *temp = *head;
		*head = (*head)->next;
		free(temp->var);
		free(temp);
	}
}

/**
 * custom_env - custom implementation of the env command
 * @ac: The argument count
 * @av: The argument vector
 * @environ: The environment variables
 */
void custom_env(int ac, char **av, char **environ)
{
	Node *envList = NULL;
	int i;
	(void)ac;
	(void)av;

	for (i = 0; environ[i] != NULL; i++)
	{
		addNode(&envList, strdup(environ[i]));
	}

	printList(envList);

    /* Free the linked list */
	freeList(&envList);
}
