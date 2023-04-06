#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>

using namespace std;

int main(void)
{
	string *menu;
	double *price;
	int menucount;
	int menuamt = 20;
	int menucurrent;
	int option;
	int editoption;
	int tableamt;
	int tableno;
	int counter;
	int counter2;
	int counter3;
	int choice;
	int stock[menuamt];
	double total;
	double totalforday;
	int **order;
	char yesno;
	time_t time;
	tm *local_time;
	ostringstream time_stream;
	string current_time;

	yesno = 1;
	tableamt = 30;
	price = (double *)malloc(sizeof(double) * (menuamt + 1));
	menu = (string *)calloc(sizeof(string), (menuamt + 1));
	order = (int **)malloc(sizeof(int *) * tableamt);
	while (counter <= 100)
	{
		order[counter] = (int *)malloc(sizeof(int) * 100);
		counter++;
	}
	menu[0] = "Roti Kosong";
	menu[1] = "Roti Telur";
	menu[2] = "Teh ";
	price[0] = 1.20;
	price[1] = 2.20;
	price[2] = 1.80;
	while (counter2 <= menuamt)
	{
		stock[counter2] = 200;
		counter2++;
	}
	// add order or print receipt or edit menu and price
	// first prompt
	cout << "Welcome to interactive menu v1.1\n";
	cout << "The Menu Defaults to 30 tables 200 stock\n";
	cout << "You can Edit your menu under 'edit menu'\n";
	option = 1;
	do
	{
		menucount = 0;
		// Select what you want to do
		do
		{
			// Prompt for option
			if (option < 0 || option > 4)
				cout << "\n\n\nPlease Enter a valid option\n";
			cout << "\nWould you like to\n";
			cout << "1, Add an Order\n";
			cout << "2, Print Receipt\n";
			cout << "3, Edit the Menu\n";
			cout << "4, Check Total Sales for the Day\n";
			cout << "5, Exit the program\n>";
			cin >> option;
		} while (option < 1 || option > 5);
		// if add order
		while (option == 1)
		{
			system("clear");
			tableno = 0;
			counter = 0;
			counter2 = 0;
			choice = 0;
			// Enter table number and check for errors
			while (tableno < 1 || tableno > tableamt)
			{
				cout << "Please Enter your table number(1 ~ " << tableamt << ")(-999 to exit): ";
				cin >> tableno;
				if (tableno == -999)
					break;
			}
			if (tableno == -999)
				break;
			// prints menu
			while (menu[menucount][0] != 0)
			{
				cout << menucount << "," << menu[menucount] << "\tRM " << price[menucount];
				if (stock != 0)
					cout << "(" << stock[menucount] << " Left)" << endl;
				else
					cout << "(out of stock)" << endl;
				menucount++;
			}
			while (order[tableno][counter] != 0)
			{
				counter++;
			}
			do
			{
				do
				{
					// prompt for order code and makesure its valid else reprompt
					cout << "Please Enter your choice: ";
					cin >> choice;
				} while (choice < 1 || choice > menuamt);
				cout << "How many would you like?: ";
				cin >> counter2;
				while (counter < counter2)
				{
					order[tableno][counter] = choice;
					counter++;
				}
				cout << counter2 << " " << menu[choice] << " added\n";
				do
				{
					cout << "Would you like to add another order?(y/n): ";
					cin >> yesno;
				} while (yesno != 'y' && yesno != 'n');
			} while (yesno == 'y');
			option = 0;
		}
		// if print receipt
		if (option == 2)
		{
			system("clear");
			counter = 0;
			counter2 = 1;
			counter3 = 0;
			total = 0;
			// choose table number and get info
			do
			{
				cout << "Please Enter Table Number: ";
				cin >> tableno;
			} while (tableno <= 0 && tableno > tableamt);
			cout << "You have ordered\n";
			while (counter2 <= menuamt)
			{
				// runs through order array and check
				while (order[tableno][counter] != 0)
				{
					// if theres an ordered food with the code 'counter2' add to total
					if (order[tableno][counter] == counter2)
					{
						// add to total for the purchased dish
						counter3++;
					}
					// goes to next array to check
					counter++;
				}
				// return back to first array
				counter = 0;
				// print order and price if theres an order
				if (counter3 != 0)
					cout << counter3 << " " << menu[counter2] << "\tRM" << price[counter2] << " * " << counter3 << ",\tRM" << price[counter2] * counter3 << endl;
				total = total + (price[counter2] * counter3);
				// move to next menu
				counter2++;
				counter3 = 0;
			}
			cout << "Total is RM" << total << endl;
			do
			{
				cout << "Paid?(y/n): " << endl;
				cin >> yesno;
			} while (yesno != 'y' && yesno != 'n');
			if (yesno == 'y')
			{
				totalforday = totalforday + total;
				cout << "Thanks for paying!";
				// empties the order for the table
				counter = 0;
				while (order[tableno][counter] != 0)
				{
					order[tableno][counter] = 0;
					counter++;
				}
			}
		}
		// print
		// if edit menu
		if (option == 3)
		{
			system("clear");
			do
			{
				cout << "1, Edit the Menu\n";
				cout << "2, Edit the Amount of Stock Left\n";
				cout << "3, Edit the Amount of menu\n";
				cout << "4, Back to Main Menu\n>";
				cin >> editoption;
				while (editoption < 1 || editoption > 4)
				{
					cout << "Please enter a valid option: ";
					cin >> editoption;
				}
				// edit menu
				if (editoption == 1)
				{
					counter = 0;
					while (menucount <= menuamt)
					{
						cout << menucount << "," << menu[menucount] << " RM " << price[menucount] << "\n";
						menucount++;
					}
					do
					{
						cout << "Which would you like to change?: ";
						cin >> counter;
					} while (counter < 1 || counter > menuamt);
					cout << "Enter Food Name: ";
					cin >> menu[counter];
					cout << "Enter Price: ";
					cin >> price[counter];
				}
				if (editoption == 2)
				{
					counter = 0;
					cout << "Which Dish would you like to change: ";
					// cin >> stock;
					order = (int **)malloc(sizeof(int) * tableamt);
					while (counter <= 100)
					{
						order[counter] = (int *)malloc(sizeof(int) * 100);
						counter++;
					}
					if (!order)
					{
						cout << "Invalid amount of tables";
						return (0);
					}
				}
			} while (editoption != 4);
			// show total sales for the day
			if (option == 4)
			{
				system("clear");
				// reset the stuff inside time_stream to prevent the date showing up multiple times after running alot
				time_stream.str("");
				// get the time now in time_t format.
				time = std::time(0);
				// format time to local time;
				local_time = localtime(&time);
				// Format the time_t format time into string format
				time_stream << std::put_time(local_time, "%Y-%m-%d");
				current_time = time_stream.str();
				// Print the current time
				cout << "Date: " << current_time << endl;
				cout << "Total Sales for the day is RM" << totalforday << "\n\n";
			}
		}
	} while (option != 5);
	return (0);
}

// stuff needed for menu info - table number, stuff ordered, price.
// if no order, dont ask for payment (done)
// rework on the whole edit menu part 
// - make a fixed array of max 20
// - make inventory mechanic
// - if inventory = 0, dont display dish
// when add menu, take into consideration of name, price, stock left.
// start the program with a default amt of 200 stock
// food stock can be added or minus-ed
// cannot edit menuamt
// cannot edit tableamt
// learn how to take inputs with 2 string like "Roti Canai"
// make 2 types of tallying for virtual credits and cash > Total for both
// work on overall indentation