
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

#include "Catch/include/catch.hpp"

using std::vector;
using std::pair;
using std::string;
using std::endl;
using Tr::Cell;
using Tr::TypeDefinitions;

TEST_CASE("Insertion of rows into table") {
    TrResources resources;
    TypeDefinitions types = resources.typeFactory()->createTypes();

    vector<pair<string, string> > columns = {
        {"name", "string"},
        {"age", "int32"},
        {"color", "string"}
    };

    TrSchema schema(types, columns, "name");
    TrTable table(schema, {"color"});

    const auto& Row = TestRow<Tr::String, Tr::Int32, Tr::String, string, int, string>;

    vector<Cell>
        v1 = Row("Bob",  45, "Blue"),
        v2 = Row("Sam",  33, "Red"),
        v3 = Row("Mike", 27, "Blue"),
        v4 = Row("Steve",38, "Green"),
        v5 = Row("John", 26, "Blue");

    table.insert(v1);
    table.insert(v2);
    table.insert(v3);
    table.insert(v4);
    table.insert(v5);

    table.removeByPrimaryKey(Tr::Cell(new Tr::String("Mike")));
    const auto& list = table.getByIndex("color", Tr::Cell(new Tr::String("Blue")));

    REQUIRE(list.size() == 2);

    for (auto itr = list.begin(); itr != list.end(); ++itr)
    {
        TRINFO << "Found: " << **itr << endl;
    }
}
