//Praneeth Sangani (PRS79)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>

//The colors that the user can pick from
typedef enum 
{
	Red,
	Green,
	Blue,
	Yellow,
	Purple,
	Orange
} Color; 

//Prints out the color corresponding to the number from the enum
void get_color(Color c)
{
	switch(c)
	{
		case Red: printf("Red "); 		  	break; 
		case Green: printf("Green "); 	  	break;
		case Blue: printf("Blue "); 	 	break;
		case Yellow: printf("Yellow ");  	break;
		case Purple: printf("Purple ");  	break;
		case Orange: printf("Orange ");  	break;
		default: printf("Not a color "); 	break;
	}
}//End get_color

//Returns a random number from [low_value, high_value]
int random_range(int low_value, int high_value)
{
	return rand() % (high_value - low_value + 1) + low_value; 
}//End random_range

//Asks the user how many colors they want to play with (3-6)
int ask_num_of_colors (char* input)
{
	int num_of_colors; 
	while((num_of_colors < 3) || (num_of_colors > 6))
	{
		printf("How many colors do you want?\n3 colors: { red, green, blue } \n4 colors: { red, green, blue, yellow }\n5 colors: { red, green, blue, yellow, purple }\n6 colors: { red, green, blue, yellow, purple, orange } :");
		fgets(input, 20, stdin);
		input[strlen(input) - 1] = '\0';
		num_of_colors = atoi(input);
	}	
	return num_of_colors;
}//End ask_num_of_colors

//Converts the letter inputed by the user to colors. 
int char_to_color(char c)
{
	switch(c)
	{
		case 'r': case 'R': return Red; 
		case 'g': case 'G': return Green; 
		case 'b': case 'B': return Blue; 
		case 'y': case 'Y': return Yellow; 
		case 'p': case 'P': return Purple; 
		case 'o': case 'O': return Orange; 
		default: return -1; //invalid color 
	}
}//End char to color

//Checks to see how many colors the user guessed are in the correct spot
int check_black_pegs(int* key, char* input)
{
	int black_pegs = 0; 
	for(int i = 0; i < 4; i++)
	{
		if(key[i] == char_to_color(input[i]))
			black_pegs++; 
	}
	return black_pegs; 
}//End check_black_pegs

//Checks to see how many colors the user guessed are contained in the key
int check_white_pegs(int* key, char* input)
{
	int white_pegs = 0; 
	int repeats[4] = {1, 1, 1, 1}; 
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			if(key[i] == char_to_color(input[j]) && repeats[j] != 0)
			{
				repeats[j] = 0; 
				++white_pegs; 
				break;
			}
		}
	}
	return white_pegs; 
}//End check_white_pegs

//Ensures that the player's guess is a valid guess. returns 1 if it is valid. Returns 0 if invalid. 
int validate_guess(char* input, int num_of_colors)
{
	for(int i = 0; i < 4; i++)
	{
		if(char_to_color(input[i]) >= num_of_colors)
			return 0; 
	}
	return 1; 
}//End validate_guess

//Asks the player to guess the key and ensures that their guess is valid
void ask_for_guess(char* input, int num_of_guesses, int num_of_colors)
{
	printf("Enter your guess, you have %d guesses left: ", num_of_guesses);
	fgets(input, 20, stdin);
	input[strlen(input) - 1] = '\0';

	int valid_guess = validate_guess(input, num_of_colors);

	while(strlen(input) != 4 || valid_guess != 1)
	{
		printf("Entered an invalid guess. Please try again, you have %d guesses left: ", num_of_guesses);
		fgets(input, 20, stdin);
		input[strlen(input) - 1] = '\0'; 
		valid_guess = validate_guess(input, num_of_colors);
	}
}//End ask for guess


//Message outputed when the player Wins. 1 = play again   0 = stop playing 
int win_message(char* input)
{
	printf("You Win! Do you want to play again? Y/N: ");
	fgets(input, 20, stdin);
	input[strlen(input) - 1] = '\0';
	if(input[0] == 'Y' || input[0] == 'y')
		return 1; 
	return 0; 
}//End win_message 

//Message outputed when the player loses. 1 = play again   0 = stop playing 
int lose_message(char* input)
{
	printf("\nYou Lost :(. Do you want to play again? Y/N: ");
	fgets(input, 20, stdin);
	input[strlen(input) - 1] = '\0';
	if(input[0] == 'Y' || input[0] == 'y')
		return 1; 
	return 0; 
}//End lose_message

int main()
{
	int play_again = 1; //While play_again == 1, the game will start over. 
	while(play_again == 1)
	{
		srand((unsigned int)time(NULL)); // Seed the random generator  
		char input[20]; //To get input from player
		int num_of_colors = ask_num_of_colors(input);	//Get number of color that user wants to play (3-6)
		int black_pegs = 0; //Number of black pegs
		int white_pegs = 0;	//Number of white pegs
	 	int key[num_of_colors]; // This is the answer that the user is trying to guess

	 	//Creates the answer that the player will try to guess 
		for(int i = 0; i < 4; i++)
		{
			Color c = random_range(0, num_of_colors - 1); 
			key[i] = c; 
		}

		for(int num_of_guesses = 10; num_of_guesses > 0; num_of_guesses--)
		{
			ask_for_guess(input, num_of_guesses, num_of_colors);

			black_pegs = check_black_pegs(key, input); 
			white_pegs = check_white_pegs(key, input) - black_pegs; //Subtract black_pegs so there arent repeats between white and black peg 

			//If this is true the user has won
			if(black_pegs == 4)
			{
				play_again = win_message(input);
				break; 
			}
			else
				printf("\nYou have %d black pegs and %d white pegs\n", black_pegs, white_pegs); //Tell them how accurate their guess was
		}
			//If this is true then the player used up all 10 tries and was unable to get it 
			if(black_pegs != 4)
			{		
				printf("The right answer was: ");
				for (int i = 0; i < 4; i++)
					get_color(key[i]);
				play_again = lose_message(input); 
			}
	}
}//End Main
