// #include "map_lib.h"
#include "functions.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <unistd.h>
void output_page_table()
{
}
void output_physical_memory()
{
}
void set_up_physical_memory(unsigned char *addresses)
{
    print_seprator();
    printf("\tThe process is starting\n");
    print_seprator();

    int no_of_frame = 0;
    srand(time(NULL));
    int num = (rand() % (MAX_BYTES - MIN_BYTES)) + MIN_BYTES;
    int page_needed = (int)ceil((double)num / (double)PAGE_SIZE);
    if (num > 0)
        page_needed -= 1;
    int first_frame_number = (rand() % (256 - page_needed - 2)) + 2;
    FILE *output_physical_memory, *output_page_table;
    char physical_memory[] = "/Users/elainechong/Desktop/201819/Semester2/OP/CA1/memory_visualization/data/physical_memory.txt";
    char page_table[] = "/Users/elainechong/Desktop/201819/Semester2/OP/CA1/memory_visualization/data/page_table.txt";
    output_physical_memory = fopen(physical_memory, "w");
    output_page_table = fopen(page_table, "w");
    fprintf(output_physical_memory, "Address\t|Frame\t|Content\t|Used\n");
    fprintf(output_physical_memory, "--------------------------------\n");
    fprintf(output_page_table, "Page\t|Frame Number\t|Present\t|Valid\n");
    fprintf(output_page_table, "----------------------------------------\n");
    int increment_page_table_entry = 0;
    for (int i = 0; i < PHYSICAL_MEMORY; i++)
    {
        if (i % PAGE_SIZE == 0 && i >= PAGE_SIZE)
        {
            no_of_frame++;
        }
        if (i >= first_frame_number * PAGE_SIZE && i < (first_frame_number * PAGE_SIZE) + num)
        {
            char c = (rand() % (126 - 33)) + 33;
            addresses[i] = c;
            if (i % 256 == 0)
            {
                //0000 0001
                unsigned char present_bit = 0x01;
                //0000 0010
                unsigned char valid_bit = 0x02;
                addresses[increment_page_table_entry] = no_of_frame;

                //0000 0011
                addresses[increment_page_table_entry + 256] = present_bit | valid_bit;
                fprintf(output_page_table, "0x%02X\t|0x%02X\t\t\t|TRUE\t\t|TRUE\n", increment_page_table_entry, no_of_frame);
                increment_page_table_entry++;
            }
        }
        else if (i >= 512)
        {
            addresses[i] = INITIAL_VALUE;
        }
    }
    for (int y = increment_page_table_entry; y < 256; y++)
    {
        addresses[y] = INITIAL_VALUE;
        fprintf(output_page_table, "0x%02X\t|-\t\t\t\t|FALSE\t\t|FALSE\n", y);
    }
    no_of_frame = 0;
    for (int i = 0; i < PHYSICAL_MEMORY; i++)
    {
        if (i % PAGE_SIZE == 0 && i >= PAGE_SIZE)
        {
            no_of_frame++;
        }
        if (i < 512)
        {
            if (addresses[i] != INITIAL_VALUE)
            {
                fprintf(output_physical_memory, "0x%04X\t|%03d\t|0x%04X\t\t|TRUE\n", i, no_of_frame, addresses[i]);
            }
            else
            {
                fprintf(output_physical_memory, "0x%04X\t|%03d\t|-\t\t\t|-\n", i, no_of_frame);
            }
            // printf("pfn %x", addresses[i]);
        }
        else
        {
            if (addresses[i] == INITIAL_VALUE)
            {
                fprintf(output_physical_memory, "0x%04X\t|%03d\t|-\t\t\t|FALSE\n", i, no_of_frame);
            }
            else
            {
                fprintf(output_physical_memory, "0x%04X\t|%03d\t|%c\t\t\t|TRUE\n", i, no_of_frame, addresses[i]);
            }
        }
    }

    fclose(output_page_table);
    fclose(output_physical_memory);
    print_seprator();
    printf("\tYour system is ready!\n");
    print_seprator();
}
void add_extra_entry(unsigned char *addresses)
{
    bool done = false;
    for (int i = 0; i < 256 && !done; i++)
    {
        if (addresses[i] == INITIAL_VALUE)
        {
            addresses[i] = 0x00;
            addresses[i + 1] = 0x01;
            //0000 0000
            unsigned char present_bit = 0x00;
            //0000 0010
            unsigned char valid_bit = 0x02;
            addresses[i + PAGE_SIZE] = valid_bit | present_bit;
            addresses[i + 1 + PAGE_SIZE] = valid_bit | present_bit;
            done = true;
            print_seprator();
            printf("\tThe page number that save in the disk is 0x%02X and 0x%02X\n", i, i + 1);
            print_seprator();
        }
    }
}
void set_up_disk_memory(unsigned char *disk_addresses)
{
    FILE *output_disk_memory;
    char disk_memory[] = "/Users/elainechong/Desktop/201819/Semester2/OP/CA1/memory_visualization/data/disk_memory.txt";
    output_disk_memory = fopen(disk_memory, "w");
    fprintf(output_disk_memory, "Address\t|Frame\t|Content\t|Used\n");
    fprintf(output_disk_memory, "--------------------------------\n");
    for (int i = 0; i < DISK_MEMORY; i++)
    {
        if (i < 512)
        {

            char c = (rand() % (126 - 33)) + 33;

            disk_addresses[i] = c;
            fprintf(output_disk_memory, "0x%02X\t|%d\t\t|%c\t\t\t|TRUE\n", i, (int)i / 256, disk_addresses[i]);
        }
        else
        {
            disk_addresses[i] = INITIAL_VALUE;
            fprintf(output_disk_memory, "0x%02X\t|%d\t\t|%c\t\t\t|FALSE\n", i, (int)i / 256, disk_addresses[i]);
        }
    }
}
void start_system(unsigned char *addresses, unsigned char *disk_addresses, struct map_t *tlb)
{
    while (true)
    {
        unsigned int user_input_address;
        print_seprator();
        printf("Please enter any virtual memory address in hexadecimal form (without 0x)(From 0000-FFFF):");
        scanf("%04X", &user_input_address);
        printf("\n");
        print_seprator();
        unsigned short offset = user_input_address & OFFSET_MASK;
        unsigned char vpn = user_input_address >> 8;

        if (user_input_address > PHYSICAL_MEMORY)
        {
            raise_exception("OUT OF BOUND FAULT");
            raise_exception("Terminating the process");
            sleep(2);
            exit(0);
        }
        // convert number to string []
        int length = snprintf(NULL, 0, "%d", 2);
        char *str = malloc(length + 1);
        snprintf(str, length + 1, "%d", vpn);
        //if the return of tlb has value
        if (map_get(tlb, str) != "")
        {
            print_seprator();
            printf("\tTLB Hit\n");
            //get frame number
            int code = atoi(map_get(tlb, str));
            unsigned int phy_address = code << OFFSET_BITS;
            phy_address |= offset;
            printf("\tThe data store in the address is '%c'  \n", addresses[phy_address]);
            print_seprator();
        }
        else
        {
            raise_exception("\tTLB Miss");
            unsigned char pfn = addresses[vpn];
            unsigned int other_bits = addresses[vpn + PAGE_SIZE];
            unsigned int present_bit = other_bits & PRESENT_BIT_MASK;
            //000 0001 or 000 0001
            unsigned int valid_bit = other_bits >> VALID_BIT_SHIFT;
            //    reconstruct
            unsigned int phy_address = pfn << ADDRESS_SHIFT;
            phy_address |= offset;
            if (valid_bit == FALSE_BIT)
            {
                raise_exception(SEGMENTATION_FAULT);
            }
            else
            {
                if (present_bit == TRUE_BIT)
                {

                    printf("\tUpdating TLB\n");
                    char str2[10];
                    sprintf(str2, "%d", pfn);
                    // set frame number
                    map_set(tlb, str, str2);

                    print_seprator();
                    printf("\tThe virtual page number is 0x%02X\n", vpn);
                    printf("\tThe page frame number is 0x%02X\n", pfn);
                    printf("\tThe physical address is 0x%04X\n", phy_address);
                    printf("\tThe data store in the address is '%c'\n", addresses[phy_address]);
                    print_seprator();
                }
                else
                {

                    //present_bit == FALSE_BIT
                    //page fault exception
                    raise_exception(PAGE_FAULT);
                    //swap
                    swap_empty(addresses, disk_addresses, pfn, vpn);
                }
            }
        }
        free(str);
    }
}

void print_seprator()
{
    printf("-------------------------------------------------------------------\n");
}

//page-fault handler
void swap_empty(unsigned char *addresses, unsigned char *disk_addresses, unsigned char pfn, unsigned char vpn)
{
    print_seprator();
    printf("\tPerforming swapping\n");
    print_seprator();
    unsigned char new_pfn = '-';
    bool done = false;
    for (int i = 512; i < PHYSICAL_MEMORY && !done; i++)
    {
        if (addresses[i] == INITIAL_VALUE)
        {
            for (int j = 0; j < 256; j++)
            {
                addresses[i + j] = disk_addresses[pfn * 256 + j];
            }
            new_pfn = (int)i / 256;
            i = PHYSICAL_MEMORY;
            done = true;
        }
    }
    addresses[vpn] = new_pfn;
    addresses[vpn + 256] = 0x01;
}

struct map_t *map_create()
{
    struct map_t *m;
    m = (struct map_t *)malloc(sizeof(struct map_t));
    m->name = NULL;
    m->value = NULL;
    m->nxt = NULL;
    return m;
}

void map_set(struct map_t *m, char *name, char *value)
{
    struct map_t *map;

    if (m->name == NULL)
    {
        m->name = (char *)malloc(strlen(name) + 1);
        strcpy(m->name, name);
        m->value = (char *)malloc(strlen(value) + 1);
        strcpy(m->value, value);
        m->nxt = NULL;
        return;
    }
    for (map = m;; map = map->nxt)
    {
        if (!strcasecmp(name, map->name))
        {
            if (map->value != NULL)
            {
                free(map->value);
                map->value = (char *)malloc(strlen(value) + 1);
                strcpy(map->value, value);
                return;
            }
        }
        if (map->nxt == NULL)
        {
            map->nxt = (struct map_t *)malloc(sizeof(struct map_t));
            map = map->nxt;
            map->name = (char *)malloc(strlen(name) + 1);
            strcpy(map->name, name);
            map->value = (char *)malloc(strlen(value) + 1);
            strcpy(map->value, value);
            map->nxt = NULL;
            return;
        }
    }
}

char *map_get(struct map_t *m, char *name)
{
    struct map_t *map;
    // printf("Size %lu ", sizeof(m));
    for (map = m; map != NULL && map->name != NULL; map = map->nxt)
    {
        if (!strcasecmp(name, map->name))
        {
            return map->value;
        }
    }
    return "";
}

void raise_exception(char *fault)
{
    print_seprator();
    printf("\n");
    printf("\t%s\n", fault);
    printf("\n");
    print_seprator();
}