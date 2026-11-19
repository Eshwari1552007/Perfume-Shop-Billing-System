#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
class Perfume
{
protected:
    string name[50];
    float price[50];
    int stock[50];
    int n = 0;

public:
    void loadData()
    {
        ifstream f("perfumes.txt");
        n = 0;
        while (n < 50 && f >> name[n] >> price[n] >> stock[n])
            n++;
        f.close();
    }
    void saveData()
    {
        ofstream f("perfumes.txt");
        for (int i = 0; i < n; i++)
            f << name[i] << " " << price[i] << " " << stock[i] << endl;
        f.close();
    }
    void display()
    {
        if (n == 0)
        {
            cout << "\nNo perfumes available.\n";
            return;
        }
        cout << "\n";
        cout << "====================================================\n";
        cout << " PERFUME CATALOGUE \n";
        cout << "====================================================\n";
        cout << left << setw(8) << "ID"
             << setw(20) << "Name"
             << right << setw(12) << "Price (Rs.)"
             << setw(10) << "Stock" << endl;
        cout << "----------------------------------------------------\n";
        for (int i = 0; i < n; i++)
        {
            cout << left << setw(8) << i + 1
                 << setw(20) << name[i]
                 << right << setw(12) << fixed << setprecision(2) << price[i]
                 << setw(10) << stock[i] << endl;
        }
        cout << "====================================================\n";
    }
};
class PerfumeShop : public Perfume
{
public:
    PerfumeShop()
    {
        loadData();
    }
    void addPerfume()
    {
        if (n >= 50)
        {
            cout << "\nCatalogue is full.\n";
            return;
        }
        cout << "\nEnter perfume name (no spaces): ";
        cin >> name[n];
        for (int i = 0; i < n; i++)
        {
            if (name[i] == name[n])
            {
                cout << "Perfume already exists.\n";
                return;
            }
        }
        cout << "Enter price: ";
        cin >> price[n];
        cout << "Enter stock: ";
        cin >> stock[n];
        if (price[n] <= 0 || stock[n] < 0)
        {
            cout << "Invalid price or stock.\n";
            return;
        }
        n++;
        saveData();
        cout << "\nPerfume added and saved successfully.\n";
    }
    void searchPerfume()
    {
        string s;
        cout << "\nEnter perfume name: ";
        cin >> s;
        for (int i = 0; i < n; i++)
        {
            if (name[i] == s)
            {

                cout << "\n----------------------------------------\n";
                cout << " PERFUME DETAILS \n";
                cout << "----------------------------------------\n";
                cout << left << setw(15) << "Name" << ": " << name[i] << endl;
                cout << left << setw(15) << "Price" << ": Rs. "
                     << fixed << setprecision(2) << price[i] << endl;
                cout << left << setw(15) << "Stock" << ": " << stock[i] << endl;
                cout << "----------------------------------------\n";
                return;
            }
        }
        cout << "Perfume not found.\n";
    }
    void updatePerfume()
    {
        int id;
        display();
        if (n == 0)
            return;
        cout << "\nEnter perfume ID to update: ";
        cin >> id;
        if (id < 1 || id > n)
        {
            cout << "Invalid ID.\n";
            return;
        }
        float newPrice;
        int newStock;
        cout << "Enter new price: ";
        cin >> newPrice;
        cout << "Enter new stock: ";
        cin >> newStock;
        if (newPrice <= 0 || newStock < 0)
        {
            cout << "Invalid price or stock.\n";
            return;
        }
        price[id - 1] = newPrice;
        stock[id - 1] = newStock;
        saveData();
        cout << "Perfume updated and saved successfully.\n";
    }
    void purchase()
    {
        int id, qty;
        float total = 0;

        bool bought = false;
        if (n == 0)
        {
            cout << "\nNo perfumes available.\n";
            return;
        }
        ofstream bill("bills.txt", ios::app);
        if (!bill)
        {
            cout << "Unable to create bill file.\n";
            return;
        }
        cout << "\n";
        cout << "============================================================\n";
        cout << " PERFUME SHOP BILL \n";
        cout << "============================================================\n";
        cout << left << setw(20) << "Name"
             << right << setw(8) << "Qty"
             << setw(14) << "Price"
             << setw(14) << "Amount" << endl;
        cout << "------------------------------------------------------------\n";
        bill << "\n";
        bill << "============================================================\n";
        bill << " PERFUME SHOP BILL \n";
        bill << "============================================================\n";
        bill << left << setw(20) << "Name"
             << right << setw(8) << "Qty"
             << setw(14) << "Price"
             << setw(14) << "Amount" << endl;
        bill << "------------------------------------------------------------\n";
        display();
        while (true)
        {
            cout << "\nEnter perfume ID (0 to finish): ";
            cin >> id;
            if (id == 0)
                break;
            if (id < 1 || id > n)
            {
                cout << "Invalid ID.\n";
                continue;
            }
            cout << "Enter quantity: ";
            cin >> qty;
            if (qty <= 0 || qty > stock[id - 1])
            {
                cout << "Invalid quantity or insufficient stock.\n";

                continue;
            }
            float amount = price[id - 1] * qty;
            total += amount;
            stock[id - 1] -= qty;
            bought = true;
            cout << left << setw(20) << name[id - 1]
                 << right << setw(8) << qty
                 << setw(14) << fixed << setprecision(2) << price[id - 1]
                 << setw(14) << amount << endl;
            bill << left << setw(20) << name[id - 1]
                 << right << setw(8) << qty
                 << setw(14) << fixed << setprecision(2) << price[id - 1]
                 << setw(14) << amount << endl;
        }
        cout << "------------------------------------------------------------\n";
        cout << right << setw(42) << "Grand Total (Rs.): "
             << setw(14) << fixed << setprecision(2) << total << endl;
        cout << "============================================================\n";
        if (bought)
        {
            bill << "------------------------------------------------------------\n";
            bill << right << setw(42) << "Grand Total (Rs.): "
                 << setw(14) << fixed << setprecision(2) << total << endl;
            bill << "============================================================\n";
            saveData();
            cout << "\nBill saved in bills.txt\n";
            cout << "Stock updated in perfumes.txt\n";
        }
        else
        {
            bill << "No purchase made.\n";
            cout << "\nNo purchase made.\n";
        }
        bill.close();
    }
    void menu()
    {
        int ch;
        do
        {
            cout << "\n";
            cout << "========================================\n";
            cout << " PERFUME SHOP BILLING SYSTEM \n";
            cout << "========================================\n";
            cout << " 1. Add Perfume\n";
            cout << " 2. Display Perfumes\n";
            cout << " 3. Search Perfume\n";
            cout << " 4. Update Perfume\n";
            cout << " 5. Purchase and Generate Bill\n";
            cout << " 6. Exit\n";

            cout << "========================================\n";
            cout << " Enter your choice: ";
            cin >> ch;
            switch (ch)
            {
            case 1:
                addPerfume();
                break;
            case 2:
                display();
                break;
            case 3:
                searchPerfume();
                break;
            case 4:
                updatePerfume();
                break;
            case 5:
                purchase();
                break;
            case 6:
                cout << "\nThank you for visiting!\n";
                break;
            default:
                cout << "\nInvalid choice. Try again.\n";
            }
        } while (ch != 6);
    }
};
int main()
{
    PerfumeShop p;
    p.menu();
    return 0;
}