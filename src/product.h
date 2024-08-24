#ifndef PRODUCT_H_
#define PRODUCT_H_

#include <iostream>
#include <mutex>
#include <string>
#include <atomic>

template <typename T>
class Product {
public:
    // Constructors
    Product(size_t id, const std::string& name, T price, int quantity)
        : id(id), name(name), price(price), quantity(quantity) {}
    Product(Product&& other) noexcept;
    Product& operator=(Product&& other) noexcept;

    // Destructor
    ~Product() = default;

    Product(const Product&) = delete;
    Product& operator=(const Product&) = delete;

    // Member functions
    size_t getID() const { return id; }
    const std::string& getName() const { return name; }
    T getPrice() const { return price; }
    int getQuantity() const { return quantity.load(); }

    void setName(const std::string& name) { this->name = name; }
    void setPrice(T price) { this->price = price; }
    void setQuantity(int quantity) { this->quantity.store(quantity); }

private:
    size_t id;
    std::string name;
    T price;
    std::atomic<int> quantity;
};

#endif // PRODUCT_H_
