#include "../domain/User.cpp"

class UserService {
public:
    virtual ~UserService() {}
    virtual std::shared_ptr<User> getUserById(long id) = 0;
};