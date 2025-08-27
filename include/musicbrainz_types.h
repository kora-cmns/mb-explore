#ifndef MUSICBRAINZ_TYPES_H_
#define MUSICBRAINZ_TYPES_H_

#include <string>
#include <vector>

struct Artist {
    std::string mbid;
    std::string name;
    std::string sort_name;
    std::string disambiguation;
};

struct Work {
    std::string mbid;
    std::string title;
    std::string type;
};

struct Recording {
    std::string mbid;
    std::string title;
    std::vector<Artist> artist_credits;
    std::string work_mbid;
    int score;
    std::string disambiguation;
};

#endif  // MUSICBRAINZ_TYPES_H_