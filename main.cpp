#include <iostream>
#include <fstream>

using namespace std;

void displayMenu(int& lineCount, ifstream& menuFile)        // Calls lineCount and menuFile by reference for use later.
{
    string line;
    while (getline(menuFile, line))
    {
        lineCount++;
        cout << lineCount << ". " << line << endl;  //Reads out menu with line numbers assigned.
    }
    cout << lineCount + 1 << ". Print Receipt" << endl;
    menuFile.clear();       // Clears eof
    menuFile.seekg(0);      // Sets the files reading location to 0
}

void displaySalesReceipt(string item, int amount, double price, int itemCount, double& priceTotal)
{
    if (amount > 0)
    {
        cout << item << "\t\t x" << amount << "\t\t $" << price * amount << endl;
        priceTotal += price * amount;
    }

}   // Gets the item, amount, double, and price, and outputs them nicely

int main()
{
    int itemCount = 0;      // Used all of these variables.
    int itemChoice;
    int priceCount = 0;
    int split;
    double priceTotal = 0;
    string line;
    ifstream menuFile;
    bool isDone = false;
    bool isEmpty = true;
    menuFile.open("qbc_menu_prices.txt");   //Opens the file for use through menuFile

    if(menuFile.fail())     // Ensures that the file opens correctly or the program exits.
    {
        cout << "File failed to open.";
        exit(1);
    }

    displayMenu(itemCount, menuFile);       // Calls displayMenu with references to set the itemCount variable
    string menuItems[itemCount];        // Creates a few variables that were dependent on the size of itemCount
    int itemCart[itemCount];
    double prices[itemCount];

    while (getline(menuFile, line))
    {
        split = line.find(" ");
        menuItems[priceCount] = line.substr(0, split);
        prices[priceCount] = stod(line.substr(split + 1, line.length()));

        itemCart[priceCount] = 0;

        priceCount++;
    }       // This loop runs through the file and splits each line into the name of the item and the price, then stores those within the corresponding variables.

    while (!isDone)
    {
        cout << "What would you like to order? ";
        while (!(cin >> itemChoice))
        {
            cin.clear();
            cin.ignore(100,'\n');
            cout << "Choice must be a number. ";
        }
        if (itemChoice > itemCount + 1 || itemChoice < 1)
        {
            cout << "Choice must be a number on the menu. "
        }
        if (itemChoice == itemCount + 1)
        {
            isDone = true;
        }
        if (itemChoice != itemCount + 1)
        {
            isEmpty = false;
            itemCart[itemChoice - 1]++;
        }
    }       // This loop gets the users input for their cart, validates that it's the right input type, and alerts them if their input is outside the bounds of the menu.

    if (!isEmpty)
    {
        for (int i = 0; i < itemCount; i++)
        {
            displaySalesReceipt(menuItems[i],itemCart[i],prices[i],itemCount,priceTotal);
        }
        double taxAmount = priceTotal * 0.08;
        cout << "\t\t\t\t Subtotal: $" << priceTotal << endl;
        cout << "\t\t\t\t Tax: $" << taxAmount << endl;
        cout << "\t\t\t\t Total: $" << priceTotal + taxAmount;
    }
    if (isEmpty)
    {
        cout << "No receipt required. Thanks!";
    }

    menuFile.close();
}
