#include "../src/test_framework.h"
#include "../src/warehouse.h"

TEST_CASE(testAddAndRemoveProduct) {
    Warehouse<int> warehouse;
    auto product = std::make_shared<Product<int>>(1, "P1", 10, 100);
    warehouse.addProduct(product);

    ASSERT_EQUAL(warehouse.getProduct(1)->getName(), std::string("P1"));
    ASSERT_EQUAL(warehouse.getProduct(1)->getPrice(), 10);

    warehouse.removeProduct(1);
    ASSERT_TRUE(warehouse.is_empty());
}

// Main function to run all tests
int main() {
    TestFramework::TestRunner::runTests();
    return 0;
}
