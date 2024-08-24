#include <atomic>
#include <iostream>
#include <thread>

#include "../src/product.h"
#include "../src/warehouse.h"
#include "gtest/gtest.h"

void runConcurrentTest() {
    Warehouse<int> warehouse;
    auto product1 = std::make_shared<Product<int>>(1, "P1", 100, 50);
    auto product2 = std::make_shared<Product<int>>(2, "P2", 150, 30);
    warehouse.addProduct(product1);
    warehouse.addProduct(product2);

    // Launch several supplier threads
    std::vector<std::thread> suppliers;
    std::atomic<bool> stopFlag{false};

    for (size_t i = 0; i < 3; ++i) {
        suppliers.emplace_back([&]() {
            while (!stopFlag.load()) {
                supplierUpdate<int>(warehouse, 1, 0, 10);
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        });
    }

    // Launch a single checker thread
    std::thread checker([&]() { inventoryCheck<int>(warehouse, 1, 40); });

    // Let the threads run for a while
    std::this_thread::sleep_for(std::chrono::seconds(3));

    // Signal threads to stop and join them
    stopFlag.store(true);

    for (auto& thread : suppliers) {
        if (thread.joinable()) thread.join();
    }
    if (checker.joinable())
        checker.detach();  // Detached to avoid blocking main thread in test

    // Test the warehouse state after threads have run
    ASSERT_GE(product1->getQuantity(),
              0);  // Ensure that the quantity hasn't gone negative
}

TEST(WarehouseTest, ConcurrentSupplierAndChecker) { runConcurrentTest(); }

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
