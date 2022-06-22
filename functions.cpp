#include "functions.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <cstdlib>
#include <Windows.h>
#include <fstream>

// ** CONSTRUCTOR ** //
Ships::Ships()
{
    game();
}

// ** MENU ** // 
void Ships::game()
{
    std::string player_1[11][11];
    std::string player_2[11][11];
    std::string bot[11][11];
    std::string player_name1;
    std::string player_name2;
    generate_the_bot(bot);

before:
    std::cout << "\t\t  ######     #    ####### ####### #       #######  #####  #     # ### ###### \n";
    std::cout << "\t\t  #     #   # #      #       #    #       #       #     # #     #  #  #     #  \n";
    std::cout << "\t\t  #     #  #   #     #       #    #       #       #       #     #  #  #     # \n";
    std::cout << "\t\t  ######  #     #    #       #    #       #####    #####  #######  #  ######  \n";
    std::cout << "\t\t  #     # #######    #       #    #       #             # #     #  #  #      \n";
    std::cout << "\t\t  #     # #     #    #       #    #       #       #     # #     #  #  #   \n";
    std::cout << "\t\t  ######  #     #    #       #    ####### #######  #####  #     # ### #   \n\n\n";


    std::cout << "MENU\n";
    std::cout << "1) Play vs bot\n";
    std::cout << "2) Rules\n";
    std::cout << "3) Exit\n";

    std::cin >> choice;
    if (choice == 1)
    {
        system("cls");
        std::cout << "Enter your nickname: ";
        std::cin >> player_name1;
        std::cout << "\n";
    before_1:
        std::cout << "1) Choose the ships by yourself\n";
        std::cout << "2) Generate your ships\n";
        std::cout << "3) Back\n";
        std::cin >> choice_p;
        system("cls");
        if (choice_p == 1)
        {
            choose_ship_pos(player_1);
        }
        else if (choice_p == 2)
        {
            generate_the_bot(player_1);
        }
        else if (choice_p == 3) goto before;
        else
        {
            std::cout << "Choose 1, 2 or 3\n";
            goto before_1;
        }
        std::cout << "Before we move on, I ask you to change the console size to fullscreen\n";
        Sleep(3000);
        fight_vs_bot(player_1, bot, player_name1);
    }
    else if (choice == 2)
    {
    before_2:
        system("cls");
        out_rules();
        std::cout << "\n\nTo back type 1 and press enter\n";
        std::cin >> choice;
        if (choice == 1)
        {
            system("cls");
            goto before;
        }
        else
        {
            std::cout << "Type 1 to back";
            goto before_2;
        }

    }
    else if (choice == 3)
    {
        system("cls");
        std::cout << "Goodbye, see you next time!\n\n";
        exit(0);
    }
    else
    {
        std::cout << "Choose 1,2 or 3\n";
        Sleep(350);
        system("cls");
        goto before;
    }
}

// ** COLOR?? ** // 
void Ships::changecolor(int c)
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hOut, c);
}

// ** CLEARING ** // 
void Ships::clear(std::string tab[11][11])
{

    for (int i = 0; i < 11; i++)
    {
        for (int j = 0; j < 11; j++)
        {
            tab[i][j] = 32;
        }

    }
}


// ** DRAWING ** // 
void Ships::draw(std::string tab[11][11])
{
    for (int i = 1; i < 11; i++)
    {
        tab[i][0] = 48 + i;
        if (i == 10) tab[10][0] = "10";
    }

    for (int i = 1; i < 11; i++)
    {
        tab[0][i] = 64 + i;
    }
    std::cout << "\n";
    for (int i = 0; i < 11; i++)
    {
        for (int j = 0; j < 11; j++)
        {
            if (i == 0)
            {
                if (j == 1)
                {
                    std::cout << "  " << tab[i][j] << "       ";
                }
                else
                {
                    if (j == 10) std::cout << tab[i][j] << "    ";
                    else std::cout << tab[i][j] << "       ";

                }

            }
            else if (i > 0 && j == 0)
            {
                if (i == 10 && j == 0)
                {

                    std::cout << " " << tab[i][j] << "   ";

                }
                else
                {
                    std::cout << "  " << tab[i][j] << "   ";
                }
            }
            else if (i > 0 && j > 0)
            {
                //changecolor(112);
                std::cout << "|  ";
                std::cout << " ";
                if (tab[i][j] == "O" || tab[i][j] == "S")
                {
                    changecolor(12);
                    std::cout << tab[i][j];
                    changecolor(7);
                }
                else if (tab[i][j] == "!")
                {
                    changecolor(9);
                    std::cout << tab[i][j];
                    changecolor(7);
                }
                else if (tab[i][j] == "X")
                {
                    changecolor(14);
                    std::cout << tab[i][j];
                    changecolor(7);
                }
                else std::cout << tab[i][j];
                

                std::cout << "   ";
            }




            if (j == 10 && i > 0)
            {
                std::cout << "|";
            }
        }
        //changecolor(7);
        std::cout << "\n      ";
        //changecolor(112);
        std::cout << "---------------------------------------------------------------------------------\n";
        //changecolor(7); 
    }
}

// ** RULES ** //
void Ships::out_rules()
{
    std::fstream file;
    int line_nb = 1;
    std::string line;
    file.open("rules.txt", std::ios::in);
    if (file.good() == false)
    {
        std::cout << "Could not open the file";
        exit(0);
    }
    while (getline(file, line))
    {
        std::cout << line << "\n";
        line_nb++;
    }
    file.close();
}

// ** CHECKING ** //
void Ships::check_4(std::string tab[11][11], int x[4], int y[4])
{
    system("cls");
    for (int i = 0; i < 4; i++)
    {
        if (tab[y[i]][(x[i]) + 1] == " ") tab[y[i]][(x[i]) + 1] = "*";
        if (tab[y[i]][(x[i]) - 1] == " ") tab[y[i]][(x[i]) - 1] = "*";
        if (tab[(y[i]) + 1][x[i]] == " ") tab[(y[i]) + 1][x[i]] = "*";
        if (tab[(y[i]) - 1][x[i]] == " ") tab[(y[i]) - 1][x[i]] = "*";
        if (tab[(y[i]) + 1][(x[i]) + 1] == " ") tab[(y[i]) + 1][(x[i]) + 1] = "*";
        if (tab[(y[i]) - 1][(x[i]) - 1] == " ") tab[(y[i]) - 1][(x[i]) - 1] = "*";
        if (tab[(y[i]) - 1][(x[i]) + 1] == " ") tab[(y[i]) - 1][(x[i]) + 1] = "*";
        if (tab[(y[i]) + 1][(x[i]) - 1] == " ") tab[(y[i]) + 1][(x[i]) - 1] = "*";
    }
}
void Ships::check_3(std::string tab[11][11], int x[3], int y[3])
{
    system("cls");
    for (int i = 0; i < 3; i++)
    {
        if (tab[y[i]][(x[i]) + 1] == " ") tab[y[i]][(x[i]) + 1] = "*";
        if (tab[y[i]][(x[i]) - 1] == " ") tab[y[i]][(x[i]) - 1] = "*";
        if (tab[(y[i]) + 1][x[i]] == " ") tab[(y[i]) + 1][x[i]] = "*";
        if (tab[(y[i]) - 1][x[i]] == " ") tab[(y[i]) - 1][x[i]] = "*";
        if (tab[(y[i]) + 1][(x[i]) + 1] == " ") tab[(y[i]) + 1][(x[i]) + 1] = "*";
        if (tab[(y[i]) - 1][(x[i]) - 1] == " ") tab[(y[i]) - 1][(x[i]) - 1] = "*";
        if (tab[(y[i]) - 1][(x[i]) + 1] == " ") tab[(y[i]) - 1][(x[i]) + 1] = "*";
        if (tab[(y[i]) + 1][(x[i]) - 1] == " ") tab[(y[i]) + 1][(x[i]) - 1] = "*";
    }


}
void Ships::check_2(std::string tab[11][11], int x[2], int y[2])
{
    system("cls");
    for (int i = 0; i < 2; i++)
    {
        if (tab[y[i]][(x[i]) + 1] == " ") tab[y[i]][(x[i]) + 1] = "*";
        if (tab[y[i]][(x[i]) - 1] == " ") tab[y[i]][(x[i]) - 1] = "*";
        if (tab[(y[i]) + 1][x[i]] == " ") tab[(y[i]) + 1][x[i]] = "*";
        if (tab[(y[i]) - 1][x[i]] == " ") tab[(y[i]) - 1][x[i]] = "*";
        if (tab[(y[i]) + 1][(x[i]) + 1] == " ") tab[(y[i]) + 1][(x[i]) + 1] = "*";
        if (tab[(y[i]) - 1][(x[i]) - 1] == " ") tab[(y[i]) - 1][(x[i]) - 1] = "*";
        if (tab[(y[i]) - 1][(x[i]) + 1] == " ") tab[(y[i]) - 1][(x[i]) + 1] = "*";
        if (tab[(y[i]) + 1][(x[i]) - 1] == " ") tab[(y[i]) + 1][(x[i]) - 1] = "*";
    }


}
void Ships::check_1(std::string tab[11][11], int x[1], int y[1])
{
    system("cls");
    int i = 0;
    if (tab[y[i]][(x[i]) + 1] == " ") tab[y[i]][(x[i]) + 1] = "*";
    if (tab[y[i]][(x[i]) - 1] == " ") tab[y[i]][(x[i]) - 1] = "*";
    if (tab[(y[i]) + 1][x[i]] == " ") tab[(y[i]) + 1][x[i]] = "*";
    if (tab[(y[i]) - 1][x[i]] == " ") tab[(y[i]) - 1][x[i]] = "*";
    if (tab[(y[i]) + 1][(x[i]) + 1] == " ") tab[(y[i]) + 1][(x[i]) + 1] = "*";
    if (tab[(y[i]) - 1][(x[i]) - 1] == " ") tab[(y[i]) - 1][(x[i]) - 1] = "*";
    if (tab[(y[i]) - 1][(x[i]) + 1] == " ") tab[(y[i]) - 1][(x[i]) + 1] = "*";
    if (tab[(y[i]) + 1][(x[i]) - 1] == " ") tab[(y[i]) + 1][(x[i]) - 1] = "*";



}

// ** CHOOSING ** //
void Ships::choose_4(std::string tab[11][11])
{
    clear(tab);
    draw(tab);
    std::string j[4];
    int x[4] = { 0,0,0,0 };
    int y[4] = { 0,0,0,0 };

    for (int t = 0; t < 4; t++)
    {
    before:
        std::cout << "\nCoordinates(A 5): ";
        std::cin >> j[t] >> y[t];

        if (j[t] == "A" || j[t] == "a") x[t] = 1;
        else if (j[t] == "B" || j[t] == "b") x[t] = 2;
        else if (j[t] == "C" || j[t] == "c") x[t] = 3;
        else if (j[t] == "D" || j[t] == "d") x[t] = 4;
        else if (j[t] == "E" || j[t] == "e") x[t] = 5;
        else if (j[t] == "F" || j[t] == "f") x[t] = 6;
        else if (j[t] == "G" || j[t] == "g") x[t] = 7;
        else if (j[t] == "H" || j[t] == "h") x[t] = 8;
        else if (j[t] == "I" || j[t] == "i") x[t] = 9;
        else if (j[t] == "J" || j[t] == "j") x[t] = 10;
        if (x[t] < 1 || x[t] >10 || y[t] > 10 || y[t] < 1)
        {
            x[t] = 0;
            y[t] = 0;
            system("cls");
            draw(tab);
            std::cout << "\nOut of range, try again\n";
            goto before;
        }
        if (tab[y[t]][x[t]] == "X") {
            system("cls");
            draw(tab);
            std::cout << "Wrong coordinates, try again\n";
            goto before;
        }


        tab[y[t]][x[t]] = "X";

        system("cls");
        draw(tab);
    }

    check_4(tab, x, y);
    draw(tab);
    for (int i = 0; i < 4; i++)
    {
        x_4[i] = x[i];
        y_4[i] = y[i];
    }

}
void Ships::choose_3(std::string tab[11][11])
{
    std::string j[3];
    int x[3] = { 0,0,0 };
    int y[3] = { 0,0,0 };
    int st_x[3];
    int st_y[3];

    int nd_x[3];
    int nd_y[3];

    int temp = 1;

    for (int l = 0; l < 2; l++)
    {
        std::cout << "\nChoose ";
        if (l == 0) std::cout << "the first ship\n";
        else if (l == 1) std::cout << "the second ship\n";
        for (int t = 0; t < 3; t++)
        {
        before:
            std::cout << "Coordinates(A 5): ";
            std::cin >> j[t] >> y[t];

            if (j[t] == "A" || j[t] == "a") x[t] = 1;
            else if (j[t] == "B" || j[t] == "b") x[t] = 2;
            else if (j[t] == "C" || j[t] == "c") x[t] = 3;
            else if (j[t] == "D" || j[t] == "d") x[t] = 4;
            else if (j[t] == "E" || j[t] == "e") x[t] = 5;
            else if (j[t] == "F" || j[t] == "f") x[t] = 6;
            else if (j[t] == "G" || j[t] == "g") x[t] = 7;
            else if (j[t] == "H" || j[t] == "h") x[t] = 8;
            else if (j[t] == "I" || j[t] == "i") x[t] = 9;
            else if (j[t] == "J" || j[t] == "j") x[t] = 10;
            if (x[t] < 1 || x[t] >10 || y[t] > 10 || y[t] < 1)
            {
                x[t] = 0;
                y[t] = 0;
                system("cls");
                draw(tab);
                std::cout << "\nOut of range, try again\n";
                goto before;
            }
            if (tab[y[t]][x[t]] == "X" || tab[y[t]][x[t]] == "*") {
                system("cls");
                draw(tab);
                std::cout << "Wrong coordinates, try again\n";
                goto before;
            }

            if (temp == 1)
            {
                st_x[t] = x[t];
                st_y[t] = y[t];
            }
            else if (temp == 2)
            {
                nd_x[t] = x[t];
                nd_y[t] = y[t];
            }

            tab[y[t]][x[t]] = "X";
            system("cls");
            draw(tab);


        }
        temp++;

        if (l == 0) check_3(tab, st_x, st_y);
        else if (l == 1) check_3(tab, nd_x, nd_y);
        draw(tab);

    }
    for (int i = 0; i < 3; i++)
    {
        st_x_3[i] = st_x[i];
        st_y_3[i] = st_y[i];
        nd_x_3[i] = nd_x[i];
        nd_y_3[i] = nd_y[i];
    }
}
void Ships::choose_2(std::string tab[11][11])
{
    std::string j[2];
    int x[2] = { 0,0 };
    int y[2];

    int st_x[2];
    int st_y[2];

    int nd_x[2];
    int nd_y[2];

    int rd_x[2];
    int rd_y[2];

    int temp = 1;

    for (int l = 0; l < 3; l++)
    {
        std::cout << "\nChoose ";
        if (l == 0) std::cout << "the first ship\n";
        else if (l == 1) std::cout << "the second ship\n";
        else if (l == 2) std::cout << "the third ship\n";

        for (int t = 0; t < 2; t++)
        {
        before:
            std::cout << "Coordinates(A 5): ";
            std::cin >> j[t] >> y[t];

            if (j[t] == "A" || j[t] == "a") x[t] = 1;
            else if (j[t] == "B" || j[t] == "b") x[t] = 2;
            else if (j[t] == "C" || j[t] == "c") x[t] = 3;
            else if (j[t] == "D" || j[t] == "d") x[t] = 4;
            else if (j[t] == "E" || j[t] == "e") x[t] = 5;
            else if (j[t] == "F" || j[t] == "f") x[t] = 6;
            else if (j[t] == "G" || j[t] == "g") x[t] = 7;
            else if (j[t] == "H" || j[t] == "h") x[t] = 8;
            else if (j[t] == "I" || j[t] == "i") x[t] = 9;
            else if (j[t] == "J" || j[t] == "j") x[t] = 10;
            if (x[t] < 1 || x[t] >10 || y[t] > 10 || y[t] < 1)
            {
                x[t] = 0;
                y[t] = 0;
                system("cls");
                draw(tab);
                std::cout << "\nOut of range, try again\n";
                goto before;
            }
            if (tab[y[t]][x[t]] == "X" || tab[y[t]][x[t]] == "*") {
                system("cls");
                draw(tab);
                std::cout << "Wrong coordinates, try again\n";
                goto before;
            }
            if (temp == 1)
            {
                st_x[t] = x[t];
                st_y[t] = y[t];
            }
            else if (temp == 2)
            {
                nd_x[t] = x[t];
                nd_y[t] = y[t];
            }
            else if (temp == 3)
            {
                rd_x[t] = x[t];
                rd_y[t] = y[t];
            }

            tab[y[t]][x[t]] = "X";
            system("cls");
            draw(tab);

        }

        temp++;
        if (l == 0) check_2(tab, st_x, st_y);
        else if (l == 1) check_2(tab, nd_x, nd_y);
        else if (l == 2) check_2(tab, rd_x, rd_y);
        draw(tab);

    }
    for (int i = 0; i < 2; i++)
    {
        st_x_2[i] = st_x[i];
        st_y_2[i] = st_y[i];
        nd_x_2[i] = nd_x[i];
        nd_y_2[i] = nd_y[i];
        rd_x_2[i] = rd_x[i];
        rd_y_2[i] = rd_y[i];
    }
}
void Ships::choose_1(std::string tab[11][11])
{
    std::string j[1];
    int x[1] = { 0 };
    int y[1] = { 0 };

    int st_x[1];
    int st_y[1];

    int nd_x[1];
    int nd_y[1];

    int rd_x[1];
    int rd_y[1];

    int th_x[1];
    int th_y[1];

    int temp = 1;

    for (int l = 0; l < 4; l++)
    {
        std::cout << "\nChoose ";
        if (l == 0) std::cout << "the first ship\n";
        if (l == 1) std::cout << "the second ship\n";
        if (l == 2) std::cout << "the third ship\n";
        if (l == 3) std::cout << "the 4th ship\n";

        for (int t = 0; t < 1; t++)
        {
        before:
            std::cout << "Coordinates(A 5): ";
            std::cin >> j[t] >> y[t];

            if (j[t] == "A" || j[t] == "a") x[t] = 1;
            else if (j[t] == "B" || j[t] == "b") x[t] = 2;
            else if (j[t] == "C" || j[t] == "c") x[t] = 3;
            else if (j[t] == "D" || j[t] == "d") x[t] = 4;
            else if (j[t] == "E" || j[t] == "e") x[t] = 5;
            else if (j[t] == "F" || j[t] == "f") x[t] = 6;
            else if (j[t] == "G" || j[t] == "g") x[t] = 7;
            else if (j[t] == "H" || j[t] == "h") x[t] = 8;
            else if (j[t] == "I" || j[t] == "i") x[t] = 9;
            else if (j[t] == "J" || j[t] == "j") x[t] = 10;
            if (x[t] < 1 || x[t] >10 || y[t] > 10 || y[t] < 1)
            {
                x[t] = 0;
                y[t] = 0;
                system("cls");
                draw(tab);
                std::cout << "\nOut of range, try again\n";
                goto before;
            }
            if (tab[y[t]][x[t]] == "X" || tab[y[t]][x[t]] == "*") {
                system("cls");
                draw(tab);
                std::cout << "Wrong coordinates, try again\n";
                goto before;
            }
            if (temp == 1)
            {
                st_x[t] = x[t];
                st_y[t] = y[t];
            }
            else if (temp == 2)
            {
                nd_x[t] = x[t];
                nd_y[t] = y[t];
            }
            else if (temp == 3)
            {
                rd_x[t] = x[t];
                rd_y[t] = y[t];
            }
            else if (temp == 4)
            {
                th_x[t] = x[t];
                th_y[t] = y[t];
            }

            tab[y[t]][x[t]] = "X";
            system("cls");
            draw(tab);
        }

        temp++;
        if (l == 0) check_1(tab, st_x, st_y);
        else if (l == 1) check_1(tab, nd_x, nd_y);
        else if (l == 2) check_1(tab, rd_x, rd_y);
        else if (l == 3) check_1(tab, th_x, th_y);
        draw(tab);

    }
    for (int i = 0; i < 1; i++)
    {
        st_x_1[i] = st_x[i];
        st_y_1[i] = st_y[i];
        nd_x_1[i] = nd_x[i];
        nd_y_1[i] = nd_y[i];
        rd_x_1[i] = rd_x[i];
        rd_y_1[i] = rd_y[i];
        th_x_1[i] = th_x[i];
        th_y_1[i] = th_y[i];
    }
}
void Ships::choose_ship_pos(std::string tab[11][11])
{
    std::cout << "\nChoose the ship with 4 elements\n\n";
    choose_4(tab);

    std::cout << "\nChoose the ship with 3 elements\n\n";
    choose_3(tab);

    std::cout << "\nChoose the ship with 2 elements\n\n";
    choose_2(tab);

    std::cout << "\nChoose the ship with 1 element\n\n";
    choose_1(tab);



}

// ** BOT GENERATOR ** //
void Ships::generate_bot4(std::string tab[11][11])
{
    srand(time(0));
    clear(tab);
    int x[4] = { 0, 0, 0, 0 };
    int y[4] = { 0, 0, 0, 0 };
    int helpme = 0;
    int helpme_1 = 0;
    int placement = 0;
    placement = rand() % 2 + 1;
    //placement == 1 vertically pionowo
    //placement == 2 horizontally poziomo
    for (int t = 0; t < 4; t++)
    {
        if (placement == 1)
        {
            switch (t)
            {
            case 0:
                x[t] = rand() % 10 + 1;
                y[t] = rand() % 10 + 1;
                tab[y[t]][x[t]] = "X";
                if (y[0] == 10)
                {
                    tab[(y[t]) - 1][x[t]] = "X";
                    y[1] = ((y[t]) - 1);
                    x[1] = x[t];
                    tab[(y[t]) - 2][x[t]] = "X";
                    y[2] = ((y[t]) - 2);
                    x[2] = x[t];
                    tab[(y[t]) - 3][x[t]] = "X";
                    y[3] = ((y[t]) - 3);
                    x[3] = x[t];
                    goto after;
                }
                else if (y[0] == 1)
                {
                    tab[(y[t]) + 1][x[t]] = "X";
                    y[1] = ((y[t]) + 1);
                    x[1] = x[t];
                    tab[(y[t]) + 2][x[t]] = "X";
                    y[2] = ((y[t]) + 2);
                    x[2] = x[t];
                    tab[(y[t]) + 3][x[t]] = "X";
                    y[3] = ((y[t]) + 3);
                    x[3] = x[t];
                    goto after;
                }
                break;

            case 1:
            back:
                x[t] = x[0];
                y[t] = y[0];
                helpme = rand() % 2 + 1;
                if (helpme == 1)//up
                {
                    if (tab[(y[t]) - 1][x[t]] != "X" && ((y[t]) - 1) > 0 && ((y[t]) - 1) < 11 && x[t] > 0 && x[t] < 11)
                    {
                        tab[(y[t]) - 1][x[t]] = "X";
                        y[t] = ((y[t]) - 1);
                    }
                    else goto back;
                }
                else if (helpme == 2)//down
                {
                    if (tab[(y[t]) + 1][x[t]] != "X" && ((y[t]) + 1) > 0 && ((y[t]) + 1) < 11 && x[t] > 0 && x[t] < 11)
                    {
                        tab[(y[t]) + 1][x[t]] = "X";
                        y[t] = ((y[t]) + 1);
                    }
                    else goto back;

                }
                break;
            case 2:
            back_1:
                helpme = rand() % 2 + 1;
                helpme_1 = rand() % 2 + 1;
                if (helpme_1 == 1)
                {
                    x[t] = x[1];
                    y[t] = y[1];
                    if (helpme == 1)//up
                    {
                        if (tab[(y[t]) - 1][x[t]] != "X" && ((y[t]) - 1) > 0 && ((y[t]) - 1) < 11 && x[t] > 0 && x[t] < 11)
                        {
                            tab[(y[t]) - 1][x[t]] = "X";
                            y[t] = ((y[t]) - 1);
                        }
                        else goto back_1;
                    }
                    else if (helpme == 2)//down
                    {
                        if (tab[(y[t]) + 1][x[t]] != "X" && ((y[t]) + 1) > 0 && ((y[t]) + 1) < 11 && x[t] > 0 && x[t] < 11)
                        {
                            tab[(y[t]) + 1][x[t]] = "X";
                            y[t] = ((y[t]) + 1);
                        }
                        else goto back_1;

                    }
                }
                else
                {
                    x[t] = x[0];
                    y[t] = y[0];
                    if (helpme == 1)//up
                    {
                        if (tab[(y[t]) - 1][x[t]] != "X" && ((y[t]) - 1) > 0 && ((y[t]) - 1) < 11 && x[t] > 0 && x[t] < 11)
                        {
                            tab[(y[t]) - 1][x[t]] = "X";
                            y[t] = ((y[t]) - 1);
                        }
                        else goto back_1;
                    }
                    else if (helpme == 2)//down
                    {
                        if (tab[(y[t]) + 1][x[t]] != "X" && ((y[t]) + 1) > 0 && ((y[t]) + 1) < 11 && x[t] > 0 && x[t] < 11)
                        {
                            tab[(y[t]) + 1][x[t]] = "X";
                            y[t] = ((y[t]) + 1);
                        }
                        else goto back_1;

                    }
                }
                break;

            case 3:
            back_2:
                helpme = rand() % 2 + 1;
                helpme_1 = rand() % 3 + 1;

                if (helpme_1 == 1)
                {
                    x[t] = x[1];
                    y[t] = y[1];
                    if (helpme == 1)//up
                    {
                        if ((tab[(y[t]) - 1][x[t]]) != "X" && ((y[t]) - 1) > 0 && ((y[t]) - 1) < 11 && x[t] > 0 && x[t] < 11)
                        {
                            tab[(y[t]) - 1][x[t]] = "X";
                            y[t] = ((y[t]) - 1);
                        }
                        else goto back_2;
                    }
                    else if (helpme == 2)//down
                    {
                        if ((tab[(y[t]) + 1][x[t]]) != "X" && ((y[t]) + 1) > 0 && ((y[t]) + 1) < 11 && x[t] > 0 && x[t] < 11)
                        {
                            tab[(y[t]) + 1][x[t]] = "X";
                            y[t] = ((y[t]) + 1);
                        }
                        else goto back_2;
                    }
                }
                else if (helpme_1 == 2)
                {
                    x[t] = x[2];
                    y[t] = y[2];
                    if (helpme == 1)//up
                    {
                        if ((tab[(y[t]) - 1][x[t]]) != "X" && ((y[t]) - 1) > 0 && ((y[t]) - 1) < 11 && x[t] > 0 && x[t] < 11)
                        {
                            tab[(y[t]) - 1][x[t]] = "X";
                            y[t] = ((y[t]) - 1);
                        }
                        else goto back_2;
                    }
                    else if (helpme == 2)//down
                    {
                        if ((tab[(y[t]) + 1][x[t]]) != "X" && ((y[t]) + 1) > 0 && ((y[t]) + 1) < 11 && x[t] > 0 && x[t] < 11)
                        {
                            tab[(y[t]) + 1][x[t]] = "X";
                            y[t] = ((y[t]) + 1);
                        }
                        else goto back_2;
                    }
                }
                else if (helpme_1 == 3)
                {
                    x[t] = x[0];
                    y[t] = y[0];
                    if (helpme == 1)//up
                    {
                        if ((tab[(y[t]) - 1][x[t]]) != "X" && ((y[t]) - 1) > 0 && ((y[t]) - 1) < 11 && x[t] > 0 && x[t] < 11)
                        {
                            tab[(y[t]) - 1][x[t]] = "X";
                            y[t] = ((y[t]) - 1);
                        }
                        else goto back_2;
                    }
                    else if (helpme == 2)//down
                    {
                        if ((tab[(y[t]) + 1][x[t]]) != "X" && ((y[t]) + 1) > 0 && ((y[t]) + 1) < 11 && x[t] > 0 && x[t] < 11)
                        {
                            tab[(y[t]) + 1][x[t]] = "X";
                            y[t] = ((y[t]) + 1);
                        }
                        else goto back_2;


                    }
                }
                break;
            }

        }
        else if (placement == 2)
        {
            switch (t)
            {
            case 0:
                x[t] = rand() % 10 + 1;
                y[t] = rand() % 10 + 1;
                tab[y[t]][x[t]] = "X";
                if (x[0] == 10)
                {
                    tab[y[t]][(x[t]) - 1] = "X";
                    x[1] = ((x[t]) - 1);
                    y[1] = y[t];
                    tab[y[t]][(x[t]) - 2] = "X";
                    x[2] = ((x[t]) - 2);
                    y[2] = y[t];
                    tab[y[t]][(x[t]) - 3] = "X";
                    x[3] = ((x[t]) - 3);
                    y[3] = y[t];
                    goto after;
                }
                else if (x[0] == 1)
                {
                    tab[y[t]][(x[t]) + 1] = "X";
                    x[1] = ((x[t]) + 1);
                    y[1] = y[t];
                    tab[y[t]][(x[t]) + 2] = "X";
                    x[2] = ((x[t]) + 2);
                    y[2] = y[t];
                    tab[y[t]][(x[t]) + 3] = "X";
                    x[3] = ((x[t]) + 3);
                    y[3] = y[t];
                    goto after;
                }
                break;

            case 1:
            back_3:
                x[t] = x[0];
                y[t] = y[0];
                helpme = rand() % 2 + 1;
                if (helpme == 1)//right
                {
                    if (tab[y[t]][(x[t]) + 1] != "X" && y[t] > 0 && y[t] < 11 && ((x[t]) + 1) > 0 && ((x[t]) + 1) < 11)
                    {
                        tab[y[t]][(x[t]) + 1] = "X";
                        x[t] = ((x[t]) + 1);
                    }
                    else goto back_3;
                }
                else if (helpme == 2)//left
                {
                    if (tab[y[t]][(x[t]) - 1] != "X" && y[t] > 0 && y[t] < 11 && ((x[t]) - 1) > 0 && ((x[t]) - 1) < 11)
                    {
                        tab[y[t]][(x[t]) - 1] = "X";
                        x[t] = ((x[t]) - 1);
                    }
                    else goto back_3;

                }
                break;
            case 2:
            back_4:
                helpme = rand() % 2 + 1;
                helpme_1 = rand() % 2 + 1;
                if (helpme_1 == 1)
                {
                    x[t] = x[1];
                    y[t] = y[1];
                    if (helpme == 1)//right
                    {
                        if (tab[y[t]][(x[t]) + 1] != "X" && y[t] > 0 && y[t] < 11 && ((x[t]) + 1) > 0 && ((x[t]) + 1) < 11)
                        {
                            tab[y[t]][(x[t]) + 1] = "X";
                            x[t] = ((x[t]) + 1);
                        }
                        else goto back_4;
                    }
                    else if (helpme == 2)//left
                    {
                        if (tab[y[t]][(x[t]) - 1] != "X" && y[t] > 0 && y[t] < 11 && ((x[t]) - 1) > 0 && ((x[t]) - 1) < 11)
                        {
                            tab[y[t]][(x[t]) - 1] = "X";
                            x[t] = ((x[t]) - 1);
                        }
                        else goto back_4;

                    }
                }
                else
                {
                    x[t] = x[0];
                    y[t] = y[0];
                    if (helpme == 1)//right
                    {
                        if (tab[y[t]][(x[t]) + 1] != "X" && y[t] > 0 && y[t] < 11 && ((x[t]) + 1) > 0 && ((x[t]) + 1) < 11)
                        {
                            tab[y[t]][(x[t]) + 1] = "X";
                            x[t] = ((x[t]) + 1);
                        }
                        else goto back_4;
                    }
                    else if (helpme == 2)//left
                    {
                        if (tab[y[t]][(x[t]) - 1] != "X" && y[t] > 0 && y[t] < 11 && ((x[t]) - 1) > 0 && ((x[t]) - 1) < 11)
                        {
                            tab[y[t]][(x[t]) - 1] = "X";
                            x[t] = ((x[t]) - 1);
                        }
                        else goto back_4;

                    }
                }
                break;

            case 3:
            back_5:
                helpme = rand() % 2 + 1;
                helpme_1 = rand() % 3 + 1;

                if (helpme_1 == 1)
                {
                    x[t] = x[1];
                    y[t] = y[1];
                    if (helpme == 1)//right
                    {
                        if (tab[y[t]][(x[t]) + 1] != "X" && y[t] > 0 && y[t] < 11 && ((x[t]) + 1) > 0 && ((x[t]) + 1) < 11)
                        {
                            tab[y[t]][(x[t]) + 1] = "X";
                            x[t] = ((x[t]) + 1);
                        }
                        else goto back_5;
                    }
                    else if (helpme == 2)//left
                    {
                        if (tab[y[t]][(x[t]) - 1] != "X" && y[t] > 0 && y[t] < 11 && ((x[t]) - 1) > 0 && ((x[t]) - 1) < 11)
                        {
                            tab[y[t]][(x[t]) - 1] = "X";
                            x[t] = ((x[t]) - 1);
                        }
                        else goto back_5;
                    }
                }
                else if (helpme_1 == 2)
                {
                    x[t] = x[2];
                    y[t] = y[2];
                    if (helpme == 1)//right
                    {
                        if (tab[y[t]][(x[t]) + 1] != "X" && y[t] > 0 && y[t] < 11 && ((x[t]) + 1) > 0 && ((x[t]) + 1) < 11)
                        {
                            tab[y[t]][(x[t]) + 1] = "X";
                            x[t] = ((x[t]) + 1);
                        }
                        else goto back_5;
                    }
                    else if (helpme == 2)//left
                    {
                        if (tab[y[t]][(x[t]) - 1] != "X" && y[t] > 0 && y[t] < 11 && ((x[t]) - 1) > 0 && ((x[t]) - 1) < 11)
                        {
                            tab[y[t]][(x[t]) - 1] = "X";
                            x[t] = ((x[t]) - 1);
                        }
                        else goto back_5;
                    }
                }
                else if (helpme_1 == 3)
                {
                    x[t] = x[0];
                    y[t] = y[0];
                    if (helpme == 1)//right
                    {
                        if (tab[y[t]][(x[t]) + 1] != "X" && y[t] > 0 && y[t] < 11 && ((x[t]) + 1) > 0 && ((x[t]) + 1) < 11)
                        {
                            tab[y[t]][(x[t]) + 1] = "X";
                            x[t] = ((x[t]) + 1);
                        }
                        else goto back_5;
                    }
                    else if (helpme == 2)//left
                    {
                        if (tab[y[t]][(x[t]) - 1] != "X" && y[t] > 0 && y[t] < 11 && ((x[t]) - 1) > 0 && ((x[t]) - 1) < 11)
                        {
                            tab[y[t]][(x[t]) - 1] = "X";
                            x[t] = ((x[t]) - 1);
                        }
                        else goto back_5;


                    }
                }
                break;
            }


        }
    }

after:
    check_4(tab, x, y);
    if (choice_p == 2)
    {
        for (int i = 0; i < 4; i++)
        {
            x_4[i] = x[i];
            y_4[i] = y[i];
        }
    }
    else
    {
        for (int i = 0; i < 4; i++)
        {
            bot_x_4[i] = x[i];
            bot_y_4[i] = y[i];
        }
    }

}
void Ships::generate_bot3(std::string tab[11][11])
{
    srand(time(0));
    int x[3] = { 0, 0, 0 };
    int y[3] = { 0, 0, 0 };
    int st_x[3] = { 0, 0, 0 };
    int st_y[3] = { 0, 0, 0 };
    int nd_x[3] = { 0, 0, 0 };
    int nd_y[3] = { 0, 0, 0 };
    int helpme = 0;
    int helpme_1 = 0;
    int placement = 0;
    int count = 0;
    int count_1 = 0;
    int count_2 = 0;
    int count_3 = 0;
    int count_4 = 0;
    placement = rand() % 2 + 1;

    //placement == 1 vertically pionowo
    //placement == 2 horizontally poziomo
    for (int i = 0; i < 2; i++)
    {
        if (i == 1)
        {
            check_3(tab, st_x, st_y);
            placement = rand() % 2 + 1;
            count = 0;
            count_1 = 0;
            count_2 = 0;
            count_3 = 0;
            count_4 = 0;
        }
        for (int t = 0; t < 3; t++)
        {
            if (placement == 1)
            {
                switch (t)
                {
                case 0:
                before:
                    x[t] = rand() % 10 + 1;
                    y[t] = rand() % 10 + 1;
                    if (tab[y[t]][x[t]] == " ")
                    {
                        tab[y[t]][x[t]] = "X";
                    }
                    else goto before;

                    if (y[0] == 10)
                    {
                        if ((tab[(y[t]) - 1][x[t]] == " " && (y[t] - 1) > 0 && (y[t] - 1) < 11 && x[t] > 0 && x[t] < 11) && (tab[(y[t]) - 2][x[t]] == " " && (y[t] - 2) > 0 && (y[t] - 2) < 11 && x[t] > 0 && x[t] < 11))
                        {
                            tab[(y[t]) - 1][x[t]] = "X";
                            y[1] = ((y[t]) - 1);
                            x[1] = x[t];
                            tab[(y[t]) - 2][x[t]] = "X";
                            y[2] = ((y[t]) - 2);
                            x[2] = x[t];

                            if (i == 0)
                            {
                                for (int j = 0; j < 3; j++)
                                {
                                    st_x[j] = x[j];
                                    st_y[j] = y[j];
                                }
                                goto doit;
                            }
                            else
                            {
                                for (int j = 0; j < 3; j++)
                                {
                                    nd_x[j] = x[j];
                                    nd_y[j] = y[j];
                                }
                                goto after;
                            }
                        }
                        else
                        {
                            tab[y[t]][x[t]] = " ";
                            goto before;
                        }

                    }
                    else if (y[0] == 1)
                    {
                        if ((tab[(y[t]) + 1][x[t]] == " " && (y[t] + 1) > 0 && (y[t] + 1) < 11 && x[t] > 0 && x[t] < 11) && (tab[(y[t]) + 2][x[t]] == " " && (y[t] + 2) > 0 && (y[t] - 2) < 11 && x[t] > 0 && x[t] < 11))
                        {
                            tab[(y[t]) + 1][x[t]] = "X";
                            y[1] = ((y[t]) + 1);
                            x[1] = x[t];
                            tab[(y[t]) + 2][x[t]] = "X";
                            y[2] = ((y[t]) + 2);
                            x[2] = x[t];

                            if (i == 0)
                            {
                                for (int j = 0; j < 3; j++)
                                {
                                    st_x[j] = x[j];
                                    st_y[j] = y[j];
                                }
                                goto doit;
                            }
                            else
                            {
                                for (int j = 0; j < 3; j++)
                                {
                                    nd_x[j] = x[j];
                                    nd_y[j] = y[j];
                                }
                                goto after;
                            }
                        }
                        else
                        {
                            tab[y[t]][x[t]] = " ";
                            goto before;
                        }
                    }
                    break;

                case 1:

                    helpme = rand() % 2 + 1;
                back:
                    if (count == 1 && helpme == 1)
                    {
                        helpme = 2;
                    }
                    else if (count == 1 && helpme == 2)
                    {
                        helpme = 1;
                    }
                    else if (count == 2)
                    {
                        tab[y[0]][x[0]] = " ";
                        tab[y[t]][x[t]] = " ";
                        goto before;
                    }
                    x[t] = x[0];
                    y[t] = y[0];

                    if (helpme == 1)//up
                    {
                        if (tab[(y[t]) - 1][x[t]] == " " && ((y[t]) - 1) > 0 && ((y[t]) - 1) < 11 && x[t] > 0 && x[t] < 11)
                        {
                            tab[(y[t]) - 1][x[t]] = "X";
                            y[t] = ((y[t]) - 1);
                        }
                        else
                        {
                            count++;
                            goto back;
                        }
                    }
                    else if (helpme == 2)//down
                    {
                        if (tab[(y[t]) + 1][x[t]] == " " && ((y[t]) + 1) > 0 && ((y[t]) + 1) < 11 && x[t] > 0 && x[t] < 11)
                        {
                            tab[(y[t]) + 1][x[t]] = "X";
                            y[t] = ((y[t]) + 1);
                        }
                        else
                        {
                            count++;
                            goto back;
                        }

                    }
                    break;

                case 2:

                    helpme = rand() % 2 + 1;
                    helpme_1 = rand() % 2 + 1;
                back_1:
                    if (count_1 == 1 && count_2 == 1 && count_3 == 1 && count_4 == 1)
                    {
                        tab[y[0]][x[0]] = " ";
                        tab[y[1]][x[1]] = " ";
                        tab[y[t]][x[t]] = " ";
                        goto before;
                    }
                    if (helpme_1 == 1 && helpme == 1)
                    {
                        helpme_1 = rand() % 2 + 1;
                        if (helpme_1 == 1)
                        {
                            helpme = 2;
                        }
                        else
                        {
                            helpme = rand() % 2 + 1;
                        }
                    }
                    else if (helpme_1 == 1 && helpme == 2)
                    {
                        helpme_1 = rand() % 2 + 1;
                        if (helpme_1 == 1)
                        {
                            helpme = 1;
                        }
                        else
                        {
                            helpme = rand() % 2 + 1;
                        }
                    }
                    else if (helpme_1 == 2 && helpme == 1)
                    {
                        helpme_1 = rand() % 2 + 1;
                        if (helpme_1 == 2)
                        {
                            helpme = 2;
                        }
                        else
                        {
                            helpme = rand() % 2 + 1;
                        }
                    }
                    else if (helpme_1 == 2 && helpme == 2)
                    {
                        helpme_1 = rand() % 2 + 1;
                        if (helpme_1 == 2)
                        {
                            helpme = 1;
                        }
                        else
                        {
                            helpme = rand() % 2 + 1;
                        }
                    }
                    else continue;
                    if (helpme_1 == 1)
                    {
                        x[t] = x[1];
                        y[t] = y[1];
                        if (helpme == 1)//up
                        {
                            if (tab[(y[t]) - 1][x[t]] == " " && ((y[t]) - 1) > 0 && ((y[t]) - 1) < 11 && x[t] > 0 && x[t] < 11)
                            {
                                tab[(y[t]) - 1][x[t]] = "X";
                                y[t] = ((y[t]) - 1);
                            }
                            else
                            {
                                count_1++;
                                goto back_1;
                            }
                        }
                        else if (helpme == 2)//down
                        {
                            if (tab[(y[t]) + 1][x[t]] == " " && ((y[t]) + 1) > 0 && ((y[t]) + 1) < 11 && x[t] > 0 && x[t] < 11)
                            {
                                tab[(y[t]) + 1][x[t]] = "X";
                                y[t] = ((y[t]) + 1);
                            }
                            else
                            {
                                count_2++;
                                goto back_1;
                            }

                        }
                    }
                    else
                    {
                        x[t] = x[0];
                        y[t] = y[0];
                        if (helpme == 1)//up
                        {
                            if (tab[(y[t]) - 1][x[t]] == " " && ((y[t]) - 1) > 0 && ((y[t]) - 1) < 11 && x[t] > 0 && x[t] < 11)
                            {
                                tab[(y[t]) - 1][x[t]] = "X";
                                y[t] = ((y[t]) - 1);
                            }
                            else
                            {
                                count_3++;
                                goto back_1;
                            }
                        }
                        else if (helpme == 2)//down
                        {
                            if (tab[(y[t]) + 1][x[t]] == " " && ((y[t]) + 1) > 0 && ((y[t]) + 1) < 11 && x[t] > 0 && x[t] < 11)
                            {
                                tab[(y[t]) + 1][x[t]] = "X";
                                y[t] = ((y[t]) + 1);
                            }
                            else
                            {
                                count_4++;
                                goto back_1;
                            }

                        }
                    }
                    break;
                }

                if (i == 0)
                {

                    for (int j = 0; j < 3; j++)
                    {
                        st_x[j] = x[j];
                        st_y[j] = y[j];
                    }

                }
                else
                {
                    for (int j = 0; j < 3; j++)
                    {
                        nd_x[j] = x[j];
                        nd_y[j] = y[j];
                    }
                }


            }
            else if (placement == 2)
            {
                switch (t)
                {
                case 0:
                before_1:
                    x[t] = rand() % 10 + 1;
                    y[t] = rand() % 10 + 1;
                    if (tab[y[t]][x[t]] == " ")
                    {
                        tab[y[t]][x[t]] = "X";
                    }
                    else goto before_1;

                    if (x[0] == 10)
                    {
                        if ((tab[y[t]][(x[t]) - 1] == " " && y[t] > 0 && y[t] < 11 && (x[t] - 1) > 0 && (x[t] - 1) < 11) && (tab[y[t]][(x[t]) - 2] == " " && y[t] > 0 && y[t] < 11 && (x[t] - 2) > 0 && (x[t] - 2) < 11))
                        {
                            tab[y[t]][(x[t]) - 1] = "X";
                            y[1] = y[t];
                            x[1] = (x[t] - 1);
                            tab[y[t]][(x[t]) - 2] = "X";
                            y[2] = y[t];
                            x[2] = (x[t] - 2);

                            if (i == 0)
                            {
                                for (int j = 0; j < 3; j++)
                                {
                                    st_x[j] = x[j];
                                    st_y[j] = y[j];
                                }
                                goto doit;
                            }
                            else
                            {
                                for (int j = 0; j < 3; j++)
                                {
                                    nd_x[j] = x[j];
                                    nd_y[j] = y[j];
                                }
                                goto after;
                            }
                        }
                        else
                        {
                            tab[y[t]][x[t]] = " ";
                            goto before_1;
                        }

                    }
                    else if (x[0] == 1)
                    {
                        if ((tab[y[t]][(x[t]) + 1] == " " && y[t] > 0 && y[t] < 11 && (x[t] + 1) > 0 && (x[t] + 1) < 11) && (tab[y[t]][(x[t]) + 2] == " " && y[t] > 0 && y[t] < 11 && (x[t] + 2) > 0 && (x[t] + 2) < 11))
                        {
                            tab[y[t]][(x[t]) + 1] = "X";
                            y[1] = y[t];
                            x[1] = (x[t] + 1);
                            tab[y[t]][(x[t]) + 2] = "X";
                            y[2] = y[t];
                            x[2] = (x[t] + 2);

                            if (i == 0)
                            {
                                for (int j = 0; j < 3; j++)
                                {
                                    st_x[j] = x[j];
                                    st_y[j] = y[j];
                                }
                                goto doit;
                            }
                            else
                            {
                                for (int j = 0; j < 3; j++)
                                {
                                    nd_x[j] = x[j];
                                    nd_y[j] = y[j];
                                }
                                goto after;
                            }
                        }
                        else
                        {
                            tab[y[t]][x[t]] = " ";
                            goto before_1;
                        }
                    }
                    break;

                case 1:
                    helpme = rand() % 2 + 1;
                back_3:


                    if (count == 1 && helpme == 1)
                    {
                        helpme = 2;
                    }
                    else if (count == 1 && helpme == 2)
                    {
                        helpme = 1;
                    }
                    else if (count == 2)
                    {
                        tab[y[0]][x[0]] = " ";
                        tab[y[t]][x[t]] = " ";
                        goto before_1;
                    }
                    x[t] = x[0];
                    y[t] = y[0];

                    if (helpme == 1)//right
                    {
                        if (tab[y[t]][(x[t]) + 1] == " " && y[t] > 0 && y[t] < 11 && ((x[t]) + 1) > 0 && ((x[t]) + 1) < 11)
                        {
                            tab[y[t]][(x[t]) + 1] = "X";
                            x[t] = ((x[t]) + 1);
                        }
                        else
                        {
                            count++;
                            goto back_3;
                        }
                    }
                    else if (helpme == 2)//left
                    {
                        if (tab[y[t]][(x[t]) - 1] == " " && y[t] > 0 && y[t] < 11 && ((x[t]) - 1) > 0 && ((x[t]) - 1) < 11)
                        {
                            tab[y[t]][(x[t]) - 1] = "X";
                            x[t] = ((x[t]) - 1);
                        }
                        else
                        {
                            count++;
                            goto back_3;
                        }

                    }
                    break;
                case 2:
                    helpme = rand() % 2 + 1;
                    helpme_1 = rand() % 2 + 1;
                back_4:
                    if (count_1 == 1 && count_2 == 1 && count_3 == 1 && count_4 == 1)
                    {
                        tab[y[0]][x[0]] = " ";
                        tab[y[1]][x[1]] = " ";
                        tab[y[t]][x[t]] = " ";
                        goto before_1;
                    }
                    if (helpme_1 == 1 && helpme == 1)
                    {
                        helpme_1 = rand() % 2 + 1;
                        if (helpme_1 == 1)
                        {
                            helpme = 2;
                        }
                        else
                        {
                            helpme = rand() % 2 + 1;
                        }
                    }
                    else if (helpme_1 == 1 && helpme == 2)
                    {
                        helpme_1 = rand() % 2 + 1;
                        if (helpme_1 == 1)
                        {
                            helpme = 1;
                        }
                        else
                        {
                            helpme = rand() % 2 + 1;
                        }
                    }
                    else if (helpme_1 == 2 && helpme == 1)
                    {
                        helpme_1 = rand() % 2 + 1;
                        if (helpme_1 == 2)
                        {
                            helpme = 2;
                        }
                        else
                        {
                            helpme = rand() % 2 + 1;
                        }
                    }
                    else if (helpme_1 == 2 && helpme == 2)
                    {
                        helpme_1 = rand() % 2 + 1;
                        if (helpme_1 == 2)
                        {
                            helpme = 1;
                        }
                        else
                        {
                            helpme = rand() % 2 + 1;
                        }
                    }
                    else continue;

                    if (helpme_1 == 1)
                    {
                        x[t] = x[1];
                        y[t] = y[1];
                        if (helpme == 1)//right
                        {
                            if (tab[y[t]][(x[t]) + 1] == " " && y[t] > 0 && y[t] < 11 && ((x[t]) + 1) > 0 && ((x[t]) + 1) < 11)
                            {
                                tab[y[t]][(x[t]) + 1] = "X";
                                x[t] = ((x[t]) + 1);
                            }
                            else
                            {
                                count_1++;
                                goto back_4;
                            }
                        }
                        else if (helpme == 2)//left
                        {
                            if (tab[y[t]][(x[t]) - 1] == " " && y[t] > 0 && y[t] < 11 && ((x[t]) - 1) > 0 && ((x[t]) - 1) < 11)
                            {
                                tab[y[t]][(x[t]) - 1] = "X";
                                x[t] = ((x[t]) - 1);
                            }
                            else
                            {
                                count_2++;
                                goto back_4;
                            }

                        }
                    }
                    else
                    {
                        x[t] = x[0];
                        y[t] = y[0];
                        if (helpme == 1)//right
                        {
                            if (tab[y[t]][(x[t]) + 1] == " " && y[t] > 0 && y[t] < 11 && ((x[t]) + 1) > 0 && ((x[t]) + 1) < 11)
                            {
                                tab[y[t]][(x[t]) + 1] = "X";
                                x[t] = ((x[t]) + 1);
                            }
                            else
                            {
                                count_3++;
                                goto back_4;
                            }
                        }
                        else if (helpme == 2)//left
                        {
                            if (tab[y[t]][(x[t]) - 1] == " " && y[t] > 0 && y[t] < 11 && ((x[t]) - 1) > 0 && ((x[t]) - 1) < 11)
                            {
                                tab[y[t]][(x[t]) - 1] = "X";
                                x[t] = ((x[t]) - 1);
                            }
                            else
                            {
                                count_4++;
                                goto back_4;
                            }

                        }
                    }
                    break;
                }

                if (i == 0)
                {
                    for (int j = 0; j < 3; j++)
                    {
                        st_x[j] = x[j];
                        st_y[j] = y[j];

                    }
                }
                else
                {
                    for (int j = 0; j < 3; j++)
                    {
                        nd_x[j] = x[j];
                        nd_y[j] = y[j];
                    }
                }

            }
        }
    doit:
        int why = 0;
    }
after:
    check_3(tab, nd_x, nd_y);
    if (choice_p == 2)
    {
        for (int i = 0; i < 3; i++)
        {
            st_x_3[i] = st_x[i];
            st_y_3[i] = st_y[i];
            nd_x_3[i] = nd_x[i];
            nd_y_3[i] = nd_y[i];
        }
    }
    else
    {
        for (int i = 0; i < 3; i++)
        {
            bot_st_x_3[i] = st_x[i];
            bot_st_y_3[i] = st_y[i];
            bot_nd_x_3[i] = nd_x[i];
            bot_nd_y_3[i] = nd_y[i];
        }
    }

}
void Ships::generate_bot2(std::string tab[11][11])
{
    srand(time(0));
    int x[2] = { 0, 0 };
    int y[2] = { 0, 0 };
    int st_x[2] = { 0, 0 };
    int st_y[2] = { 0, 0 };
    int nd_x[2] = { 0, 0 };
    int nd_y[2] = { 0, 0 };
    int rd_x[2] = { 0,0 };
    int rd_y[2] = { 0,0 };
    int helpme = 0;
    int helpme_1 = 0;
    int placement = 0;
    int count = 0;
    placement = rand() % 2 + 1;

    for (int i = 0; i < 3; i++)
    {
        if (i == 1 || i == 2)
        {
            if (i == 1)
            {
                check_2(tab, st_x, st_y);
            }
            else if (i == 2)
            {
                check_2(tab, nd_x, nd_y);
            }
            placement = rand() % 2 + 1;
            count = 0;
        }
        for (int t = 0; t < 2; t++)
        {
            if (placement == 1)
            {
                switch (t)
                {
                case 0:
                before:
                    x[t] = rand() % 10 + 1;
                    y[t] = rand() % 10 + 1;
                    if (tab[y[t]][x[t]] == " ")
                    {
                        tab[y[t]][x[t]] = "X";
                    }
                    else goto before;

                    if (y[0] == 10)
                    {
                        if ((tab[(y[t]) - 1][x[t]] == " " && (y[t] - 1) > 0 && (y[t] - 1) < 11 && x[t] > 0 && x[t] < 11))
                        {
                            tab[(y[t]) - 1][x[t]] = "X";
                            y[1] = ((y[t]) - 1);
                            x[1] = x[t];

                            if (i == 0)
                            {
                                for (int j = 0; j < 2; j++)
                                {
                                    st_x[j] = x[j];
                                    st_y[j] = y[j];
                                }
                                goto doit;
                            }
                            else if (i == 1)
                            {
                                for (int j = 0; j < 2; j++)
                                {
                                    nd_x[j] = x[j];
                                    nd_y[j] = y[j];
                                }
                                goto doit;
                            }
                            else
                            {
                                for (int j = 0; j < 2; j++)
                                {
                                    rd_x[j] = x[j];
                                    rd_y[j] = y[j];
                                }
                                goto after;
                            }
                        }
                        else
                        {
                            tab[y[t]][x[t]] = " ";
                            goto before;
                        }

                    }
                    else if (y[0] == 1)
                    {
                        if ((tab[(y[t]) + 1][x[t]] == " " && (y[t] + 1) > 0 && (y[t] + 1) < 11 && x[t] > 0))
                        {
                            tab[(y[t]) + 1][x[t]] = "X";
                            y[1] = ((y[t]) + 1);
                            x[1] = x[t];

                            if (i == 0)
                            {
                                for (int j = 0; j < 2; j++)
                                {
                                    st_x[j] = x[j];
                                    st_y[j] = y[j];
                                }
                                goto doit;
                            }
                            else if (i == 1)
                            {
                                for (int j = 0; j < 2; j++)
                                {
                                    nd_x[j] = x[j];
                                    nd_y[j] = y[j];
                                }
                                goto doit;
                            }
                            else
                            {
                                for (int j = 0; j < 2; j++)
                                {
                                    rd_x[j] = x[j];
                                    rd_y[j] = y[j];
                                }
                                goto after;
                            }
                        }
                        else
                        {
                            tab[y[t]][x[t]] = " ";
                            goto before;
                        }
                    }
                    break;

                case 1:

                    helpme = rand() % 2 + 1;
                back:
                    if (count == 1 && helpme == 1)
                    {
                        helpme = 2;
                    }
                    else if (count == 1 && helpme == 2)
                    {
                        helpme = 1;
                    }
                    else if (count == 2)
                    {
                        tab[y[0]][x[0]] = " ";
                        tab[y[1]][x[1]] = " ";
                        goto before;
                    }
                    x[t] = x[0];
                    y[t] = y[0];

                    if (helpme == 1)//up
                    {
                        if (tab[(y[t]) - 1][x[t]] == " " && ((y[t]) - 1) > 0 && ((y[t]) - 1) < 11 && x[t] > 0 && x[t] < 11)
                        {
                            tab[(y[t]) - 1][x[t]] = "X";
                            y[t] = ((y[t]) - 1);
                        }
                        else
                        {
                            count++;
                            goto back;
                        }
                    }
                    else if (helpme == 2)//down
                    {
                        if (tab[(y[t]) + 1][x[t]] == " " && ((y[t]) + 1) > 0 && ((y[t]) + 1) < 11 && x[t] > 0 && x[t] < 11)
                        {
                            tab[(y[t]) + 1][x[t]] = "X";
                            y[t] = ((y[t]) + 1);
                        }
                        else
                        {
                            count++;
                            goto back;
                        }

                    }
                    break;
                }
                if (i == 0)
                {

                    for (int j = 0; j < 3; j++)
                    {
                        st_x[j] = x[j];
                        st_y[j] = y[j];
                    }

                }
                else if (i == 1)
                {
                    for (int j = 0; j < 3; j++)
                    {
                        nd_x[j] = x[j];
                        nd_y[j] = y[j];
                    }
                }
                else
                {
                    for (int j = 0; j < 3; j++)
                    {
                        rd_x[j] = x[j];
                        rd_y[j] = y[j];
                    }
                }
            }
            else if (placement == 2)
            {
                switch (t)
                {
                case 0:
                before_1:
                    x[t] = rand() % 10 + 1;
                    y[t] = rand() % 10 + 1;
                    if (tab[y[t]][x[t]] == " ")
                    {
                        tab[y[t]][x[t]] = "X";
                    }
                    else goto before_1;

                    if (x[0] == 10)
                    {
                        if ((tab[y[t]][(x[t]) - 1] == " " && y[t] > 0 && y[t] < 11 && (x[t] - 1) > 0))
                        {
                            tab[y[t]][(x[t]) - 1] = "X";
                            y[1] = y[t];
                            x[1] = (x[t] - 1);

                            if (i == 0)
                            {
                                for (int j = 0; j < 2; j++)
                                {
                                    st_x[j] = x[j];
                                    st_y[j] = y[j];
                                }
                                goto doit;
                            }
                            else if (i == 1)
                            {
                                for (int j = 0; j < 2; j++)
                                {
                                    nd_x[j] = x[j];
                                    nd_y[j] = y[j];
                                }
                                goto doit;
                            }
                            else
                            {
                                for (int j = 0; j < 2; j++)
                                {
                                    rd_x[j] = x[j];
                                    rd_y[j] = y[j];
                                }
                                goto after;
                            }
                        }
                        else
                        {
                            tab[y[t]][x[t]] = " ";
                            goto before_1;
                        }

                    }
                    else if (x[0] == 1)
                    {
                        if ((tab[y[t]][(x[t]) + 1] == " " && y[t] > 0 && y[t] < 11 && (x[t] + 1) > 0))
                        {
                            tab[y[t]][(x[t]) + 1] = "X";
                            y[1] = y[t];
                            x[1] = (x[t] + 1);

                            if (i == 0)
                            {
                                for (int j = 0; j < 2; j++)
                                {
                                    st_x[j] = x[j];
                                    st_y[j] = y[j];
                                }
                                goto doit;
                            }
                            else if (i == 1)
                            {
                                for (int j = 0; j < 2; j++)
                                {
                                    nd_x[j] = x[j];
                                    nd_y[j] = y[j];
                                }
                                goto doit;
                            }
                            else
                            {
                                for (int j = 0; j < 2; j++)
                                {
                                    rd_x[j] = x[j];
                                    rd_y[j] = y[j];
                                }
                                goto after;
                            }
                        }
                        else
                        {
                            tab[y[t]][x[t]] = " ";
                            goto before_1;
                        }
                    }
                    break;

                case 1:
                    helpme = rand() % 2 + 1;
                back_3:


                    if (count == 1 && helpme == 1)
                    {
                        helpme = 2;
                    }
                    else if (count == 1 && helpme == 2)
                    {
                        helpme = 1;
                    }
                    else if (count == 2)
                    {
                        tab[y[0]][x[0]] = " ";
                        tab[y[1]][x[1]] = " ";
                        goto before_1;
                    }
                    x[t] = x[0];
                    y[t] = y[0];

                    if (helpme == 1)//right
                    {
                        if ((tab[y[t]][(x[t]) + 1] == " " && y[t] > 0 && y[t] < 11 && ((x[t]) + 1) > 0 && ((x[t]) + 1) < 11))
                        {
                            tab[y[t]][(x[t]) + 1] = "X";
                            x[t] = ((x[t]) + 1);
                        }
                        else
                        {
                            count++;
                            goto back_3;
                        }
                    }
                    else if (helpme == 2)//left
                    {
                        if (tab[y[t]][(x[t]) - 1] == " " && y[t] > 0 && y[t] < 11 && ((x[t]) - 1) > 0 && ((x[t]) - 1) < 11)
                        {
                            tab[y[t]][(x[t]) - 1] = "X";
                            x[t] = ((x[t]) - 1);
                        }
                        else
                        {
                            count++;
                            goto back_3;
                        }

                    }
                    break;
                }
                if (i == 0)
                {

                    for (int j = 0; j < 2; j++)
                    {
                        st_x[j] = x[j];
                        st_y[j] = y[j];
                    }

                }
                else if (i == 1)
                {
                    for (int j = 0; j < 2; j++)
                    {
                        nd_x[j] = x[j];
                        nd_y[j] = y[j];
                    }
                }
                else
                {
                    for (int j = 0; j < 2; j++)
                    {
                        rd_x[j] = x[j];
                        rd_y[j] = y[j];
                    }
                }
            }
        }
    doit:
        int why = 0;
    }
after:
    check_2(tab, rd_x, rd_y);
    if (choice_p == 2)
    {
        for (int i = 0; i < 2; i++)
        {
            st_x_2[i] = st_x[i];
            st_y_2[i] = st_y[i];
            nd_x_2[i] = nd_x[i];
            nd_y_2[i] = nd_y[i];
            rd_x_2[i] = rd_x[i];
            rd_y_2[i] = rd_y[i];
        }
    }
    else
    {
        for (int i = 0; i < 2; i++)
        {
            bot_st_x_2[i] = st_x[i];
            bot_st_y_2[i] = st_y[i];
            bot_nd_x_2[i] = nd_x[i];
            bot_nd_y_2[i] = nd_y[i];
            bot_rd_x_2[i] = rd_x[i];
            bot_rd_y_2[i] = rd_y[i];
        }
    }

}
void Ships::generate_bot1(std::string tab[11][11])
{
    int x[1] = { 0 };
    int y[1] = { 0 };
    int st_x[1] = { 0 };
    int st_y[1] = { 0 };
    int nd_x[1] = { 0 };
    int nd_y[1] = { 0 };
    int rd_x[1] = { 0 };
    int rd_y[1] = { 0 };
    int th_x[1] = { 0 };
    int th_y[1] = { 0 };
    int count = 0;
    int t = 0;
    for (int i = 0; i < 4; i++)
    {
        if (i == 1)
        {
            check_1(tab, st_x, st_y);
        }
        else if (i == 2)
        {
            check_1(tab, nd_x, nd_y);
        }
        else if (i == 3)
        {
            check_1(tab, rd_x, rd_y);
        }

    before:
        x[t] = rand() % 10 + 1;
        y[t] = rand() % 10 + 1;
        if (tab[y[t]][x[t]] == " ")
        {
            tab[y[t]][x[t]] = "X";
        }
        else goto before;
        if (i == 0)
        {
            st_x[0] = x[0];
            st_y[0] = y[0];

        }
        else if (i == 1)
        {
            nd_x[0] = x[0];
            nd_y[0] = y[0];
        }
        else if (i == 2)
        {
            rd_x[0] = x[0];
            rd_y[0] = y[0];
        }
        else
        {
            th_x[0] = x[0];
            th_y[0] = y[0];
        }
    }
    check_1(tab, th_x, th_y);
    if (choice_p == 2)
    {
        for (int i = 0; i < 1; i++)
        {
            st_x_1[i] = st_x[i];
            st_y_1[i] = st_y[i];
            nd_x_1[i] = nd_x[i];
            nd_y_1[i] = nd_y[i];
            rd_x_1[i] = rd_x[i];
            rd_y_1[i] = rd_y[i];
            th_x_1[i] = th_x[i];
            th_y_1[i] = th_y[i];
        }
    }
    else
    {
        for (int i = 0; i < 1; i++)
        {
            bot_st_x_1[i] = st_x[i];
            bot_st_y_1[i] = st_y[i];
            bot_nd_x_1[i] = nd_x[i];
            bot_nd_y_1[i] = nd_y[i];
            bot_rd_x_1[i] = rd_x[i];
            bot_rd_y_1[i] = rd_y[i];
            bot_th_x_1[i] = th_x[i];
            bot_th_y_1[i] = th_y[i];
        }
    }

}
void Ships::generate_the_bot(std::string tab[11][11])
{
    generate_bot4(tab);
    generate_bot3(tab);
    generate_bot2(tab);
    generate_bot1(tab);
}

// ** FIGHT ** // 
void Ships::fight_vs_bot(std::string player_1[11][11], std::string bot[11][11], std::string player_name1)
{

    std::string player_1_empty[11][11];
    std::string bot_empty[11][11];
    std::string player_X_empty[11][11];
    std::string bot_X_empty[11][11];
    clear(player_1_empty);
    clear(bot_empty);
    srand(time(0));


    int x, y;
    int life_bot = 20;
    int life_player_1 = 20;

    Sleep(1000);
    do {
    before:
        std::cout << "Bot's turn:\n";
        Sleep(1500);
        x = rand() % 10 + 1;
        y = rand() % 10 + 1;
        if (bot_empty[y][x] != "X" && bot_empty[y][x] != "S" && bot_empty[y][x] != "*") {

            bot_empty[y][x] = "X";

            if (bot_empty[y][x] == player_1[y][x] && bot_empty[y][x] != "S") {
                bot_empty[y][x] = "S";
                player_1[y][x] = "O"; // zaznaczanie na naszej planszy  celnego strzalu  bota
                bot_X_empty[y][x] = "X";
                std::cout << "Bot hit your ship\n";
                Sleep(800);

                life_player_1--;
                if (life_player_1 <= 0) {
                    std::cout << "GG!\n";
                    std::cout << "Bot won the game\n";
                    Sleep(4000);
                    break;
                }
                if (bot_X_empty[x_4[0]][y_4[0]] == "X" && bot_X_empty[x_4[1]][y_4[1]] == "X" && bot_X_empty[x_4[2]][y_4[2]] == "X" && bot_X_empty[x_4[3]][y_4[3]] == "X")
                {
                    std::cout << "4 elements sunk";
                    bot_X_empty[x_4[0]][y_4[0]] = "Ende";
                    Sleep(800);
                }
                if (bot_X_empty[st_x_3[0]][st_y_3[0]] == "X" && bot_X_empty[st_x_3[1]][st_y_3[1]] == "X" && bot_X_empty[st_x_3[2]][st_y_3[2]] == "X") {
                    std::cout << "3 elements sunk";
                    bot_X_empty[st_x_3[0]][st_y_3[0]] = "Ende";
                    Sleep(800);
                }
                if (bot_X_empty[nd_x_3[0]][nd_y_3[0]] == "X" && bot_X_empty[nd_x_3[1]][nd_y_3[1]] == "X" && bot_X_empty[nd_x_3[2]][nd_y_3[2]] == "X") {
                    std::cout << "3 elements sunk";
                    bot_X_empty[nd_x_3[0]][nd_y_3[0]] = "Ende";
                    Sleep(800);
                }
                if (bot_X_empty[nd_x_2[0]][nd_y_2[0]] == "X" && bot_X_empty[nd_x_2[1]][nd_y_2[1]] == "X") {
                    std::cout << "2 elements sunk";
                    bot_X_empty[nd_x_2[0]][nd_y_2[0]] = "Ende";
                    Sleep(800);
                }
                if (bot_X_empty[st_x_2[0]][st_y_2[0]] == "X" && bot_X_empty[st_x_2[1]][st_y_2[1]] == "X") {
                    std::cout << "2 elements sunk";
                    bot_X_empty[st_x_2[0]][st_y_2[0]] = "Ende";
                    Sleep(800);
                }
                if (bot_X_empty[rd_x_2[0]][rd_y_2[0]] == "X" && bot_X_empty[rd_x_2[1]][rd_y_2[1]] == "X") {
                    std::cout << "2 elements sunk";
                    bot_X_empty[rd_x_2[0]][rd_y_2[0]] = "Ende";
                    Sleep(800);
                }
                if (bot_X_empty[st_x_1[0]][st_y_1[0]] == "X") {
                    std::cout << "1 elements sunk";
                    bot_X_empty[st_x_1[0]][st_y_1[0]] = "Ende";
                    Sleep(800);
                }
                if (bot_X_empty[nd_x_1[0]][nd_y_1[0]] == "X") {
                    std::cout << "1 elements sunk";
                    bot_X_empty[nd_x_1[0]][nd_y_1[0]] = "Ende";
                    Sleep(800);
                }
                if (bot_X_empty[rd_x_1[0]][rd_y_1[0]] == "X") {
                    std::cout << "1 elements sunk";
                    bot_X_empty[rd_x_1[0]][rd_y_1[0]] = "Ende";
                    Sleep(800);
                }
                if (bot_X_empty[th_x_1[0]][th_y_1[0]] == "X") {
                    std::cout << "1 elements sunk";
                    bot_X_empty[th_x_1[0]][th_y_1[0]] = "Ende";
                    Sleep(800);
                }
                goto before;
            }
            else if (bot_empty[y][x] != player_1[y][x]) {
                bot_empty[y][x] = "*";
                std::cout << "Bot missed\n";
                player_1[y][x] = "!";
                Sleep(1000);
            }



        }
        system("cls");

        draw(player_1);
        draw(player_1_empty);

        int y2 = 0;
        int x2 = 0;
        std::string j;
        std::cout << "Your turn:\n";
    Chose1:

        std::cout << "\nEnter the coordinates (A 6):";
        std::cin >> j >> y2;
        if (j == "A" || j == "a") x2 = 1;
        else if (j == "B" || j == "b") x2 = 2;
        else if (j == "C" || j == "c") x2 = 3;
        else if (j == "D" || j == "d") x2 = 4;
        else if (j == "E" || j == "e") x2 = 5;
        else if (j == "F" || j == "f") x2 = 6;
        else if (j == "G" || j == "g") x2 = 7;
        else if (j == "H" || j == "h") x2 = 8;
        else if (j == "I" || j == "i") x2 = 9;
        else if (j == "J" || j == "j") x2 = 10;
        if (x2 < 1 || x2>10 || y2 < 1 || y2>10)
        {
            std::cout << "\nOut of range, try again\n";
            goto Chose1;
        }
        if (player_1_empty[y2][x2] != "*" && player_1_empty[y2][x2] != "S") {
            player_1_empty[y2][x2] = "X";

            if (player_1_empty[y2][x2] == bot[y2][x2])
            {
                player_1_empty[y2][x2] = "S";  //strike
                player_X_empty[y2][x2] = "X";
                std::cout << "Nice shot\n";
                Sleep(2000);
                if (player_X_empty[bot_y_4[0]][bot_x_4[0]] == "X" && player_X_empty[bot_y_4[1]][bot_x_4[1]] == "X" && player_X_empty[bot_y_4[2]][bot_x_4[2]] == "X" && player_X_empty[bot_y_4[3]][bot_x_4[3]] == "X") {
                    std::cout << "4 elements sunk\n";
                    player_X_empty[bot_y_4[0]][bot_x_4[0]] = "Ende"; // aby nie powtarzało wyswietlania
                    Sleep(800);
                    check_4(player_1_empty, bot_x_4, bot_y_4);
                }
                if (player_X_empty[bot_st_y_3[0]][bot_st_x_3[0]] == "X" && player_X_empty[bot_st_y_3[1]][bot_st_x_3[1]] == "X" && player_X_empty[bot_st_y_3[2]][bot_st_x_3[2]] == "X") {
                    std::cout << "3 elements sunk\n";
                    player_X_empty[bot_st_y_3[0]][bot_st_x_3[0]] = "Ende";
                    Sleep(800);
                    check_3(player_1_empty, bot_st_x_3, bot_st_y_3);
                }
                if (player_X_empty[bot_nd_y_3[0]][bot_nd_x_3[0]] == "X" && player_X_empty[bot_nd_y_3[1]][bot_nd_x_3[1]] == "X" && player_X_empty[bot_nd_y_3[2]][bot_nd_x_3[2]] == "X") {
                    std::cout << "3 elements sunk\n";
                    player_X_empty[bot_nd_y_3[0]][bot_nd_x_3[0]] = "Ende";
                    Sleep(800);
                    check_3(player_1_empty, bot_nd_x_3, bot_nd_y_3);
                }
                if (player_X_empty[bot_st_y_2[0]][bot_st_x_2[0]] == "X" && player_X_empty[bot_st_y_2[1]][bot_st_x_2[1]] == "X") {
                    std::cout << "2 elements sunk\n";
                    player_X_empty[bot_st_y_2[0]][bot_st_x_2[0]] = "Ende";
                    Sleep(800);
                    check_2(player_1_empty, bot_st_x_2, bot_st_y_2);
                }
                if (player_X_empty[bot_nd_y_2[0]][bot_nd_x_2[0]] == "X" && player_X_empty[bot_nd_y_2[1]][bot_nd_x_2[1]] == "X") {
                    std::cout << "2 elements sunk\n";
                    player_X_empty[bot_nd_y_2[0]][bot_nd_x_2[0]] = "Ende";
                    Sleep(800);
                    check_2(player_1_empty, bot_nd_x_2, bot_nd_y_2);
                }
                if (player_X_empty[bot_rd_y_2[0]][bot_rd_x_2[0]] == "X" && player_X_empty[bot_rd_y_2[1]][bot_rd_x_2[1]] == "X") {
                    std::cout << "2 elements sunk\n";
                    player_X_empty[bot_rd_y_2[0]][bot_rd_x_2[0]] = "Ende";
                    Sleep(800);
                    check_2(player_1_empty, bot_rd_x_2, bot_rd_y_2);
                }
                if (player_X_empty[bot_st_y_1[0]][bot_st_x_1[0]] == "X") {
                    std::cout << "1 elements sunk\n";
                    player_X_empty[bot_st_y_1[0]][bot_st_x_1[0]] = "Ende";
                    Sleep(800);
                    check_1(player_1_empty, bot_st_x_1, bot_st_y_1);
                }
                if (player_X_empty[bot_nd_y_1[0]][bot_nd_x_1[0]] == "X") {
                    std::cout << "1 elements sunk\n";
                    player_X_empty[bot_nd_y_1[0]][bot_nd_x_1[0]] = "Ende";
                    Sleep(800);
                    check_1(player_1_empty, bot_nd_x_1, bot_nd_y_1);
                }
                if (player_X_empty[bot_rd_y_1[0]][bot_rd_x_1[0]] == "X") {
                    std::cout << "1 elements sunk\n";
                    player_X_empty[bot_rd_y_1[0]][bot_rd_x_1[0]] = "Ende";
                    Sleep(800);
                    check_1(player_1_empty, bot_rd_x_1, bot_rd_y_1);
                }
                if (player_X_empty[bot_th_y_1[0]][bot_th_x_1[0]] == "X") {
                    std::cout << "1 elements sunk\n";
                    player_X_empty[bot_th_y_1[0]][bot_th_x_1[0]] = "Ende";
                    Sleep(800);
                    check_1(player_1_empty, bot_th_x_1, bot_th_y_1);
                }



                life_bot--;
                if (life_bot <= 0) {
                    std::cout << "GG!\n";
                    std::cout << "Won: " << player_name1;
                    Sleep(4000);
                    break;
                }
                system("cls");
                draw(player_1);
                draw(player_1_empty);

                goto Chose1;

            }
            else if (player_1_empty[y2][x2] != bot[y2][x2]) {
                player_1_empty[y2][x2] = "*";

                std::cout << "You missed\n\n";
                Sleep(2000);
                goto before;

            }
        }
        else if (player_1_empty[y2][x2] == "*" || player_1_empty[y2][x2] == "S") {
            std::cout << "Wrong coordinations...\n";
            goto Chose1;
        }

        //system("cls");
    } while (life_player_1 > 0 || life_bot > 0);
}





