#ifndef __INFO_MANAGER_H___
#define __INFO_MANAGER_H___

#include <map>
#include "Global.h"
#include "ObjectConfig.h"

class CInfoManager
{
public:
	~CInfoManager();
	static CInfoManager *GetInstance();
	virtual void update(int a_deltaTime);

	void resetSwitchScreen();
	void SetStage(int);
	void ChangeNumberOfHearts(int a_numberOfHearts);
	void ChangeScore(int a_number_score_increase);
	void ChangeP(int a_number_p);
	void ChangePlayerLife(int a_number_life);
	void Reset();
	void setStatusWhip(int a_status);
	int getStatusWhip();
	void SetTime(int a_time);
	void StartClock();
	void StopClock();
	void SwitchScene(bool a_switch = true);
	bool IsSwitchingScene();
	bool shouldOpenGate();
	void setShouldOpenGate(bool should);
	void SetSpecialWeapon(WeaponEnum a_specialWeapon);
	void SetMoveableCameraBeforeGate(bool a_true);
	void SetMoveableCameraAfterGate(bool a_true);
	void SetMovingThroughGate(bool a_true);
	int GetNumberOfHearts();
	int GetScore();
	int GetClockTime();
	int GetStage();
	int GetP();
	int GetPlayerLife();
	int GetEnemyLife();
	WeaponEnum GetCurrentSpeciaWeapon();
	bool IsMoveableCameraBeforeGate();
	bool IsMoveableCameraAfterGate();
	bool IsMovingThroughGate();
	void SetNewPosition(std::string a_key, GPoint2D a_position);
	GPoint2D GetCurrentPosition(std::string a_key);
	void setStopCamera(bool stop);
	bool isStopCamera();
	void activeBoss();
	bool isActiveBoss();
private:
	static CInfoManager *_instance;
	CInfoManager();

	// manage the required position
	std::map<std::string, GPoint2D> _position;

	bool _stopCamera;
	bool _activeBoss;

	// true if switching scene
	bool _switchingScene;

	bool _shouldOpenGate;

	bool _moveableCameraBeforeGate;
	bool _moveableCameraAfterGate;

	bool _movingThroughGate;

	// true if you want the clock run countdown
	bool _enableClock;

	// clock helper
	int _remainningTime;
	int _time;

	// status whip if whip upgradded
	int _statusWhip;

	// score, time, stage, player, enemy hp and hearts, p display
	int _score;
	int _stage;
	int _player;
	int _enemy;
	int _hearts;
	int _p;

	// current special weapon
	WeaponEnum _specialWeapon;
};
#endif //!__INFO_MANAGER_H___