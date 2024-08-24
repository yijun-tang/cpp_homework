#ifndef WAREHOUSE_H_
#define WAREHOUSE_H_

#include "product.h"
#include <unordered_map>
#include <mutex>
#include <memory>
#include <stdexcept>
#include <random>
#include <thread>

// Custom exception class for the Warehouse
class WarehouseException : public std::runtime_error {
public:
    explicit WarehouseException(const std::string& message)
        : std::runtime_error("Warehouse Error: " + message) {}
};

// Warehouse template class
template <typename T>
class Warehouse {
public:
    // Add a new product to the warehouse
    void addProduct(std::shared_ptr<Product<T>> product) {
        std::lock_guard<std::mutex> lock(mtx);
        size_t id = product->getID();
        if (products.find(id) != products.end()) {
            throw WarehouseException("Product with ID " + std::to_string(id) + " already exists.");
        }
        products[id] = product;
    }

    // Remove a product from the warehouse by ID
    void removeProduct(size_t id) {
        std::lock_guard<std::mutex> lock(mtx);
        auto it = products.find(id);
        if (it == products.end()) {
            throw WarehouseException("Product with ID " + std::to_string(id) + " not found.");
        }
        products.erase(it);
    }

    // Update an existing product's details
    void updateProduct(size_t id, const std::string& name, T price, int quantity) {
        std::lock_guard<std::mutex> lock(mtx);
        auto it = products.find(id);
        if (it == products.end()) {
            throw WarehouseException("Product with ID " + std::to_string(id) + " not found.");
        }
        it->second->setName(name);
        it->second->setPrice(price);
        it->second->setQuantity(quantity);
    }

    // Retrieve a product's information by ID
    std::shared_ptr<Product<T>> getProduct(size_t id) {
        std::lock_guard<std::mutex> lock(mtx);
        auto it = products.find(id);
        if (it == products.end()) {
            throw WarehouseException("Product with ID " + std::to_string(id) + " not found.");
        }
        return it->second;
    }

    // Get the products map (for internal use)
    const std::unordered_map<size_t, std::shared_ptr<Product<T>>>& getProducts() const { return products; }

    // Print all products in the warehouse (for demonstration purposes)
    void printProducts() {
        std::lock_guard<std::mutex> lock(mtx);
        for (const auto& pair : products) {
            std::cout << "Product ID: " << pair.second->getID()
                    << ", Name: " << pair.second->getName()
                    << ", Price: " << pair.second->getPrice()
                    << ", Quantity: " << pair.second->getQuantity() << std::endl;
        }
    }

private:
    std::unordered_map<size_t, std::shared_ptr<Product<T>>> products;
    std::mutex mtx;
};

// Concurrent supplier updates
template <typename T>
void supplierUpdate(Warehouse<T>& warehouse, size_t productID, int minQuantity, int maxQuantity) {
    std::default_random_engine engine(std::random_device{}());
    std::uniform_int_distribution<int> distribution(minQuantity, maxQuantity);

    int quantityChange = distribution(engine);
    try {
        auto product = warehouse.getProduct(productID);
        if (product) {
            int currentQuantity = product->getQuantity();
            product->setQuantity(currentQuantity + quantityChange);
            std::cout << "Supplier updated Product ID " << productID
                        << " by " << quantityChange
                        << ". New Quantity: " << product->getQuantity() << std::endl;
        }
    } catch (const WarehouseException& e) {
        std::cerr << e.what() << std::endl;
    }
}

// Periodic inventory check
template <typename T>
void inventoryCheck(Warehouse<T>& warehouse, int checkInterval, int lowStockThreshold) {
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(checkInterval)); // Periodic check

        try {
            // warehouse.printProducts();
            std::cout << "Checking inventory for low stock items..." << std::endl;

            for (const auto& pair : warehouse.getProducts()) {
                auto product = pair.second;
                if (product->getQuantity() < lowStockThreshold) {
                    std::cout << "Low stock alert! Product ID: " << product->getID()
                              << ", Name: " << product->getName()
                              << ", Quantity: " << product->getQuantity() << std::endl;
                }
            }
        } catch (const WarehouseException& e) {
            std::cerr << e.what() << std::endl;
        }
    }
}

#endif // WAREHOUSE_H_
