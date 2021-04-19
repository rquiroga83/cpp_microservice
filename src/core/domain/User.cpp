#ifndef USER_CPP
#define USER_CPP
#include <string>

using namespace std;

class User {
public:
    User();
    virtual ~User();

    long getId();
    string getName();
    string getEmail();
        

private:
    long id;
    string name;
    string email;

};

User::User() { }

User::~User() { }

long User::getId() {
    return id;
}

string User::getName() {
    return name;
}

string User::getEmail() {
    return email;
}

#endif // USER_CPP