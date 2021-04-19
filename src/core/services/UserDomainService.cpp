#include <memory>
#include "../ports/UserService.cpp"
#include "../ports/UserRepository.cpp"
#include "../domain/User.cpp"

class UserDomainService : UserService {
public:
    UserDomainService(std::shared_ptr<UserRepository> _userRepository);
    virtual ~UserDomainService();

    std::shared_ptr<User> getUserById(long id) override;

private:
    std::shared_ptr<UserRepository> userRepository;
};


UserDomainService::UserDomainService(std::shared_ptr<UserRepository> _userRepository) {
    userRepository = _userRepository;
}

UserDomainService::~UserDomainService(){ }

std::shared_ptr<User> UserDomainService::getUserById(long id) {
    std::shared_ptr<User> user = userRepository->findById(id);

    return user;
}