#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/generators/catch_generators_range.hpp>

#include "../src/power.hpp"

TEST_CASE("power correctness across small cases") {
    using namespace power;
    
    for (int x : {1, 2, 3, 5, 10}) {
        for (int n : {0, 1, 2, 3, 5, 10, 15}) {
            double r1 = naivePower(x, n);
            double r2 = unoptimizedDCPower(x, n);
            double r3 = optimizedDCPower(x, n);
            
            REQUIRE(r1 == Catch::Approx(r2).epsilon(1e-12));
            REQUIRE(r2 == Catch::Approx(r3).epsilon(1e-12));
        }
    }
}

TEST_CASE("power edge cases") {
    using namespace power;
    
    REQUIRE(naivePower(0, 5) == 0);
    REQUIRE(unoptimizedDCPower(0, 5) == 0);
    REQUIRE(optimizedDCPower(0, 5) == 0);
    
    REQUIRE(naivePower(5, 0) == 1);
    REQUIRE(unoptimizedDCPower(5, 0) == 1);
    REQUIRE(optimizedDCPower(5, 0) == 1);
    
    REQUIRE(naivePower(1, 100) == 1);
    REQUIRE(unoptimizedDCPower(1, 100) == 1);
    REQUIRE(optimizedDCPower(1, 100) == 1);
}

TEST_CASE("power benchmarks representative sizes") {
    using namespace power;

    BENCHMARK("naivePower       x=2 n=20") { return naivePower(2, 20); };
    BENCHMARK("unoptimizedDC    x=2 n=20") { return unoptimizedDCPower(2, 20); };
    BENCHMARK("optimizedDC      x=2 n=20") { return optimizedDCPower(2, 20); };

    BENCHMARK("naivePower       x=3 n=25") { return naivePower(3, 25); };
    BENCHMARK("unoptimizedDC    x=3 n=25") { return unoptimizedDCPower(3, 25); };
    BENCHMARK("optimizedDC      x=3 n=25") { return optimizedDCPower(3, 25); };
}
