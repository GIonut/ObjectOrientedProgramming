#include <iostream>
#include <string>
#include <ctime>
using namespace std;

class Channel
{
public:
    virtual ~Channel() {};
    virtual void send(string message) = 0;
};

class FailOver : public Channel
{
    shared_ptr<Channel> ch1, ch2;
public:
    FailOver(shared_ptr<Channel> _ch1, shared_ptr<Channel> _ch2) : ch1(_ch1), ch2(_ch2) {};
    void send(string message) override
    {
        try
        {
            ch1->send(message);
            ch2->send(message);
        }
        catch (exception& e)
        {
            cout << e.what() << "\n";
        }
    }
};

class Telephone : public Channel
{
protected:
    string number;
public:
    Telephone() {};
    Telephone(string _number) : number(_number) {};
    void send(string message) override
    {
        cout << "dialing " << number << "\n";
        int r = rand() % 10;
        if (r % 2 == 0)
            throw exception("Line is busy!");
    }
};

class Fax : public Telephone
{
public:
    Fax(string _number) : Telephone(_number) {};
    void send(string message) override
    {
        Telephone::send(message);
        cout << "sending fax " << number << "\n";
    }
};

class SMS : public Telephone
{
public:
    SMS(string _number) : Telephone(_number) {};
    void send(string message) override
    {
        Telephone::send(message);
        cout << "sending fax " << number << "\n";
    }
};

class Contact
{
    shared_ptr<Channel> ch1, ch2, ch3;
public:
    Contact(shared_ptr<Channel> _ch1, shared_ptr<Channel> _ch2, shared_ptr<Channel> _ch3) :ch1(_ch1), ch2(_ch2), ch3(_ch3) {};
    void sendAlarm(string message)
    {
        bool flag = 0;
        while (!flag)
        {
            try
            {
                ch1->send(message);
                ch2->send(message);
                ch3->send(message);
                flag = 1;
            }
            catch (exception& e)
            {
            }
        }
    }
};
int main()
{
    std::srand(std::time(0));
    Contact contact{
      std::make_shared<Telephone>("000-000"),
      std::make_shared<FailOver>(
        std::make_shared<Fax>("111-111"),
        std::make_shared<SMS>("111-111")),
      std::make_shared<FailOver>(
        std::make_shared<Telephone>("222-222"),
        std::make_shared<FailOver>(
          std::make_shared<Fax>("222-222"),
          std::make_shared<SMS>("222-222"))) };

    contact.sendAlarm("Hello?");
    
}