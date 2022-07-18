
enum Color 
{
    RED ,
    BLUE ,
    GREEN ,
    YELLOW
};

struct Player
{
    unsigned short int player_number;
    char address[32][4];
    enum Color color;
};