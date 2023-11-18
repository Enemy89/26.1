#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include <iomanip>
#include <cstdlib>

class Track {
    std::string name;
    std::time_t t = std::time(nullptr);
    std::tm dateCreation = *std::localtime(&t);
    int lengthTime;

public:

    std::string getName() {
        return name;
    }

    std::tm getDateCreation() {
        return dateCreation;
    }

    int getLengthTime() {
        return lengthTime;
    }

    void initialize(const std::string &title, int duration) {
        name = title;
        lengthTime = duration;
    }
};

    class Player {
        std::string state = "none";
        std::vector<Track> tracks;

    public:
        std::string getState() {
            return state;
        }

        void addTrack(Track* track) {
            tracks.push_back(*track);
        }

        void play() {
            state = "play";
            int check = 0;
            std::string userTrack;
            std::cout << "Enter the name of the song:" << std::endl;
            std::cin >> userTrack;
            for (int i = 0; i < tracks.size(); ++i) {
                if (tracks[i].getName() == userTrack) {
                    check = i+1;
                }
            }
            if (check == 0) {
                std::cout << "Track not found." << std::endl;
            } else {
                std::tm tmp = tracks[check-1].getDateCreation();
                std::cout << tracks[check-1].getName() << " " << std::put_time(&tmp, "%d/%m/%Y") << " "
                          << tracks[check-1].getLengthTime() << std::endl;
            }
        }

        void pause () {
            state = "pause";
            std::cout<<"Pause"<<std::endl;
        }

        void next () {
            std::srand(std::time(nullptr));
            int randomNumber = std::rand() % 3;
            std::tm tmp = tracks[randomNumber].getDateCreation();
            std::cout << tracks[randomNumber].getName() << " " << std::put_time(&tmp, "%d/%m/%Y") << " "
                      << tracks[randomNumber].getLengthTime() << std::endl;
        }

        void stop () {
            state="none";
            std::cout<<"Music stopped."<<std::endl;
        }
    };

    int main() {
        Player *player = new Player;

        Track *track1 = new Track;
        track1->initialize("One", 360);
        player->addTrack(track1);

        Track *track2 = new Track;
        track2->initialize("Two", 285);
        player->addTrack(track2);

        Track *track3 = new Track;
        track3->initialize("Three", 300);
        player->addTrack(track3);

        while (true) {
            std::cout << "Enter the command (play/pause/next/stop/exit):" << std::endl;
            std::string command;
            std::cin >> command;

            if (command == "play" && command != player->getState()) {
                player->play();
            } else {
                if (command == "exit") {
                    break;
                } else {
                    if (command == "pause" && command != player->getState() && "none" != player->getState()) {
                        player->pause();
                    } else {
                        if (player->getState() == "play") {
                            player->next();
                        }
                        else {
                            if (player->getState() == "play") {
                                player->stop();
                            }
                        }
                    }
                }
            }
        }

        delete track1;
        delete track2;
        delete track3;
        delete player;
    }