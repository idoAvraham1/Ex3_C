#include <stdio.h>
#include "StrList.h"
#include <string.h>
#include <ctype.h>

char* scan_word() {
    char* word = NULL;
    int word_size = 0;
    char ch;

    // Skip leading whitespace characters
    while (scanf("%c", &ch) == 1 && isspace(ch)){
    }
    // Read the word
     while(!isspace(ch)){
        word = realloc(word, (word_size + 1) * sizeof(char));
        if(!word){
            free(word);
            return NULL;}
        word[word_size++] = ch;

        // Read the next character
        if (scanf("%c", &ch) != 1) {
            break;  // Exit the loop if unable to read next character
        }
    } 
    // Null-terminate the word
    word = realloc(word, (word_size + 1) * sizeof(char));
    if(!word) {
        free(word);
        return NULL;
    }
    word[word_size] = '\0';

    return word;
}
void init_list(StrList* list){
    int num_of_words;
    scanf(" %d", &num_of_words);
    getchar();
    for (int i = 0; i < num_of_words; i++) {
        char* word = scan_word();
        if (word == NULL) {
            return;
        }
        StrList_insertLast(list, word);
        free(word);
    }
}



int main() {

    int options;
    StrList* list=StrList_alloc();

    do {
        scanf("%d", &options);

        if(options==1){
                init_list(list);
        }
        else if(options==2){
            int index;
            scanf("%d",&index);
            char* word=scan_word();
            StrList_insertAt(list,word,index);
            free(word);
        }
        else if(options==3){
            StrList_print(list);
        }
        else if(options==4){
            printf("%zu\n",StrList_size(list));
        }
        else if(options==5){
            int index;
            scanf("%d",&index);
            StrList_printAt(list,index);
        }
        else if(options==6){
            printf("%d\n",StrList_printLen(list));
        }
        else if(options==7){
            char* word=scan_word();
            int n=StrList_count(list,word);
            printf("%d\n",n);
            free(word);
        }
        else if(options==8){
            char* word=scan_word();
            StrList_remove(list,word);
            free(word);
        }
        else if(options==9){
            int index;
            scanf("%d",&index);
            StrList_removeAt(list,index);
        }
        else if(options==10){
            StrList_reverse(list);
        }
        else if(options==11){
            int i=0;
            size_t original_size= StrList_size(list);
            while(i< original_size){
                StrList_removeAt(list,0);
                i++;
            }
        }
        else if(options==12){
            StrList_sort(list);
        }
        else if(options==13){
            if(StrList_isSorted(list)){
                printf("true\n");
            }
            else{ printf("false\n");}
        }


       }
        while(options !=0);

    StrList_free(list);

    return 0;
}
