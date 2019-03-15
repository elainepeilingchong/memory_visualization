#include "functions.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
int calculateBitsRequired()
{
    int pageSizeBit = (int)(log((double)PAGE_SIZE) / log((double)2));
    return SYS_BITS - pageSizeBit;
}
char *set_up_memory()
{
    int noOfFrame = 0;
    int VPNBits = calculateBitsRequired();
    int offset = SYS_BITS - VPNBits;
    char *addresses = malloc(sizeof(char) * ADDEESSABLE_MEMORY);
    int noOfPages = ADDEESSABLE_MEMORY / PAGE_SIZE;
    srand(time(NULL));
    int num = (rand() % (MAX_BYTES - MIN_BYTES)) + MIN_BYTES;
    int pageNeeded = (int)ceil((double)num / (double)PAGE_SIZE);
    if (num > 0)
        pageNeeded -= 1;
    int startFrameNumber = (rand() % (256 - pageNeeded - 2)) + 2;
    FILE *ofMemory, *ofPage;
    char physical_memory[] = "/Users/elainechong/Desktop/201819/Semester2/OP/CA1/memory_visualization/data/physical_memory.txt";
    char page_table[] = "/Users/elainechong/Desktop/201819/Semester2/OP/CA1/memory_visualization/data/page_table.txt";
    ofMemory = fopen(physical_memory, "w");
    ofPage = fopen(page_table, "w");

    fprintf(ofMemory, "Address\t|Frame\t|Content\n");
    fprintf(ofMemory, "-------------------------\n");
    fprintf(ofPage, "Page\t|Frame Number\t|Present\n");
    fprintf(ofPage, "-----------------------------\n");
    int increment_page_table_entry = 0;
    for (int i = 0; i < ADDEESSABLE_MEMORY; i++)
    {
        if (i % noOfPages == 0 && i >= PAGE_SIZE)
        {
            noOfFrame++;
        }
        if (i >= startFrameNumber * PAGE_SIZE && i < (startFrameNumber * PAGE_SIZE) + num)
        {
            char c = (rand() % (126 - 33)) + 33;
            addresses[i] = c;
            if (i % 256 == 0)
            {
                unsigned char present_bit = 0x01;
                unsigned short pfn = noOfFrame;
                // // unsigned short page_table_entry = pfn << 8;
                // // page_table_entry |= present_bit;
                addresses[increment_page_table_entry] = pfn;
                addresses[increment_page_table_entry + 256] = present_bit;
                fprintf(ofPage, "0x%02X\t|0x%02X\t\t|%x\n", increment_page_table_entry, noOfFrame, present_bit);
                increment_page_table_entry++;
            }
        }
    }
    noOfFrame = 0;
    for (int i = 0; i < ADDEESSABLE_MEMORY; i++)
    {
        if (i % noOfPages == 0 && i >= PAGE_SIZE)
        {
            noOfFrame++;
        }
        if (i < 512)
        {

            fprintf(ofMemory, "0x%04X\t|%d\t|0x%x\n", i, noOfFrame, addresses[i]);
        }
        else
        {
            if (addresses[i] == NULL)
            {
                fprintf(ofMemory, "0x%04X\t|%d\t|-\n", i, noOfFrame);
            }
            else
            {
                fprintf(ofMemory, "0x%04X\t|%d\t|%c\n", i, noOfFrame, addresses[i]);
            }
        }
    }
    for (int y = increment_page_table_entry; y < 256; y++)
    {
        addresses[y] = 0x0000;
        fprintf(ofPage, "0x%02X\t|-\t\t|0\n", y);
    }
    fclose(ofPage);
    fclose(ofMemory);
    printf("Your system is ready!\n");
    return addresses;
}
void start_system(char *addresses)
{
    unsigned int offset_mask = 0x00FF;

    unsigned int user_input_address;
    while (true)
    {
        printf("Please enter any virtual memory address in hexadecimal form (without 0x):");
        scanf("%04X", &user_input_address);
        printf("\n");

        unsigned short offset = user_input_address & offset_mask;

        unsigned int vpn = user_input_address >> 8;
        unsigned int pfn = addresses[vpn];
        unsigned int present_bit = addresses[vpn + 256];
        unsigned short pte = pfn << 8;
        pte |= present_bit;
        //extract value
        if (present_bit == 0x01)
        {
            //    reconstruct
            unsigned int phy_address = pfn << OFFSET_BITS;
            phy_address |= offset;
            printf("phy_address %x\n", phy_address);
        }
        else
        {
            unsigned int dfn = addresses[vpn] >> 8;
            //page fault exception
            printf("Page Fault exception!!\n");
            //swap
        }
    }
}
