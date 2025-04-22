#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int fc; // frame count
    printf("Enter the number of frames available : ");
    scanf("%d", &fc);

    int frame[fc];
    for(int i = 0 ; i<fc ; i++) frame[i] = -1;

    int pg_count; // frame count
    printf("Enter the total number of pages : ");
    scanf("%d", &pg_count);
    
    int q[pg_count+1][1000];
    int qs[pg_count+1];
    for(int i = 0 ; i<=pg_count ; i++) qs[i] = 0;

    int len;
    printf("Enter the length of the reference string :"); scanf("%d", &len);
    printf("Enter the elements : ");

    int ref[len];
    for(int i = 0 ; i<len ; i++)
    {
        int curr;
        scanf("%d", &curr);
        ref[i] = curr;
        q[curr][qs[curr]] = i;
        qs[curr]++;
        // printf("%d#\n", qs[curr]);
    }

    for(int i = 1 ; i<=pg_count ; i++)
    {
        q[i][qs[i]] = (int)(1e9);
        for(int j = 0 ; j<qs[i]-j ; j++)
        {
            int x = q[i][j];
            q[i][j] = q[i][qs[i]-j];
            q[i][qs[i]-j] = x;
        }
        // printf("\n");
    }

    // for(int i = 1 ; i<=pg_count ; i++)
    // {
    //     for(int j = 0 ; j<=qs[i] ; j++)
    //         printf("%d ", q[i][j]);
    //     printf("!\n");
    // }

    for(int i = 0 ; i<len ; i++)
    {

        printf("..............................................\nRequired page : %d\n", ref[i]);

        qs[ref[i]]--;

        for(int j = 0 ; j<fc ; j++)
        {
            if(ref[i] == frame[j])
            {
                printf("Page already available in frame %d\n", j+1);
                goto NEXT_ITR;
            }
        }

        int choice = 0;
        int occur = -1;


        for(int j = 0 ; j<fc ; j++)
        {
            if(frame[j] == -1)
            {
                choice = j;
                break;
            }
            if(occur < q[frame[j]][qs[frame[j]]])
            {
                choice = j;
                occur = q[frame[j]][qs[frame[j]]];
            }
        }

        if(frame[choice] == -1)
        {
            printf("Loading in frame %d\n", choice+1);
            frame[choice] = ref[i];            
        }
        else
        {
            printf("Evicting page %d from Frame %d\n", frame[choice], choice+1);
            printf("Loading in frame %d\n", choice+1);
            frame[choice] = ref[i];            
        }

        NEXT_ITR:;
        // printf("####\n");
    }

    printf("\n\nThe End!\n");

    return 0;
}