/* Assignment 8.2.1:  C6 PA
 * File:    C6_PA_goodma15.c
 * Date:    20 Jan 2016
 * By:      Adam Goodman
 *          goodma15
 * Section: 3, 1:30pm
 * Team:    40 
 *
 * ELECTRONIC SIGNATURE
 * Adam Goodman
 *
 * The electronic signature above indicates that the
 * program submitted for evaluation is my individual work
 * and I have a general understanding of all aspects of 
 * its development and execution.
 *
 * A BRIEF DESCRIPTION OF WHAT THE PROGRAM OR FUNCTION DOES
 * Sort a file of information alphabetically and output
 * that information into another file with only the user
 * inputted number of columns
 */


#include <stdio.h>

//Structure created of type Pokemon
typedef struct Pokemon{
	char head[100];
	char name[100];
	char type[100];
	double height;
	int hp;
	int attack;
	int defense;
	char evo[100];
	
} Pokemon;


int main(void){
	//Variable creation
	FILE *input = NULL;
	FILE *output = NULL;
	char file[31];
	char nextChar;
	int colNum[7];
	char b = 0;
	int n = 0;
	int i, j, k, tempint, m = 0;
	int rows = 0;
	
	//Open files
	printf("Please enter the file name: ");
	scanf("%s", file);
	input = fopen(file, "r");
	output = fopen("C6_PA_goodma15_output.txt", "w");
	
	//Check for broken file input and output
	if (input == NULL) {
		printf("Broken\n");
		return -1;
	}
	if (output == NULL) {
		printf("Broken\n");
		return -1;
	}
	// Finding row number
	b = fgetc(input);
	while (b != EOF){
		if (b == '\n'){
			rows++;
		}
		b = fgetc(input);
	}
	
	//printf("%d\n", rows); //ERROR CHECKING
	//creating array of str of structure type pokemon 
	Pokemon str[rows];
	
	//User input number of columns
	printf("Please enter which columns you would like to access: ");
	scanf("%d%c", &colNum[0], &nextChar);
	n = 1;
	//Error checking for number of columns
	if (nextChar == '\n'){
		n = 1;
	}
	
	if (colNum[0] > 7){
		printf("Invalid column request there are only 7 columns.\n");
		return 0;
	}
	else if (colNum[0] < 1){
		printf("Invalid column request there are no negative columns.\n");
		return 0;
	}
	else {
		while(nextChar != '\n'){
			scanf("%d%c", &colNum[n], &nextChar);
			//printf("column number = %d\n", colNum[n]);
			if (colNum[n] > 7){
				printf("Invalid Column request there are only 7 columns.\n");
				return 0;
			}
			else if (colNum[0] < 1){
				printf("Invalid column request there");
				printf(" are no negative columns.\n");
				return 0;
			}
			n++;
		}
	}
	if (n > 7){
		printf("Invalid column requests, there are only 7 columns.\n");
		return 0;
	}
	// Sort inputted column numbers
	for (i = 0; i < n - 1; i++){
		for (j = i + 1; j < n; j++){
			
			if (colNum[i] > colNum[j]){
				tempint = colNum[i];
				colNum[i] = colNum[j];
				colNum[j] = tempint;
			}
			
			else if(colNum[i] == colNum[j]){
				printf("Invalid column input double number inputted.\n");
				return 0;
			}
			
		}
		
	}
	//rewind the point in the file to the beginning
	rewind(input);
	
	char newline = '\n';
	//scan in headers
	fscanf(input, "%s%s%s%s",str[0].head,str[1].head,str[2].head, str[3].head);
	fscanf(input, "%s%s%s", str[4].head, str[5].head, str[6].head);
	// define an array of pointer of type pokemon
	Pokemon *pointer[rows];
	//define array of pointers to the str
	for (i = 0; i < rows; i++){
		pointer[i] = (str + i);
		
	}
	//define temporary pointer
	Pokemon *temp;
	
	// Scan in all information from file to appropriate structure var
	while(feof(input) != 1){
		fscanf(input, "%s%s%lf", str[m].name, str[m].type, &str[m].height);
		fscanf(input,"%d%d%d",&str[m].hp, &str[m].attack, &str[m].defense);
		fscanf(input, "%s", str[m].evo);
		m++;
	}
	// Alphabetize the rows according to corresponding pointer
	for (j = 0; j < rows - 1; j++){
		for (k = j + 1; k < rows; k++){
		/*
			printf("%s ", pointer[j]->name);
			printf("%s\n", pointer[k]->name);
			g = *pointer[j]->name;
			printf("%d", g);
		*/ //ERROR CHECKING THAT SAVED MY LIFE
			if (*pointer[j]->name) > (*pointer[k]->name)){
				temp = pointer[j];
				pointer[j] = pointer[k];
				pointer[k] = temp;
				//printf("Execute"); // ERROR CHECKING
				//printf("%s", pointer[j]->name); //ERROR CHECKING
				//printf("%s\n", pointer[k]->name); // ERROR CHECKING
			}
		}
	}
	
	// output appropriate headers to specified file
	for (i = -1; i < n + 1; i++){
		if (i == -1) {
			fprintf(output, "%s\t\t", str[0].head);
		}
		else if (colNum[i] == 2) {
			fprintf(output, "%s\t\t", str[1].head);
		}
		else if (colNum[i] == 3) {
			fprintf(output, "%s\t", str[2].head);
		}
		else if (colNum[i] == 4) {
			fprintf(output, "%s\t", str[3].head);
		}
		else if (colNum[i] == 5) {
			fprintf(output, "%s\t", str[4].head);
		}
		else if (colNum[i] == 6) {
			fprintf(output, "%s\t", str[5].head);
		}
		else if (colNum[i] == 7) {
			fprintf(output, "%s\t", str[6].head);
		}
	}
	fprintf(output, "%c", newline);
	// output appropriate columns to specified file
	for (j = 0; j < rows; j++){
		for (i = -1; i < n + 1; i++){
			if (i == -1) {
				fprintf(output, "%s", pointer[j]->name);
			}
			else if (i == n){
				fprintf(output, "%c", newline);
			}
			else if (colNum[i] == 2){
				fprintf(output, "   \t%s", pointer[j]->type);
			}
			else if (colNum[i] == 3){
				fprintf(output, "    \t%.1lf", pointer[j]->height);
			}
			else if (colNum[i] == 4) {
				fprintf(output, "\t%d", pointer[j]->hp);
			}
			else if (colNum[i] == 5) {
				fprintf(output, "\t%d", pointer[j]->attack);
			}
			else if (colNum[i] == 6) {
				fprintf(output, "\t%d", pointer[j]->defense);
			}
			else if (colNum[i] == 7) {
				fprintf(output, "\t%s", pointer[j]->evo);
			}
		}
	}
	
	
	fclose(input);
	fclose(output);
	
	return 0;
}
