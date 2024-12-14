#ifndef SONG_H
#define SONG_H
#include <QString>
#include <QDebug>
#include <QDir>
#include <QFileInfoList>
#include <QFileInfo>
#include <QStringList>
class song {
private:
    QString title;   // Song title
    QString artist;  // Artist name
    float duration;  // Duration in seconds
    int plays;       // Play count

public:
    // Default constructor
    song() : title(""), artist(""), duration(0), plays(0) {}

    // Parameterized constructor
    song(const QString& title, const QString& artist, int duration);

    // Getters and Setters
    QString getTitle() const;
    QString getArtist() const;
    float getDuration() const;
    int getPlays() const;
    void setTitle(const QString& newTitle);
    void setArtist(const QString& newArtist);
    void setDuration(float newDuration);

    // Functionalities
    void playSong();
    void displaySongInfo() const;
    void searchAndPlay(const QString& songName, const QString& directory);
};

#endif
