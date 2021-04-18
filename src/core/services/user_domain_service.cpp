#include "../ports/user_service.cpp"
#include "../ports/user_repository.cpp"
#include "../domain/user.cpp"

class UserDomainService : UserService {
    public:
        UserDomainService(UserRepository *tUserRepository);
        virtual ~UserDomainService();

        User *getUserById(long id);
        
    private:
        UserRepository *userRepository;
};


UserDomainService::UserDomainService(UserRepository *tUserRepository) {
    userRepository = tUserRepository;
}

UserDomainService::~UserDomainService(){ }

User *UserDomainService::getUserById(long id) {
    User *user = userRepository->findById(id);

    return user;
}