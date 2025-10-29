/*********************************************************************
File name: supermarket_simulator_program_2.cpp
Author: Bibek Tiwari (akf81)
Date: 10/28/2025

Purpose:
    Simulates a supermarket that manages customer checkout,
    loyalty memberships, and employee operations such as payroll,
    member clearing, and file updating.

Command Parameters:
    None.

Input:
    - supermarket file (e.g., supermarket.txt)
    - members.txt for loyalty members

Results:
    Displays supermarket information, checkout interface,
    and employee management menu with full functionality.

Notes:
    Follows C++ Programming Standards & Practices.
*********************************************************************/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

/*********************************************************************
Structure Name: Supermarket
Purpose:
    Stores all information related to a supermarket.
Notes:
    Includes data for name, store hours, employee pay, loyalty fee, and budget.
*********************************************************************/
struct Supermarket
{
    string szName;              // Supermarket name
    string szStoreHours;        // Store operating hours
    int iNumEmployees;          // Number of employees
    double dEmployeeSalaries;   // Employee salary (hourly)
    double dLoyaltyFee;         // Loyalty card fee
    double dBudget;             // Current supermarket budget
};

/*********************************************************************
Structure Name: Item
Purpose:
    Represents a product sold in the supermarket.
Notes:
    Contains wholesale cost, regular price, and member price.
*********************************************************************/
struct Item
{
    double dWholesale;      // Wholesale price
    double dRegularPrice;   // Regular customer price
    double dMembersPrice;   // Member price
};

static void displayMainMenu()
{
    cout << "Menu\n";
    cout << "=============================\n";
    cout << "1. Display Supermarket Information\n";
    cout << "2. Display Aisles information\n";
    cout << "3. Checkout\n";
    cout << "4. Access Employee Menu\n";
    cout << "-1. Exit program\n";
    cout << "=============================\n\n";
    cout << "Enter choice: ";
}

static void displayEmployeeMenu()
{
    cout << "\nEmployee Menu\n";
    cout << "=============================\n";
    cout << "1. Update Supermarket File\n";
    cout << "2. Pay Employees\n";
    cout << "3. Display Total Funds\n";
    cout << "4. Clear Current Members\n";
    cout << "5. Change Password\n";
    cout << "-1. Exit Employee Menu\n";
    cout << "=============================\n";
    cout << "\nEnter choice: ";
}

static bool isValidFilepath(const string &path)
{
    if (path.find(' ') != string::npos) return false;
    if (path.size() < 4) return false;
    if (path.rfind(".txt") == string::npos) return false;
    return true;
}

int main()
{
    const double D_SALES_TAX = 0.07;
    const string MEMBERS_FILE = "members.txt";

    // Items
    Item frozenPizza = {3.75, 5.99, 5.49};
    Item iceCream    = {2.95, 4.79, 4.29};
    Item chips       = {1.85, 3.49, 2.99};
    Item bleach      = {2.10, 3.79, 3.29};
    Item shampoo     = {4.20, 6.99, 6.49};

    cout.setf(ios::fixed);
    cout << setprecision(2);

    // Part 1: Read supermarket file
    Supermarket myMarket{};

    string szFileName;
    while (true)
    {
        cout << "Please specify the filename: ";
        cin >> szFileName;

        if (szFileName == "exit")
        {
            cout << "Exiting simulation early";
            return 0;
        }

        if (!isValidFilepath(szFileName))
        {
            cout << "Error: File path invalid. Please try again." << '\n' << '\n';
            continue;
        }

        ifstream fin(szFileName.c_str());
        if (!fin.is_open())
        {
            cout << "Error: File not found. Please try again." << '\n' << '\n';
            continue;
        }

        cout << "Processing " << szFileName << "..." << '\n';

        // Read supermarket info according to specified format
        getline(fin, myMarket.szName);             // Name
        getline(fin, myMarket.szStoreHours);       // Hours
        fin >> myMarket.dLoyaltyFee;               // Loyalty fee
        fin >> myMarket.dBudget;                   // Starting budget

        // Consume end of line after dBudget and the breaker line
        string dummy;
        getline(fin, dummy);  // consume remainder of the line after budget
        getline(fin, dummy);  // consume the breaker line: *Employee Information*

        fin >> myMarket.iNumEmployees;             // Number of employees
        fin >> myMarket.dEmployeeSalaries;         // Employee salary
        fin.close();
        break;
    }

    int iChoice = 0;
    int iFailedAttempts = 0;
    string szEmployeePass = "csmart";

    // Main menu loop (sentinel-controlled, executes at least once)
    do
    {
        displayMainMenu();
        if (!(cin >> iChoice))
        {
            return 0; // Non-numeric input: terminate gracefully
        }

        if (iChoice == -1)
        {
            break;
        }

        if (iChoice == 1)
        {
            cout << "Name: " << myMarket.szName << '\n';
            cout << "Loyalty card cost: $" << myMarket.dLoyaltyFee << '\n';
            cout << "Starting budget: $" << myMarket.dBudget << '\n';
            cout << "=============================\n";
        }
        else if (iChoice == 2)
        {
            // Aisles from LSP 1
            cout << "Aisles:\n";
            cout << "1. Frozen Foods\n";
            cout << "2. Snacks\n";
            cout << "3. Cleaning Supplies\n";
            cout << "4. Health & Beauty\n";
            cout << "5. Ice Creams\n";
        }
        else if (iChoice == 3)
        {
            // Checkout
            string szCustomerName;
            cout << "What is your name? ";
            cin >> ws;
            getline(cin, szCustomerName);

            bool bIsMember = false;
            {
                ifstream fileMembers(MEMBERS_FILE.c_str());
                if (fileMembers.is_open())
                {
                    string szMemberName;
                    while (getline(fileMembers, szMemberName))
                    {
                        if (szMemberName == szCustomerName)
                        {
                            bIsMember = true;
                            break;
                        }
                    }
                }
            }

            double dCartTotal = 0.0;
            if (bIsMember)
            {
                cout << "Welcome back " << szCustomerName << '\n';
            }
            else
            {
                cout << "Would you like to become a loyalty member (y/n)? ";
                char cResponse = 'n';
                cin >> cResponse;
                if (cResponse == 'y' || cResponse == 'Y')
                {
                    ofstream fileOut(MEMBERS_FILE.c_str(), ios::app);
                    if (fileOut.is_open())
                    {
                        fileOut << szCustomerName << '\n';
                    }
                    // Add membership fee to cart and to store funds (full fee is revenue)
                    dCartTotal += myMarket.dLoyaltyFee;
                    myMarket.dBudget += myMarket.dLoyaltyFee;
                    bIsMember = true;
                }
            }

            string szItemName;
            int iQuantity = 0;

            do
            {
                cout << "\nCurrent cart total: $" << dCartTotal << '\n';
                cout << "Please enter item name (End to exit): ";
                cin >> szItemName;

                if (szItemName == "End")
                    break;

                double dUnitPrice = 0.0;
                double dWholesale = 0.0;
                bool bFound = true;

                if (szItemName == "frozenPizza")
                {
                    cout << "Please enter the amount you would like to purchase: ";
                    cin >> iQuantity;
                    dUnitPrice = (bIsMember ? frozenPizza.dMembersPrice : frozenPizza.dRegularPrice);
                    dWholesale = frozenPizza.dWholesale;
                }
                else if (szItemName == "chips")
                {
                    cout << "Please enter the amount you would like to purchase: ";
                    cin >> iQuantity;
                    dUnitPrice = (bIsMember ? chips.dMembersPrice : chips.dRegularPrice);
                    dWholesale = chips.dWholesale;
                }
                else if (szItemName == "bleach")
                {
                    cout << "Please enter the amount you would like to purchase: ";
                    cin >> iQuantity;
                    dUnitPrice = (bIsMember ? bleach.dMembersPrice : bleach.dRegularPrice);
                    dWholesale = bleach.dWholesale;
                }
                else if (szItemName == "shampoo")
                {
                    cout << "Please enter the amount you would like to purchase: ";
                    cin >> iQuantity;
                    dUnitPrice = (bIsMember ? shampoo.dMembersPrice : shampoo.dRegularPrice);
                    dWholesale = shampoo.dWholesale;
                }
                else if (szItemName == "iceCream")
                {
                    cout << "Please enter the amount you would like to purchase: ";
                    cin >> iQuantity;
                    dUnitPrice = (bIsMember ? iceCream.dMembersPrice : iceCream.dRegularPrice);
                    dWholesale = iceCream.dWholesale;
                }
                else
                {
                    cout << szItemName << " is not sold at this store\n";
                    bFound = false;
                }

                if (bFound)
                {
                    const double dPrice = dUnitPrice * iQuantity;
                    const double dProfit = (dUnitPrice - dWholesale) * iQuantity; // profit based on actual charge
                    dCartTotal += dPrice;
                    myMarket.dBudget += dProfit;
                }

            } while (szItemName != "End");

            const double dTotalWithTax = dCartTotal * (1.0 + D_SALES_TAX);
            cout << "\nYour total is $" << dTotalWithTax << '\n';
        }
        else if (iChoice == 4)
        {
            cout << "Enter employee password: ";
            string szEnteredPass;
            cin >> szEnteredPass;

            if (szEnteredPass == szEmployeePass)
            {
                cout << "Access granted" << '\n';
                iFailedAttempts = 0;

                int iEmpChoice = 0;
                do
                {
                    displayEmployeeMenu();
                    if (!(cin >> iEmpChoice))
                    {
                        return 0;
                    }

                    if (iEmpChoice == -1)
                    {
                        break;
                    }
                    else if (iEmpChoice == 1)
                    {
                        cout << "Enter new supermarket file: ";
                        string szNewFile;
                        cin >> szNewFile;

                        ifstream fileNew(szNewFile.c_str());
                        if (fileNew.is_open())
                        {
                            getline(fileNew, myMarket.szName);
                            getline(fileNew, myMarket.szStoreHours);
                            fileNew >> myMarket.dLoyaltyFee;
                            fileNew >> myMarket.dBudget;
                            string throwAway;
                            getline(fileNew, throwAway); // consume endline after budget
                            getline(fileNew, throwAway); // consume breaker line
                            fileNew >> myMarket.iNumEmployees;
                            fileNew >> myMarket.dEmployeeSalaries;
                            fileNew.close();
                            cout << "Supermarket information updated." << '\n';
                        }
                        else
                        {
                            cout << "Error loading file. Retaining current data." << '\n';
                        }
                    }
                    else if (iEmpChoice == 2)
                    {
                        const double dTotalPay = myMarket.iNumEmployees * myMarket.dEmployeeSalaries;
                        cout << "Total payroll: $" << dTotalPay << '\n';
                        if (myMarket.dBudget >= dTotalPay)
                        {
                            myMarket.dBudget -= dTotalPay;
                            cout << "Employees paid successfully." << '\n';
                        }
                        else
                        {
                            cout << "Not enough funds to pay employees" << '\n';
                        }
                    }
                    else if (iEmpChoice == 3)
                    {
                        cout << "Current total funds: $" << myMarket.dBudget << '\n';
                    }
                    else if (iEmpChoice == 4)
                    {
                        ofstream fileClear(MEMBERS_FILE.c_str(), ios::trunc);
                        // just open+close to clear
                        cout << "Members cleared." << '\n';
                    }
                    else if (iEmpChoice == 5)
                    {
                        cout << "Enter new password: ";
                        cin >> szEmployeePass;
                        cout << "Password updated." << '\n';
                        break; // Return to original menu
                    }
                } while (true);
            }
            else
            {
                cout << "Incorrect password." << '\n';
                iFailedAttempts++;
                if (iFailedAttempts >= 3)
                {
                    cout << "Locking terminal. Please contact a store manager for assistance";
                    return 0;
                }
            }
        }

    } while (iChoice != -1);

    return 0;
}
