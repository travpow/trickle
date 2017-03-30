
#include <utility>
#include <vector>
#include <string>

#include "TrResources.hpp"
#include "TrType.hpp"
#include "TrSchema.hpp"
#include "TrTable.hpp"
#include "TrLog.hpp"
#include "TrTestHelper.hpp"
#include "TypeImplementations.hpp"

#include "Catch-master/include/catch.hpp"

using std::vector;
using std::pair;
using std::string;
using std::endl;
using Tr::Cell;
using Tr::TypeDefinitions;

TEST_CASE("Creation of view and insertion of rows") {
    TrResources resources;
    TypeDefinitions types = resources.typeFactory()->createTypes();

    vector<pair<string, string> > columns = {
        {"name", "string"},
        {"index", "int32"},
        {"color", "string"}
    };

    TrSchema schema(types, columns, "name");
    TrTable table(schema, {"color"});

    const auto& Row = TestRow<Tr::String, Tr::Int32, Tr::String>;

    /*REQUIRE(list.size() == 2);

    for (auto itr = list.begin(); itr != list.end(); ++itr)
    {
        TRINFO << "Found: " << **itr << endl;
    } */
}
