#include <stdio.h>
#include <stdlib.h>
#include "node.h"

int FIFO_cache_put(int Newpageno, node_t **head_fifo, int cache_capacity);
int LRU_cache_put(int Newpageno, node_t **head_lru, int cache_capacity);
void DisplayResult(node_t *head);

int main(int argc, char *argv[])
{

    printf("------------------------------------------------------------\n");
    printf("Page Replacement Simulated Program for CSCI 3150 (Hong Xu, Henry@CSE,CUHK)\n");

    FILE *fp = NULL;
    int cache_capacity; //The size of FIFO cache and LRU cache
    int refer_total; //The total of elements in refernce row

    fp = fopen(argv[2], "r");
    fscanf(fp, "%d", &cache_capacity);
    fscanf(fp, "%d", &refer_total);

    int pageno[refer_total]; //The reference row

    for(int i=0; i<refer_total; i++)
        fscanf(fp, "%d", &pageno[i]);

    node_t *head_fifo=NULL; //The header pointer for fifo cache
    node_t *head_lru=NULL; //The header pointer for lru cache

    int page_fault_time_FIFO = 0; //The total times of missing when using FIFO cache
    int page_fault_time_LRU = 0;  //The total times of missing when using LRU cache

    int page_fault_flag_FIFO;
    int page_fault_flag_LRU;


    for(int i=0; i<refer_total; i++)
    {
        page_fault_flag_FIFO = FIFO_cache_put(pageno[i], &head_fifo, cache_capacity);
        printf("After assessing %d, the elements in FIFO cache:", pageno[i]);
        DisplayResult(head_fifo);
        
        page_fault_flag_LRU = LRU_cache_put(pageno[i], &head_lru, cache_capacity);
        printf("the elements in LRU cache:");
        DisplayResult(head_lru);

        printf("\n");

        if(page_fault_flag_FIFO)
            page_fault_time_FIFO++;

        if(page_fault_flag_LRU)
            page_fault_time_LRU++;
    }

    printf("Total times of missing in FIFO:%d\n", page_fault_time_FIFO);
    printf("Total times of missing in LRU:%d\n", page_fault_time_LRU);    

    return 0;

}

//Display the status of the FIFO cache or LRU cache
void DisplayResult(node_t *head)
{
    node_t *curr;
    curr = head;

    while(curr!=NULL)
    {
        printf("%d ", curr->page_no);
        curr = curr->next;
    }
}