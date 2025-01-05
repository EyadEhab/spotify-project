Music Player Application

Overview:
  This is a Music Player Application developed in C++. It allows users to create and manage playlists, add/remove songs, play songs, sort playlists, and perform various operations on a music database. The application uses a combination of linked lists, binary search trees (BST), and file handling to manage playlists and songs.

Features
  1-Playlist Management:

   Create new playlists.

   Load existing playlists.

   Delete playlists.

  2-Song Management:

   Add songs to a playlist.

   Remove songs from a playlist.

   Delete songs from the music database.

  3-Playback:

   Play all songs in a playlist.

   Play a specific song by name.

   Pause, resume, skip to the next song, or go back to the previous song during playback.

  4-Sorting:

   Sort songs by:

   Number of plays (ascending/descending).

   Song name (A-Z/Z-A).

   Artist name (A-Z/Z-A).

   Recently played (most/least recent).

   Time played (most/least recent).

  5-Binary Search Tree (BST) Operations:

   In-order, pre-order, and post-order traversal of songs in a playlist.

  6-Search:

   Search for a song in the music database.

   Search for a playlist in the playlist database.

  7-File Handling:

   Save and load playlists and songs from text files.

Requirements
  C++ Compiler: Ensure you have a C++ compiler installed (e.g., g++).

  MiniAudio Library: The application uses the MiniAudio library for audio playback. Ensure the library is properly set up in your environment.

  Terminal: The application is designed to run in a terminal environment.

File Structure
  main.cpp: The main driver program that handles user input and menu navigation.
  
  playlist.cpp: Implements the playList class for managing playlists and songs.
  
  song.cpp: Implements the song class for managing individual songs and audio playback.
  
  playlist.h: Header file for the playList class.
  
  song.h: Header file for the song class.

  resources/: Directory containing the music database and media files.

   musics.txt: Text file storing song metadata (title, artist, duration, plays, time played).
  
   playlist.txt: Text file storing playlist metadata (playlist name, number of songs, song titles).
  
   media/: Directory containing audio files (e.g., .mp3 files).

How to Run
  Clone the Repository:
   git clone https://github.com/EyadEhab/spotify-project.git
   cd music-player
   Compile the Program:
      g++ main.cpp playlist.cpp song.cpp -o music_player -lminiaudio
      Run the Program:
        ./music_player
  Follow the On-Screen Instructions:
    Use the menu to create playlists, add/remove songs, play songs, and perform other operations.

Code Structure
  Key Classes
   1-song:
    Manages individual songs.
    Handles audio playback using the MiniAudio library.
    Provides methods to load, play, and delete songs.

   2-playList:
  Manages playlists as a linked list of songs.
  Provides methods to add, remove, sort, and play songs.
  Implements BST operations for sorting and traversal.
  
Contributing
  Contributions are welcome! If you find any issues or have suggestions for improvements, please open an issue or submit a pull request.  

Acknowledgments
  MiniAudio for providing the audio playback library.
  The C++ community for resources and inspiration.

Enjoy your music! 🎵
