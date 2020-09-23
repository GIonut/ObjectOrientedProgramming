// HTML.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <assert.h>
#include <algorithm>

#include <vector>
using namespace std;
class Encoder
{
protected:
    //string msg;
public:
    //Encoder(string _msg) : msg(_msg) {};
    virtual ~Encoder() {};
    virtual string encode(string msg) = 0;
};

class AlienEncoder : public Encoder
{
    string header;
public:
    AlienEncoder(string _header) : header(_header) {}
    string encode(string msg) override
    {
        return msg + header;
    }
};

class MorseEncoder :public Encoder
{
public:
    string encode(string msg) override
    {
        string text;
        for (auto character : msg)
            text += ".";
        
        return text;
    }
};

class Mixer : public Encoder
{
    shared_ptr<Encoder> e1, e2;
public:
    Mixer(shared_ptr<Encoder> _e1, shared_ptr<Encoder> _e2) : e1(_e1), e2(_e2) {}
    string encode(string msg) override
    {
        string text;
        string textE1 = e1->encode(msg);
        string textE2 = e2->encode(msg);
        unsigned int i = 0, j = 0;
        while (i < textE1.size() && j < textE2.size())
        {
            text += textE1[i];
            text += textE2[i];
            i++;
            j++;
        }
        while (i < textE1.size())
        {
            text += to_string(textE1[i]);
            i++;
        }
        while (j < textE2.size())
        {
            text += to_string(textE2[j]);
            j++;
        }

        return text;
    }
};

class Communication
{
    vector<string> messages;
    shared_ptr<Encoder> e;
public:
    Communication(shared_ptr<Encoder> _e) : e(_e) {}

    void add(string message)
    {
        messages.push_back(message);
    }

    string communicate()
    {
        sort(messages.begin(), messages.end(), [](auto i, auto j) {return i < j; });
        string text;
        for (auto message : messages)
        {
            text += e->encode(message) + " ";
        }

        return text;
    }
};
int main()
{
    shared_ptr<Encoder> morse = make_shared<MorseEncoder>();
    shared_ptr<Encoder> alien = make_shared<AlienEncoder>("ET");
    shared_ptr<Encoder> mixer = make_shared<Mixer>(morse, alien);
    Communication c1(morse);
    Communication c2(mixer);
    c1.add("Ana are mere");
    c1.add("galbene si verzi");
    c2.add("Ana are mere");
    c2.add("galbene si verzi");
    cout << c1.communicate() << "\n" << c2.communicate();

}
