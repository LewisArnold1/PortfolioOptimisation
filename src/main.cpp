#include <iostream>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <vector>

using json = nlohmann::json;

int main() {
    std::cout << "Welcome to Portfolio Optimiser!" << std::endl;

    json stockData = {{"AAPL", 177.30}};
    std::cout << stockData.dump() << std::endl;
    
    return 0;
}
