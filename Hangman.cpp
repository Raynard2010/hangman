#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

struct wordData{
	char word[11];
	char clue[20];
};

void printLivesAndHangman(int nlives){
	printf("Lives: ");
	
	for(int i = 1; i <= nlives; i++) printf("\3");
	
	if(nlives == 0) printf("You lose! :(");

	printf("\n\n");
	
	printf("+----+\n");
	printf("|");

	if(nlives <= 6) printf("    |");
	printf("\n");	
	printf("|");
	
	if(nlives <= 5) printf("    O");
	printf("\n");	
	printf("|");
	
	if(nlives <= 4) printf("   /");
	
	if(nlives <= 3) printf("|");
	
	if(nlives <= 2) printf("\\");
	printf("\n");	
	printf("|");	
	
	if(nlives <= 1) printf("   /");

	if(nlives == 0) printf(" \\");
	printf("\n");
	
	printf("|");	
	printf("\n\n");		
}

int main(){
	struct wordData data[101];

	int idx = 0;
	
	FILE *fptr;
	
	fptr = fopen("wordlist.csv", "r");
	
	fscanf(fptr, "Word,Clue\n");
	
	while(!feof(fptr)){
		fscanf(fptr, "%[^,],%[^\n]\n", &data[idx].word, &data[idx].clue);
		idx++;
	}

	int nidx = idx - 1;
	
	printf("Welcome to Hangman!!!");
	sleep(3);	
	system("cls");
	
	bool didntInputANumber = 1;

	printf("How many times do you want to play? (Input a number)\n");
	
	int nplay;
	
	scanf("%d", &nplay);
	getchar();
	
	system("cls");
	
	printf("Have fun!!!");
	sleep(3);
	system("cls");
		
	srand(time(0));
	
	int wordNumber[101];

	for(int i = 0; i < nplay; i++) wordNumber[i] = rand() % (nidx + 1);
		
	for(int i = 0; i < nplay; i++){
		didntInputANumber = 0;
		
		printf("GAME %d\n", i + 1);

		bool finished = 0;
		
		char guessedLetters[27] = "";

		int len = strlen(data[wordNumber[i]].word);
		
		char answer[11] = "A";
		
		for(int j = 0; j < len; j++) answer[j] = '_';
		
		int nattempt = 0;
		
		int nlives = 7;

		while(nlives > 0){			
			printLivesAndHangman(nlives);
			printf("Clue: %s (%d letters)\n\n", data[wordNumber[i]].clue, len);

			char letter[11];
			
			for(int j = 0; j < len; j++) printf("%c ", answer[j]);
			printf("\n\n");
			
			if(strcmp(answer, data[wordNumber[i]].word) == 0) finished = 1;
			
			int lenGuessedLetters = strlen(guessedLetters);
			
			printf("Attempted letters:\n");
			for(int j = 0; j < lenGuessedLetters; j++) printf("%c", guessedLetters[j]);
			printf("\n\n");
			
			if(finished){
				printf("\n\nYOU WIN!!!");
				sleep(3);
				system("cls");
				break;
			}
			
			if(!finished){
				printf("Input the letter you wanna try:\n");
				scanf("%s", &letter);
				getchar();
				printf("\n");
			}

			if(strlen(letter) > 1){
				printf("Please input one letter!");
				sleep(3);
				system("cls");
				
				printf("GAME %d\n", i + 1);			
				continue;
			}

			if((letter[0] < 'A' || letter[0] > 'Z') && (letter[0] < 'a' || letter[0] > 'z')){
				printf("Please input a letter!");
				sleep(3);
				system("cls");
				
				printf("GAME %d\n", i + 1);			
				continue;
			}
						
			if(letter[0] >= 'a' || letter[0] <= 'z') letter[0] = letter[0] - 32;
			
			bool guessedSameLetter = 0;
						
			if(lenGuessedLetters == 0) strcat(guessedLetters, letter);
			else{
				for(int j = 0; j < lenGuessedLetters; j++){
					if(letter[0] == guessedLetters[j]){
						printf("You've tried this letter!");
						sleep(3);
						system("cls");
						guessedSameLetter = 1;
				
						printf("GAME %d\n", i + 1);			
						break;
					}
				}
			}
	
			if(guessedSameLetter) continue;
			else{
				guessedLetters[nattempt] = letter[0];
				nattempt++;
			}

			bool letterInWord = 0;
			
			for(int j = 0; j < len; j++){
				if(answer[j] == '_'){
					if(data[wordNumber[i]].word[j] == letter[0]){
						answer[j] = letter[0];
						letterInWord = 1;
					}
				}
			}
			
			if(letterInWord) printf("The letter is in the word!");
			else{
				printf("The letter is not in the word!");
				nlives--;
			}

			sleep(3);
			system("cls");
			printf("GAME %d\n", i + 1);
		}		
		
		if(nlives == 0){
			printLivesAndHangman(nlives);
			printf("Clue: %s (%d letters)\n\n", data[wordNumber[i]].clue, len);
						
			for(int j = 0; j < len; j++) printf("%c ", answer[j]);
			printf("\n\n");
			
			int lenGuessedLetters = strlen(guessedLetters);

			printf("Attempted letters:\n");
			for(int j = 0; j < lenGuessedLetters; j++) printf("%c", guessedLetters[j]);
			printf("\n\n");
			
			printf("Correct word:\n");
			printf("%s\n", data[wordNumber[i]].word);
						
			printf("\nYou lose!!!");

			sleep(3);
			system("cls");
			continue;
		}		
	}
	
	if(didntInputANumber) printf("Please input a number!");
	else printf("Thank you for playing!!!");
	
	fclose(fptr);
	return 0;
}
