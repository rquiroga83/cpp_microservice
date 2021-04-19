#include <memory>
#include "../core/domain/User.cpp"
#include "../core/ports/UserRepository.cpp"

class UserRepositoryImpl : UserRepository {
private:

public:
    UserRepositoryImpl();
    ~UserRepositoryImpl();

    std::shared_ptr<User> findById(long id) override;
};

UserRepositoryImpl::UserRepositoryImpl() { }

UserRepositoryImpl::~UserRepositoryImpl() { }

std::shared_ptr<User>  UserRepositoryImpl::findById(long id) {
    auto fakeUser = std::make_shared<User>();

    fakeUser->id(1);
    fakeUser->name("MyName");
    fakeUser->email("test@test.com");

    return fakeUser;
}