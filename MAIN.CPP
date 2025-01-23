#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct Product
{
    int id;
    string name;
    string description;
    vector<string> tags;
    double price;
    int quantity;
};

vector<Product> products;

void addInitialProducts()
{
    products.push_back({1, "Laptop", "High-end gaming laptop", {"electronics", "gaming"}, 1200.99, 5});
    products.push_back({2, "Phone", "Smartphone with great camera", {"electronics", "camera"}, 799.99, 10});
    products.push_back({3, "Book", "Science fiction novel", {"books", "fiction"}, 15.99, 20});
    products.push_back({4, "Headphones", "Noise-cancelling headphones", {"electronics", "audio"}, 299.99, 15});
    products.push_back({5, "Keyboard", "Mechanical gaming keyboard", {"electronics", "gaming"}, 99.99, 25});
    products.push_back({6, "Mouse", "Wireless mouse for gaming", {"electronics", "gaming"}, 49.99, 30});
    products.push_back({7, "Monitor", "24-inch gaming monitor", {"electronics", "gaming"}, 199.99, 10});
    products.push_back({8, "Speaker", "High-quality speaker system", {"electronics", "audio"}, 399.99, 5});
    products.push_back({9, "Tablet", "iPad with high-performance processor", {"electronics", "gaming"}, 699.99, 8});
    products.push_back({10, "Camera", "Professional DSLR camera", {"electronics", "camera"}, 1499.99, 3});
    products.push_back({11, "Watch", "Smartwatch with fitness tracking", {"electronics", "fitness"}, 249.99, 12});
    products.push_back({12, "Sunglasses", "Polarized sunglasses for outdoor activities", {"fashion", "outdoor"}, 129.99, 20});
    products.push_back({13, "Bike", "Mountain bike for off-road adventures", {"sports", "outdoor", "sports"}, 599.99, 5});
    products.push_back({14, "Backpack", "Waterproof hiking backpack", {"outdoor", "travel"}, 79.99, 15});
    products.push_back({15, "Headphones", "Wireless earbuds with active noise cancellation", {"electronics", "audio"}, 199.99, 10});
    products.push_back({16, "Smartphone", "Flagship smartphone with advanced features", {"electronics", "gaming"}, 999.99, 5});
    products.push_back({17, "Laptop", "Ultra-thin laptop with long battery life", {"electronics", "gaming"}, 899.99, 8});
    products.push_back({18, "Tablet", "Android tablet with high-resolution display", {"electronics", "gaming"}, 499.99, 10});
    products.push_back({19, "Novels", "Collection of classic novels", {"books", "fiction"}, 49.99, 20});
    products.push_back({20, "Sports Shoes", "Running shoes with cushioned soles", {"sports", "running"}, 99.99, 15});
    products.push_back({21, "T-shirt", "Cotton t-shirt with graphic print", {"fashion", "clothing"}, 19.99, 30});
    products.push_back({22, "Socks", "Pack of 6 athletic socks", {"sports", "clothing"}, 14.99, 50});
    products.push_back({23, "Sunglasses", "Polarized sunglasses for outdoor activities", {"fashion", "outdoor"}, 129.99, 20});
    products.push_back({24, "Shirts", "Cotton shirts with different colors", {"fashion", "clothing"}, 29.99, 40});
    products.push_back({25, "Jeans", "Denim jeans with different styles", {"fashion", "clothing"}, 49.99, 30});
    products.push_back({26, "Jacket", "Winter jacket with fur lining", {"fashion", "clothing"}, 79.99, 20});
    products.push_back({27, "Sweatshirt", "Cotton sweatshirt with different colors", {"fashion", "clothing"}, 39.99, 25});
    products.push_back({28, "Sneakers", "Running sneakers with cushioned soles", {"sports", "running"}, 89.99, 15});
    products.push_back({29, "Sandals", "Casual sandals for everyday wear", {"fashion", "footwear"}, 24.99, 35});
    products.push_back({30, "Boots", "Leather boots for outdoor adventures", {"fashion", "footwear"}, 69.99, 10});
}

void displayProduct(const Product &product)
{
    cout << "Product ID: " << product.id << endl;
    cout << "Name: " << product.name << endl;
    cout << "Description: " << product.description << endl;
    cout << "Tags: ";
    for (const auto &tag : product.tags)
    {
        cout << tag << " ";
    }
    cout << endl;
    cout << "Price: $" << product.price << endl;
    cout << "Available Quantity: " << product.quantity << endl;
    cout << "-----------------------------------" << endl;
}

void displayAllProducts()
{
    if (products.empty())
    {
        cout << "No products available." << endl;
        return;
    }
    for (const auto &product : products)
    {
        displayProduct(product);
    }
}

void linearSearch(string keyword)
{
    bool found = false;
    for (const auto &product : products)
    {
        if (product.description.find(keyword) != string::npos ||
            find(product.tags.begin(), product.tags.end(), keyword) != product.tags.end())
        {
            found = true;
            displayProduct(product);
        }
    }
    if (!found)
    {
        cout << "No products found for keyword: " << keyword << endl;
    }
}

int binarySearch(const vector<Product> &sortedProducts, int left, int right, double key, bool isPriceSearch)
{
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        double value = isPriceSearch ? sortedProducts[mid].price : sortedProducts[mid].id;

        if (value == key)
            return mid;
        else if (value < key)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

void searchByPriceOrID(double key, bool isPriceSearch)
{
    vector<Product> sortedProducts = products;

    sort(sortedProducts.begin(), sortedProducts.end(), [&](Product a, Product b)
         { return isPriceSearch ? a.price < b.price : a.id < b.id; });

    int index = binarySearch(sortedProducts, 0, sortedProducts.size() - 1, key, isPriceSearch);
    if (index != -1)
    {
        displayProduct(sortedProducts[index]);
    }
    else
    {
        cout << (isPriceSearch ? "Price" : "Product ID") << " not found: " << key << endl;
    }
}

void addNewProduct()
{
    Product newProduct;
    cout << "Enter Product ID: ";
    cin >> newProduct.id;
    cin.ignore(); // Clear newline character
    cout << "Enter Product Name: ";
    getline(cin, newProduct.name);
    cout << "Enter Product Description: ";
    getline(cin, newProduct.description);

    cout << "Enter Tags (space-separated): ";
    string tagsLine;
    getline(cin, tagsLine);
    newProduct.tags = {};
    size_t pos;
    while ((pos = tagsLine.find(' ')) != string::npos)
    {
        newProduct.tags.push_back(tagsLine.substr(0, pos));
        tagsLine.erase(0, pos + 1);
    }
    newProduct.tags.push_back(tagsLine);

    cout << "Enter Product Price: ";
    cin >> newProduct.price;
    cout << "Enter Product Quantity: ";
    cin >> newProduct.quantity;

    products.push_back(newProduct);
    cout << "Product added successfully!" << endl;
}

void updateProductQuantity()
{
    int id, newQuantity;
    cout << "Enter Product ID to update quantity: ";
    cin >> id;

    auto it = find_if(products.begin(), products.end(), [id](Product &p)
                      { return p.id == id; });
    if (it != products.end())
    {
        cout << "Enter new quantity: ";
        cin >> newQuantity;
        it->quantity = newQuantity;
        cout << "Quantity updated successfully!" << endl;
    }
    else
    {
        cout << "Product not found." << endl;
    }
}

void deleteProduct()
{
    int id;
    cout << "Enter Product ID to delete: ";
    cin >> id;

    auto it = remove_if(products.begin(), products.end(), [id](Product &p)
                        { return p.id == id; });
    if (it != products.end())
    {
        products.erase(it, products.end());
        cout << "Product deleted successfully!" << endl;
    }
    else
    {
        cout << "Product not found." << endl;
    }
}

void bubbleSort(vector<Product> &products, bool sortByPrice)
{
    for (size_t i = 0; i < products.size() - 1; ++i)
    {
        for (size_t j = 0; j < products.size() - i - 1; ++j)
        {
            if ((sortByPrice && products[j].price > products[j + 1].price) ||
                (!sortByPrice && products[j].id > products[j + 1].id))
            {
                swap(products[j], products[j + 1]);
            }
        }
    }
}

void selectionSort(vector<Product> &products, bool sortByPrice)
{
    for (size_t i = 0; i < products.size() - 1; ++i)
    {
        size_t minIndex = i;
        for (size_t j = i + 1; j < products.size(); ++j)
        {
            if ((sortByPrice && products[j].price < products[minIndex].price) ||
                (!sortByPrice && products[j].id < products[minIndex].id))
            {
                minIndex = j;
            }
        }
        if (minIndex != i)
        {
            swap(products[i], products[minIndex]);
        }
    }
}

int main()
{
    addInitialProducts();

    int choice;
    do
    {
        cout << "\nE-Commerce Product Management System" << endl;
        cout << "1. Display All Products" << endl;
        cout << "2. Search Product by Keyword (Linear Search)" << endl;
        cout << "3. Search Product by Price or ID (Binary Search)" << endl;
        cout << "4. Add New Product" << endl;
        cout << "5. Update Product Quantity" << endl;
        cout << "6. Delete a Product" << endl;
        cout << "7. Sort Products (Bubble Sort)" << endl;
        cout << "8. Sort Products (Selection Sort)" << endl;
        cout << "9. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            displayAllProducts();
            break;
        case 2:
        {
            cout << "Enter keyword to search: ";
            string keyword;
            cin.ignore();
            getline(cin, keyword);
            linearSearch(keyword);
            break;
        }
        case 3:
        {
            cout << "Search by: 1. Price  2. ID (Enter 1 or 2): ";
            int option;
            cin >> option;
            if (option == 1)
            {
                cout << "Enter price to search: ";
                double price;
                cin >> price;
                searchByPriceOrID(price, true);
            }
            else if (option == 2)
            {
                cout << "Enter ID to search: ";
                int id;
                cin >> id;
                searchByPriceOrID(id, false);
            }
            else
            {
                cout << "Invalid option." << endl;
            }
            break;
        }
        case 4:
            addNewProduct();
            break;
        case 5:
            updateProductQuantity();
            break;
        case 6:
            deleteProduct();
            break;
        case 7:
        {
            cout << "Sort by: 1. Price  2. ID (Enter 1 or 2): ";
            int option;
            cin >> option;
            bubbleSort(products, option == 1);
            cout << "Products sorted successfully using Bubble Sort!" << endl;
            break;
        }
        case 8:
        {
            cout << "Sort by: 1. Price  2. ID (Enter 1 or 2): ";
            int option;
            cin >> option;
            selectionSort(products, option == 1);
            cout << "Products sorted successfully using Selection Sort!" << endl;
            break;
        }
        case 9:
            cout << "Exiting the program. Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 9);

    return 0;
}
void updateProductPrice()
{
    int id;
    double newPrice;
    cout << "Enter Product ID to update price: ";
    cin >> id;

    auto it = find_if(products.begin(), products.end(), [id](Product &p)
                      { return p.id == id; });
    if (it != products.end())
    {
        cout << "Enter new price: ";
        cin >> newPrice;
        it->price = newPrice;
        cout << "Price updated successfully!" << endl;
    }
    else
    {
        cout << "Product not found." << endl;
    }
}

void displayProductsByTag()
{
    string tag;
    cout << "Enter tag to filter products: ";
    cin.ignore();
    getline(cin, tag);

    bool found = false;
    for (const auto &product : products)
    {
        if (find(product.tags.begin(), product.tags.end(), tag) != product.tags.end())
        {
            found = true;
            displayProduct(product);
        }
    }
    if (!found)
    {
        cout << "No products found with tag: " << tag << endl;
    }
}
void addToCart()
{
    int id, quantity;
    cout << "Enter Product ID to add to cart: ";
    cin >> id;
    cout << "Enter quantity: ";
    cin >> quantity;

    auto it = find_if(products.begin(), products.end(), [id](Product &p)
                      { return p.id == id; });
    if (it != products.end())
    {
        if (it->quantity >= quantity)
        {
            it->quantity -= quantity;
            cout << "Product added to cart successfully!" << endl;
        }
        else
        {
            cout << "Insufficient stock available." << endl;
        }
    }
    else
    {
        cout << "Product not found." << endl;
    }
}

void printBill()
{
    double total = 0;
    cout << "Enter delivery address: ";
    string address;
    cin.ignore();
    getline(cin, address);

    cout << "\nBill Summary:" << endl;
    cout << "-----------------------------------" << endl;
    for (const auto &product : products)
    {
        if (product.quantity < 0)
        {
            cout << "Product ID: " << product.id << endl;
            cout << "Name: " << product.name << endl;
            cout << "Quantity: " << -product.quantity << endl;
            cout << "Price per unit: ₹" << product.price << endl;
            double cost = -product.quantity * product.price;
            total += cost;
            cout << "Cost: ₹" << cost << endl;
            cout << "-----------------------------------" << endl;
        }
    }
    cout << "Total Amount: ₹" << total << endl;
    cout << "Delivery Address: " << address << endl;
    cout << "Estimated Delivery Time: 3-5 business days" << endl;
    cout << "-----------------------------------" << endl;
}

void displayMenu()
{
    int choice;
    do
    {
        cout << "\nE-Commerce Product Management System" << endl;
        cout << "1. Display All Products" << endl;
        cout << "2. Search Product by Keyword (Linear Search)" << endl;
        cout << "3. Search Product by Price or ID (Binary Search)" << endl;
        cout << "4. Add New Product" << endl;
        cout << "5. Update Product Quantity" << endl;
        cout << "6. Delete a Product" << endl;
        cout << "7. Sort Products (Bubble Sort)" << endl;
        cout << "8. Sort Products (Selection Sort)" << endl;
        cout << "9. Add to Cart" << endl;
        cout << "10. Print Bill" << endl;
        cout << "11. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            displayAllProducts();
            break;
        case 2:
        {
            cout << "Enter keyword to search: ";
            string keyword;
            cin.ignore();
            getline(cin, keyword);
            linearSearch(keyword);
            break;
        }
        case 3:
        {
            cout << "Search by: 1. Price  2. ID (Enter 1 or 2): ";
            int option;
            cin >> option;
            if (option == 1)
            {
                cout << "Enter price to search: ";
                double price;
                cin >> price;
                searchByPriceOrID(price, true);
            }
            else if (option == 2)
            {
                cout << "Enter ID to search: ";
                int id;
                cin >> id;
                searchByPriceOrID(id, false);
            }
            else
            {
                cout << "Invalid option." << endl;
            }
            break;
        }
        case 4:
            addNewProduct();
            break;
        case 5:
            updateProductQuantity();
            break;
        case 6:
            deleteProduct();
            break;
        case 7:
        {
            cout << "Sort by: 1. Price  2. ID (Enter 1 or 2): ";
            int option;
            cin >> option;
            bubbleSort(products, option == 1);
            cout << "Products sorted successfully using Bubble Sort!" << endl;
            break;
        }
        case 8:
        {
            cout << "Sort by: 1. Price  2. ID (Enter 1 or 2): ";
            int option;
            cin >> option;
            selectionSort(products, option == 1);
            cout << "Products sorted successfully using Selection Sort!" << endl;
            break;
        }
        case 9:
            addToCart();
            break;
        case 10:
            printBill();
            break;
        case 11:
            cout << "Exiting the program. Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 11);
}