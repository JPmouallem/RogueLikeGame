typedef struct //Stores information such as type of items as well as their locations
{
    char elements[10];
    int positions[10][2];

}Items;

typedef struct //Stores data located inside different levels
{
    int roomDimensions [2];
    int numOfItems;
    int xOffset;
    int yOffset;
    int entryDoor[2];
    Items * items;

}Room;

typedef struct //Stores info about the user, gold held, room on, and position
{
    int position[2];
    int room;
    int totalGold;
}Hero;

/*
readLine
Reads a data file given by the user. Reads the file line by line and sends the line to parseData()
*/
void readLine();

/*
parseData
Takes the read data file line and splits it into useful information.
IN:room represents the struct room. hero represents the users character and their data.
roomNum keeps track of the current room being used. line is the current line of data being parsed.
*/
void parseData(Room * room,Hero * hero, int roomNum, char line[]);

/*
doorPosition
Finds the position of all door elements.
IN: tokenHolder stores the data from the file that has been parsed and is relevant to door elements.
Index is a variable to store the index position of the parsed data inside the array tokenHolder.
OUT: The function returns the position of the door read.
*/
int doorPosition(char ( * tokenHolder)[10], int index);

/*
elementPosition
Determines the poisition of the elements to be spawned into each room.
IN: tokenHolder stores the data from the file that has been parsed and is relevant to the elements.
Index is a variable to store the index position of the parsed data inside the array tokenHolder.
*/
void elementPosition(char ( * tokenHolder)[10], int index, int * coords);

/*
setRoomDimensions
Stores the data read from the file into the struct Room.
IN: room is a struct that stores information relevant to rooms. roomNum keeps track of which room the data is used for.
roomRows contains the number of rows in the room. roomCols contains the number of columns in the room.
*/
void setRoomDimensions(Room * room, int roomNum, int roomRows, int roomCols);

/*
addRoomItems
This function adds the elements from the data file into their respected room and stores their data in the struct Items.
IN: room is a struct that stores information relevant to rooms.roomNum keeps track of which room the data is used for.
elementType contains the type of element into the struct. yPos contains the y position of the element. xPos contains the x position of the element.
*/
void addRoomItems(Room * room, int roomNum, char elementType, int yPos, int xPos);

/*
drawScreen
Takes the data stored in Room * room and draws those rooms the the screen using ncurses.
IN:room is a struct that stores information relevant to rooms. This allows drawScreen to access the stored data.
*/
void drawScreen(Room * room);

/*
drawLine
Uses the parameters to draw rows using ncurses.
IN: startingY contains the Y position which the row will be made on. startingX contains the X position which the row will be made on.
length contains how long the row will be. drawnChar contains which chars will create the row.
*/
void drawLine(int startingY, int startingX, int length, char drawnChar);

/*
runGame
This function gathers the input that the user give while using the program and determines its use.
IN: room is a struct that stores information relevant to rooms. hero represents the struct which stores information relevant to the character.
*/
void runGame(Room * room, Hero * hero);

/*
canMove
Determines if the user is able to move to the location they desire.
IN:yPos contains the y value of the tile the user will move to. xPos contains the x value of the tile the user will move to.
OUT: returns a value 0,1, or 2. 0 means you can move, 1 mean you cannot and 2 represents that the user has quit.
*/
int canMove(int yPos, int xPos);

/*
handleMove
This function determines what should be done with the element that the user walks on.
IN:hero represents a struct that stores information about the character. room is a struct which stores information relevant to rooms.
currentYPos/currentXPos contains the heros current poisiton. newYPos/newXPos contains the position where they will move to.
xOffset/yOffset contains how much the position is shifted.
*/
void handleMove(Hero * hero, Room * room, int currentYPos, int currentXPos, int newYPos, int newXPos, int xOffset, int yOffset);

/*
teleport
Moves the character to the next room when they step on a door.
IN: hero is a struct which stores data relevant to the character. room is a struct which stores data releveant to rooms.
*/
void teleport(Hero * hero, Room * room);

/*
handleGameOver
Ends the game and displays the total gold collected
IN: hero is a struct which stores data relevant to the character. room is a struct which stores data relevant to the room.
*/
void handleGameOver(Hero * hero, Room * room);

