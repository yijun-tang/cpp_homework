#include <utility>
#include "product.h"

// Move constructor
template <typename T>
Product<T>::Product(Product&& other) noexcept
    : id(other.id),
      name(std::move(other.name)),
      price(other.price),
      quantity(other.quantity.load()) {}

// Move assignment operator
template <typename T>
Product<T>& Product<T>::operator=(Product&& other) noexcept {
    if (this != &other) {
        id = other.id;
        name = std::move(other.name);
        price = other.price;
        quantity.store(other.quantity.load());
    }
    return *this;
}
