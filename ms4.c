#include <stdio.h>
#define MAX_INVENTORY_SIZE 10
#define TAX .13
#define MAX_ITEMS 10

/* 
 * I declare that the attached assignment is wholly my own work in accordance with Seneca Academic Policy. No part of this assignment has been copied manually or 
 * electronically from any other sources (including websites) or distributed to other students.
 * Name- Gaurav Verma                 Student ID-  041334152              
*/

/*
 * Declaration of the structure type.
*/
struct Cart
{
	int sku[MAX_ITEMS];
	float price[MAX_ITEMS];
	int quantity[MAX_ITEMS];
	float totalCost;
	int size;
};

/*
 * Clear's the screen in the beginning.
*/
void clear();

/*
 *Shows a menu to the user to choose options.
*/
void menu();

/*
 * Retrieves an input from the user and performs range validation.
 *
 * low    The minimum range the user can enter.
 * high   The maximum range the user can enter.
 *
 * Returns validated integer.
*/
int validate(const int low, const int high);

/*
 * Displays the list of itmes in the inventory.
 *
 * sku    Receives array of inventory items.
 * price  Receives array of price for inventory items.
*/
void displayInventory(const int sku[],const float price[]);

/*
 * Use to search for an item in inventory.
 *
 * sku    Receives array of inventory items.
 * item   Receives user input.
 *
 * Returns the index number for the item if it is in inventory or (-1) if it is not in the inventory.
*/
int searchInventory(const int sku[],const int item);

/*
 * Use to check the price of an item.
 *
 * sku    Receives array of inventory items.
 * price  Receives array of price for inventory items.
*/
void checkPrice(const int sku[],const float price[]);

/*
 * Displays the shopping cart of the customer.
*/
void displayCart(const struct Cart* pShoppingCart);

/*
 * Prompts user to add items to their cart.
 *
 * pShoppingCart   Pointer which holds the address for the user shopping cart.
 * sku             Receives array of inventory items.
 * price           Receives array of price for inventory items.
*/
void addCart(struct Cart* pShoppingCart,const int sku[],const float price[]);

/*
 * Removes all items from the shopping cart.
*/
void removeCart(struct Cart* pShoppingCart);

/*
 * Calculates the total price for the items in shoppingcart.
*/
void checkOut(struct Cart* pShoppingCart);

/*
 * Retrieves inventory details from the file and initialize arrays.
 *
 * filename    Receives array of the file.
 * returns 0 if file is found otherwise -1. 
*/
int readInventory(const char filename[],int sku[],float price[]);

/*
 * Prints user shopping cart and the price of the cart to a file.
*/
void printReceipt(const char filename[], struct Cart* pShoppinCart);


int main()
{
	int choice = 0,i;
	// Array for items.
	int iSku[MAX_INVENTORY_SIZE];
	// Array for the prices of the items.
	float iPrice[MAX_INVENTORY_SIZE];
	// Structure for users shopping cart.
	struct Cart myCart;
	// Initialize the size of user shopping cart to 0.
	myCart.size = 0;

	// Calling clear function to clear the screen.                  		
	clear();
	printf("Welcome to the Groccery Store\n");
	printf("===============================\n");

	// Looping until user enter 8 to exit.	
	while(choice != 8)
	{               
		// Calling menu function to show the menu to the user.
		menu();			
		printf("Select:  ");
		// Calling validate function to validate the input from the user.
		choice = validate(1,8);
		
		if(choice == 1)
		{
			// Calling function to read data from the file.
			i = readInventory("inventory.dat",iSku,iPrice);
			if(i == -1)
			{
				printf("Unable to retrieve data sorry for the inconvenience.\n\n");
				return 0;
			}

			// Calling function to display inventory to the user.
			displayInventory(iSku,iPrice);
		}
		else if(choice == 2)
		{
			// Calling function to check the price for an item.
			checkPrice(iSku,iPrice);
		}
		else if(choice == 3)
		{
			// Calling Function to display user shopping cart.
			displayCart(&myCart);
		}
		else if(choice == 4)
		{
			// Calling function to add items to the shopping cart of the user.
			addCart(&myCart,iSku,iPrice);
		}
		else if(choice == 5)
		{
			// Calling function to empty the user cart.
			removeCart(&myCart);
		}
		else if(choice == 6)
		{
			// Calling function to calculate the total price of the shopping cart.
			checkOut(&myCart);
			// Calling function to generate receipt and to save it to a file.
			printReceipt("receipt.dat",&myCart);
		}
		else if(choice == 7)
		{
			// Calling function to clear the screen.
			clear();
		}
	}

	printf("Good Bye!\n\n");
	return 0 ;
}


void clear()
{
	// Prints 40 new lines in the beginning.
	int i;

	for(i = 0; i < 40; i++)
	{
		printf("\n");
	}
}


void menu()
{
	// Prints menu on the screen with options.
	printf("Please select from the following options:\n");
	printf("1) Display the inventory.\n");
	printf("2) Price check.\n");
	printf("3) Display my shopping cart.\n");
	printf("4) Add to cart.\n");
	printf("5) Remove from cart.\n");
	printf("6) Check out.\n");
	printf("7) Clear screen\n");
	printf("8) Exit.\n");
}


int validate(const int low, const int high)
{
	int input = 0;

	// Looping until user didn't enter the desired input between the low and high range.
	while(input < low || input > high)
	{
		// Retrieves input from user and save it inside input variable.
		scanf("%d", &input);
		// If input is out of range.
		if(input < low || input > high)
		{
			printf("Invalid	input, try again: ");
		}
	}

	return input;
}


void displayInventory(const int sku[],const float price[])
{
	int i;

	printf("\n");
	printf("Inventory\n");
	printf("===========================================\n");
	printf("Sku           Price\n");

	// Looping to print the list of items inside inventory.
	for(i = 0; i < MAX_INVENTORY_SIZE; i++)
	{
		printf("%d          %.2f\n", sku[i],price[i]);
	}

       	printf("===========================================\n\n");
}


void checkPrice(const int sku[],const float price[])
{
	int input = 0,num;

	printf("Please input the sku number of the item:\n");
	scanf("%d", &input);

	// Calling function to look for an item inside inventory.
	num = searchInventory(sku,input);

	// Use to print the price of an item.
	if(num == -1)
	{
		printf("Item does not exist in the shop! Please try again.\n\n");
	}
	else
	{
		// Otherwise...
		printf("Item %d costs $%.2f.\n\n", sku[num],price[num]);
	}
}


int searchInventory(const int sku[],const int item)
{
	// Search for an item inside the inventory on the basis of user input.
	int index = 0,i;

	// Returns the index number of the item if found in the inventory.
	for(i = 0; i < MAX_INVENTORY_SIZE; i++)
	{
		if(sku[i] == item)
		{	
			index = i;
			break;
		}
		else
		{
			index = -1;
		}
	}

	return index;
}


void displayCart(const struct Cart* pShoppingCart)
{
	// Displays the shopping cart to the user.
	int i;

	printf("\n");
	printf("Shopping Cart\n");
	printf("==========================================\n");
	printf("Sku            Quantity           Price\n");

	for(i = 0; i < pShoppingCart->size; i++)
	{
		printf("%d             %d                 %.2f\n",pShoppingCart->sku[i],pShoppingCart->quantity[i],pShoppingCart->price[i]);
	}

	printf("==========================================\n\n");
}


void addCart(struct Cart* pShoppingCart,const int sku[],const float price[])
{
	// Prompts user to add items to their cart.
	int input = 0,num,quan = 0;

	// Looping until user enter a valid item number.
	while(num = -1)
	{
		printf("Please input a SKU number:");
		scanf("%d", &input);

		num = searchInventory(sku,input);
		if(num == -1)
		{	
			printf("Item does not exist in the shop! Please try again.\n\n");
		}	
		else
		{
			// Otherwise...
			printf("Quantity:");
			scanf("%d", &quan);
			pShoppingCart->sku[pShoppingCart->size]=sku[num];
			pShoppingCart->quantity[pShoppingCart->size]=quan;
			pShoppingCart->price[pShoppingCart->size]=price[num];
			pShoppingCart->size += 1;
			printf("The item is successfully added to the cart.\n\n");
			break;	
		}
	}
}


void removeCart(struct Cart* pShoppingCart)
{
	// Removes all items from the cart.
	if(pShoppingCart->size == 0) 
	{
		printf("The cart is already empty.\n\n");
	}
	else
	{
		// Otherwise...
		pShoppingCart->size=0;
		printf("The cart is successfully removed!\n\n");
	}
}


void checkOut(struct Cart* pShoppingCart)
{
	// Total price of the items in shopping cart
	int i;
	float bill = 0;
	pShoppingCart->totalCost = 0;

	for(i = 0; i < pShoppingCart->size; i++)
	{
		bill = pShoppingCart->quantity[i] * pShoppingCart->price[i];
		pShoppingCart->totalCost += bill;
	}

	printf("\n");
}


int readInventory(const char filename[],int sku[],float price[])
{
	// Reads data from the file.
	int i;
	FILE* fp = NULL;

	fp = fopen(filename,"r");
	if(fp == NULL)
	{
		return -1;
	}
	else
	{
		// Otherwise...
		for(i = 0; i < MAX_INVENTORY_SIZE; i++)
		{
			fscanf(fp, "%d , %f", &sku[i],&price[i]);
		}
	}

	fclose(fp);
	fp = NULL;

	return 0;
	
}


void printReceipt(const char filename[], struct Cart* pShoppingCart)
{
	// Prints receipt to the file.
	int i;
	FILE* fp = NULL;

	fp = fopen(filename,"w");
	if(fp != NULL)
	{
		fprintf(fp,"\n");
		fprintf(fp,"Shopping Cart\n");
		fprintf(fp,"==========================================\n");
		fprintf(fp,"Sku            Quantity           Price\n");
		for(i = 0; i < pShoppingCart->size; i++)
		{
			fprintf(fp,"%d             %d                 %.2f\n",pShoppingCart->sku[i],pShoppingCart->quantity[i],pShoppingCart->price[i]);
		}

		fprintf(fp,"==========================================\n\n");

		fprintf(fp,"The total price is sum = $%.2f\n\n", pShoppingCart->totalCost);

		fclose(fp);
		fp = NULL;		
	}
}
