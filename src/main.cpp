#include <iostream>
#include <fstream>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <vector>

using json = nlohmann::json;

class Api {
private:  
    std::string configFile; 
    std::string apiKey;
public:
    Api(const std::string& configFilePath) {
        apiKey = loadApiKey(configFilePath);
    };

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
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userData) {
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

    std::string fetchStockData(const std::string& function, const std::string& symbol, const std::string& interval) {
        std::string url = "https://www.alphavantage.co/query?function=" + function + "&symbol=" + symbol + "&interval=" + interval + "&apikey=" + apiKey;

    return fetchURL(url);
}

};

int main() {
    std::cout << "Welcome to Portfolio Optimiser!" << std::endl;
    
    Api alphaVantage("../config.json");
    std::string response = alphaVantage.fetchStockData("TIME_SERIES_INTRADAY", "MSFT", "5min");
    std::cout << "API Response: " << response << std::endl;

    return 0;
}
