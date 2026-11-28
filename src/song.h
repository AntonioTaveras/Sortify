#ifndef SONG_H
#define SONG_H

#include <string>
#include <vector>

struct Song {
  std::string track_name;
  std::string artists;
  int popularity = 0;
  double danceability = 0.0;
  double energy = 0.0;
  double tempo = 0.0;
  int duration_ms = 0;
};

// Load all tracks from CSV into a vector
std::vector<Song> loadSongs(const std::string& filename);

// Prints top N tracks for chosen attribute ("popularity", "danceability", etc.)
void topNTracks(const std::vector<Song>& songs, int n, const std::string& attribute);

#endif
