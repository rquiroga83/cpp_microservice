#include "../ports/UserService.cpp"
#include "../ports/UserRepository.cpp"
#include "../domain/User.cpp"

class UserDomainService : public UserService {
private:
    std::shared_ptr<UserRepository> userRepository;
    
public:
    UserDomainService(std::shared_ptr<UserRepository> repo);
    virtual ~UserDomainService();

    std::shared_ptr<User> getUserById(long id) override;
};


UserDomainService::UserDomainService(std::shared_ptr<UserRepository> repo) : userRepository(repo){ }

UserDomainService::~UserDomainService(){ }

std::shared_ptr<User> UserDomainService::getUserById(long id) {
    std::shared_ptr<User> user = userRepository->findById(id);

    return user;
}