#ifndef SONG_H
#define SONG_H

#include <QString>
#include <QDebug>
#include <QDir>
#include <QFileInfoList>
#include <QFileInfo>
#include <QStringList>

class Song {
private:
    QString title;   // Song title
    QString artist;  // Artist name
    float duration;    // Duration in seconds
    int plays;       // Play count

public:
    // Constructor
    Song(const QString& title, const QString& artist, int duration);



    // Getters
    QString getTitle() const;
    QString getArtist() const;
    float getDuration() const;
    int getPlays() const;

    // Setters
    void setTitle(const QString& newTitle);
    void setArtist(const QString& newArtist);
    void setDuration(float newDuration);
    void searchAndPlay(const QString& songName); // Searches for a song by title and plays it
    void searchAndPlay(const QString& songName, const QString& directory);

    // Functionalities
    void playSong();
    void displaySongInfo() const;
};

#endif // SONG_H
