#include <iostream>

int Max(int a, int b) {
    return a > b ? a : b;
}

int Min(int a, int b) {
    return a < b ? a : b;
}

void SetSymbol(char** array, int size, char symbol, int posY, int posX) {
    array[posY][posX] = symbol;
    for (int i = Max(0, posY - 1); i <= Min(size - 1, posY + 1); i++)
    {
        for (int j = Max(0, posX - 1); j <= Min(size - 1, posX + 1); j++)
        {
            if (array[i][j] == '~')
            {
                array[i][j] = '_';
            }
        }
    }
}

bool StupSave(char** array, int size, int posY, int posX) {
    int summ = 0;
    for (int i = Max(0, posY - 1); i <= Min(size - 1, posY + 1); i++)
    {
        for (int j = Max(0, posX - 1); j <= Min(size - 1, posX + 1); j++)
        {
            if (array[i][j] != '~' && array[i][j] != '_')
            {
                summ++;
            }
        }
    }
    if (summ == 0)
        return true;
    else
        return false;
}

void PrintArr(char** array, int size) {
    std::cout << "   ";
    for (int i = 0; i < size; i++)
    {
        std::cout << i + 1 << " ";
    }
    std::cout << std::endl;

    for (int i = 0; i < size; i++)
    {
        if (i < 9)
            std::cout << i + 1 << "  ";
        else
            std::cout << i + 1 << " ";
        for (int j = 0; j < size; j++)
        {
            std::cout << array[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void WaterArr(char** array, int size) {
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            array[i][j] = '~';
        }
    }
    std::cout << std::endl;
}

void SaveMatrix(char** map, char** mapcopy, int size) {
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++) {
            mapcopy[i][j] = map[i][j];
        }
    }
}

void MatrixRecover(char** map, char** mapcopy, int size) {
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++) {
            map[i][j] = mapcopy[i][j];
        }
    }
}

bool PlaceMap(int team[], int teamcol, char** UMap, char** UMapcopy, int size) {
    int vall, Y_poz, X_poz, inventory[4] = { '1', '2', '3', '4' }, numst = 0;
    std::string direct;
    SaveMatrix(UMap, UMapcopy, size);
    std::cout << "Состав: " << std::endl;
    for (int i = teamcol; i > 0; i--)
    {
        std::cout << teamcol - i + 1 << ") Количество кораблей с " << teamcol - i + 1 << "-ти палубами: " << team[teamcol - i] << std::endl;
    }

    std::cout << "Выберите корабль: ";
    std::cin >> vall;
    if (vall < 5 && vall > 0 && team[vall - 1] > 0) {
        std::cout << "Введите позицию по Х: ";
        std::cin >> X_poz;
        std::cout << "Введите позицию по Y: ";
        std::cin >> Y_poz;
        X_poz--;
        Y_poz--;
        if (vall != 1)
        {
            std::cout << "Введите направлене: \nDown: d or D \nLeft: l or L \nRight: r or R \nUp: u or U \n";
            std::cin >> direct;
        }
        if ((direct == "d" || direct == "D" || direct == "Down" || vall == 1) && (Y_poz + vall <= size))
        {
            int good = 0;
            for (int i = 0; i < vall; i++)
            {
                if (StupSave(UMap, size, Y_poz + i, X_poz))
                    good++;

            }
            if (good == vall)
            {
                for (int i = 0; i < vall; i++)
                {
                    SetSymbol(UMap, size, inventory[vall - 1], Y_poz + i, X_poz);
                }
            }
            else
                numst++;
        }
        else if ((direct == "l" || direct == "L" || direct == "Left") && (X_poz - vall >= 0))
        {
            int good = 0;
            for (int i = 0; i < vall; i++)
            {
                if (StupSave(UMap, size, Y_poz + i, X_poz - i))
                    good++;

            }
            if (good == vall)
            {
                for (int i = 0; i < vall; i++)
                {
                    if (UMap[Y_poz][X_poz - i] == '~' || UMap[Y_poz][X_poz - i] == '_')
                        SetSymbol(UMap, size, inventory[vall - 1], Y_poz, X_poz - i);
                    else {
                        std::cout << 2;
                        numst++;
                    }
                }
            }
            else
                numst++;
        }
        else if ((direct == "r" || direct == "R" || direct == "Right") && (X_poz + vall < size))
        {
            int good = 0;
            for (int i = 0; i < vall; i++)
            {
                if (StupSave(UMap, size, X_poz + i, X_poz))
                    good++;

            }
            if (good == vall)
            {
                for (int i = 0; i < vall; i++)
                {
                    if (UMap[Y_poz][X_poz + i] == '~' || UMap[Y_poz][X_poz + i] == '_')
                        SetSymbol(UMap, size, inventory[vall - 1], Y_poz, X_poz + i);
                    else
                        numst++;
                }
            }
            else
                numst++;
        }
        else if ((direct == "u" || direct == "U" || direct == "Up") && (Y_poz - vall >= 0))
        {
            int good = 0;
            for (int i = 0; i < vall; i++)
            {
                if (StupSave(UMap, size, Y_poz - i, X_poz))
                    good++;

            }
            if (good == vall)
            {
                for (int i = 0; i < vall; i++)
                {
                    if (UMap[Y_poz - i][X_poz] == '~' || UMap[Y_poz - i][X_poz] == '_')
                        SetSymbol(UMap, size, inventory[vall - 1], Y_poz - i, X_poz);
                    else
                        numst++;
                }
            }
            else
                numst++;
        }
        else {
            std::cout << "Error: Invalid command" << std::endl;
            PlaceMap(team, teamcol, UMap, UMapcopy, size);
            return false;
        }
    }
    else {
        std::cout << "Error: Invalid command" << std::endl;
        PlaceMap(team, teamcol, UMap, UMapcopy, size);
        return false;
    }
    if (numst != 0)
    {
        std::cout << "Error: Place installation" << std::endl;
        MatrixRecover(UMap, UMapcopy, size);
        PlaceMap(team, teamcol, UMap, UMapcopy, size);
        return false;
    }
    else {
        team[vall - 1] = team[vall - 1] - 1;
        return true;
    }
}

bool Check(char** villMap, int size, int botPosX, int botPosY) {
    for (int i = Max(0, botPosX - 1); i <= Min(botPosX + 1, size - 1); i++)
    {
        for (int j = Max(0, botPosY - 1); j <= Min(botPosY + 1, size - 1); j++)
        {
            if (villMap[i][j] != '~') {
                return false;
            }
        }
    }
    return true;
}

bool Check2(char** villMap, int size, int botPosX, int botPosY) {
    if (botPosX < 10 && botPosX >= 0 && botPosY < 10 && botPosY >= 0)
        return true;
    return false;
}

void RandGenVill1(char** villMap, int size) {
    int oneShip = 4, twoShip = 3, threeShip = 2, fourShip = 1;
    while (fourShip != 0) {
        int botChoise = rand() % 2;
        if (botChoise == 0) {
            int botPosX = rand() % 10;
            int dopInt = rand() % 7 - 3;
            int botPosY1 = botPosX;
            while (!Check(villMap, size, botPosX, botPosY1)) {
                botPosX = rand() % 10;
                botPosY1 = botPosX;
            }
            if (dopInt == 0 || dopInt == 1 || dopInt == -1 || dopInt == -2 || dopInt == 2) {
                while (dopInt == 0 || dopInt == 1 || dopInt == -1 || dopInt == -2 || dopInt == 2) {
                    dopInt = rand() % 7 - 3;
                }
            }
            int botPosY2 = botPosX - dopInt;
            int botPosY3 = 0, botPosY4 = 0;
            if (dopInt > 0) {
                botPosY3 = botPosX - dopInt + 1;
                botPosY4 = botPosX - dopInt + 2;
            }
            else if (dopInt < 0) {
                botPosY3 = botPosX - dopInt - 1;
                botPosY4 = botPosX - dopInt - 2;
            }
            while (!Check2(villMap, size, botPosX, botPosY2)) {
                int dopInt = rand() % 7 - 3;
                if (dopInt == 0 || dopInt == 1 || dopInt == -1 || dopInt == -2 || dopInt == 2) {
                    while (dopInt == 0 || dopInt == 1 || dopInt == -1 || dopInt == 2 || dopInt == -2) {
                        dopInt = rand() % 7 - 3;
                    }
                }
                int botPosY2 = botPosX - dopInt;
            }
            while (!Check2(villMap, size, botPosX, botPosY3)) {
                int dopInt = rand() % 7 - 3;
                if (dopInt == 0 || dopInt == 1 || dopInt == -1 || dopInt == 2 || dopInt == -2) {
                    while (dopInt == 0 || dopInt == 1 || dopInt == -1 || dopInt == -2 || dopInt == 2) {
                        dopInt = rand() % 7 - 3;
                    }
                }
                if (dopInt > 0) {
                    int botPosY3 = botPosX - dopInt + 1;
                }
                else if (dopInt < 0) {
                    int botPosY3 = botPosX - dopInt - 1;
                }
            }
            while (!Check2(villMap, size, botPosX, botPosY4)) {
                int dopInt = rand() % 7 - 3;
                if (dopInt == 0 || dopInt == 1 || dopInt == -1 || dopInt == 2 || dopInt == -2) {
                    while (dopInt == 0 || dopInt == 1 || dopInt == -1 || dopInt == 2 || dopInt == -2) {
                        dopInt = rand() % 7 - 3;
                    }
                }
                if (dopInt > 0) {
                    int botPosY4 = botPosX - dopInt + 2;
                }
                else if (dopInt < 0) {
                    int botPosY4 = botPosX - dopInt - 2;
                }
            }
            if ((Check2(villMap, size, botPosX, botPosY1) && Check2(villMap, size, botPosX, botPosY2) && Check2(villMap, size, botPosX, botPosY3) && Check2(villMap, size, botPosX, botPosY4) && Check(villMap, size, botPosX, botPosY1) && Check(villMap, size, botPosX, botPosY2) && Check(villMap, size, botPosX, botPosY3) && Check(villMap, size, botPosX, botPosY4))) {
                villMap[botPosX][botPosY1] = '4';
                villMap[botPosX][botPosY2] = '4';
                villMap[botPosX][botPosY3] = '4';
                villMap[botPosX][botPosY4] = '4';
                fourShip--;
            }

            else if (botChoise == 1) {
                int botPosY = rand() % 10;
                int dopInt = rand() % 7 - 3;
                int botPosX1 = botPosY;
                while (!Check(villMap, size, botPosX1, botPosY)) {
                    botPosY = rand() % 10;
                    botPosX1 = botPosY;
                }
                if (dopInt == 0 || dopInt == 1 || dopInt == -1 || dopInt == 2 || dopInt == -2) {
                    while (dopInt == 0 || dopInt == 1 || dopInt == -1 || dopInt == 2 || dopInt == -2) {
                        dopInt = rand() % 7 - 3;
                    }
                }
                int botPosX2 = botPosY - dopInt;
                int botPosX3 = 0, botPosX4 = 0;
                if (dopInt > 0) {
                    botPosX3 = botPosY - dopInt + 1;
                    botPosX4 = botPosY - dopInt + 2;
                }
                else if (dopInt < 0) {
                    botPosX3 = botPosY - dopInt - 1;
                    botPosX4 = botPosY - dopInt - 2;
                }
                while (!Check2(villMap, size, botPosX2, botPosY)) {
                    int dopInt = rand() % 7 - 3;
                    if (dopInt == 0 || dopInt == 1 || dopInt == -1 || dopInt == 2 || dopInt == -2) {
                        while (dopInt == 0 || dopInt == 1 || dopInt == -1 || dopInt == 2 || dopInt == -2) {
                            dopInt = rand() % 7 - 3;
                        }
                    }
                    int botPosX2 = botPosY - dopInt;
                }
                while (!Check2(villMap, size, botPosX4, botPosY)) {
                    int dopInt = rand() % 7 - 3;
                    if (dopInt == 0 || dopInt == 1 || dopInt == -1 || dopInt == 2 || dopInt == -2) {
                        while (dopInt == 0 || dopInt == 1 || dopInt == -1 || dopInt == 2 || dopInt == -2) {
                            dopInt = rand() % 7 - 3;
                        }
                    }
                    if (dopInt > 0) {
                        int botPosX4 = botPosY - dopInt + 2;
                    }
                    else if (dopInt < 0) {
                        int botPosX4 = botPosY - dopInt - 2;
                    }
                }
                while (!Check2(villMap, size, botPosX3, botPosY)) {
                    int dopInt = rand() % 7 - 3;
                    if (dopInt == 0 || dopInt == 1 || dopInt == -1 || dopInt == 2 || dopInt == -2) {
                        while (dopInt == 0 || dopInt == 1 || dopInt == -1 || dopInt == 2 || dopInt == -2) {
                            dopInt = rand() % 7 - 3;
                        }
                    }
                    if (dopInt > 0) {
                        int botPosX3 = botPosY - dopInt + 1;
                    }
                    else if (dopInt < 0) {
                        int botPosX3 = botPosY - dopInt - 1;
                    }
                }
                if (Check2(villMap, size, botPosX1, botPosY) && Check2(villMap, size, botPosX2, botPosY) && Check2(villMap, size, botPosX3, botPosY) && Check2(villMap, size, botPosX4, botPosY) && Check(villMap, size, botPosX1, botPosY) && Check(villMap, size, botPosX2, botPosY) && Check(villMap, size, botPosX3, botPosY) && Check(villMap, size, botPosX4, botPosY)) {
                    villMap[botPosX1][botPosY] = '4';
                    villMap[botPosX2][botPosY] = '4';
                    villMap[botPosX3][botPosY] = '4';
                    villMap[botPosX4][botPosY] = '4';
                    fourShip--;
                }
            }
        }
    }
    std::cout << std::endl;
    PrintArr(villMap, size);
    while (threeShip != 0) {
        int botChoise = rand() % 2;
        if (botChoise == 0) {
            int botPosX = rand() % 10;
            int dopInt = rand() % 5 - 2;
            int botPosY1 = botPosX;
            while (!Check(villMap, size, botPosX, botPosY1))
            {
                botPosX = rand() % 10;
                botPosY1 = botPosX;
            }
            if (dopInt == 0 || dopInt == 1 || dopInt == -1) {
                while (dopInt == 0 || dopInt == 1 || dopInt == -1) {
                    dopInt = rand() % 5 - 2;
                }
            }
            int botPosY2 = botPosX - dopInt;
            int botPosY3 = 0;
            if (dopInt > 0) {
                botPosY3 = botPosX - dopInt + 1;
            }
            else if (dopInt < 0) {
                botPosY3 = botPosX - dopInt - 1;
            }
            while (!Check2(villMap, size, botPosX, botPosY2)) {
                int dopInt = rand() % 5 - 2;
                if (dopInt == 0 || dopInt == 1 || dopInt == -1) {
                    while (dopInt == 0 || dopInt == 1 || dopInt == -1) {
                        dopInt = rand() % 5 - 2;
                    }
                }
                botPosY2 = botPosX - dopInt;
            }
            while (!Check2(villMap, size, botPosX, botPosY3)) {
                int dopInt = rand() % 5 - 2;
                if (dopInt == 0 || dopInt == 1 || dopInt == -1) {
                    while (dopInt == 0 || dopInt == 1 || dopInt == -1) {
                        dopInt = rand() % 5 - 2;
                    }
                }
                if (dopInt > 0) {
                    botPosY3 = botPosX - dopInt + 1;
                }
                else if (dopInt < 0) {
                    botPosY3 = botPosX - dopInt - 1;
                }
            }
            if (Check(villMap, size, botPosX, botPosY1) && Check(villMap, size, botPosX, botPosY2) && Check(villMap, size, botPosX, botPosY3) && Check2(villMap, size, botPosX, botPosY1) && Check2(villMap, size, botPosX, botPosY2) && Check2(villMap, size, botPosX, botPosY3)) {
                villMap[botPosX][botPosY1] = '3';
                villMap[botPosX][botPosY2] = '3';
                villMap[botPosX][botPosY3] = '3';
                threeShip--;
            }
        }

        else if (botChoise == 1) {
            int botPosY = rand() % 10;
            int dopInt = rand() % 5 - 2;
            int botPosX1 = botPosY;
            while (!Check(villMap, size, botPosY, botPosX1))
            {
                botPosY = rand() % 10;
                botPosX1 = botPosY;
            }
            if (dopInt == 0 || dopInt == 1 || dopInt == -1) {
                while (dopInt == 0 || dopInt == 1 || dopInt == -1) {
                    dopInt = rand() % 5 - 2;
                }
            }
            int botPosX2 = botPosY - dopInt;
            int botPosX3 = 0;
            if (dopInt > 0) {
                botPosX3 = botPosY - dopInt + 1;
            }
            else if (dopInt < 0) {
                botPosX3 = botPosY - dopInt - 1;
            }
            while (!Check2(villMap, size, botPosX2, botPosY)) {
                int dopInt = rand() % 5 - 2;
                if (dopInt == 0 || dopInt == 1 || dopInt == -1) {
                    while (dopInt == 0 || dopInt == 1 || dopInt == -1) {
                        dopInt = rand() % 5 - 2;
                    }
                }
                botPosX2 = botPosY - dopInt;
            }
            while (!Check2(villMap, size, botPosX3, botPosY)) {
                int dopInt = rand() % 5 - 2;
                if (dopInt == 0 || dopInt == 1 || dopInt == -1) {
                    while (dopInt == 0 || dopInt == 1 || dopInt == -1) {
                        dopInt = rand() % 5 - 2;
                    }
                }
                if (dopInt > 0) {
                    botPosX3 = botPosY - dopInt + 1;
                }
                else if (dopInt < 0) {
                    botPosX3 = botPosY - dopInt - 1;
                }
            }
            if (Check2(villMap, size, botPosX1, botPosY) && Check2(villMap, size, botPosX2, botPosY) && Check2(villMap, size, botPosX3, botPosY) && Check(villMap, size, botPosX1, botPosY) && Check(villMap, size, botPosX2, botPosY) && Check(villMap, size, botPosX3, botPosY)) {
                villMap[botPosX1][botPosY] = '3';
                villMap[botPosX2][botPosY] = '3';
                villMap[botPosX3][botPosY] = '3';
                threeShip--;
            }
        }
    }
    std::cout << std::endl;
    PrintArr(villMap, size);
    while (twoShip != 0) {
        int botChoise = rand() % 2;
        if (botChoise == 0) {
            int botPosX = rand() % 10;
            int dopInt = rand() % 2 - 1;
            int botPosY1 = botPosX;
            while (!Check(villMap, size, botPosX, botPosY1)) {
                botPosX = rand() % 10;
                botPosY1 = botPosX;
            }
            if (dopInt == 0) {
                while (dopInt == 0) {
                    dopInt = rand() % 2 - 1;
                }
            }
            int botPosY2 = botPosX - dopInt;
            while (!Check(villMap, size, botPosX, botPosY2)) {
                int dopInt = rand() % 3 - 1;
                if (dopInt == 0) {
                    while (dopInt == 0) {
                        dopInt = rand() % 3 - 1;
                    }
                }
                botPosY2 = botPosX - dopInt;
            }
            if (Check(villMap, size, botPosX, botPosY1) && Check(villMap, size, botPosX, botPosY2) && Check2(villMap, size, botPosX, botPosY2)) {
                villMap[botPosX][botPosY1] = '2';
                villMap[botPosX][botPosY2] = '2';
                twoShip--;
            }
        }
        else if (botChoise == 1) {
            int botPosY = rand() % 10;
            int dopInt = rand() % 2 - 1;
            int botPosX1 = botPosY;
            while (!Check(villMap, size, botPosX1, botPosY)) {
                botPosY = rand() % 10;
                botPosX1 = botPosY;
            }
            if (dopInt == 0) {
                while (dopInt == 0) {
                    dopInt = rand() % 2 - 1;
                }
            }
            int botPosX2 = botPosY - dopInt;
            while (!Check2(villMap, size, botPosX2, botPosY)) {
                int dopInt = rand() % 3 - 1;
                if (dopInt == 0) {
                    while (dopInt == 0) {
                        dopInt = rand() % 3 - 1;
                    }
                }
                botPosX2 = botPosY - dopInt;
            }
            if (Check(villMap, size, botPosX1, botPosY) && Check(villMap, size, botPosX2, botPosY) && Check2(villMap, size, botPosX2, botPosY)) {
                villMap[botPosX1][botPosY] = '2';
                villMap[botPosX2][botPosY] = '2';
                twoShip--;
            }
        }
    }
    std::cout << std::endl;
    PrintArr(villMap, size);
    while (oneShip != 0) {
        int botPosX = rand() % 10;
        int botPosY = rand() % 10;
        if (Check(villMap, size, botPosX, botPosY) && Check2(villMap, size, botPosX, botPosY)) {
            villMap[botPosX][botPosY] = '1';
            oneShip--;
        }
    }


}


int main()
{
    setlocale(LC_ALL, "ru");
    srand(time(nullptr));
    const int size = 10;
    char** UMap;
    UMap = new char* [size];
    const int teamcol = 4;
    int team[teamcol] = { 4, 3, 2, 1 };
    char** UMapcopy;
    UMapcopy = new char* [size];
    for (int i = 0; i < size; i++)
    {
        UMap[i] = new char[size];
        UMapcopy[i] = new char[size];
    }

    char** mapShoot = new char* [size];
    for (size_t i = 0; i < size; i++)
    {
        mapShoot[i] = new char[size];
    }
    WaterArr(mapShoot, size);

    char** villMap = new char* [size];
    for (int i = 0; i < size; i++)
    {
        villMap[i] = new char[size];
    }
    WaterArr(villMap, size);

    WaterArr(UMap, size);
    PrintArr(UMap, size);
    for (int i = 0; i < 10; i++)
    {
        if (PlaceMap(team, teamcol, UMap, UMapcopy, size)) {
            system("cls");
        }
        PrintArr(UMap, size);
    }
    int positionX, positionY;
    int count = 0;
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
        {
            if (villMap[i][j] != '~')
                count++;
        }
    }
    while (count != 0) {
        std::cout << "The enemy is still intact!!!" << std::endl
            << count << std::endl;
        std::cout << "Enter X position: ";
        std::cin >> positionX;
        std::cout << std::endl << "Enter Y position: ";
        std::cin >> positionY;
        char choise = villMap[positionX][positionY];
        std::cout << choise << std::endl;
        if (choise == '1' || choise == '2' || choise == '3' || choise == '4') {
            villMap[positionX][positionY] = '*';
            mapShoot[positionX][positionY] = '*';
            count--;
        }
        else if (choise == '~' || choise == '*')
            mapShoot[positionX][positionY] = '.';
        system("cls");
        PrintArr(mapShoot, size);
        std::cout << std::endl;
        PrintArr(villMap, size);
    }
    std::cout << "Congratulations, fighter!\nThe enemy is defeated!" << std::endl;
    std::cout << "END" << std::endl;
}