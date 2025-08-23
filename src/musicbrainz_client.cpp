#include "musicbrainz_client.h"

#include <curl/curl.h>
#include <iostream>
#include <sstream>

namespace {
size_t WriteCallback(void* contents, size_t size, size_t nmemb,
                     std::string* userp) {
    userp->append(static_cast<char*>(contents), size * nmemb);
    return size * nmemb;
}
}  // namespace

MusicBrainzClient::MusicBrainzClient() {
    curl_global_init(CURL_GLOBAL_DEFAULT);
}

MusicBrainzClient::HttpResponse MusicBrainzClient::MakeRequest(
    const std::string& url) {
    HttpResponse response;
    
    CURL* curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response.data);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "musicbrainz-explorer/1.0");
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 30L);
        
        CURLcode res = curl_easy_perform(curl);
        if (res == CURLE_OK) {
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response.response_code);
        } else {
            response.response_code = 0;
        }
        
        curl_easy_cleanup(curl);
    }
    
    return response;
}

bool MusicBrainzClient::TestConnection() {
    try {
        std::string url = 
            "https://musicbrainz.org/ws/2/recording?query=artist:Beatles&limit=1&fmt=json";
        HttpResponse response = MakeRequest(url);
        
        if (response.response_code == 200 && !response.data.empty()) {
            return true;
        } else {
            std::cerr << "Connection test failed: HTTP " << response.response_code 
                      << std::endl;
            return false;
        }
    } catch (const std::exception& e) {
        std::cerr << "Connection test failed: " << e.what() << std::endl;
        return false;
    }
}
