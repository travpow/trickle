
#include <utility>
#include <vector>
#include <string>

#include "TrResources.hpp"
#include "TrType.hpp"
#include "TrSchema.hpp"

#include "Catch-master/include/catch.hpp"

using std::vector;
using std::pair;
using std::string;
using Tr::TypeDefinitions;

TEST_CASE("Test initialize schema") {
    TrResources resources;
    TypeDefinitions types = resources.typeFactory()->createTypes();

    vector<pair<string, string> > columns = {
        {"name", "string"},
        {"age", "int32"},
        {"height", "double"},
        {"birthday", "date"},
        {"badcol", "unknownType"}
    };

    TrSchema schema(types, columns, "name");

    REQUIRE(schema.pos("birthday") == 3);
    REQUIRE(types.map["date"].get() == schema.type("birthday"));
    REQUIRE(schema.pos("badcol") == -1);
    REQUIRE(schema.type("badcol")->name() == "none");
}
