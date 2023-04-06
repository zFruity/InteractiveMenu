#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <fstream>

using namespace std;

// function to count the current amount of dishes in the menu
int ft_activemenu(string menu[])
{
    int count = 0;

    while (menu[count + 1][0] != 0)
        count++;
    return (count);
}

void ft_displaymenu(string menu[], double price[], int stock[], int activedrinks)
{
    int counter = 1;

    // print the makanan category of the menu
    cout << "Makanan\n";
    while (counter <= ft_activemenu(menu) - activedrinks)
    {
        cout << counter << "," << left << setw(15) << menu[counter] << fixed << setprecision(2) << "\tRM " << left << setw(10) << price[counter];
        if (stock[counter] != 0)
            cout << "(" << stock[counter] << " Left)" << endl;
        else
            cout << "(out of stock)" << endl;
        counter++;
    }
    // print the minuman part
    cout << "\nMinuman\n";
    while (counter <= ft_activemenu(menu))
    {
        cout << counter << "," << left << setw(15) << menu[counter] << fixed << setprecision(2) << "\tRM " << left << setw(10) << price[counter];
        if (stock[counter] != 0)
            cout << "(" << stock[counter] << " Left)" << endl;
        else
            cout << "(out of stock)" << endl;
        counter++;
    }
}

void ft_printtime(void)
{
    time_t time;
    tm *local_time;
    ostringstream time_stream;
    string current_time;

    // reset the stuff inside time_stream to prevent the date showing up multiple times after running alot
    time_stream.str("");
    // get the global time now in time_t format.
    time = std::time(0);
    // format global time to local time;
    local_time = localtime(&time);
    // Format the time_t format time into string format
    time_stream << std::put_time(local_time, "%Y-%m-%d");
    current_time = time_stream.str();
    // Print the current time
    cout << "Date: " << current_time << endl;
}

void ft_assignmenu(string menu[], double price[])
{
    menu[1] = "Roti Kosong";
    menu[2] = "Roti Telur";
    menu[3] = "Roti Planta";
    menu[4] = "Roti Pisang";
    menu[5] = "Roti Bom";
    menu[6] = "Roti Tisu";
    menu[7] = "Thosai";
    menu[8] = "Naan";
    menu[9] = "Nasi Lemak";
    menu[10] = "Indomee";
    menu[11] = "Maggi Sup";
    menu[12] = "Nasi Goreng";
    menu[13] = "Maggi Goreng";
    menu[14] = "Mee Goreng";
    menu[15] = "Kuey teow Goreng";
    menu[16] = "Ayam Goreng";
    menu[17] = "Rojak";
    menu[18] = "Telur Mata";
    menu[19] = "Air Suam";
    menu[20] = "Teh";
    menu[21] = "Milo";

    price[1] = 1.20;
    price[2] = 2.50;
    price[3] = 2.00;
    price[4] = 4.00;
    price[5] = 5.00;
    price[6] = 4.50;
    price[7] = 2.00;
    price[8] = 2.20;
    price[9] = 3.00;
    price[10] = 4.00;
    price[11] = 4.50;
    price[12] = 6.00;
    price[13] = 5.00;
    price[14] = 5.50;
    price[15] = 7.00;
    price[16] = 5.00;
    price[17] = 5.50;
    price[18] = 1.00;
    price[19] = 0.80;
    price[20] = 1.80;
    price[21] = 2.50;
}

int main(void)
{
    const int max = 10000;
    const int tableamt = 30;
    string menu[max];
    double price[max];
    int order[tableamt][max];
    int stock[max];
    int paxNo[tableamt];
    int tableno;
    int choice;
    int choice2;
    int choice3;
    int activedrinks = 3;
    double total;
    double totalcash;
    double totalcredit;
    double totalmonth;
    int counter;
    int counter2;
    int counter3;
    int option;
    char yesno;

    ft_assignmenu(menu, price);

    // assign 200 stock to every dish
    for (int i = 1; i <= ft_activemenu(menu); i++)
        stock[i] = 200;
    option = 1;
    system("clear");
    do
    {
        tableno = 0;
        counter = 0;
        counter2 = 0;
        counter3 = 0;
        choice = 0;
        choice2 = 0;
        choice3 = 0;
        yesno = 0;
        total = 0;
        // Read the total earnings from the file
        ifstream inFile("earnings.txt");
        if (inFile.is_open())
        {
            inFile >> totalmonth;
            inFile.close();
        }
        do
        {
            // Prompt for option
            cout << "Welcome to interactive menu v1.2\n";
            cout << "The Menu Defaults to 30 tables 200 stock\n";
            cout << "You can Edit your menu under 'Edit the menu'\n\n";
            if (option < 1 || option > 5)
            {
                system("clear");
                cout << "Please Enter a valid option\n";
            }
            cout << "Would you like to\n";
            cout << "1, Add an Order\n";
            cout << "2, Print Receipt\n";
            cout << "3, Edit the Menu\n";
            cout << "4, Check Total Sales for the Day and Month\n";
            cout << "5, Exit the program\n>";
            cin >> option;
            cin.ignore(100, '\n');
        } while (option < 1 || option > 5);
        // if add order
        while (option == 1)
        {
            system("clear");
            // Enter table number and check for errors
            do
            {
                cout << "Please Enter your table number(0 ~ " << tableamt - 1 << ")(-999 to exit): ";
                cin >> tableno;
                cin.ignore(100, '\n');
                if (tableno == -999)
                    break;
            } while (tableno < 0 || tableno > tableamt - 1);
            if (tableno == -999)
                break;
            // runs arrays to go to next slot to add order if table has active order
            while (order[tableno][counter] != 0)
            {
                counter++;
            }
            // only asks for amount of pax if the table is empty
            if (counter == 0)
            {
                do
                {
                    cout << "How many pax?: ";
                    cin >> paxNo[tableno];
                    cin.ignore(100, '\n');
                } while (paxNo[tableno] <= 0);
            }
            do
            {
                // prints menu
                ft_displaymenu(menu, price, stock, activedrinks);
                do
                {
                    // prompt for order code and makesure its valid else reprompt
                    cout << "Please Enter your choice: ";
                    cin >> choice;
                    cin.ignore(100, '\n');
                    if ((choice > 0 && choice <= ft_activemenu(menu)) && stock[choice] == 0)
                    {
                        cout << "It is out of stock\n";
                    }
                } while ((choice < 1 || choice > ft_activemenu(menu)) || stock[choice] == 0);
                do
                {
                    cout << "How many would you like?: ";
                    cin >> counter2;
                    cin.ignore(100, '\n');
                    if (counter2 > stock[choice])
                    {
                        cout << "There is not enough stock left\n";
                    }
                } while ((counter2 > stock[choice]) || counter2 < 0);
                // minus current stock
                stock[choice] -= counter2;
                // assign a temporary thing to put total ordered item
                counter3 = counter2;
                counter2 += counter;
                while (counter < counter2)
                {
                    order[tableno][counter] = choice;
                    counter++;
                }
                cout << counter3 << " " << menu[choice] << " added\n";
                do
                {
                    cout << "Would you like to add another order?(y/n): ";
                    cin >> yesno;
                    cin.ignore(100, '\n');
                } while (yesno != 'y' && yesno != 'n');
                (system("clear"));
            } while (yesno == 'y');
            option = 0;
            system("clear");
        }
        // if print receipt
        if (option == 2)
        {
            system("clear");
            // choose table number and get info
            do
            {
                cout << "Please Enter Table Number: ";
                cin >> tableno;
                cin.ignore(100, '\n');
            } while (tableno <= 0 && tableno > tableamt);
            cout << "No of Pax: " << paxNo[tableno] << endl;
            if (order[tableno][counter] != 0)
            {
                cout << "You have ordered\n";
                while (counter2 <= ft_activemenu(menu))
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
                        cout << left << setw(15) << menu[counter2] << "RM" << fixed << setprecision(2) << price[counter2] << " * " << left << setw(5) << fixed << setprecision(0) << counter3 << "= RM" << fixed << setprecision(2) << price[counter2] * counter3 << endl;
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
                    cin.ignore(100, '\n');
                } while (yesno != 'y' && yesno != 'n');
                if (yesno == 'y')
                {
                    do
                    {
                        cout << "with cash(0) or card(1)?: " << endl;
                        cin >> choice;
                        cin.ignore(100, '\n');
                    } while (choice != 0 && choice != 1);
                    if (choice == 0)
                    {
                        totalcash += total;
                        totalmonth += total;
                    }
                    else
                    {
                        totalcredit += total;
                        totalmonth += total;
                    }
                    // Add today's earnings to the total earnings
                    ofstream outFile("earnings.txt");
                    if (outFile.is_open())
                    {
                        outFile << totalmonth;
                        outFile.close();
                    }
                    system("clear");
                    cout << "Thanks for paying!\n\n";
                    // empties the order for the table
                    counter = 0;
                    while (order[tableno][counter] != 0)
                    {
                        order[tableno][counter] = 0;
                        counter++;
                    }
                }
                else
                    system("clear");
            }
            else
            {
                system("clear");
                cout << "Theres no active order for this table\n\n";
            }
        }
        if (option == 3)
        {
            system("clear");
            do
            {
                cout << "1, Add a dish to the Menu\n";
                cout << "2, Add a drink to the Menu\n";
                cout << "3, Edit the Amount of Stock Left\n";
                cout << "4, Back to Main Menu\n>";
                cin >> choice;
                cin.ignore(100, '\n');
                while (choice < 1 || choice > 4)
                {
                    cout << "Please enter a valid option: ";
                    cin >> choice;
                    cin.ignore(100, '\n');
                }
                // edit menu
                if (choice == 1)
                {
                    counter = 0;
                    // push all drink to 1 array back to categorize dish properly
                    while (counter <= activedrinks)
                    {
                        menu[ft_activemenu(menu) - counter + 1] = menu[ft_activemenu(menu) - counter];
                        price[ft_activemenu(menu) - counter + 1] = price[ft_activemenu(menu) - counter];
                        stock[ft_activemenu(menu) - counter + 1] = stock[ft_activemenu(menu) - counter];
                        counter++;
                    }
                    cout << "Enter Food Name: ";
                    getline(cin, menu[ft_activemenu(menu) - activedrinks]);
                    do
                    {
                        cout << "Enter Price: ";
                        cin >> price[ft_activemenu(menu) - activedrinks];
                        cin.ignore(100, '\n');
                    } while (price[ft_activemenu(menu) - activedrinks] < 0);
                    do
                    {
                        cout << "Enter Stock: ";
                        cin >> stock[ft_activemenu(menu) - activedrinks];
                        cin.ignore(100, '\n');
                    } while (stock[ft_activemenu(menu) - activedrinks] < 0);
                    system("clear");
                    cout << stock[ft_activemenu(menu) - activedrinks] << " " << menu[ft_activemenu(menu) - activedrinks] << " added\n\n";
                }
                if (choice == 2)
                {
                    cout << "Enter Drink Name: ";
                    getline(cin, menu[ft_activemenu(menu) + 1]);
                    do
                    {
                        cout << "Enter Price: ";
                        cin >> price[ft_activemenu(menu)];
                        cin.ignore(100, '\n');
                    } while (price[ft_activemenu(menu)] < 0);
                    do
                    {
                        cout << "Enter Stock: ";
                        cin >> stock[ft_activemenu(menu)];
                        cin.ignore(100, '\n');
                    } while (stock[ft_activemenu(menu)] < 0);
                    activedrinks++;
                    system("clear");
                    cout << stock[ft_activemenu(menu)] << " " << menu[ft_activemenu(menu)] << " added\n\n";
                }
                if (choice == 3)
                {
                    do
                    {
                        system("clear");
                        ft_displaymenu(menu, price, stock, activedrinks);
                        cout << "Which Dish would you like to change: ";
                        cin >> choice2;
                        cin.ignore(100, '\n');
                    } while (choice2 < 1 || choice2 > ft_activemenu(menu));
                    do
                    {
                        cout << "Would you like to add(0) or minus(1)?: ";
                        cin >> choice3;
                        cin.ignore(100, '\n');
                    } while (choice3 != 0 && choice3 != 1);
                    if (choice3 == 0)
                    {
                        cout << "How many would you like to add?: ";
                        cin >> counter;
                        cin.ignore(100, '\n');
                        stock[choice2] += counter;
                        system("clear");
                        cout << stock[choice2] << " " << menu[choice2] << " left\n\n";
                    }
                    else
                    {
                        cout << "How many would you like to minus?: ";
                        cin >> counter;
                        cin.ignore(100, '\n');
                        while (counter > stock[choice2])
                        {
                            cout << "Theres not that many stock left to reduce\n";
                            cout << "How many would you like to minus?: ";
                            cin >> counter;
                            cin.ignore(100, '\n');
                        }
                        stock[choice2] -= counter;
                        system("clear");
                        cout << stock[choice2] << " " << menu[choice2] << " left\n\n";
                    }
                }
            } while (choice != 4);
            system("clear");
        }
        // show total sales for the day
        if (option == 4)
        {
            system("clear");
            ft_printtime();
            cout << "Total Cash Sales for the day is RM" << totalcash << endl;
            cout << "Total Credit Sales for the day is RM" << totalcredit << endl;
            cout << "Total Sales for the day is RM" << totalcash + totalcredit << endl;
            cout << "Total Sales for the month is RM" << totalmonth << "\n\n";
            do
            {
                cout << "Would you like to reset the monthly earnings?(y/n): ";
                cin >> yesno;
                cin.ignore(100, '\n');
            } while (yesno != 'y' && yesno != 'n');
            if (yesno == 'y')
            {
                totalmonth = 0;
                totalcash = 0;
                totalcredit = 0;
                ofstream outFile("earnings.txt");
                if (outFile.is_open())
                {
                    outFile << totalmonth;
                    outFile.close();
                }
                system("clear");
                cout << "Cleared!\n\n";
            }
            else
                system("clear");
        }
    } while (option != 5);
}
