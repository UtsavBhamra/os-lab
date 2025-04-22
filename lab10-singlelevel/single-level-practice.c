#include<stdio.h>
#include<string.h>

#define MAX_FILES 100
#define MAX_FILENAME_LEN 100

char directory[MAX_FILES][MAX_FILENAME_LEN];
int filecount=0;

void createFile(){
    if(filecount>=MAX_FILES){
        printf("file limit exceeded\n");
    }

    char filename[MAX_FILENAME_LEN];
    scanf("%s",filename);

    for(int i=0;i<filecount;i++){
        if(strcmp(directory[i],filename)==0){
            printf("Filename already exists\n");
            return;
        }
    }

    strcpy(directory[filecount],filename);
    filecount++;
    printf("File %s created successfully\n",filename);
}

void deleteFile(){
    if(filecount==0){
        printf("No files to delete\n");
        return;
    }

    char filename[MAX_FILENAME_LEN];
    scanf("%s",filename);

    int found=0;
    for(int i=0;i<filecount;i++){
        if(strcmp(directory[i],filename)==0){
            found=1;
            for(int j=i;j<MAX_FILES;j++){
                strcpy(directory[i],directory[i+1]);
            }
            filecount--;
            printf("File with name %s deleted successfully\n",filename);
            return;
        }
    }

    if(found==0){
        printf("Filename not found\n");
        return;
    }
}

void searchfile(){
    if(filecount==0){
        printf("No files in directory\n");
        return;
    }

    char filename[MAX_FILENAME_LEN];
    scanf("%s",filename);

    for(int i=0;i<filecount;i++){
        if(strcmp(directory[i],filename)==0){
            printf("File was found in directory\n");
            return;
        }
    }

    printf("File was not found in directory\n");
}

void displayfiles(){
    if(filecount==0){
        printf("No files in directory\n");
        return;
    }

    printf("Files in the directory:\n");
    for(int i=0;i<filecount;i++){
        printf("%s  ",directory[i]);
    }
    printf("\n");
}

int main(){

    while(1){
        int choice;
        printf("Enter your choice: ");
        scanf("%d",&choice);

        switch(choice){
            case 1: 
                createFile();
                break;
            case 2:
                deleteFile();
                break;
            case 3:
                searchfile();
                break;
            case 4:
                displayfiles();
                break;
            default:
                printf("invalid choice\n");
                break;
        }
    }
    return 0;
}