#ifndef PLAYER_H
#define PLAYER_H
#define default_s 5
using namespace std;

class player{
private:
    string name;
    int top_pos;
    int bot_pos;
    int score;
    char body[default_s]={'|','|','|','|','|'};

public:
    player(){
        this->name="default";
        this->top_pos=0;
        this->bot_pos=0;
        this->score=0;
    }
    player(const player& v):name(v.name),top_pos(v.top_pos),bot_pos(v.bot_pos),score(v.score){};
    const int _size=5;
    int getTopPos(){
        return this->top_pos;
    }
    void setTopPos(int t){
        this->top_pos=t;
    }
    int getBotPos(){
        return this->bot_pos;
    }
    void setBotPos(int t){
        this->bot_pos=t;
    }
    void addOne(){
        this->score+=1;
    }
    int getScore(){
        return this->score;
    }
    void setScore(int koliko){
        score=koliko;
    }

    char getBody(int w){
        return this->body[w];
    }
};

#endif // PLAYER_H
