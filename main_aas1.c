#include <stdio.h>

#include <stdlib.h>

/* Define structures and global constants, including:

the pcb type, the children linked list type, the maximum number of

processes*/

#define MAX_PROCESSES 100

struct node {

    int process_id;

    struct node* next;

};

typedef struct node linked_list_type;

struct node2 {

    int parent;

    linked_list_type* children;

};

typedef struct node2 pcb_type;



pcb_type* pcb_array[MAX_PROCESSES];

/***************************************************************/



void printHierachy() {

/* declare local vars */
    linked_list_type *current_child_node;

    printf("\nProcess list:\n");
    /* for each process index i from 0 up to (but not including) maximum number of processes */
    for(int i = 0; i < MAX_PROCESSES; i++)
    {
        /* if PCB[i] is not NULL */
        if(pcb_array[i] != NULL)
        {
            /* print process id, parent id, list of children processes */
            printf("Process id: %d\n", i);
            if(pcb_array[i]->parent == -1)
            {
                printf("\tNo parent process\n");
            }
            else
            {
                printf("\tParent process: %d \n", pcb_array[i]->parent);
            }
            
            if(pcb_array[i]->children == NULL)
            {
                printf("\tNo child processes\n");
            }
            else
            {
                current_child_node = pcb_array[i]->children;
                while(current_child_node != NULL)
                {
                    printf("\tChild process: %d \n", current_child_node->process_id);
                    current_child_node = current_child_node->next;
                }
            }
            
            
            
        }
        }
         printf("\n");
    
         return;

/* if PCB[i] is not NULL */

/* print process id, parent id, list of

children processes */

} /* end of procedure */

/***************************************************************/




void inputParameters() {

/* declare local vars */

/* Allocate memory for PCB[0] */

    pcb_array[0] = (pcb_type*)malloc(sizeof(pcb_type));

    pcb_array[0]->parent = -1;

    pcb_array[0]->children = NULL;

/* Intitialize all other PCB's to NULL */

    for(int i=1;i<MAX_PROCESSES;i++){

        pcb_array[i] = NULL;
    }
    printHierachy();

/* print hierarchy of processes */

    return;

} /* end of procedure */

/***************************************************************/

void createChild() {

/* define local vars */

    int p;

    int q = 1;
    linked_list_type *new_child_node;
    linked_list_type *current_child_node;

/* prompt for parent process index p */

    printf("Enter the parent process id:");

    scanf("%d",&p);

/* if PCB[p] is NULL, print message process does not exist, return

*/

    if(pcb_array[p] == NULL) {

        printf("Process does not exist");

        return;

    }

/* search for first available index q without a parent in a while

loop */

    while((q < MAX_PROCESSES)&&(pcb_array[q] != NULL)){

        q++;

    }/*end while*/

/* if maximum number of processes reached, print message of no more

avaiable PCBs */
 if(q == MAX_PROCESSES)
    {
        printf("Max number of processes reached, no more available PCBs\n");
        return;
    }

/* allocate memory for new child process, initialize fields */

    pcb_array[q] = (pcb_type*)malloc(sizeof(pcb_type));

/* record the parent's index p in PCB[q] */

    pcb_array[q]->parent = p;

/* initialize the list of children of PCB[q] as empty */

    pcb_array[q]->children = NULL;



/* append the node containing the child's index q to the children

linked list of PCB[p] */

    new_child_node = (linked_list_type*)malloc(sizeof (linked_list_type));

    new_child_node->process_id = q;

    new_child_node->next = NULL;

    

    if(pcb_array[p]->children == NULL){

        pcb_array[p]->children = new_child_node;

    }

    else{

    current_child_node =  pcb_array[p]->children;   

        while((current_child_node->next) != NULL){

        current_child_node = current_child_node->next;

        }

        current_child_node->next = new_child_node;

    }

    

/* print hierarchy of processes */
printHierachy();

return;

} /* end of procedure */

/***************************************************************/

void destroyChilds(linked_list_type *current) {
     int q; 
    
    if (current == NULL) {
        return;
    } 
    
    destroyChilds(current->next);
    q = current->process_id;
    destroyChilds(pcb_array[q]->children);
    free(pcb_array[q]);
    pcb_array[q] = NULL;
    free(current);
    

/* declare local vars */

/* check if end of linked list--if so return */

/* else call self on next node in linked list */

/* set variable q to current node's process index field

*/

/* call self on children of PCB[q] */

/* free memory of PCB[q] and set PCB[q] to NULL*/

/* free memory of paramter and set to NULL */

    return;

} /* end of procedure */

/***************************************************************/

void destroyChildsOfProcess() {
    int p;

/* declare local vars */

/* prompt for process index p */
    printf("Enter the parent process id: ");
    scanf("%d", &p);
    
     
    if(pcb_array[p] == NULL)
    {
        printf("Parent process does not exist\n");
        return;
    }

/* call recursive procedure to destroy children of PCB[p] */

    destroyChilds(pcb_array[p]->children);

/* reset children of PCB[p] to NULL */

    pcb_array[p]->children = NULL;

/* print hierarchy of processes */
    printHierachy();

    return;

} /* end of procedure */

/***************************************************************/

void freeMemory() {

 /* if PCB[0] is non null) */
    if(pcb_array[0] != NULL)
    {
        /* if children of PCB[0] is not null */
        if(pcb_array[0]->children != NULL)
        {
            /* call recursive procedure to destroy children of PCB[0] */
            destroyChilds(pcb_array[0]->children);
        }
        /* free memory of all PCB's */
        free(pcb_array[0]);
    }
    return;

} /* end of procedure */

/***************************************************************/

int main() {
    

/* declare local vars */
    int choice = 0;

/* while user has not chosen to quit */
    while (choice != 4){

/* print menu of options */
        printf ("Process creation and destruction\n");
        printf("----------------------------------\n");
        printf("1) Initialize process hierarchy\n");
        printf("2) Create a new child process\n");
        printf("3) Destroy all descendants of a process\n");
        printf("4) Quit program and free memory\n");
        printf("Enter selection: ");

/* prompt for menu selection */
        scanf("%d", &choice);

/* call appropriate procedure based on choice--use switch

statement or series of if, else if, else statements */
            switch (choice) 
            {
            case 1:
                
            
               inputParameters();
                
                break;
            case 2:
                createChild();
                break;
            case 3:
                destroyChildsOfProcess();
                break;
            case 4:
                freeMemory();
                printf("Quitting program...\n");
                break;
            default:
                printf("Invalid option!\n");
                break;
        }
         
    }
return 1; /* indicates success */

} /* end of procedure */

