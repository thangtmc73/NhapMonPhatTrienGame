#include "InfoManager.h"
#include "ObjectConfig.h"

CInfoManager* CInfoManager::_instance = nullptr;

CInfoManager * CInfoManager::GetInstance()
{
	if (_instance == nullptr)
	{
		_instance = new CInfoManager();
	}
	return _instance;
}

void CInfoManager::resetSwitchScreen()
{
	// true if switching scene
	_switchingScene = false;
	_shouldOpenGate = false;
	_moveableCameraBeforeGate = false;
	_moveableCameraAfterGate = false;
	_movingThroughGate = false;
}

void CInfoManager::SetStage(int a_stage)
{
	_stage = a_stage;
}

void CInfoManager::ChangeNumberOfHearts(int a_numberOfHearts)
{
	_hearts += a_numberOfHearts;
}

void CInfoManager::ChangeScore(int a_number_score_increase)
{
	_score += a_number_score_increase;
}

void CInfoManager::ChangeP(int a_number_p)
{
	_p += a_number_p;
}

void CInfoManager::ChangePlayerLife(int a_number_life)
{
	_player += a_number_life;
}

void CInfoManager::Reset()
{
}

void CInfoManager::setStatusWhip(int a_status)
{
	_statusWhip = a_status;
}

int CInfoManager::getStatusWhip()
{
	return _statusWhip;
}

void CInfoManager::SetTime(int a_time)
{
	_time = a_time;
}

void CInfoManager::StartClock()
{
	_enableClock = true;
}

void CInfoManager::StopClock()
{
	_enableClock = false;
}

void CInfoManager::SwitchScene(bool a_switch)
{
	_switchingScene = a_switch;
}

bool CInfoManager::IsSwitchingScene()
{
	return _switchingScene;
}

bool CInfoManager::shouldOpenGate()
{
	return _shouldOpenGate;
}

void CInfoManager::setShouldOpenGate(bool should)
{
	_shouldOpenGate = should;
}


void CInfoManager::SetSpecialWeapon(WeaponEnum a_specialWeapon)
{
	_specialWeapon = a_specialWeapon;
}


void CInfoManager::SetMoveableCameraBeforeGate(bool a_true)
{
	_moveableCameraBeforeGate = a_true;
}

void CInfoManager::SetMoveableCameraAfterGate(bool a_true)
{
	_moveableCameraAfterGate = a_true;
}

void CInfoManager::SetMovingThroughGate(bool a_true)
{
	_movingThroughGate = a_true;
}

int CInfoManager::GetNumberOfHearts()
{
	return _hearts;
}

int CInfoManager::GetScore()
{
	return _score;
}

int CInfoManager::GetClockTime()
{
	return _time;
}

int CInfoManager::GetStage()
{
	return _stage;
}

int CInfoManager::GetP()
{
	return _p;
}

int CInfoManager::GetPlayerLife()
{
	return _player;
}

int CInfoManager::GetEnemyLife()
{
	return _enemy;
}

WeaponEnum CInfoManager::GetCurrentSpeciaWeapon()
{
	return _specialWeapon;
}

void CInfoManager::update(int a_deltaTime)
{
	if (_enableClock)
	{
		if (_remainningTime / 1000 > 0)
		{
			_time -= _remainningTime / 1000;
			_remainningTime = a_deltaTime;
		}
		else
		{
			_remainningTime += a_deltaTime;
		}
	}
}

CInfoManager::~CInfoManager() {}

CInfoManager::CInfoManager()
{
	_score = 0;
	_time = 300;
	_stage = 1;
	_player = 16;
	_enemy = 16;
	_hearts = 5;
	_p = 3;
	
	_statusWhip = WhipState::NORMAL_WHIP;
	_enableClock = false;
	_switchingScene = false;

	_specialWeapon = WeaponEnum::WhipWeapon;

	_moveableCameraBeforeGate = false;
	_moveableCameraAfterGate = false;
	_shouldOpenGate = false;
	_stopCamera = false;
}

bool CInfoManager::IsMoveableCameraBeforeGate()
{
	return _moveableCameraBeforeGate;
}

bool CInfoManager::IsMoveableCameraAfterGate()
{
	return _moveableCameraAfterGate;
}

bool CInfoManager::IsMovingThroughGate()
{
	return _movingThroughGate;
}

void CInfoManager::SetNewPosition(std::string a_key, GPoint2D a_position)
{
	_position[a_key] = a_position;
}

GPoint2D CInfoManager::GetCurrentPosition(std::string a_key)
{
	std::map<std::string, GPoint2D>::iterator it = _position.find(a_key);
	if (it != _position.end())
	{
		return _position[a_key];
	}
	return GPoint2D(0, 0);
}

void CInfoManager::setStopCamera(bool stop)
{
	_stopCamera = stop;
}

bool CInfoManager::isStopCamera()
{
	return _stopCamera;
}

void CInfoManager::activeBoss()
{
	_activeBoss = true;
}

bool CInfoManager::isActiveBoss()
{
	return _activeBoss;
}
