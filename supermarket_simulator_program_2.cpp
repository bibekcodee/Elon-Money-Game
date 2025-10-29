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

#include <iostream>   // For input/output operations
#include <iomanip>    // For setprecision and fixed formatting
#include <fstream>    // For file I/O operations
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
    double dEmployeeSalaries;   // Employee salary
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

int main()
{
    /*********************************************************************
    Purpose:
        Controls program flow for supermarket simulation.
    *********************************************************************/

    // ------------------- Variable Declarations -------------------
    string szBreakMessage = "=============================\n";
    const double D_SALES_TAX = 0.07;
    string szEmployeePass = "csmart";
    int iChoice = 0;
    int iFailedAttempts = 0;
    Supermarket myMarket;

    // ------------------- Item Initialization -------------------
    Item frozenPizza = {3.75, 5.99, 5.49};
    Item iceCream    = {2.95, 4.79, 4.29};
    Item chips       = {1.85, 3.49, 2.99};
    Item bleach      = {2.10, 3.79, 3.29};
    Item shampoo     = {4.20, 6.99, 6.49};

    cout << fixed << setprecision(2);

    // ------------------- Part 1: Read supermarket file -------------------
    string szFileName;
    cout << "Starting supermarket simulation" << endl << endl;

    while (true)
    {
        cout << "Please specify the filename: ";
        cin >> szFileName;

        if (szFileName == "exit")
        {
            cout << "Exiting simulation early" << endl;
            return 0;
        }

        if (szFileName.find(' ') != string::npos || szFileName.find(".txt") == string::npos)
        {
            cout << "Error: File path invalid. Please try again." << endl;
            continue;
        }

        ifstream fin(szFileName.c_str());
        if (!fin.is_open())
        {
            cout << "Error: File not found. Please try again." << endl;
            continue;
        }

        cout << "Processing " << szFileName << "..." << endl;
        getline(fin, myMarket.szName);
        getline(fin, myMarket.szStoreHours);
        fin >> myMarket.dLoyaltyFee;
        fin >> myMarket.dBudget;
        string szTemp;
        fin >> szTemp;
        fin >> myMarket.iNumEmployees;
        fin >> myMarket.dEmployeeSalaries;
        fin.close();
        break;
    }

    // ------------------- Main Menu Loop -------------------
    do{

        cout << "\nMenu\n" << szBreakMessage;
        cout << "1. Display Supermarket Information\n";
        cout << "2. Display Aisles information\n";
        cout << "3. Checkout\n";
        cout << "4. Access Employee Menu\n";
        cout << "-1. Exit program\n" << szBreakMessage << endl;
        cout << "Enter choice: ";
        cin >> iChoice;

        if (iChoice == -1)
        {
            break;
        }

        cout << szBreakMessage << endl;

        // ---------- Option 1: Display Supermarket Info ----------
        if (iChoice == 1)
        {
            cout << "Name: " << myMarket.szName << endl;
            cout << "Loyalty card cost: $" << myMarket.dLoyaltyFee << endl;
            cout << "Starting budget: $" << myMarket.dBudget << endl;
            cout << szBreakMessage;
        }

        // ---------- Option 2: Display Aisles ----------
        else if (iChoice == 2)
        {
            cout << "Aisles:\n";
            cout << "1. Frozen Foods\n";
            cout << "2. Snacks\n";
            cout << "3. Cleaning Supplies\n";
            cout << "4. Health & Beauty\n";
            cout << "5. Ice Creams\n";
        }

        // ---------- Option 3: Checkout ----------
        else if (iChoice == 3)
        {
            string szCustomerName;
            cout << "What is your name? ";
            cin >> ws;
            getline(cin, szCustomerName);

            bool bIsMember = false;
            ifstream fileMembers("members.txt");
            string szMemberName;
            while (getline(fileMembers, szMemberName))
            {
                if (szMemberName == szCustomerName)
                {
                    bIsMember = true;
                    break;
                }
            }
            fileMembers.close();

            double dCartTotal = 0.0;

            if (bIsMember)
            {
                cout << "Welcome back " << szCustomerName << endl;
            }
            else
            {
                cout << "Would you like to become a loyalty member (y/n)? ";
                char cResponse;
                cin >> cResponse;

                if (cResponse == 'y' || cResponse == 'Y')
                {
                    ofstream fileOut("members.txt", ios::app);
                    fileOut << szCustomerName << endl;
                    fileOut.close();
                    bIsMember = true;
                    dCartTotal = myMarket.dLoyaltyFee;
                }
            }

            string szItemName;
            int iQuantity = 0;

            do
            {
                cout << "\nCurrent cart total: $" << dCartTotal << endl;
                cout << "Please enter item name (End to exit): ";
                cin >> szItemName;

                if (szItemName == "End")
                    break;

                double dPrice = 0.0;
                double dProfit = 0.0;
                bool bFound = true;

                if (szItemName == "frozenPizza")
                {
                    cout << "Please enter the amount you would like to purchase: ";
                    cin >> iQuantity;
                    dPrice = (bIsMember ? frozenPizza.dMembersPrice : frozenPizza.dRegularPrice) * iQuantity;
                    dProfit = (frozenPizza.dRegularPrice - frozenPizza.dWholesale) * iQuantity;
                }
                else if (szItemName == "chips")
                {
                    cout << "Please enter the amount you would like to purchase: ";
                    cin >> iQuantity;
                    dPrice = (bIsMember ? chips.dMembersPrice : chips.dRegularPrice) * iQuantity;
                    dProfit = (chips.dRegularPrice - chips.dWholesale) * iQuantity;
                }
                else if (szItemName == "bleach")
                {
                    cout << "Please enter the amount you would like to purchase: ";
                    cin >> iQuantity;
                    dPrice = (bIsMember ? bleach.dMembersPrice : bleach.dRegularPrice) * iQuantity;
                    dProfit = (bleach.dRegularPrice - bleach.dWholesale) * iQuantity;
                }
                else if (szItemName == "shampoo")
                {
                    cout << "Please enter the amount you would like to purchase: ";
                    cin >> iQuantity;
                    dPrice = (bIsMember ? shampoo.dMembersPrice : shampoo.dRegularPrice) * iQuantity;
                    dProfit = (shampoo.dRegularPrice - shampoo.dWholesale) * iQuantity;
                }
                else if (szItemName == "iceCream")
                {
                    cout << "Please enter the amount you would like to purchase: ";
                    cin >> iQuantity;
                    dPrice = (bIsMember ? iceCream.dMembersPrice : iceCream.dRegularPrice) * iQuantity;
                    dProfit = (iceCream.dRegularPrice - iceCream.dWholesale) * iQuantity;
                }
                else
                {
                    cout << szItemName << " is not sold at this store" << endl;
                    bFound = false;
                }

                if (bFound)
                {
                    dCartTotal += dPrice;
                    myMarket.dBudget += dProfit;
                }

            } while (szItemName != "End");

            double dTotalWithTax = dCartTotal * (1 + D_SALES_TAX);
            cout << "\nYour total is $" << dTotalWithTax << endl;
        }

        // ---------- Option 4: Employee Menu ----------
        else if (iChoice == 4)
        {
            string szEnteredPass;
            cout << "Enter employee password: ";
            cin >> szEnteredPass;

            if (szEnteredPass == szEmployeePass)
            {
                cout << "Access granted" << endl;
                iFailedAttempts = 0;

                int iEmpChoice = 0;
                do
                {
                    cout << "\nEmployee Menu\n" << szBreakMessage;
                    cout << "1. Update Supermarket File\n";
                    cout << "2. Pay Employees\n";
                    cout << "3. Display Total Funds\n";
                    cout << "4. Clear Current Members\n";
                    cout << "5. Change Password\n";
                    cout << "-1. Exit Employee Menu\n" << szBreakMessage;
                    cout << "Enter choice: ";
                    cin >> iEmpChoice;

                    if (iEmpChoice == 1)
                    {
                        string szNewFile;
                        cout << "Enter new supermarket file: ";
                        cin >> szNewFile;

                        ifstream fileNew(szNewFile.c_str());
                        if (fileNew.is_open())
                        {
                            getline(fileNew, myMarket.szName);
                            getline(fileNew, myMarket.szStoreHours);
                            fileNew >> myMarket.dLoyaltyFee;
                            fileNew >> myMarket.dBudget;
                            string szTemp;
                            fileNew >> szTemp;
                            fileNew >> myMarket.iNumEmployees;
                            fileNew >> myMarket.dEmployeeSalaries;
                            fileNew.close();
                            cout << "Supermarket information updated.\n";
                        }
                        else
                        {
                            cout << "Error loading file. Retaining current data.\n";
                        }
                    }
                    else if (iEmpChoice == 2)
                    {
                        double dTotalPay = myMarket.iNumEmployees * myMarket.dEmployeeSalaries;
                        cout << "Total payroll: $" << dTotalPay << endl;
                        if (myMarket.dBudget >= dTotalPay)
                        {
                            myMarket.dBudget -= dTotalPay;
                            cout << "Employees paid successfully.\n";
                        }
                        else
                        {
                            cout << "Not enough funds to pay employees\n";
                        }
                    }
                    else if (iEmpChoice == 3)
                    {
                        cout << "Current total funds: $" << myMarket.dBudget << endl;
                    }
                    else if (iEmpChoice == 4)
                    {
                        ofstream fileClear("members.txt", ios::trunc);
                        fileClear.close();
                        cout << "Members cleared.\n";
                    }
                    else if (iEmpChoice == 5)
                    {
                        cout << "Enter new password: ";
                        cin >> szEmployeePass;
                        cout << "Password updated.\n";
                        iEmpChoice = -1;
                    }

                } while (iEmpChoice != -1);

                cout << "Exiting employee menu.\n";
            }
            else
            {
                cout << "Incorrect password." << endl;
                iFailedAttempts++;
                if (iFailedAttempts >= 3)
                {
                    cout << "Locking terminal. Please contact a store manager for assistance" << endl;
                    return 0;
                }
            }
        }

    } while (iChoice != -1);
    
    cout << "Finished simulation" << endl;
    return 0;
}
