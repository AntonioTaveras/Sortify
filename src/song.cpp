#include "song.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

// Helper: Parses a single CSV line
static std::vector<std::string> parseCSVLine(const std::string& line) {
	std::vector<std::string> fields;
	std::string current;
	bool inQuotes = false;

	for (size_t i = 0; i < line.size(); i++) {
		char c = line[i];
		if (c == '"') {
			// Handle escaped quotes ("") inside quoted fields
			if (inQuotes && i + 1 < line.size() && line[i + 1] == '"') {
				current += '"';
				i++;
			} else {
				inQuotes = !inQuotes;
			}
		} else if (c == ',' && !inQuotes) {
			fields.push_back(current);
			current.clear();
		} else if (c != '\r') {
			current += c;
		}
	}
	fields.push_back(current);
	return fields;
}

// Load songs
std::vector<Song> loadSongs(const std::string& filename) {
	std::vector<Song> songs;
	std::ifstream file(filename);

	if (!file.is_open()) {
		std::cerr << "Error: Could not open file " << filename << std::endl;
		return songs;
	}

	// Reserve space for 114,000 tracks to prevent resizing
	songs.reserve(114000);

	std::string line;
	if (!std::getline(file, line))
		return songs;

	// Read column headers and record each column's index
	std::vector<std::string> headers = parseCSVLine(line);
	std::unordered_map<std::string, size_t> colIdx;
	for (size_t i = 0; i < headers.size(); i++)
		colIdx[headers[i]] = i;

	// Look up each column index by name (with Kaggle's default indices as backup)
	size_t idxArtists = colIdx.count("artists") ? colIdx["artists"] : 2;
	size_t idxTrackName = colIdx.count("track_name") ? colIdx["track_name"] : 4;
	size_t idxPopularity = colIdx.count("popularity") ? colIdx["popularity"] : 5;
	size_t idxDuration = colIdx.count("duration_ms") ? colIdx["duration_ms"] : 6;
	size_t idxDanceability = colIdx.count("danceability") ? colIdx["danceability"] : 8;
	size_t idxEnergy = colIdx.count("energy") ? colIdx["energy"] : 9;
	size_t idxTempo = colIdx.count("tempo") ? colIdx["tempo"] : 18;

	size_t maxRequiredIdx = std::max({idxArtists, idxTrackName, idxPopularity, idxDuration,
		idxDanceability, idxEnergy, idxTempo});

	// Loop through all CSV lines
	while (std::getline(file, line)) {
		if (line.empty())
			continue;

		std::vector<std::string> row = parseCSVLine(line);
		if (row.size() <= maxRequiredIdx)
			continue;

		try {
			Song s;
			s.track_name = row[idxTrackName];
			s.artists = row[idxArtists];
			s.popularity = std::stoi(row[idxPopularity]);
			s.duration_ms = std::stoi(row[idxDuration]);
			s.danceability = std::stod(row[idxDanceability]);
			s.energy = std::stod(row[idxEnergy]);
			s.tempo = std::stod(row[idxTempo]);

			songs.push_back(s);
		} catch (const std::exception&) {
			// Skip any corrupted rows without crashing the program
			continue;
		}
	}

	return songs;
}

// Top N Tracks
void topNTracks(const std::vector<Song>& songs, int n, const std::string& attribute) {
	if (songs.empty() || n <= 0) {
		std::cout << "No tracks to display." << std::endl;
		return;
	}

	std::unordered_set<std::string> seen;
	int shown = 0;
	
	std::cout << "Top " << n << " tracks:" << std::endl;

	for (size_t i = 0; i < songs.size() && shown < n; i++) {
		const Song& s = songs[i];

		// Combine track_name and artists as a unique key (using '|' as delimiter)
		// prevents collisions between two different name/artist pairs
		std::string key = s.track_name + "|" + s.artists;
		if (seen.count(key))
			continue; // Skip duplicate song
		seen.insert(key);
		shown++;
		
		std::cout << shown << ". " << s.track_name << " - " << s.artists << " ("; 
		
		if (attribute == "popularity")
			std::cout << "popularity: " << s.popularity;
		else if (attribute == "danceability")
			std::cout << std::fixed << std::setprecision(3) << "danceability: " << s.danceability;
		else if (attribute == "energy") 
			std::cout << std::fixed << std::setprecision(3) << "energy: " << s.energy;
		else if (attribute == "tempo") 
			std::cout << std::fixed << std::setprecision(3) << "tempo: " << s.tempo;
		else if (attribute == "duration")
			std::cout << "duration: " << s.duration_ms << " ms";

		std::cout << ")" << std::endl;
	}
}
