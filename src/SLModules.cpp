#include "./ServiceLocator.hpp"
#include "./core/ports/UserRepository.cpp"
#include "./repositories/UserRepositoryImpl.cpp"
#include "./core/services/UserDomainService.cpp"
#include "./core/ports/UserService.cpp"

class RepositoriesSLModule : public ServiceLocator::Module {
public:
  void load() override {
    bind<UserRepository>().to<UserRepositoryImpl>([] (SLContext_sptr slc) {
      return new UserRepositoryImpl();
    });
  }
};

// ServicesSLModule is intimate with Bar, it knows what dependencies Bar has ..
class ServicesSLModule : public ServiceLocator::Module {
public:
    void load() override {
		bind<UserService>().to<UserDomainService>([] (SLContext_sptr slc) { 
			return new UserDomainService(slc->resolve<UserRepository>());
		});
	}
};