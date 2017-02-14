#include "A2.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ncurses.h>

void readLine(char * argv[])
{
    char line[150];

    int roomNum;
    roomNum = 0;

    FILE * fileptr;
    fileptr = fopen(argv[1], "r");

    if (fileptr == NULL)
    {

        printf("Failed to open input file.\n");
        exit(1);

    }

    Room * room = malloc(sizeof(Room)*6);

    Hero * hero = malloc(sizeof(Hero));

    for(int t = 0; t < 6; t++)
    {

        room[t].items = malloc(sizeof(Items));
        room[t].numOfItems = 0;

    }

    while(fgets(line, 150, fileptr))
    {

        parseData(room, hero, roomNum, line);
        roomNum++;

    }

    fclose(fileptr);

    drawScreen(room);

    runGame(room, hero);

}
void parseData(Room * room, Hero * hero, int roomNum, char line[])
{

    char * token = NULL;
    char * point = NULL;
    char modifiedLine[150];
    char tokenHolder[10][10];
    int tokenCounter;
    tokenCounter = 0;
    int elementCoord[2];

    int randomNumber;

    int doorPos;

    int yPoint;
    int xPoint;

    for(int i = 0; i < 150; i++)
    {

        modifiedLine[i] = '\0';

    }

    strcpy(modifiedLine, line);

    token = strtok(modifiedLine," ");
    strcpy(tokenHolder[0], token);

    while(token != NULL)
    {

        token = strtok(NULL," ");

        tokenCounter += 1;

        if(token == NULL)
        {
            break;
        }

        strcpy(tokenHolder[tokenCounter],token);
    }


    point = strtok(tokenHolder[0], "X");

    yPoint = atoi(point);

    point = strtok(NULL, "X");

    xPoint = atoi(point);

    setRoomDimensions(room, roomNum, yPoint, xPoint);

    for(int i = 1; i < tokenCounter; i++)
    {
        switch(tokenHolder[i][0]){

        case 'd':
                switch(tokenHolder[i][1])
                {

                case 'n':
                    doorPos = doorPosition(tokenHolder, i) + 1;
                    addRoomItems(room, roomNum, '+', 0, doorPos);

                    room[roomNum].entryDoor[0] = 1;
                    room[roomNum].entryDoor[1] = doorPos;

                    break;
                case 's':
                    doorPos = doorPosition(tokenHolder, i) + 1;
                    addRoomItems(room, roomNum, '+', room[roomNum].roomDimensions[0] + 1, doorPos);

                    room[roomNum].entryDoor[0] = room[roomNum].roomDimensions[0];
                    room[roomNum].entryDoor[1] = doorPos;

                    break;
                case 'e':
                    doorPos = doorPosition(tokenHolder, i) + 1;
                    addRoomItems(room, roomNum, '+', doorPos, room[roomNum].roomDimensions[1] + 1);

                    room[roomNum].entryDoor[0] = doorPos;
                    room[roomNum].entryDoor[1] = room[roomNum].roomDimensions[1];

                    break;
                case 'w':
                    doorPos = doorPosition(tokenHolder, i) + 1;
                    addRoomItems(room, roomNum, '+', doorPos, 0);

                    room[roomNum].entryDoor[0] = doorPos;
                    room[roomNum].entryDoor[1] = 1;
                    break;
                default:
                    break;
                }
            break;
        case 'h':
            elementPosition(tokenHolder, i, elementCoord);
            addRoomItems(room, roomNum, '@', elementCoord[0], elementCoord[1]);
            hero->room = roomNum;
            hero->position[0] = elementCoord[0] + 1;
            hero->position[1] = elementCoord[1] + 1;
            break;
        case 'z':
            elementPosition(tokenHolder, i, elementCoord);
            addRoomItems(room, roomNum, '<', elementCoord[0], elementCoord[1]);
            break;
        case 'a':
            elementPosition(tokenHolder, i, elementCoord);
            addRoomItems(room, roomNum, '>', elementCoord[0], elementCoord[1]);
            break;
        case 'g':
            elementPosition(tokenHolder, i, elementCoord);
            addRoomItems(room, roomNum, '*', elementCoord[0], elementCoord[1]);
            break;
        case 'G':
            elementPosition(tokenHolder, i, elementCoord);
            addRoomItems(room, roomNum, '8', elementCoord[0], elementCoord[1]);
            break;
        case 'w':
            elementPosition(tokenHolder, i, elementCoord);
            addRoomItems(room, roomNum, ')', elementCoord[0], elementCoord[1]);
            break;
        case 'W':
            elementPosition(tokenHolder, i, elementCoord);
            addRoomItems(room, roomNum, '(', elementCoord[0], elementCoord[1]);
            break;
        case 'm':
            elementPosition(tokenHolder, i, elementCoord);

            randomNumber = rand() % 4;

            switch(randomNumber)
            {

                case 0:
                    addRoomItems(room, roomNum, 'A', elementCoord[0], elementCoord[1]);
                    break;
                case 1:
                    addRoomItems(room, roomNum, 'B', elementCoord[0], elementCoord[1]);
                    break;
                case 2:
                    addRoomItems(room, roomNum, 'S', elementCoord[0], elementCoord[1]);
                    break;
                default:
                    addRoomItems(room, roomNum, 'Z', elementCoord[0], elementCoord[1]);
                    break;

            }

            break;
        case 'e':
            elementPosition(tokenHolder, i, elementCoord);
            addRoomItems(room, roomNum, ']', elementCoord[0], elementCoord[1]);
            break;
        case 'M':
            elementPosition(tokenHolder, i, elementCoord);
            addRoomItems(room, roomNum, 'T', elementCoord[0], elementCoord[1]);
            break;
        case 'p':
            elementPosition(tokenHolder, i, elementCoord);
            addRoomItems(room, roomNum, '!', elementCoord[0], elementCoord[1]);
            break;
        default:
            break;

        }

    }

}
int doorPosition(char ( * tokenHolder)[10], int index)
{
    int j = 2;
    char converison[2];

    while(tokenHolder[index][j] != '\0')
    {
        strcpy(&converison[j-2], &tokenHolder[index][j]);
        j ++;
    }

    return(atoi(converison));
}

void elementPosition(char ( * tokenHolder)[10], int index, int * coords)
{

    int j = 1;
    int h = 0;
    char yCoord[2];
    char xCoord[2];

    for (int r = 0; r < 2; r++)
    {
        yCoord[r] = '\0';
        xCoord[r] = '\0';
    }

    while(tokenHolder[index][j] != ',')
    {

        strcpy(&yCoord[j-1], &tokenHolder[index][j]);
        j ++;
    }

    j++;

    while(tokenHolder[index][j] != '\0')
    {
        strcpy(&xCoord[h], &tokenHolder[index][j]);
        j ++;
        h ++;
    }

    coords[0] = atoi(yCoord);
    coords[1] = atoi(xCoord);

}

void setRoomDimensions(Room * room, int roomNum, int roomRows, int roomCols)
{

    room[roomNum].roomDimensions[0] = roomRows;
    room[roomNum].roomDimensions[1] = roomCols;

}
void addRoomItems(Room * room, int roomNum, char elementType, int yPos, int xPos)
{

    int wallOffset;
    wallOffset = 1;

    if (elementType == '+')
    {

        wallOffset = 0;

    }

    room[roomNum].items->elements[room[roomNum].numOfItems] = elementType;
    room[roomNum].items->positions[room[roomNum].numOfItems][0] = yPos + wallOffset;
    room[roomNum].items->positions[room[roomNum].numOfItems][1] = xPos + wallOffset;

    room[roomNum].numOfItems++;
}

void drawScreen(Room * room)
{
    int roomNum;
    roomNum = 0;

    int originY;
    int originX;
    originY = 1;
    originX = 1;

    int maxY;
    maxY = 0;
    int space;
    space = 5;
    int minYScr;
    minYScr = 0;
    int minXScr;
    minXScr = 0;

    int dimensionY;
    dimensionY = 0;
    int dimensionX;
    dimensionX = 0;

    char northSouthWall = '-';
    char eastWestWall = '|';
    char tile = '.';

    Items * items;
    int numberOfItems;

    initscr();

    getmaxyx(stdscr, minYScr, minXScr);

    if ((minYScr < 50) && (minXScr < 90))
    {

        printf("You screen needs to be large [Minimum y of 50 and x of 90]\n");
        endwin();
        exit(1);
    }

    for (; roomNum < 6; roomNum++)
    {

        if (roomNum > 0 && roomNum < 3)
        {

            originX = originX + dimensionX + space;
        }

        if (roomNum == 3)
        {

            originY = maxY + space;
            originX = 1;
        }

        if (roomNum > 3)
        {

            originX = originX + dimensionX + space;
        }

        dimensionY = room[roomNum].roomDimensions[0];
        dimensionX = room[roomNum].roomDimensions[1];

        room[roomNum].yOffset = originY;
        room[roomNum].xOffset = originX;

        items = room[roomNum].items;
        numberOfItems = room[roomNum].numOfItems;

        if (dimensionY > maxY && roomNum < 3)
        {

            maxY = dimensionY;

        }

        drawLine(originY - 1, originX - 1, dimensionX + 2, northSouthWall);

        for(int row = originY; row < originY + dimensionY; row++)
        {

            drawLine(row, originX - 1, 1, eastWestWall);

            drawLine(row, originX, dimensionX, tile);

            drawLine(row, originX + dimensionX, 1, eastWestWall);
        }

        drawLine(originY + dimensionY, originX - 1, dimensionX + 2, northSouthWall);

        for (int itemNum = 0; itemNum < numberOfItems; itemNum ++)
        {

            drawLine(originY + items->positions[itemNum][0] - 1, originX + items->positions[itemNum][1] - 1, 1, items->elements[itemNum]);
        }
    }
}

void drawLine(int startingY, int startingX, int length, char drawnChar)
{
    for(int i = startingX; i < startingX + length; i++)
    {

        mvaddch(startingY, i, drawnChar);
    }
}

void runGame(Room * room, Hero * hero){

    char inputChar;
    int moveable;
    moveable = 0;

    int currentHeroY;
    currentHeroY = 0;
    int currentHeroX;
    currentHeroX = 0;

    int proposedHeroY;
    proposedHeroY = 0;
    int proposedHeroX;
    proposedHeroX = 0;

    int offsetX;
    int offsetY;

    noecho();
    curs_set(FALSE);

    do {

    offsetX = room[hero->room].xOffset;
    offsetY = room[hero->room].yOffset;

    currentHeroY = hero->position[0];
    currentHeroX = hero->position[1];

    move(currentHeroY, currentHeroX);

    inputChar = getch();

    switch(inputChar){

    case 'q':
        break;

    case 'w':
        proposedHeroY = currentHeroY - 1;
        proposedHeroX = currentHeroX;

        break;
    case 'a':
        proposedHeroY = currentHeroY;
        proposedHeroX = currentHeroX - 1;
        break;
    case 's':
        proposedHeroY = currentHeroY + 1;
        proposedHeroX = currentHeroX;
        break;
    case 'd':
        proposedHeroY = currentHeroY;
        proposedHeroX = currentHeroX + 1;
        break;

    }

        moveable = canMove(proposedHeroY, proposedHeroX);

        if (moveable == 0){

            handleMove(hero, room, currentHeroY, currentHeroX, proposedHeroY, proposedHeroX, offsetY, offsetX);

        }
        else if (moveable == 2)
        {

            break;

        }

    }while(inputChar != 'q');


    handleGameOver(hero, room);


}

int canMove(int yPos, int xPos){
    switch(mvinch(yPos, xPos)){

    case '|':
    case '-':
    case 'A':
    case 'B':
    case 'S':
    case 'Z':
    case 'T':
        return 1;
    case '<':
    case '>':
        return 2;

    default:
        return 0;
    }

}

void handleMove(Hero * hero, Room * room, int currentYPos, int currentXPos, int newYPos, int newXPos, int xOffset, int yOffset) {

    switch (mvinch(newYPos, newXPos)) {
        case '+':
            teleport(hero, room);
            return;
        case '*':
            hero->totalGold += rand() % 51;
            break;
        case '8':
            hero->totalGold += ( (rand() % 201) + 50);
            break;
    }

    drawLine(currentYPos, currentXPos, 1, '.');
    drawLine(newYPos, newXPos, 1, '@');

    hero->position[0] = newYPos;
    hero->position[1] = newXPos;
    move(newYPos, newXPos);
}

void teleport(Hero * hero, Room * room){

    int newRoom;
    int currentRoom;

    int offsetY;
    int offsetX;

    currentRoom = hero->room;

    if(currentRoom == 5){

        newRoom = 0;
        hero->room = newRoom;

    }
    else
    {

        newRoom = currentRoom + 1;
        hero->room = newRoom;

    }

    offsetY = room[currentRoom].yOffset;
    offsetX = room[currentRoom].xOffset;

    drawLine(hero->position[0], hero->position[1], 1, '.');

    offsetY = room[newRoom].yOffset;
    offsetX = room[newRoom].xOffset;

    hero->position[0] = room[newRoom].entryDoor[0] - 1 + offsetY;
    hero->position[1] = room[newRoom].entryDoor[1] - 1 + offsetX;

    drawLine(hero->position[0], hero->position[1], 1, '@');
    move(hero->position[0] + offsetY - 1, hero->position[1] - 1 + offsetX);

}

void handleGameOver(Hero * hero, Room * room){

    endwin();

    printf("You and your hero collect %d gold!\n", hero->totalGold);

    free(room);
    free(hero);

    exit(1);
}

