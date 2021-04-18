#include "../domain/user.cpp"

class UserService {
    public:
        virtual ~UserService() {}
        virtual User *getUserById(long id) = 0;
};