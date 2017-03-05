

#include "TrResources.hpp"
#include "TrType.hpp"

#include "Catch/include/catch.hpp"

using Tr::TypeDefinitions;

TEST_CASE("asdf") {
    TrResources resources;
    TypeDefinitions* types = resources.typeFactory()->createTypes();

    REQUIRE(true);
}
