#include "prison_helper.h"
#include <stdlib.h>
#include <stdio.h>
#include "../types.h"

// Function to create a new node
pd_block_node_t *create_node(pd_block_t block)
{
  pd_block_node_t *newNode = (pd_block_node_t *)malloc(sizeof(pd_block_node_t));
  if (newNode == NULL)
  {
    fprintf(stderr, "Memory allocation failed in function create_node in linked_list.c\n");
    exit(EXIT_FAILURE);
  }
  newNode->block = block;
  newNode->next = NULL;
  return newNode;
}

// Function to insert a new node at the beginning of the list
void insert_at_beginning(pd_block_node_t **head, pd_block_t block)
{
  pd_block_node_t *newNode = create_node(block);
  newNode->next = *head;
  *head = newNode;
}

// Function to insert a new node at the end of the list
void insert_at_end(pd_block_node_t **head, pd_block_t block)
{
  pd_block_node_t *newNode = create_node(block);
  if (*head == NULL)
  {
    *head = newNode;
    return;
  }
  pd_block_node_t *temp = *head;
  while (temp->next != NULL)
  {
    temp = temp->next;
  }
  temp->next = newNode;
}

// Function to print the elements of the list
void print_list(pd_block_node_t *head)
{
  pd_block_node_t *temp = head;
  while (temp != NULL)
  {
    printf("%d ", temp->block);
    temp = temp->next;
  }
  printf("\n");
}

// Function to delete a node by value
void delete_node_by_value(pd_block_node_t **head, pd_block_t block)
{
  pd_block_node_t *temp = *head;
  pd_block_node_t *prev = NULL;

  if (temp != NULL && temp->block == block)
  {
    *head = temp->next;
    free(temp);
    return;
  }

  while (temp != NULL && temp->block != block)
  {
    prev = temp;
    temp = temp->next;
  }

  if (temp == NULL)
    return;

  prev->next = temp->next;
  free(temp);
}

// Function to delete a node by reference
void delete_node_by_reference(pd_block_node_t **head, pd_block_node_t *pd_block_node_to_delete)
{
  if (*head == NULL || pd_block_node_to_delete == NULL)
    return;

  if (*head == pd_block_node_to_delete)
  {
    *head = pd_block_node_to_delete->next;
    free(pd_block_node_to_delete);
    return;
  }

  pd_block_node_t *current = *head;
  pd_block_node_t *prev = NULL;
  while (current != NULL && current != pd_block_node_to_delete)
  {
    prev = current;
    current = current->next;
  }

  if (current == NULL)
    return;

  prev->next = current->next;
  free(current);
}

// Function to delete the entire list
void delete_list(pd_block_node_t **head)
{
  pd_block_node_t *current = *head;
  pd_block_node_t *next;
  while (current != NULL)
  {
    next = current->next;
    free(current);
    current = next;
  }
  *head = NULL;
}