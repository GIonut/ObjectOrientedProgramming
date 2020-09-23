#include <iostream>
#include<string>
#include <vector>
using namespace std;

class Action
{
public:
    virtual void execute() = 0;
};

class CreateAction : public Action
{
public:
    void execute() override
    {
        cout << "Create file" << "\n";
    }
};

class ExitAction : public Action
{
public:
    void execute() override
    {
        cout << "Exit Application" << "\n";
    }
};

class MenuItem
{
protected:
    string text;
    shared_ptr<Action> action;
public:
    MenuItem(string _text, shared_ptr<Action> _action) : text(_text), action(_action) {}
    void print()
    {
        cout << text << "\n";
    }
    void clicked()
    {
        cout << text << "\n";
        if(action != nullptr)
            action->execute();
    }
};

class Menu : public MenuItem
{
    //string text;
    //shared_ptr<Action> action;
    vector<MenuItem> menu;
public:
    Menu(string _text, shared_ptr<Action> _action) : MenuItem(_text, _action) {} //text{ _text }, action{ _action }
    void add(MenuItem m)
    {
        menu.push_back(m);
    }
    void print()
    {
        cout << this->text << "\n";
        for (auto elem : menu)
            elem.print();
    }
};

class MenuBar
{
    vector<Menu> m;
public:
    void print()
    {
        for (auto elem : m)
            elem.print();
    }
    void add(Menu menu)
    {
        m.push_back(menu);
    }
};

int main()
{
    shared_ptr<Action> exit = make_shared<ExitAction>();
    shared_ptr<Action> c = make_shared<CreateAction>();
    shared_ptr<Action> text = make_shared<CreateAction>();
    Menu File("File", nullptr);
    Menu About("About", nullptr);
    Menu New("New", nullptr);
    Menu Exit("Exit", exit);
    Menu C("C++", c);
    Menu Text("Text", text);
    MenuBar mb;
    New.add(Text);
    New.add(C);
    File.add(New);
    File.add(Exit);
    mb.add(File);
    mb.add(About);

    File.clicked();
    New.clicked();
    C.clicked();
    Exit.clicked();


}