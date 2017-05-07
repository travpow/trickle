
#include <utility>
#include <memory>
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

using std::shared_ptr;
using std::vector;
using std::pair;
using std::string;
using std::endl;
using Tr::Cell;
using Tr::TypeDefinitions;

const auto Row = TestRow<Tr::String, Tr::Int32, Tr::String>;

TrResources resources;
TypeDefinitions types = resources.typeFactory()->createTypes();

vector<pair<string, string> > columns = {
    {"name", "string"},
    {"index", "int32"},
    {"color", "string"}
};

TrSchema schema(types, columns, "index");

void insertRows(TrTable& table)
{
    for (int i = 0; i < 1000; ++i)
    {
        string color = (i % 2 == 0) ? "blue" : "green";
        string person = (i % 4 < 2) ? "One" : "Two";

        table.insert(Row(person, i, color));
    }
}

TEST_CASE("Creation of view and insertion of rows") {
    TrTable table(schema, {"color"});
    TrView view(table, "color");

    insertRows(table);

    TestViewDelegate d;
    view.setWindowSize(20);
    view.setDelegate(&d);

    view.snap();

    REQUIRE(d.size() == 20);

    int i = 0;
    const int indexPos = schema.pos("index");

    for (auto itr = d.begin(); itr != d.end(); ++itr, i += 2)
    {
        const Tr::Cell& cell = itr->get(indexPos);
        REQUIRE(cell == Cell(new Tr::Int32(i)));
    }

    REQUIRE(i == 40);
}

TEST_CASE("View delegate not required for snap") {
    TrTable table(schema, {"color"});
    TrView view(table, "color");

    insertRows(table);

    view.setWindowSize(10);
    view.snap();

    TRINFO << "Snap is no-op without a view provider." << endl;
}

TEST_CASE("Preset view window") {
    TrTable table(schema, {"color"});
    TrView view(table, "color",
        Cell(new Tr::String("green")), 30, Cell(new Tr::String("green")), 150);

    insertRows(table);

    TestViewDelegate d;
    view.setWindowSize(10);
    view.setDelegate(&d);

    view.snap();

    REQUIRE(d.size() == 10);
}
