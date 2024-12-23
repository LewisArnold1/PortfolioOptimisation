#include <iostream>
#include <fstream>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <vector>

using json = nlohmann::json;

void displayStockData(const json& stockData) {
    for (auto& [symbol, price] : stockData.items()) {
        std::cout << symbol << ": " << price << std::endl;
    }
}

std::string loadApiKey(const std::string& filename){
    std::ifstream file(filename);
    if (!file) {
        throw std::runtime_error("Could not open config file.");
    }

    json config;
    file >> config;
    return config["alphaVantageApiKey"];
}

// Callback function to handle data received from cURL
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userData) {
    userData->append(static_cast<char*>(contents), size * nmemb);
    return size * nmemb;
}

// Function to perform a GET request using cURL
std::string fetchURL(const std::string& url) {
    CURL* curl;
    CURLcode res;
    std::string response;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "cURL error: " << curl_easy_strerror(res) << std::endl;
        }
        curl_easy_cleanup(curl);
    }
    return response;
}

int main() {
    std::cout << "Welcome to Portfolio Optimiser!" << std::endl;

    try{
        // Load API key
        std::string apiKey = loadApiKey("../config.json");

        // Test with Alpha Vantage API
        std::string url = "https://www.alphavantage.co/query?function=TIME_SERIES_INTRADAY&symbol=AAPL&interval=1min&apikey=" + apiKey;
        std::string response = fetchURL(url);

        std::cout << "API Response: " << response << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    // JSON object for stock data
    json stockData = {{"AAPL", 177.30}, {"MSFT", 315.40}, {"GOOG", 2845.50}};
    displayStockData(stockData);
    
    return 0;
}
