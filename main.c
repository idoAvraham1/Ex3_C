#include <stdio.h>
#include "StrList.h"
#include <string.h>
#include <ctype.h>
// Function to scan a word from the input stream
// Parameters:
//   - input: FILE pointer representing the input stream
//   - size: Initial size for memory allocation
// Returns:
//   - A dynamically allocated string containing the scanned word
char* scan_word(FILE* input, size_t size) {
    char* word = NULL;
    size_t word_size = 0;
    int ch;

    // Skip leading whitespace characters
    while ((ch = fgetc(input)) != EOF && isspace(ch)) {
    }

    // Read the word
    while (ch != EOF && !isspace(ch) && ch != '\n') {
        word = realloc(word, (word_size + 1) * sizeof(char));
        if (!word) {
            fprintf(stderr, "Error: Memory allocation failure\n");
            exit(EXIT_FAILURE);
        }
        word[word_size++] = ch;

        // Read the next character
        ch = fgetc(input);
    }

    // Null-terminate the word
    word = realloc(word, (word_size + 1) * sizeof(char));
    if (!word) {
        fprintf(stderr, "Error: Memory allocation failure\n");
        exit(EXIT_FAILURE);
    }
    word[word_size] = '\0';

    return word;
}
// Function to initialize a StrList with words scanned from the input stream
// Parameters:
//   - list: Pointer to the StrList to be initialized
// Returns:
//   - None
void init_list(StrList* list){
    int num_of_words;
    scanf(" %d", &num_of_words);
     getchar();
    for (int i = 0; i < num_of_words; i++) {
        char* word = scan_word(stdin,10);
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
            char* word=scan_word(stdin,10);
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
            char* word=scan_word(stdin,10);
            int n=StrList_count(list,word);
            printf("%d\n",n);
            free(word);
        }
        else if(options==8){
            char* word=scan_word(stdin,10);
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
