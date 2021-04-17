#include "../include/handler.h"

handler::handler() {
    // Contructor
}

handler::handler(utility::string_t url):m_listener(url) {
    m_listener.support(methods::GET, std::bind(&handler::handle_get, this, std::placeholders::_1));
    // m_listener.support(methods::PUT, std::bind(&handler::handle_put, this, std::placeholders::_1));
    // m_listener.support(methods::POST, std::bind(&handler::handle_post, this, std::placeholders::_1));
    // m_listener.support(methods::DEL, std::bind(&handler::handle_delete, this, std::placeholders::_1));

}

handler::~handler() {
    // Destructor
}

void handler::handle_error(pplx::task<void>& t) {
    try {
        t.get();
    }
    catch(...) {
        // TODO: Loguear el error
    }
}

/**
 * @brief Get Request
 * 
 * @param message 
 */
void handler::handle_get(http_request message) {
    ucout <<  message.to_string() << endl;

    try {
        auto http_get_vars = uri::split_query(message.request_uri().query());
        auto found_id_user = http_get_vars.find("id_user");

        if (found_id_user == http_get_vars.end()) {
			auto err = U("Request received with get var \"id_user\" omitted from query.");
			ucout << err << endl;
			message.reply(status_codes::BadRequest, json::value::string(err));
			return;
		}

        auto j = R"(
            {
                "name": "Andres",
                "email": "test@test.com"
            }
        )"_json;

        j["id"] = found_id_user->second;

        message.reply(status_codes::OK, U(j.dump()), U("application/json"));
    }
    catch(...) {
        message.reply(status_codes::InternalError,U("Internal Error "));
    }

    return;
};