#include <stdio.h>
#include "StrList.h"

char* scan_word() {
    char* word = NULL;
    int word_size = 0;
    char ch;

    // Skip leading whitespace characters
    while (scanf("%c", &ch) == 1 && (ch == ' ' || ch == '\n'));

    // Read the word
    do {
        word = realloc(word, (word_size + 1) * sizeof(char));
        if (word == NULL) {
            free(word);
            return NULL;
        }
        word[word_size++] = ch;

        // Read the next character
        if (scanf("%c", &ch) != 1) {
            break;  // Exit the loop if unable to read next character
        }
    } while (ch != ' ' && ch != '\n');

    // Null-terminate the word
    word = realloc(word, (word_size + 1) * sizeof(char));
    if (word == NULL) {
        free(word);
        return NULL;
    }
    word[word_size] = '\0';

    return word;
}

void init_list(StrList* list) {
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
    StrList* clone=StrList_alloc();

    do {
        scanf("%d", &options);

        if(options==1){
                init_list(list);
        }
        else if(options==2){
            int index=-1;
            scanf(" %d",&index);
            char* word=scan_word();
            StrList_insertAt(list,word,index);
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
            printf("%d\n",StrList_count(list,word));
        }
        else if(options==8){
            char* word=scan_word();
            StrList_remove(list,word);
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
            printf("%d\n",StrList_isSorted(list));
        }


       }
        while(options !=0);

    StrList_free(list);
    StrList_free(clone);
    return 0;
}
