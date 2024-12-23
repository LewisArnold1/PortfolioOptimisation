#include <iostream>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <vector>

using json = nlohmann::json;

void displayStockData(const json& stockData) {
    for (auto& [symbol, price] : stockData.items()) {
        std::cout << symbol << ": " << price << std::endl;
    }
}

int main() {
    std::cout << "Welcome to Portfolio Optimiser!" << std::endl;

    // JSON object for stock data
    json stockData = {{"AAPL", 177.30}, {"MSFT", 315.40}, {"GOOG", 2845.50}};
    displayStockData(stockData);
    
    return 0;
}
