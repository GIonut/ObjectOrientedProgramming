#include <iostream>
#include<vector>
#include<memory>

using namespace std;

class SaleItem
{
    int code;
    double price;

public:
    SaleItem(int _code, double _price) : code(_code), price(_price) {};
    int getCode() { return code; }
    double getPrice() { return price; }
};

class Sale
{
    vector<SaleItem> v;
public:
    const vector<SaleItem>& get() const { return v; }
    void add(SaleItem e) { v.push_back(e); }
};

class Discount
{
public:
    //virtual ~Discount() {};
    virtual double calc(const Sale& sale) = 0;
    virtual void add(shared_ptr<Discount> disc) = 0;
};

class ItemDiscount:public Discount
{
    int code, percentage;
public:
    ItemDiscount(int _code, int _percentage) :code(_code), percentage(_percentage) {};
    void add(shared_ptr<Discount> discount) override{}
    double calc(const Sale& sale) override
    {
        double disc = 0;
        for (auto elem : sale.get())
        {
            if (elem.getCode() == code)
                disc += elem.getPrice() * percentage / 100;
        }
        return disc;
    };
};

class SumDiscount : public Discount
{
    vector<shared_ptr<Discount>> v;

public:
    void add(shared_ptr<Discount> discount) override
    {
        v.push_back(discount);
    }
    double calc(const Sale& sale) override
    {
        double disc = 0;
        for (auto it = v.begin(); it != v.end(); it++ )
        {
            disc += (*it)->calc(sale);
        }
        return disc;
    }
};
int main()
{
    Sale sale{};
    SaleItem s1{ 100, 45 };
    SaleItem s2{ 890, 100 };
    SaleItem s3{ 100, 77 };
    sale.add(s1);
    sale.add(s2);
    sale.add(s3);
    std::shared_ptr<Discount> d1 = make_shared<ItemDiscount>(100, 10);
    std::shared_ptr<Discount> d2 = make_shared<ItemDiscount>(890, 15);
    cout << "The discount1 " << d1->calc(sale) << "\n";
    cout << "The discount2 " << d2->calc(sale) << "\n";
    std::shared_ptr<Discount> sum = make_shared<SumDiscount>();
    sum->add(d1);
    sum->add(d2);
    cout << "The total sum discount " << sum->calc(sale) << "\n";

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
