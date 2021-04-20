#ifndef MyController_hpp
#define MyController_hpp

#include <memory>
#include <iostream>
#include "dto/DTOs.hpp"

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"

#include "../core/ports/UserService.cpp"

#include OATPP_CODEGEN_BEGIN(ApiController) //<-- Begin Codegen

/**
 * Sample Api Controller.
 */
class UserController : public oatpp::web::server::api::ApiController {
private:
    std::shared_ptr<UserService> userService;

public:
  /**
   * Constructor with object mapper.
   * @param objectMapper - default object mapper used to serialize/deserialize DTOs.
   */
  UserController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
    : oatpp::web::server::api::ApiController(objectMapper)
  {}

  void setUserService(std::shared_ptr<UserService> service) {
    userService = service;
  }

public:
  
  ENDPOINT("GET", "/", root) {
    auto dto = MyDto::createShared();
    dto->statusCode = 200;
    dto->message = "Hola Mundo!";

    auto user = userService->getUserById(10);

    return createDtoResponse(Status::CODE_200, dto);
  }
  
  // TODO Insert Your endpoints here !!!
  
};

#include OATPP_CODEGEN_END(ApiController) //<-- End Codegen

#endif /* UserController_hpp */