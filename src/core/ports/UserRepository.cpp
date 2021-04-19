#include "../domain/User.cpp"

class UserRepository  {
public:
    virtual ~UserRepository() {}
    virtual std::shared_ptr<User> findById(long id) = 0;
};