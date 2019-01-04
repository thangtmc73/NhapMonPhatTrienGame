#ifndef __OBJECT_CONFIG_H__
#define __OBJECT_CONFIG_H__

// weapon vx vy
#define WEAPON_VX 0.085	
#define WEAPON_VY 0.6

// simon
// Up and down stair
#define SIMON_VX_STAIR 0.085	
#define SIMON_VY_STAIR 0.15

// start
#define SIMON_Y_CROUCHING(y) (y-17)

// normal
#define SIMON_NORMAL_VX 0.055

// jump
#define SIMON_JUMP_VX 0.1
#define SIMON_JUMP_VY 0.3
// trong luc luc nhay
#define SIMON_GRAVITY 0.07

//trong luc luc roi
#define SIMON_FALL 180

//luc bi dinh damaged nhay ve phia sau
#define SIMON_VX_DAMAGED 0.085
#define SIMON_VY_DAMAGED 0.3

#define DISTANCE_SWITCHING_SCENE 100

#define CAMERA_VX 0.07

enum SimonState
{
	RUNNING = 0,
	STAY = 1,
	JUMPING = 2,
	FALLING = 3,
	STANDING_ATTACK_WHIP = 4,
	CROUCHING = 5,
	JUMPING_ATTACK_WHIP = 6,
	CROUCHING_ATTACK_WHIP = 7,
	DAMAGED = 8,
	DEAD = 9,
	STEPPING_UP = 10,
	STEPPING_DOWN = 11,
	STEPPING_UP_ATTACK = 12,
	STEPPING_DOWN_ATTACK = 13,
	TOTAL_SIMON_STATES,
};

enum PantherState
{
	PANTHER_RUNNING = 0,
	SITTING_DOWN = 1,
	PANTHER_JUMPING = 2,
	PANTHER_FALLING = 3,
	TOTAL_PANTHER_STATES,
};

enum WeaponEnum {
	WhipWeapon = 0,
	DaggeBullet = 1,
	HollyWaterBullet = 2,
	AxeBullet = 3
};

enum FishmanState {
	FISHMAN_RUNNING = 0,
	FISHMAN_JUMPING = 1,
	FISHMAN_DOWN = 2,
	TOTAL_FISHMAN_STATES
};


enum eGroupTypeObject {
	DEFAULT = 0,
	STATIC_ITEM = 1,
	DYNAMIC_ITEM = 2,
	ENEMY = 3,
	GROUND = 4,
	WEAPON_MAIN = 5,
	BACKGROUND = 6,
	MAIN = 7,
	WEAPON_ENEMY = 8
};

enum eTypeObject
{
	Default = 0,

	// undefine 
	CharacterSimon = 1,

	//boss
	BossLv1 = 401,
	BossLv2 = 402,
	BossLv3 = 403,

	// Enemy
	EnemeyGhoul = 201,
	EnemyPanther = 202,
	EnemyVampireBat = 203,
	EnemyMedusa = 204,
	EnemyFishMan = 205,
	EnemyAxeMan = 206,
	EnemyDragonSkullCannon = 207,
	EnemySpearKnight = 208,
	EnemyWhiteSkeleton = 209,
	EnemyGhost = 210,
	EnemyBat = 211,

	//ground
	BigCandleWithLargeHeart = 601,
	BigCandleWithUpgradeWhip = 602,
	BigCandleWithDagger = 603,
	LittleCandleWithSmallHeart = 605,
	LittleCandleWithPurpleMoneyBag = 606,
	LittleCandleWithWhiteMoneyBag = 607,
	LittleCandleWithLargeHeart = 608,
	LittleCandleWithHolyWater = 609,
	//LittleCandleWithRedMoneyBag = 607,
	LittleCandleWithHolyCross = 610,
	LittleCandleStopWatch = 613,
	LittleCandleWithGoldPotion = 614,
	LittleCandleWithAxe = 615,
	/*GroundSmallLightAxe = 611,
	GroundSmallLightBoomerang = 612,
	GroundSmallLightCross = 613,
	GroundSmallLightDoubleShot = 614,
	GroundSmallLightFireBomb = 615,
	GroundSmallLightRandom = 616,
	GroundTrident = 654,*/

	//Hiden

	GroundHorizontal = 702,
	Bonuses = 604,
	BlueMoneyBag = 611,
	PorkChop = 612,
	CrystalBall = 616,
	DoubleShot = 617,
	// Other
	Simon = 1001,
	LargeHeart = 618,
	SmallHeart = 619,
	Whip = 620,
	Dagger = 621,
	WhiteMoneyBag = 623,
	RedMoneyBag = 624,
	HolyWater = 625,
	Cross = 626,
	GoldPotion = 627,
	Axe = 628,
	StopWatch = 629,

	HiddenSwitchScene = 650,
	HiddenPassableGate = 651,
	HiddenSpawnFishman = 652,
	HiddenStopCamera = 653,
	HiddenStopSimonAfterGate = 654,
	HiddenBossBatActive = 655,

	BrickNothing = 670,
	BrickBlueMoneyBag = 671,
	BrickPorkChop = 672,
	BrickDoubleShot = 673,

	WeaponWhip = 701,
	WeaponDagger = 702,
	WeaponHolyWater = 703,
	Gate = 801,

	GROUND_1 = 900,
	GROUND_2 = 901,
	GROUND_3 = 903,
	STAIR_1 = 904,
	STAIR_2 = 905,

};

enum WhipState
{
	NORMAL_WHIP = 0,
	UPGRADE_1 = 1,
	UPGRADE_2 = 2,
	TOTAL_WHIP_STATES = 3,
};

enum eSoundIndex
{
	LEVEL_1 = 0,
	LEVEL_2 = 1,
	GAME_OVER = 2,
	STAGE_CLEAR = 3,
	GAME_START = 4,
	TITLE_THEME = 5,
	LIFE_LOST = 6,
	BOSS_BATTLE_POISON_MIND = 7,
	USING_WHIP = 8,
	COLLECTING_ITEM = 9,
	COLLECTING_WEAPON = 10,
};

const int NUM_FISHMEN_SPAWN = 3;
#endif // ! __OBJECT_CONFIG_H__
