#include "song.h"

// Constructor
Song::Song(const QString& title, const QString& artist, int duration)
    : title(title), artist(artist), duration(duration), plays(0) {}

// Getters
QString Song::getTitle() const { return title; }
QString Song::getArtist() const { return artist; }
float Song::getDuration() const { return duration; }
int Song::getPlays() const { return plays; }

// Setters
void Song::setTitle(const QString& newTitle) { title = newTitle; }
void Song::setArtist(const QString& newArtist) { artist = newArtist; }
void Song::setDuration(float newDuration) { duration = newDuration; }

// Functionalities
void Song::playSong() {
    // Increment the play counter
    plays++;

    // Simulate playing the song
    qDebug() << "Now playing:" << title << "by" << artist;
    qDebug() << "Play count for this song:" << plays;
}

void Song::searchAndPlay(const QString& songName, const QString& directory) {
    // Create a QDir object for the specified directory
    QDir temp(directory);  // 'directory' is passed from main(), pointing to the song's location

    // Set filter to search for .mp3 files
    temp.setNameFilters(QStringList() << "D:\spotify\spotify-project\3l_baraka\resources");
    temp.setFilter(QDir::Files);

    // Get the list of files in the directory
    QFileInfoList files = temp.entryInfoList();

    bool found = false;

    // Iterate over the files and check if any match the song title
    for (const QFileInfo &file : files) {
        if (file.fileName().startsWith(songName, Qt::CaseInsensitive)) {
            found = true;
            qDebug() << "Song found: " << file.fileName();
            playSong(); // Play the song if found
            break;
        }
    }

    if (!found) {
        qDebug() << "Song not found in the directory!";
    }
}


void Song::displaySongInfo() const {
    qDebug() << "Song Info:";
    qDebug() << "Title:" << title;
    qDebug() << "Artist:" << artist;
    qDebug() << "Duration:" << duration << "seconds";
    qDebug() << "Plays:" << plays;
}
