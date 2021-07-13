#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int card_number(char);
int deal_cards();
int hand_value(int[], int);
int gamestart(int[], int[]);
int display_hand(int[], int);
int main()

{
	int playerhand[12] = {0}, dealerhand[12] = {0};
	int dwin = 0, pwin = 0;
	char command = 'h', replay = 'a';
	printf("\t\t*********************************\n\t\t*\t\t\t\t*\n");
	printf("\t\t*\t   GAME COMMANDS\t*\n\t\t*\t\t\t\t*\n");
	printf("\t\t*\th : Take another card\t*\n");
	printf("\t\t*\ts : Dealer's play\t*\n");
	printf("\t\t*\tq : quit hand\t\t*\n\t\t*\t\t\t\t*\n");
	printf("\t\t*********************************\n");
	while(replay != 'q')
	{
		srand(time(0));
		int playercards = 2, dealercards = 2, hand1 = 0, hand2 = 0, stop = 0;
		command = 'h';
		gamestart(playerhand, dealerhand);
		
		while(command == 'h')
		{
			printf("\nPlayer's hand:");
			display_hand(playerhand, playercards);
			hand1 = hand_value(playerhand, playercards);//hand1 is sum of all cards of player
			if (hand1 == 21)
			{
				if (hand2 == 21)
				{
					printf("\nDealer's hand:");
					display_hand(dealerhand, dealercards);
					hand2 = hand_value(dealerhand, dealercards);//hand2 is sum of all cards of dealer
					if (dealercards < playercards)
					{
						printf("\nDealer Wins");
						dwin++;
						stop = 1;
						break;
					}
					else if (dealercards > playercards)
					{
						printf("\nPlayer Wins");
						pwin++;
						stop = 1;
						break;
					}
					else
					{
						printf("\nIt's a push");
						stop = 1;
						break;
					}
				}
				else if (hand2 >= 17)
				{
					printf("\nDealer's hand:");
					display_hand(dealerhand, dealercards);
					hand2 = hand_value(dealerhand, dealercards);//hand2 is sum of all cards of dealer
					printf("\nPlayer Wins");
					pwin++;
					stop = 1;
					break;
				}
				else
				{
					printf("\nDealer's hand: ");
					while (hand2 < 17)
					{
						dealercards++;
						dealerhand[dealercards - 1] = deal_cards();
						hand2 = hand_value(dealerhand, dealercards);
					}
					display_hand(dealerhand, dealercards);
					printf("\nPlayer Wins");
					pwin++;
					stop = 1;
					break;
				}
			}
			else
			{
				printf("\nDealer's hand:");
				display_dealer(dealerhand, dealercards);
				hand2 = hand_value(dealerhand, dealercards);
				printf("\n\nEnter command: ");
				scanf("%c%*c", &command);//%*c is used so that scanf can't use multiple values
				if (command != 'h')
					break;
				else
				{
					playercards++;
					playerhand[playercards - 1] = deal_cards();
					hand1 = hand_value(playerhand, playercards);
				}
				if (hand1 > 21)
				{	
					printf("\nPlayer's hand:");
					display_hand(playerhand, playercards);
					printf("\nDealer's hand:");
					display_hand(dealerhand, dealercards);
					printf("\nPlayer busts");
					stop = 1;
					break;
				}
			}
		}
		if(command == 's' && stop != 1)
		{	
			printf("\nPlayer's hand:");
			display_hand(playerhand, playercards);
			hand1 = hand_value(playerhand, playercards);
		}
		while(command == 's' && stop != 1)
		{
			if (hand2 == 21)
			{		
				printf("\nDealer's hand:");
				display_hand(dealerhand, dealercards);
				printf("\nDealer Wins");
				dwin++;
				stop = 1;
				break;
			}
			else if (hand2 > 21)
			{
				printf("\nDealer's hand:");
				display_hand(dealerhand, dealercards);
				printf("\nDealer busts");
				stop = 1;
				break;
			}
			else if (hand2 >= 17)
			{
				if (hand2 > hand1)
					{
					printf("\nDealer's hand:");
					display_hand(dealerhand, dealercards);
					printf("\nDealer Wins");
					dwin++;
					stop = 1;
					break;
					}
				else if (hand2 == hand1)
				{
					printf("\nDealer's hand:");
					display_hand(dealerhand, dealercards);
					printf("\nIts a push");
					stop = 1;
					break;
				}
				else
				{
					printf("\nDealer's hand:");
					display_hand(dealerhand, dealercards);
					printf("\nPlayer Wins");
					pwin++;
					stop = 1;
					break;
				}
			}
			else
			{
				dealercards++;
				dealerhand[dealercards - 1] = deal_cards();
				hand2 = hand_value(dealerhand, dealercards);
			}
		}
		printf("\n\nEnter 'q' to quit, anything else to play another game ");
		scanf("%c%*c", &replay);
	}
	printf("\t\t\t\t\tTotal Score\n\t\t\t\t\tDealer Wins=%d\n\t\t\t\t\tPlayer Wins=%d\n\n\n\n",dwin, pwin);
	getchar();
	return 0;
}

int gamestart(int h1[], int h2[])
{
	int i;
	for (i = 0; i < 12; i++)
	{
		h1[i] = 0;
		h2[i] = 0;
	}
	h1[0] = deal_cards();
	h1[1] = deal_cards();
	h2[0] = deal_cards();
	h2[1] = deal_cards();
}

int display_hand(int v[], int size)//The function to display the cards in player and dealer hand 
{
	int i;
	for (i = 0; i < size; i++)
	{
		if (v[i] == 1)
			printf(" A");
		else if(v[i] == 11)
			printf(" J");
		else if (v[i] == 12)
			printf(" Q");
		else if (v[i] == 13)
			printf(" K");
		else
			printf(" %d", v[i]);
		if (i < size - 1)
			printf(",");
	}
}

int display_dealer(int v[], int size)//The function to display the cards in dealer hand with hole card
{
		if (v[0] == 1)
			printf(" A,");
		else if(v[0] == 11)
			printf(" J,");
		else if (v[0] == 12)
			printf(" Q,");
		else if (v[0] == 13)
			printf(" K,");
		else
			printf(" %d,", v[0]);
		printf(" X");//X is printed for hole card
}

int hand_value(int v[], int size)
{
	int i, aces = 0, value = 0, face;
	for (i = 0; i < size; i++)
	{
		face = v[i];
		if (v[i] > 10)//Managing value for face card
			face = 10;
		value = value + face;
		if (v[i] == 1)
			aces++;
	}
	if (aces > 0 && value < 12)
	{
		value = value + 10;
		aces--;
	}
	return value;
}

int deal_cards()
{	
	static int deck[14] = {4,4,4,4,4,4,4,4,4,4,4,4,4,4};//To set 4 cards of each denomination
	int card = 1 + rand()%13;
	while(deck[card] < 1)//To restrain drawing of more than 4 cards
	{
		card = 1 + rand()%13;
	}
	deck[card]--;
	return card;
}

