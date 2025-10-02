#include <iostream>
#include <vector>
#include "bank_customer.h"
#include "buyer.h"
#include "seller.h"

enum PrimaryPrompt{LOGIN, REGISTER, EXIT, ADMIN_LOGIN};
enum RegisterPrompt{CREATE_BUYER, CREATE_SELLER, BACK};
using namespace std;

int main() {
    //create a loop prompt 
    PrimaryPrompt prompt = LOGIN;
    RegisterPrompt regPrompt = CREATE_BUYER;
    const string ADMIN_USERNAME = "root";
    const string ADMIN_PASSWORD = "toor";
    string username, password;

    //Penyimpanan data
    vector<Buyer> buyers;
    vector<seller> sellers;
    int nextBuyerId = 1;
    int nextSellerId = 1;

    while (prompt != EXIT) {
        cout << "Select an option: " << endl;
        cout << "1. Login" << endl;
        cout << "2. Register" << endl;
        cout << "3. Exit" << endl;
        cout << "4. Admin Login" << endl;
        int choice;
        cin >> choice;
        prompt = static_cast<PrimaryPrompt>(choice - 1);
        switch (prompt) {
            case LOGIN: {
                cout << "=== Login ===" << endl;
                int id;
                cout << "Enter Buyer/Seller ID: ";
                cin >> id;

                bool loggedIn = false;

                // cek Buyer dulu
                for (auto &b : buyers) {
                    if (b.getId() == id) {
                        cout << "Logged in as Buyer: " << b.getName() << endl;
                        // TODO: menu Buyer
                        loggedIn = true;
                        break;
                    }
                }

                // cek Seller
                for (auto &s : sellers) {
                    if (s.getId() == id) {
                        cout << "Logged in as Seller: " << s.getName() << endl;
                        // TODO: menu Seller
                        loggedIn = true;
                        break;
                    }
                }

                if (!loggedIn) {
                    cout << "Account not found!" << endl;
                }
                break;
            }

                /* if Login is selected, based on authority then provide options:
                assume user is logged in as Buyer for now
                1. Chek Account Status (will display if user is Buyer or Seller or both and linked banking account status)
                Will display Buyer, Seller and Banking Account details
                2. Upgrade Account to Seller
                Will prompt user to enter Seller details and create a Seller account linked to Buyer account
                Will reject if a user dont have a banking account linked
                3. Create Banking Account (if not already linked), will be replaced with banking functions
                Must provides: initial deposit amount, Address, Phone number, Email
                Banking functions will provides: Balance checking, Transaction History, Deposit, Withdraw
                4. Browse Store Functionality
                Will display all stores initially
                Need to select a store to browse each store inventory
                Will display all items in the store inventory
                After selecting an item, will display item details and option to add to cart
                After adding to cart, will notify user item is added to cart
                5. Order Functionality
                Will display all items in cart
                Will provide option to remove item from cart
                Will provide option to checkout
                After checkout invoide will be generated (will go to payment functionality)
                6. Payment Functionality
                Will display all listed invoices
                Pick an invoice to pay
                Will display invoice details and total amount
                Will provide option to pay invoice
                Payment is done through confirmation dialogue
                In confirmation dialogue, will display account balance as precursor
                User will need to manually enter invoice id to pay
                After paying balance will be redacted from buyer and added to the responding seller account
                After payment, order status will be changed to paid
                7. Logout (return to main menu)
                Display confirmation dialogue
                If confirmed, return to main menu
                If not, return to Buyer menu
                8. Delete Account (remove both Buyer and Seller account and relevant banking account)
                Display confirmation dialogue
                If confirmed, delete account and return to main menu
                If not, return to Buyer menu

                assume user is logged in as Seller for now
                9. Check Inventory
                10. Add Item to Inventory
                11. Remove Item from Inventory
                12. View Orders (will display all orders placed to this seller
                Only orders with paid status will be listed
                Order details will listing items, quantity, total amount, buyer details, order status (paid, cancelled, completed)
                extra functions
                9. Exit to main Menu
                10. Exit Program
                **/
            case REGISTER:
                regPrompt = CREATE_BUYER; // reset regPrompt to CREATE_BUYER when entering register menu
                while (regPrompt != BACK){
                    cout << "Register selected. " << endl;
                    cout << "Select an option: " << endl;
                    cout << "1. Create Buyer Account" << endl;
                    cout << "2. Create Seller Account" << endl;
                    cout << "3. Back" << endl;
                    int regChoice;
                    cin >> regChoice;
                    regPrompt = static_cast<RegisterPrompt>(regChoice - 1);
                    switch (regPrompt) {
                        case CREATE_BUYER: {
                            cout << "=== Create Buyer Account ===" << endl;
                            string name;
                            cout << "Enter name: ";
                            cin >> name;

                            // buat BankCustomer dummy dengan saldo awal 0
                            BankCustomer newCustomer(nextBuyerId, name, 0.0);

                            // buat Buyer dengan akun bank
                            Buyer newBuyer(nextBuyerId, name, newCustomer);
                            buyers.push_back(newBuyer);

                            cout << "Buyer account created with ID: " << nextBuyerId << endl;
                            nextBuyerId++;
                            break;
                            }
                        case CREATE_SELLER: {
                            if (buyers.empty()) {
                                cout << "No buyers available to upgrade. Please create a Buyer first." << endl;
                                break;
                            }

                            cout << "=== Upgrade Buyer to Seller ===" << endl;
                            int buyerId;
                            cout << "Enter Buyer ID to upgrade: ";
                            cin >> buyerId;

                            bool found = false;
                            for (auto &b : buyers) {
                                if (b.getId() == buyerId) {
                                    string storeName;
                                    cout << "Enter Store Name: ";
                                    cin >> storeName;
                                    seller newSeller(b, nextSellerId, storeName);
                                    sellers.push_back(newSeller);
                                    cout << "Seller account created for Buyer ID: " << buyerId << endl;
                                    nextSellerId++;
                                    found = true;
                                    break;
                                }
                            }
                            if (!found) {
                                cout << "Buyer not found!" << endl;
                            }
                            break;
                        }

                        case BACK:
                            cout << "Back selected." << endl;
                            break;
                        default:
                            cout << "Invalid option." << endl;
                            break;
                    }
                }
                /* if register is selected then went throuhh registration process:
                1. Create a new Buyer Account
                Must provides: Name, Home Address, Phone number, Email
                2. Option to create a Seller Account (will be linked to Buyer account)
                Must Provides 1: Home Address, Phone number, Email
                Must provides 2: Store Name, Store Address, Store Phone number, Store Email
                Must provides 3: initial deposit amount
                After finished immediately logged in as Buyer/Seller
                */
                break;
            case EXIT:
                cout << "Exiting." << endl;
                break;
            case ADMIN_LOGIN:
                /* Prompt for username & password then check the entries with our hard coded features */
                cout << "=== Admin Login ===" << endl;
                cout << "Username: ";
                cin >> username;
                cout << "Password: ";
                cin >> password;
                
                if (username == ADMIN_USERNAME && password == ADMIN_PASSWORD) {
                cout << "Admin login sukses.\n";

                bool adminExit = false;
                while (!adminExit) {
                    cout << "\n--- ADMIN MENU ---\n";
                    cout << "1. View all Buyers\n";
                    cout << "2. View all Sellers\n";
                    cout << "3. Logout to main menu\n";
                    cout << "Pilih: ";
                    int achoice;
                    cin >> achoice;

                    switch (achoice) {
                        case 1: {
                            cout << "\n-- Buyers List --\n";
                            if (buyers.empty()) {
                                cout << "No buyers registered.\n";
                            } else {
                                for (const auto &b : buyers) {
                                    cout << "ID: " << b.getId()
                                        << " | Name: " << b.getName() << "\n";
                                }
                            }
                            break;
                        }
                        case 2: {
                            cout << "\n-- Sellers List --\n";
                            if (sellers.empty()) {
                                cout << "No sellers registered.\n";
                            } else {
                                for (const auto &s : sellers) {
                                    cout << "SellerID: " << s.getSellerId()
                                        << " | Store: " << s.getStoreName()
                                        << " | OwnerID: " << s.getId()
                                        << " | OwnerName: " << s.getName() << "\n";
                                }
                            }
                            break;
                        }
                        case 3:
                            adminExit = true;
                            cout << "Logging out admin...\n";
                            break;
                        default:
                            cout << "Invalid admin option.\n";
                    }
                }
            } else {
                cout << "Admin login failed: invalid credentials.\n";
            }
            break;
            }

                /** After login create a sub prompt that provides the following features
                1. Account Management
                    - View All Buyers, Sellers
                    - View All details of Buyers, Sellers
                    - Seek certain buyer of seller based on Name / account Id / address / phone number
                    - Create new buyer/seller/Bank account
                    - Remove buyer/seller based on ID (all related info will be deleted)
                2. System Report
                    - Total number of Buyers, Sellers
                    - Total number of Banking Accounts
                */
                
        cout << endl;
    }

    //BankCustomer customer1(1, "Alice", 1000.0);
    //Buyer buyer1(1, customer1.getName(), customer1);
    return 1;
}