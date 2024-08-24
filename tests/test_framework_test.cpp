#include "../src/test_framework.h"
#include "../src/warehouse.h"

// Test case example for adding a product
TEST_CASE(testAddProduct) {
    Warehouse<int> warehouse;
    auto product = std::make_shared<Product<int>>(1, "P1", 10, 100);
    warehouse.addProduct(product);

    ASSERT_EQUAL(warehouse.getProducts().size(), 1ul);
    ASSERT_EQUAL(warehouse.getProducts().at(1)->getName(), std::string("P1"));
    ASSERT_EQUAL(warehouse.getProducts().at(1)->getPrice(), 10);
}

// Test case example for removing a product
TEST_CASE(testRemoveProduct) {
    Warehouse<int> warehouse;
    auto product = std::make_shared<Product<int>>(1, "P1", 10, 100);
    warehouse.addProduct(product);
    warehouse.removeProduct(1);

    ASSERT_EQUAL(warehouse.getProducts().size(), 0ul);
}

// Test case example for updating a product's quantity
TEST_CASE(testUpdateProductQuantity) {
    Warehouse<int> warehouse;
    auto product = std::make_shared<Product<int>>(1, "P1", 10, 100);
    warehouse.addProduct(product);
    warehouse.updateProduct(1, "P1", 10, 50);

    ASSERT_EQUAL(warehouse.getProducts().at(1)->getQuantity(), 50);
}

// Main function to run all tests
int main() {
    TestFramework::TestRunner::runTests();
    return 0;
}
