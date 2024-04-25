#ifndef PRISON_HELPER_H
#define PRISON_HELPER_H

// Function to create a new node
pd_block_node_t *create_node(pd_block_t block);

// Function to insert a new node at the beginning of the list
void insert_at_beginning(pd_block_node_t **head, pd_block_t block);

// Function to insert a new node at the end of the list
void insert_at_end(pd_block_node_t **head, pd_block_t block);

// Function to print the elements of the list
void print_list(pd_block_node_t *head);

// Function to delete a node by value
void delete_node_by_value(pd_block_node_t **head, pd_block_t block);

// Function to delete a node by reference
void delete_node_by_reference(pd_block_node_t **head, pd_block_node_t *pd_block_node_to_delete);

// Function to delete the entire list
void delete_list(pd_block_node_t **head);


#endif