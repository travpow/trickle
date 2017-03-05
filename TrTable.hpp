

class TrTable
{
public:
    TrTable(const TrSchema& schema);

    void insert(const std::vector<Tr::Cell>& row);

private:
    const TrSchema& schema_;

    map<Tr::Cell, std::vector<Tr::Cell>> rows_;
}
