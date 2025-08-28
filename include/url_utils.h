#ifndef URL_UTILS_H_
#define URL_UTILS_H_

#include <string>

// URL encoding utility function
std::string UrlEncode(const std::string& input);

// Build MusicBrainz search URL for recordings by artist and title
std::string BuildSearchUrl(const std::string& artist, const std::string& title, int limit = 10);

#endif  // URL_UTILS_H_