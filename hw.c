#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
char *search(char *ptr, char *pat, int mode);
void replace(char *str, char *replacement, char *ptr, int patlen);
int main(){
	char input[4096];
	char article[4096];
	char pattern[4096];
	char replacement[4096];
	int flag = 0;
	char *ptr;
	char *ptr1;
	fgets(input, 4096, stdin);
	int i = 0;
	int isString = 0;
	while (input[i] != '\0'){
		if (isString == 0){
				if (input[i] == '-' || isalnum(input[i]) != 0){
					isString = 1;
					ptr = input + i;
				}
				else if (input[i] != ' ' && input[i] != '\n'){
					flag = 0;
					break;
				}
				i++;
				continue;
			}
		else {
			if (input[i] != '-' && isalnum(input[i]) == 0){
				if (input[i] == ' ' || input[i] == '\n') {
					isString = 0;
					input[i] = '\0';
					flag++;
					switch (flag) { 
    						case 1: 
							strcpy(pattern, ptr);
        						break; 
    						case 2: 
        						strcpy(replacement, ptr); 
        						break;
        					case 3: 
        						if (strcmp(ptr, "-i") != 0)
								flag ++; 
        						break;  
					}
				}
				else {
					flag = 0;
					break;
				}
			}
			i++;
			continue;
		}
	}
	if (flag != 2 && flag != 3){
		printf("The input  format: string1 string2 [parameter]");
		exit(0);
	}
	while(fgets(article, 4096, stdin) != NULL){
		ptr = article;
		int isString = 0;
		int i = 0;
		while (article[i] != '\0'){
			if (isString == 0){
				if (article[i] == '-' || isalnum(article[i]) != 0){
					isString = 1;
					ptr = article + i;
				}
				i++;
				continue;
			}
			else {
				if (article[i] != '-' && isalnum(article[i]) == 0){
					isString = 0;
					article[i] = '\0';
					ptr1 = search(ptr, pattern, flag);
					if (ptr1 != NULL)
						replace(ptr, replacement, ptr1, strlen(pattern));
				}
				i++;
				continue;
			}
		}
	}
	return 0;
}
char *search(char *ptr, char *pat, int mode){
	char *ptr1 = NULL;
	if (mode == 2){
		ptr1 = strstr(ptr, pat);
	}
	else {
		char ptrcpy[4096];
		char patcpy[4096];
		strcpy(ptrcpy, ptr);
		strcpy(patcpy, pat);
		int i = 0;
		while (ptrcpy[i] != '\0'){
			ptrcpy[i] = tolower(ptrcpy[i]);
			i++;
		}
		i = 0;
		while (patcpy[i] != '\0'){
			patcpy[i] = tolower(patcpy[i]);
			i++;
		}
		if (strstr(ptrcpy, patcpy) != NULL){
			ptr1 = ptr + (strstr(ptrcpy, patcpy) - ptrcpy);
		}
	}
	return ptr1;
}
void replace(char *str, char *replacement, char *ptr, int patlen){
	char temp[4096];
	char temp1[4096];
	strcpy(temp, ptr + patlen);
	strcpy(temp1, str);
	strcpy(temp1 + (ptr - str), replacement);
	strcat(temp1, temp);
	printf("%s\n", temp1);
	return;
}

