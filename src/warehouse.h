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
    using ProductPtr = std::shared_ptr<Product<T>>;
    using ConstIterator = typename std::unordered_map<size_t, ProductPtr>::const_iterator;

    // Add a new product to the warehouse
    void addProduct(std::shared_ptr<Product<T>> product);

    // Remove a product from the warehouse by ID
    void removeProduct(size_t id);

    // Update an existing product's details
    void updateProduct(size_t id, const std::string& name, T price, int quantity);

    // Retrieve a product's information by ID
    std::shared_ptr<Product<T>> getProduct(size_t id);

    // Check if the warehouse is empty
    bool is_empty();

    ConstIterator cbegin();
    ConstIterator cend();

private:
    std::unordered_map<size_t, ProductPtr> products;
    std::mutex mtx;
};

// Concurrent supplier updates
template <typename T>
void supplierUpdate(Warehouse<T>& warehouse, size_t productID, int minQuantity, int maxQuantity);

// Periodic inventory check
template <typename T>
void inventoryCheck(Warehouse<T>& warehouse, int checkInterval, int lowStockThreshold);

#endif // WAREHOUSE_H_
