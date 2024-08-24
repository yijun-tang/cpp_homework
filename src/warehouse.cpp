#include "warehouse.h"

template<typename T>
void Warehouse<T>::addProduct(std::shared_ptr<Product<T>> product) {
    std::lock_guard<std::mutex> lock(mtx);
    size_t id = product->getID();
    if (products.find(id) != products.end()) {
        throw WarehouseException("Product with ID " + std::to_string(id) + " already exists.");
    }
    products[id] = std::move(product);
}

template<typename T>
void Warehouse<T>::removeProduct(size_t id) {
    std::lock_guard<std::mutex> lock(mtx);
    auto it = products.find(id);
    if (it == products.end()) {
        throw WarehouseException("Product with ID " + std::to_string(id) + " not found.");
    }
    products.erase(it);
}

template<typename T>
void Warehouse<T>::updateProduct(size_t id, const std::string& name, T price, int quantity) {
    if (quantity < 0) {
        throw WarehouseException("Updated quantity shouldn't be negative.");
    }
    std::lock_guard<std::mutex> lock(mtx);
    auto it = products.find(id);
    if (it == products.end()) {
        throw WarehouseException("Product with ID " + std::to_string(id) + " not found.");
    }
    it->second->setName(name);
    it->second->setPrice(price);
    it->second->setQuantity(quantity);
}

template<typename T>
std::shared_ptr<Product<T>> Warehouse<T>::getProduct(size_t id) {
    std::lock_guard<std::mutex> lock(mtx);
    auto it = products.find(id);
    if (it == products.end()) {
        throw WarehouseException("Product with ID " + std::to_string(id) + " not found.");
    }
    return it->second;
}

template<typename T>
typename Warehouse<T>::ConstIterator Warehouse<T>::cbegin() {
    std::lock_guard<std::mutex> lock(mtx);
    return products.cbegin();
}

template<typename T>
typename Warehouse<T>::ConstIterator Warehouse<T>::cend() {
    std::lock_guard<std::mutex> lock(mtx);
    return products.cend();
}

template<typename T>
bool Warehouse<T>::is_empty() {
    std::lock_guard<std::mutex> lock(mtx);
    return products.empty();
}

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
        std::this_thread::sleep_for(std::chrono::seconds(checkInterval));

        try {
            std::cout << "Checking inventory for low stock items..." << std::endl;

            for (auto it = warehouse.cbegin(); it != warehouse.cend(); ++it) {
                auto product = it->second;
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

template void Warehouse<int>::addProduct(std::shared_ptr<Product<int>>);
template void Warehouse<int>::removeProduct(size_t);
template bool Warehouse<int>::is_empty();
template void supplierUpdate(Warehouse<int>&, size_t, int, int);
template void inventoryCheck(Warehouse<int>&, int, int);
