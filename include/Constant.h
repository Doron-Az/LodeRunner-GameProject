#pragma once
//Speed------------------------------------
constexpr auto PLAYER_SPEED = 130.f;
constexpr auto ENEMY_SPEED = 100.f;
constexpr auto FALL_SPEED = 200.f;

//Widely Used-------------------------------
const auto  OBJECT_SIZE = 50;
int const EMPTY = 0;
const int RESET = 0;

enum  ObjectType
{
	PlayerChar = '@',
	EnemyChar = '%',
	PresentChar = '+',
	RodChar = '-',
	LadderChar = 'H',
	WallChar = '#',
	CoinChar = '*',
	SpaceChar = ' ',
	EndLineChar = '\n'
};
//Animation---------------------------------
const float FALL_RIGHT_ICON_ROW = 1;
const float FALL_ICON_COL = 8;

//Moving -----------------------------------
const auto FALL_LEFT_ICON_ROW = 0;
int const NUM_OF_DIRECTIONS = 4;
int const SWITCH_TIME = 5;

enum directionType
{
	e_up,
	e_down,
	e_left,
	e_right
};

//Controler---------------------------------
const int MIN_WIDTH_WINDOW = 900;
const int HEIGHT_GAME_OVER = 48;
const int WIDTH_GAME_OVER = 356;
const int NUM_ENEMY_TYPE = 3;
const int SCORE_PER_COIN = 2;
const int PRESENT_BONUS = 20;
const int START_WINDOW = 0;
const int PLAYER_INDEX = 0;
const int FIRST_LEVEL = 1;
const int BONUS_LEVEL = 50;
const int TIME_BONUS = 10;
const int NO_TIME = -1;

enum EnemyType
{
	Regular,
	LeftRight,
	Smart
};

//Player------------------------------------
const int BEGIN_LIFE = 3;
const int END_LIVE = 0;
enum digDierction {
	d_digLeft = 'z',
	d_digRight = 'x'
};
//Board-------------------------------------
const int NUM_PRESENT_TYPE = 4;
const int MIN_COLLISION = 5;

//Images Singleton---------------------------
const int NUM_OF_TEXTURE = 7;

enum vectorIconType {
	i_enemy,
	i_coin,
	i_ladder,
	i_player,
	i_rod,
	i_wall,
	i_present,
	i_over,
	i_explanation,
	i_open,
	i_play,
	i_exit
};

//soundes Singleton-------------------------
const int NUM_OF_SOUNDS = 10;

enum soundType
{
	s_born,
	s_dead,
	s_dig,
	s_down,
	s_fall,
	s_getGold,
	s_pass,
	s_present,
	s_nextLevel,
	s_createEnemy
};
//MainMenu---------------------------------
const int OPEN_WINDOWS_HEIGHT = 761;
const int OPEN_WINDOWS_WIDTH = 1200;
const int OPEN_BUTTON_HEIGHT = 123;
const int OPEN_BUTTON_WIDTH = 300;
const int PLAY_POSITION_X = 600;
const int PLAY_POSITION_Y = 200;
const int EXIT_POSITION_X = 600;
const int EXIT_POSITION_Y = 700;

//Information-------------------------------
const int  MAX_NUM_TEXT = 8;










