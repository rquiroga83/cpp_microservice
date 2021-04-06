#include "pistache/http.h"
#include "pistache/router.h"
#include "pistache/endpoint.h"

using namespace Pistache;

namespace Generic {
    void handleReady(const Rest::Request&, Http::ResponseWriter response) {
        response.send(Http::Code::Ok, "1");
    }
}


class HelloEndpoint {
public:
    explicit HelloEndpoint(Address addr) : httpEndpoint(std::make_shared<Http::Endpoint>(addr)) 
    {}

    void init(size_t thr = 2) {
        auto opts = Http::Endpoint::options()
            .threads(static_cast<int>(thr));
        httpEndpoint->init(opts);
        setupRoutes();
    }

    void start() {
        httpEndpoint->setHandler(router.handler());
        httpEndpoint->serve();
    }


private:
    using Lock = std::mutex;
    using Guard = std::lock_guard<Lock>;
    Lock metricsLock;

    std::shared_ptr<Http::Endpoint> httpEndpoint;
    Rest::Router router;

    void doGetHello(const Rest::Request& request, Http::ResponseWriter response) {
        auto name = request.param(":name").as<std::string>();

        std::cout << "Hola " << name << std::endl;

        response.send(Http::Code::Ok, std::to_string(10));
    }

    void setupRoutes() {
        using namespace Rest;

        Routes::Get(router, "/ready", Routes::bind(&Generic::handleReady));
        Routes::Get(router, "/hello/:name", Routes::bind(&HelloEndpoint::doGetHello, this));

        // Routes::Post(router, "/record/:name/:value?", Routes::bind(&StatsEndpoint::doRecordMetric, this));
        // Routes::Get(router, "/value/:name", Routes::bind(&StatsEndpoint::doGetMetric, this));
        // Routes::Get(router, "/auth", Routes::bind(&StatsEndpoint::doAuth, this));
    }

};


int main(int argc, char *argv[]) {
    Port port(9080);

    int thr = 2;

    if (argc >= 2) {
        port = static_cast<uint16_t>(std::stol(argv[1]));

        if (argc == 3)
            thr = std::stoi(argv[2]);
    }

    Address addr(Ipv4::any(), port);

    std::cout << "Cores = " << hardware_concurrency() << std::endl;
    std::cout << "Using " << thr << " threads" << std::endl;

    HelloEndpoint hello(addr);

    hello.init(thr);
    hello.start();
}