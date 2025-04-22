#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#define INF ((int)(1e9))

int main()
{
    int fc; // frame count
    printf("Enter the number of frames available : ");
    scanf("%d", &fc);

    int pg_count; // frame count
    printf("Enter the total number of pages : ");
    scanf("%d", &pg_count);
    
    int pginfo[pg_count+1];
    for(int i = 0 ; i<=pg_count ; i++) pginfo[i] = INF;


    int time = 0;
    while(1)
    {
        time++;
        printf(".....................................................................\n");
        printf("Pages in main memory currently : ");
        int counter = 0;
        int fi = 0;
        for(int i = 1 ; i<=pg_count ; i++)
        {
            if(pginfo[i] != INF)
            {
                counter++;
                if(pginfo[fi] > pginfo[i]) fi = i;
                printf("%d ", i);
            }
        }
        printf("\n");
        printf("Enter the page number (-1 to terminate) : ");
        int pg; scanf("%d", &pg);
        
        if(pg == -1) break;

        if(pginfo[pg] != INF)
        {
            printf("Page available in memory already\n");
            pginfo[pg] = time;
            continue;
        }
        
        if(counter >= fc)
        {
            pginfo[fi] = INF;
            printf("Evicting page-%d...\n", fi);
        }
        printf("Loading pg-%d...\n", pg);
        pginfo[pg] = time;
    }

    printf("\n\n");
    printf("The End!\n");

    return 0;
}