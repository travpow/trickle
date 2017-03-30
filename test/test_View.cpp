
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
#include "TrView.hpp"
#include "TestViewDelegate.hpp"

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

    TrSchema schema(types, columns, "index");
    TrTable table(schema, {"color"});

    const auto& Row = TestRow<Tr::String, Tr::Int32, Tr::String>;

    for (int i = 0; i < 1000; ++i)
    {
        string color = (i % 2 == 0) ? "blue" : "green";
        string person = (i % 4 < 2) ? "Bob" : "Steve";

        table.insert(Row(person, i, color));
    }

    TrView view(table, "color");

    TestViewDelegate d;
    view.setDelegate(&d);

    view.snap();

    int i = 0;
    for (auto itr = d.begin(); itr != d.end() && i < 200; ++itr, i += 2)
    {
        const Cell& cell = (*itr)->get(1);
        REQUIRE(cell == i);
    } 

    REQUIRE(i == 200);
}
