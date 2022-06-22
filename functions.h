#pragma once
#include <iostream>
#include <string>
#include <stdlib.h>
#include <cstdlib>
#include <Windows.h>


class Ships
{
public:

	// ** PLAYER COORDINATES ** //
	int x_4[4];
	int y_4[4];

	int st_x_3[3];
	int st_y_3[3];
	int nd_x_3[3];
	int nd_y_3[3];

	int st_x_2[2];
	int st_y_2[2];
	int nd_x_2[2];
	int nd_y_2[2];
	int rd_x_2[2];
	int rd_y_2[2];

	int st_x_1[1];
	int st_y_1[1];
	int nd_x_1[1];
	int nd_y_1[1];
	int rd_x_1[1];
	int rd_y_1[1];
	int th_x_1[1];
	int th_y_1[1];

	// ** BOT COORDINATES ** //
	int bot_x_4[4];
	int bot_y_4[4];

	int bot_st_x_3[3];
	int bot_st_y_3[3];
	int bot_nd_x_3[3];
	int bot_nd_y_3[3];

	int bot_st_x_2[2];
	int bot_st_y_2[2];
	int bot_nd_x_2[2];
	int bot_nd_y_2[2];
	int bot_rd_x_2[2];
	int bot_rd_y_2[2];

	int bot_st_x_1[1];
	int bot_st_y_1[1];
	int bot_nd_x_1[1];
	int bot_nd_y_1[1];
	int bot_rd_x_1[1];
	int bot_rd_y_1[1];
	int bot_th_x_1[1];
	int bot_th_y_1[1];

	int choice = 0;
	int choice_p = 0;
	

	// ** CONSTRUCTOR ** //
	Ships();

	// ** MENU ** // 
	void game();

	// ** COLOR?? ** // 
	void changecolor(int c);

	// ** CLEARING ** //
	void clear(std::string tab[11][11]);

	// ** DRAWING ** // 
	void draw(std::string tab[11][11]);

	// ** RULES ** //
	void out_rules();
	
	// ** CHECKING ** // 
	void check_4(std::string tab[11][11], int x[4], int y[4]);
	void check_3(std::string tab[11][11], int x[3], int y[3]);
	void check_2(std::string tab[11][11], int x[2], int y[2]);
	void check_1(std::string tab[11][11], int x[1], int y[1]);

	// ** CHOOSING ** //
	void choose_4(std::string tab[11][11]);
	void choose_3(std::string tab[11][11]);
	void choose_2(std::string tab[11][11]);
	void choose_1(std::string tab[11][11]);
	void choose_ship_pos(std::string tab[11][11]);

	// ** BOT GENERATOR ** //
	void generate_bot4(std::string tab[11][11]);
	void generate_bot3(std::string tab[11][11]);
	void generate_bot2(std::string tab[11][11]);
	void generate_bot1(std::string tab[11][11]);
	void generate_the_bot(std::string tab[11][11]);

	// ** FIGHT ** // 
	void fight_vs_bot(std::string player_1[11][11], std::string bot[11][11], std::string player_name1);
};



