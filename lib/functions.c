#include "functions.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
int calculateBitsRequired()
{
    int pageSizeBit = (int)(log((double)PAGE_SIZE) / log((double)2));
    return SYS_BITS - pageSizeBit;
}

void set_up_memory(){
   int noOfFrame = 0;
    int VPNBits = calculateBitsRequired();
    int offset = SYS_BITS - VPNBits;
    char *addresses = malloc(sizeof(char)*ADDEESSABLE_MEMORY);
    int noOfPages = ADDEESSABLE_MEMORY / PAGE_SIZE;
    bool done0 = false;
    srand(time(NULL));
    int num = (rand() % (MAX_BYTES - MIN_BYTES )) + MIN_BYTES;
    int pageNeeded=(int)ceil((double)num/(double)PAGE_SIZE);
    if(num>0)
        pageNeeded-=1;
    int startFrameNumber =(rand()%(256-pageNeeded-2))+2;
    FILE *ofMemory, *ofPage;
//     ./data/
    char physical_memory[] = "/Users/elainechong/Desktop/201819/Semester2/OP/CA1/data/physical_memory.txt";
    char page_table[]="/Users/elainechong/Desktop/201819/Semester2/OP/CA1/data/page_table.txt";
    ofMemory = fopen(physical_memory, "w");
    ofPage = fopen(page_table, "w");

    fprintf(ofMemory, "Address\t|Frame\t|Content\n");
    fprintf(ofMemory, "-------------------------\n");
    fprintf(ofPage, "Page\t|Frame Number\t|Present\t|check\n");
    fprintf(ofPage, "-----------------------------------\n");
    int increment_page_table_entry = 0;
    for(int i=0;i < ADDEESSABLE_MEMORY;i++){
        if(i==PAGE_SIZE){
            done0=true;
        }
        if (i % noOfPages == 0&& done0)
        {
            noOfFrame++;
        }
        
        if(i>=startFrameNumber*PAGE_SIZE && i < (startFrameNumber*PAGE_SIZE)+num){
            char  c= (rand() % (126-33))+33;
            addresses[i] = c;
            if(i%256==0){
//                addresses[increment_page_table_entry] = (char *) realloc(addresses[increment_page_table_entry], sizeof(short));
                unsigned short present_bit= 1;
                unsigned short pfn = noOfFrame;
                unsigned short page_table_entry =pfn << 8;
                page_table_entry|=present_bit;
                addresses[increment_page_table_entry] =page_table_entry;
                // printf("%x ", addresses[increment_page_table_entry]);
                // char a[sizeof(short)];
//                memcpy(&addresses[increment_page_table_entry], a, sizeof(short)); // copy a to s
                // memcpy(a, &addresses[increment_page_table_entry], sizeof(short));
                // printf("%x ", addresses[increment_page_table_entry]);
                fprintf(ofPage, "0x%02X\t|0x%02X\t\t|1\t%04X\n",increment_page_table_entry,noOfFrame,page_table_entry);
                increment_page_table_entry++;
            }
        }
        
        fprintf(ofMemory, "0x%04X\t|%d\t|%s\n",i,noOfFrame,&addresses[i]);
    }
    for(int y = increment_page_table_entry; y<256;y++){
        addresses[y] = 0x0000;
        fprintf(ofPage, "0x%02X\t|-\t\t|0\n",y);

    }
    fclose(ofPage);
    fclose(ofMemory);
    printf("Your system is ready!\n");
}