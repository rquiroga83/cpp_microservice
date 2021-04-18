#include "../domain/user.cpp"

class UserRepository  {
    public:
        virtual ~UserRepository() {}
        virtual User *findById(long id) = 0;
};