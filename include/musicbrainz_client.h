#ifndef MUSICBRAINZ_CLIENT_H_
#define MUSICBRAINZ_CLIENT_H_

#include <string>

class MusicBrainzClient {
public:
    MusicBrainzClient();
    ~MusicBrainzClient() = default;

    bool TestConnection();

private:
    struct HttpResponse {
        std::string data;
        long response_code;
    };
    
    HttpResponse MakeRequest(const std::string& url);
};

#endif  // MUSICBRAINZ_CLIENT_H_
