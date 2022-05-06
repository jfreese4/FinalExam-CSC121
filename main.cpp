#include <iostream>
#include <fstream>

using namespace std;

void displayMenu(int& lineCount, ifstream& menuFile)
{
    string line;
    while (getline(menuFile, line))
    {
        lineCount++;
        cout << lineCount << ". " << line << endl;
    }
    cout << lineCount + 1 << ". Print Receipt" << endl;
    menuFile.clear();
    menuFile.seekg(0);
}

void displaySalesReceipt(string item, int amount, double price, int itemCount, double& priceTotal)
{
    if (amount > 0)
    {
        cout << item << "\t\t x" << amount << "\t\t $" << price * amount << endl;
        priceTotal += price * amount;
    }

}

int main()
{
    int itemCount = 0;
    int itemChoice;
    int priceCount = 0;
    int split;
    double priceTotal = 0;
    string line;
    ifstream menuFile;
    bool isDone = false;
    bool isEmpty = true;
    menuFile.open("qbc_menu_prices.txt");

    if(menuFile.fail())
    {
        cout << "File failed to open.";
        exit(1);
    }

    displayMenu(itemCount, menuFile);
    string menuItems[itemCount];
    int itemCart[itemCount];
    double prices[itemCount];

    while (getline(menuFile, line))
    {
        split = line.find(" ");
        menuItems[priceCount] = line.substr(0, split);
        prices[priceCount] = stod(line.substr(split + 1, line.length()));

        itemCart[priceCount] = 0;

        priceCount++;
    }

    while (!isDone)
    {
        cout << "What would you like to order? ";
        while (!(cin >> itemChoice))
        {
            cin.clear();
            cin.ignore(100,'\n');
            cout << "Choice must be an integer.";
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
    }

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
