#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <fstream>

using namespace std;

int ft_activemenu(string menu[])
{
    int count = 0;

    while (menu[count + 1][0] != 0)
        count++;
    return (count);
}
void ft_displaymenu(string menu[], double price[], int stock[])
{
    int counter = 1;

    while (menu[counter][0] != 0)
    {
        cout << counter << "," << left << setw(15) << menu[counter] << fixed << setprecision(2) << "\tRM " << price[counter];
        if (stock[counter] != 0)
            cout << "(" << stock[counter] << " Left)" << endl;
        else
            cout << "(out of stock)" << endl;
        counter++;
    }
}

int main(void)
{
    const int max = 200;
    const int tableamt = 30;
    string menu[max];
    double price[max];
    int order[tableamt][max];
    int stock[max];
    int tableno;
    int choice;
    int choice2;
    int choice3;
    double total;
    double totalcash;
    double totalcredit;
    double totalmonth;
    int counter;
    int counter2;
    int counter3;
    int option;
    char yesno;
    time_t time;
    tm *local_time;
    ostringstream time_stream;
    string current_time;

    menu[1] = "Roti Kosong";
    menu[2] = "Roti Telur";
    menu[3] = "Roti Telur";
    menu[4] = "Roti Telur";
    menu[5] = "Roti Telur";
    menu[6] = "Roti Telur";
    menu[7] = "Roti Telur";
    menu[8] = "Roti Telur";
    menu[9] = "Roti Telur";
    menu[10] = "Roti Telur";
    menu[11] = "Roti Telur";
    menu[12] = "Teh";
    menu[13] = "Roti Telur";
    menu[14] = "Roti Telur";
    menu[15] = "Roti Telur";

    price[1] = 1.20;
    price[2] = 2.20;
    price[3] = 1.80;
    price[4] = 1.20;
    price[5] = 2.20;
    price[6] = 1.80;
    price[7] = 1.20;
    price[8] = 2.20;
    price[9] = 1.80;
    price[10] = 1.20;
    price[11] = 2.20;
    price[12] = 1.80;
    price[13] = 1.20;
    price[14] = 2.20;
    price[15] = 1.80;

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
            if (option < 0 || option > 5)
                cout << "Please Enter a valid option\n";
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
            do
            {
                // prints menu
                ft_displaymenu(menu, price, stock);
                do
                {
                    // prompt for order code and makesure its valid else reprompt
                    cout << "Please Enter your choice: ";
                    cin >> choice;
                    cin.ignore(100, '\n');
                    if ((choice >= 0 && choice < ft_activemenu(menu)) && stock[choice] == 0)
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
                        cout << left << setw(15) << menu[counter2] << "\tRM" << fixed << setprecision(2) << price[counter2] << " * " << fixed << setprecision(0) << counter3 << ", RM" << fixed << setprecision(2) << price[counter2] * counter3 << endl;
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
                cout << "2, Edit the Amount of Stock Left\n";
                cout << "3, Back to Main Menu\n>";
                cin >> choice;
                cin.ignore(100, '\n');
                while (choice < 1 || choice > 3)
                {
                    cout << "Please enter a valid option: ";
                    cin >> choice;
                    cin.ignore(100, '\n');
                }
                // edit menu
                if (choice == 1)
                {
                    cout << "Enter Food Name: ";
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
                    system("clear");
                    cout << stock[ft_activemenu(menu)] << " " << menu[ft_activemenu(menu)] << " added\n\n";
                }
                if (choice == 2)
                {
                    do
                    {
                        system("clear");
                        ft_displaymenu(menu, price, stock);
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
            } while (choice != 3);
            system("clear");
        }
        // show total sales for the day
        if (option == 4)
        {
            system("clear");
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
