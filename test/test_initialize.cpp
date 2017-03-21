
#include <utility>
#include <vector>
#include <string>

#include "TrResources.hpp"
#include "TrType.hpp"
#include "TrSchema.hpp"

#include "Catch/include/catch.hpp"

using std::vector;
using std::pair;
using std::string;
using Tr::TypeDefinitions;

TEST_CASE("asdf") {
    TrResources resources;
    TypeDefinitions types = resources.typeFactory()->createTypes();

    vector<pair<string, string> > columns = {
        {"name", "string"},
        {"age", "int32"},
        {"height", "double"},
        {"birthday", "date"},
        {"badcol", "unknownType"}
    };

    TrSchema schema(types, columns);

    REQUIRE(schema.pos("birthday") == 3);
    REQUIRE(schema.type("birthday") == types.map["date"]);
    REQUIRE(schema.pos("badcol") == -1);
    REQUIRE(schema.type("badcol") == &Tr::NoneType);
}
