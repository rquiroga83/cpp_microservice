#ifndef USERSERVICE_CPP
#define USERSERVICE_CPP
#include <memory>
#include "../domain/User.cpp"

class UserService {
public:
    virtual ~UserService() {}
    virtual std::shared_ptr<User> getUserById(long id) = 0;
};
#endif // USERSERVICE_CPP