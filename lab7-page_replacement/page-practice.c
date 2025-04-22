#include<stdio.h>

void fifo(int pages[],int num_pages,int num_frames){
    int frames[num_frames];
    int head=0;
    int hits=0;
    int faults=0;
    for(int i=0;i<num_frames;i++){
        frames[i]=-1;
    }

    for(int i=0;i<num_pages;i++){
        int found=0;

        for(int j=0;j<num_frames;j++){
            if(frames[j]==pages[i]){
                printf("Page already present (hit)\n");
                found=1;
                hits++;
                break;
            }
        }

        if(found==0){
            frames[head]=pages[i];
            head = (head+1)%num_frames;
            faults++;
        }
    }

    printf("No of hits:%d\nNo of faults: %d\n",hits,faults);
}

void lfu(int pages[],int num_pages,int num_frames){
    int frames[num_frames];
    int freq[num_frames];
    int hits=0;
    int faults=0;
    for(int i=0;i<num_frames;i++){
        frames[i]=-1;
        freq[i]=0;
    }

    for(int i=0;i<num_pages;i++){
        int found=0;

        for(int j=0;j<num_frames;j++){
            if(frames[j]==pages[i]){
                printf("Pagge found in frames (hit)\n");
                hits++;
                freq[j]++;
                found=1;
                break;
            }
        }

        if(found==0){
            int least_freq=1e6;
            int least_freq_idx=-1;
            for(int j=0;j<num_frames;j++){
                if(freq[j]<least_freq){
                    least_freq = freq[j];
                    least_freq_idx=j;
                }
            }

            frames[least_freq_idx] = pages[i];
            freq[least_freq_idx]++;
            faults++;
        }


    }
}

void lru(int pages[],int num_pages,int num_frames){
    int frames[num_frames];
    int curr_time=1;
    int time[num_frames];
    int hits=0;
    int faults=0;
    for(int i=0;i<num_frames;i++){
        frames[i]=-1;
        time[i]=-1;
    }

    for(int i=0;i<num_pages;i++){
        int found=0;

        for(int j=0;j<num_frames;j++){
            if(frames[j]==pages[i]){
                printf("Page already found (hit) \n");
                hits++;
                found=1;
                time[j]=curr_time;
                curr_time++;
                break;
            }
        }

        if(found==0){
            int min_time=1e6;
            int min_idx=-1;
            for(int j=0;j<num_frames;j++){
                if(time[j]<min_time){
                    min_time=time[j];
                    min_idx=j;
                }
            }

            frames[min_idx]=pages[i];
            faults++;
            time[min_idx]=curr_time;
            curr_time++;

            for(int k=0;k<num_frames;k++){
                printf("%d  ",frames[k]);
            }
            printf("\n");
        }
    }
}


// void optimal(int pages[],int num_pages,int num_frames){
//     int frames[num_frames];
//     int hits=0;
//     int faults=0;
//     for(int i=0;i<num_frames;i++){
//         frames[i]=-1;
//     }

//     for(int i=0;i<num_pages;i++){
//         int found=0;

//         for(int j=0;j<num_frames;j++){
//             if(frames[j]==pages[i]){
//                 printf("Page found (hit) \n");
//                 hits++;
//                 found=1;
//                 break;
//             }
//         }

//         if(found==0){
//             int max_dist=-1;
//             int ele=num_pages+1;
//             for(int j=0;j<num_frames;j++){
//                 for(int k=i;k<num_pages;k++){
//                     if(pages[k]==frames[j]){
//                         max_dist = 
//                     }
//                 }
//             }
//         }
//     }
// }

int main(){
    int num_frames;
    printf("Enter the no of frames: ");
    scanf("%d",&num_frames);

    int num_pages;
    printf("Enter the num of pages: ");
    scanf("%d",&num_pages);

    int pages[num_pages];
    printf("Enter the pages:\n");
    for(int i=0;i<num_pages;i++){
        scanf("%d",&pages[i]);
    }

    lru(pages,num_pages,num_frames);
    return 0;
}