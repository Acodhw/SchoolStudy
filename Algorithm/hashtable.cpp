#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DEFAULT_HASHMAX 31
#define MAX_LOADFACTOR 0.7

char ** hashTable;
int hashNumList[20] = {67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127,  131, 139, 149, 151, 157, 163};

void hashFunc(char * data, int maxCount){
        int i, sum = 0; 
        for(i = 0; i < strlen(data); i++){
                sum += (data[i] * hashNumList[i]);
        }
        int hash = (sum-2144) % maxCount;
        i = 0;

        //Quadratic Probing
        while(strcmp(hashTable[hash], "")){
                hash = (hash + (i * i)) % maxCount;
                i++;    
        }
        strcpy(hashTable[hash], data);
}

int main(int argc, char* argv[]){
        srand(time(NULL));
        
        int count;
        count = atoi(argv[1]);
        
        if(count == 0){
                printf("Error : Count is zero, or is not integer.");
                return 0;
        }

        int i, j;

        char **strlist = (char**)malloc(count * sizeof(char*));
        for(i = 0; i < count; i++) strlist[i] = malloc(22 * sizeof(char));

        for(i = 0; i < count; i++){
                int len = (rand() % 20) + 1;
                for(j = 0; j < len; j++){
                        strlist[i][j] = (rand() % 95) + 32;
                }
                strlist[i][len] = '\0';
        }
        
        printf("Input Data : \n");

        for(i = 0; i < count; i++) printf("%s\n", strlist[i]);
        
        int maxHashCount = 0;
        while(maxHashCount * MAX_LOADFACTOR <= count){
                if(maxHashCount == 0) maxHashCount = DEFAULT_HASHMAX;
                else maxHashCount = maxHashCount * 2 - 1; 
        }
        hashTable = (char**)malloc(maxHashCount * sizeof(char*));
        for(i = 0; i < maxHashCount; i++){ 
                hashTable[i] = (char*)malloc(22 * sizeof(char));        
                strcpy(hashTable[i],"");
        }
        
        for(i = 0; i < count; i++)
                hashFunc(strlist[i], maxHashCount);
        
        printf("\nHash : \n");

        for(i = 0; i < maxHashCount; i++) printf("Table index %d => %s\n", i, hashTable[i]);
        
        for(i = 0; i < count; i++) free(strlist[i]);
        for(i = 0; i < maxHashCount; i++) free(hashTable[i]);
        free(strlist);
        free(hashTable);
        return 0;
}