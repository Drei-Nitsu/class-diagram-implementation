#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#include <vector>

using namespace std;

class Product {
private:
    int id;
    string name;
    float price;
    int stock;

public:
    Product() {}

    Product(int i, string n, float p, int s) {
        id = i;
        name = n;
        price = p;
        stock = s;
    }

    int getId() const { return id; }
    string getName() const { return name; }
    float getPrice() const { return price; }
    int getStock() const { return stock; }
};

class Order {
public:
    vector<Product> products;
    vector<int> quantities;
    int orderID;
    float totalAmount;

    Order(int id, vector<Product> p, vector<int> q, float total) {
        orderID = id;
        products = p;
        quantities = q;
        totalAmount = total;
    }
};

class ShoppingCart {
public:
    vector<Product> products;
    vector<int> quantities;
    vector<Order> orderHistory;
    int nextOrderID;

    ShoppingCart() {
        nextOrderID = 1;
    }

    void addProduct(Product p) {
        for (size_t i = 0; i < products.size(); i++) {
            if (products[i].getId() == p.getId()) {
                quantities[i]++;
                return;
            }
        }
        products.push_back(p);
        quantities.push_back(1);
        cout << "Product added successfully!" << endl;
    }

    void viewCart() {
        if (products.empty()) {
            cout << "Shopping cart is empty!" << endl;
            return;
        }
        cout << "\nID   Name        Price    Quantity" << endl;
        float total = 0;
        for (size_t i = 0; i < products.size(); i++) {
            cout << left << setw(5) << products[i].getId() << setw(12) << products[i].getName()
                 << setw(9) << products[i].getPrice() << setw(10) << quantities[i] << endl;
            total += products[i].getPrice() * quantities[i];
        }
        cout << "Total Amount: " << total << endl;

        char confirm;
        cout << "Do you want to check out all the products? (y/n): ";
        while (!(cin >> confirm) || (confirm != 'y' && confirm != 'Y' && confirm != 'n' && confirm != 'N')) {
            cout << "Invalid input! Enter 'y' or 'n': ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        if (confirm == 'Y' || confirm == 'y') {
            orderHistory.push_back(Order(nextOrderID++, products, quantities, total));
            cout << "You have successfully checked out the products!" << endl;
            products.clear();
            quantities.clear();
        }
    }

    void viewOrders() {
        if (orderHistory.empty()) {
            cout << "\nNo orders available! Use checkout to place an order." << endl;
            return;
        }
        for (const auto& order : orderHistory) {
            cout << "\nOrder ID: " << order.orderID << endl;
            cout << "Total Amount: " << order.totalAmount << endl;
            cout << "Order Details:" << endl;
            cout << left << setw(12) << "Product ID" << setw(20) << "Name"
                 << setw(10) << "Price" << setw(10) << "Quantity" << endl;

            for (size_t i = 0; i < order.products.size(); i++) {
                cout << left << setw(12) << order.products[i].getId()
                     << setw(20) << order.products[i].getName()
                     << setw(10) << fixed << setprecision(2) << order.products[i].getPrice()
                     << setw(10) << order.quantities[i] << endl;
            }
        }
    }
};

int main() {
    Product productList[3] = {
        Product(1, "Laptop", 50000, 10),
        Product(2, "Tablet", 20000, 15),
        Product(3, "Phone", 30000, 20)
    };

    ShoppingCart cart;
    char choice;

    while (true) {
        cout << "\nMENU" << endl;
        cout << "1. View Products" << endl;
        cout << "2. View Shopping Cart" << endl;
        cout << "3. View Orders" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter choice: ";
        while (!(cin >> choice) || choice < '1' || choice > '4') {
            cout << "Invalid input! Enter a number between 1-4: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        if (choice == '1') {
            while (true) {
                cout << "\nAvailable Products:" << endl;
                cout<<"Order ID"<<endl;
                for (int i = 0; i < 3; i++) {
                    cout << left << setw(5) << productList[i].getId()
                         << setw(12) << productList[i].getName()
                         << setw(10) << productList[i].getPrice() << endl;
                }
                int prodId;
                cout << "Enter the ID of the product you want to add in the shopping cart (0 to cancel): ";
                while (!(cin >> prodId) || (prodId < 0 || prodId > 3)) {
                    cout << "Invalid input! Enter a valid product ID (0 to cancel): ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                if (prodId == 0) break;
                cart.addProduct(productList[prodId - 1]);

                char addMore;
                while (true) {
                    cout << "Do you want to add another product to the shopping cart? (y/n): ";
                    cin >> addMore;

                    if (addMore == 'y' || addMore == 'Y') {
                        break; 
                    } else if (addMore == 'n' || addMore == 'N') {
                        goto nextMenu; 
                    } else {
                        cout << "Invalid input. Please enter 'y' or 'n' only.\n";
                    }
                }
            }
        nextMenu:
            continue; 
        } 
        else if (choice == '2') {
            cart.viewCart();
        } 
        else if (choice == '3') {
            cart.viewOrders();
        } 
        else if (choice == '4') {
            cout << "Exiting program..." << endl;
            break;
        }
    }
    return 0;
}
