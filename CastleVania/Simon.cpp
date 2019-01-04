#include "Simon.h"
#include "ObjectConfig.h"
#include "Utils.h"
#include "ObjectManager.h"
#include "InfoManager.h"
#include "EffectManager.h"
#include "GSystem.h"
#include "SoundManager.h"
#include "BulletManager.h"
#include "Log.h"
#include "RSprite.h"
#include "RAnimation.h"
#include "DaggerBullet.h"
#include "AxeBullet.h"
#include "RObjectManager.h"
#include "Resources.h"
#include "Stair.h"

CSimon::CSimon(float a_x, float a_y, int a_left) : CDynamicObject()
{
	_boundingBox.position.x = a_x;
	_boundingBox.position.y = a_y;
	_boundingBox.vy = -Resources::getInstance()->getFloatConstWithName("gravity");
	_type = eTypeObject::Simon;
	_groupType = eGroupTypeObject::MAIN;
	_objectName = "csimon";
	loadResource();
	_animations = new RAnimation*[SimonState::TOTAL_SIMON_STATES];
	_animations[SimonState::STAY] = new RAnimation(_sprite, 0, 0, 0, 100);
	_animations[SimonState::CROUCHING] = new RAnimation(_sprite, 4, 4, 4, 0);
	_animations[SimonState::RUNNING] = new RAnimation(_sprite, 0, 3, 0, 100);
	_animations[SimonState::STEPPING_DOWN] = new RAnimation(_sprite, 10, 11, 11, 100);
	_animations[SimonState::STEPPING_UP] = new RAnimation(_sprite, 12, 13, 12, 100);
	_animations[SimonState::FALLING] = new RAnimation(_sprite, 0, 0, 0, 0);
	_animations[SimonState::DEAD] = new RAnimation(_sprite, 0, 0, 0, 0);
	_animations[SimonState::DAMAGED] = new RAnimation(_sprite, 8, 8, 8, 100);
	_animations[SimonState::JUMPING] = new RAnimation(_sprite, 4, 4, 4, 0);
	_animations[SimonState::JUMPING_ATTACK_WHIP] = new RAnimation(_sprite, 5, 7, 5, 100);
	_animations[SimonState::STANDING_ATTACK_WHIP] = new RAnimation(_sprite, 5, 7, 5, 100);
	_animations[SimonState::CROUCHING_ATTACK_WHIP] = new RAnimation(_sprite, 15, 17, 15, 100);
	_animations[SimonState::STEPPING_UP_ATTACK] = new RAnimation(_sprite, 21, 23, 21, 100);
	_attackOtherWeapon = false;

	setState(SimonState::STAY);
	if (a_left == 1) {
		_leftDirection = true;
	}
	else {
		_leftDirection = false;
	}
	_havingDirectionWhenJumping = false;
	_count_whip = -1;
	_attacking = false;
	_whip = new CWhip(a_x, a_y);
	//_whip->upgrade();
	//CObjectManager::GetInstance()->AddObject(eTypeObject::Whip, _whip);
	_whip->setState(CInfoManager::GetInstance()->getStatusWhip());
	_leftInput = false;
	_rightInput = false;
	_upInput = false;
	_jumpInput = false;
	_downInput = false;
	_attackInput = false;
	_collidingWithAnyGround = false;
	_boundingBox.vy = 0;
	_distanceSwitchingScene = 0;
	_doneSwitchingScene = false;
	_damaged = false;
	_leftDirectionStair = false;
	_readyToAttack = true;
	_doneDamaged = true;
	_destroyed = false;
	_startStepping = false;
	_steppingMove = false;
	_doneAction = false;
	_doneStepping = false;
	_timeBetweenTwoShot = Resources::getInstance()->getIntegerConstWithName("simon-time-shot");
}

void CSimon::setState(int a_state)
{
	if (_state == a_state || (_state != a_state && (a_state >= TOTAL_SIMON_STATES || a_state < 0)))
	{
		return;
	}
	int old_state = _state;
	_state = a_state;
	_animations[_state]->reset();
	float vx, vy;

	/*if (old_state == _state)
	{
		return;
	}*/

	switch (_state)
	{
	case SimonState::STEPPING_DOWN:
	case SimonState::STEPPING_UP:
		_boundingBox.width = 20;
		break;

	case SimonState::DEAD:
		break;

	case SimonState::DAMAGED:;
		vx = Resources::getInstance()->getFloatConstWithName("simon-damaged-vx");
		vy = Resources::getInstance()->getFloatConstWithName("simon-damaged-vy");
		setVxWithLeftDirection(-vx);
		_boundingBox.vy = vy;
		_boundingBox.position.y += _boundingBox.vy * GSystem::GetInstance()->GetDeltaTime();
		_damaged = true;
		_doneDamaged = false;
		break;
	case SimonState::STAY:
		_boundingBox.vx = 0;
		_readyToAttack = true;
		break;

	case SimonState::FALLING:
		_boundingBox.vx = 0;
		_readyToAttack = true;
		_boundingBox.height = 58;
		break;

	case SimonState::RUNNING:
		_boundingBox.width = 30;
		_boundingBox.height = 58;
		_readyToAttack = false;
		_starttime = GSystem::GetInstance()->GetNowTime();
		break;

	case SimonState::JUMPING:
		_boundingBox.vx = 0;
		_boundingBox.height = 58;
		break;

	case SimonState::CROUCHING:
		_boundingBox.vx = 0;
		break;

	case SimonState::JUMPING_ATTACK_WHIP:
		//_readyToAttack = true;
		/*if (!_leftDirection)
		{
			_whip->setX(_boundingBox.position.x + 30);
		}
		else
		{
			_whip->setX(_boundingBox.position.x - 30);
		}
		_whip->setY(_boundingBox.position.y);
		CSoundManager::GetInstance()->PlaySoundWithIndex(eSoundIndex::USING_WHIP);*/
		if (!_leftDirection)
		{
			_whip->setX(_boundingBox.position.x + 30);
		}
		else
		{
			_whip->setX(_boundingBox.position.x - 30);
		}
		_whip->setY(_boundingBox.position.y);
		break;

	case SimonState::CROUCHING_ATTACK_WHIP:
		if (!_leftDirection)
		{
			_whip->setX(_boundingBox.position.x + 30);
		}
		else
		{
			_whip->setX(_boundingBox.position.x - 30);
		}
		_whip->setY(_boundingBox.position.y);
		break;

	case SimonState::STANDING_ATTACK_WHIP:
		if (!_leftDirection)
		{
			_whip->setX(_boundingBox.position.x + 30);
		}
		else
		{
			_whip->setX(_boundingBox.position.x - 30);
		}
		_whip->setY(_boundingBox.position.y);
		
		CSoundManager::GetInstance()->PlaySoundWithIndex(eSoundIndex::USING_WHIP);
		break;
	case SimonState::STEPPING_UP_ATTACK:
		if (!_leftDirection)
		{
			_whip->setX(_boundingBox.position.x + 30);
		}
		else
		{
			_whip->setX(_boundingBox.position.x - 30);
		}
		_whip->setY(_boundingBox.position.y);

		CSoundManager::GetInstance()->PlaySoundWithIndex(eSoundIndex::USING_WHIP);
		break;
	}
	CorrectBoundingBox();
}

int CSimon::getState()
{
	return _state;
}

void CSimon::MakeSimonStepUp()
{
	setState(SimonState::STEPPING_UP);
	_simonEachStep = _boundingBox.position;
}

void CSimon::MakeSimonStepDown()
{
	setState(SimonState::STEPPING_DOWN);
	_steppingMove = false;
	_timePercentageStep = 0;
	_simonEachStep = _boundingBox.position;
	_doneAction = true;
	_doneStepping = true;
}

void CSimon::GetInputRelatingToSimon(bool a_left, bool a_right, bool a_up, bool a_down, bool a_jump, bool a_attack)
{
	_leftInput = a_left;
	_rightInput = a_right;
	_upInput = a_up;
	_jumpInput = a_jump;
	_downInput = a_down;
	_attackInput = a_attack;
}

void CSimon::update(int a_deltaTime)
{
	_listColliding.clear();
	_listOverlapping.clear();

	this->updateTimeToShot(a_deltaTime);
	_boundingBox.vy -= (Resources::getInstance()->getFloatConstWithName("gravity") * a_deltaTime);
	// run animation
	this->runAnimation(a_deltaTime);

	this->ResetAction(a_deltaTime);

	// neu dang bi thuong, tinh thoi gian khong bi thuong nua sau khi va cham
	if (_damaged)
	{
		_timeDamaged += a_deltaTime;
		if (_timeDamaged >= Resources::getInstance()->getFloatConstWithName("time-simon-damaged"))
		{
			_timeDamaged = 0;
			_damaged = false;
			_doneDamaged = true;
		}
	}

	if (_state != SimonState::DAMAGED) {
		if ((_leftInput ^ _rightInput) && !_havingDirectionWhenJumping)
		{
			if ((_rightInput ^ _leftDirection) == false)
			{
				this->SetLeftDirection(!_leftDirection);
			}
		}

		if (_leftInput || _rightInput) {
			if (_state != SimonState::STEPPING_UP && _state != SimonState::STEPPING_DOWN) {
				Run();
			}
			else if (_state == SimonState::STEPPING_UP) {
				if (_leftDirection ^ _leftDirectionStair) {
					StepDown(a_deltaTime);
				}
				else {
					StepUp(a_deltaTime);
				}
			}
			else if (_state == SimonState::STEPPING_DOWN) {
				if (_leftDirection ^ _leftDirectionStair) {
					StepDown(a_deltaTime);
				}
				else {
					StepUp(a_deltaTime);
				}
			}
		}

		if (_jumpInput) {
			Jump();
		}

		if (_downInput) {
			if (_steppable) {
				StepDown(a_deltaTime);
			}
			else {
				Crouch();
			}
		}

		if (_attackInput && _upInput) {
			AttackOtherWeapon();
		}
		else if (_upInput) {
			StepUp(a_deltaTime);
		}
		else if (_attackInput) {
			AttackWhip();
		}
	}
		
	ResetInput();
	RObjectManager::GetInstance()->collidingWith(this, a_deltaTime);

	// change position x and y
	_boundingBox.position.x += a_deltaTime * _boundingBox.vx;
	_boundingBox.position.y += a_deltaTime * _boundingBox.vy;
}

void CSimon::SetPositionToStartStepping(int a_old_state, int a_now_state, GRect a_nearest_brick)
{
	if (a_old_state != SimonState::STEPPING_UP && a_now_state == SimonState::STEPPING_UP)
	{
		if (a_old_state != SimonState::STEPPING_DOWN)
		{
			_stairPosition.y = a_nearest_brick.position.y - 16;
			if (!_leftDirection)
			{
				_stairPosition.x = a_nearest_brick.position.x + 8;
				_boundingBox.position.x = _stairPosition.x;
			}
			else
			{
				_stairPosition.x = a_nearest_brick.position.x + 28;
				_boundingBox.position.x = _stairPosition.x;
			}
			_simonEachStep = _boundingBox.position;

		}
		return;
	}
	if (a_old_state != SimonState::STEPPING_DOWN  && a_now_state == SimonState::STEPPING_DOWN)
	{
		if (a_old_state != SimonState::STEPPING_UP)
		{
			_stairPosition.y = a_nearest_brick.position.y - 16;
			//_stairPosition.x = a_nearest_brick.position.x + 16;
			if (!_leftDirection)
			{
				_stairPosition.x = a_nearest_brick.position.x + 26;
				_boundingBox.position.x = _stairPosition.x;
			}
			else
			{
				_stairPosition.x = a_nearest_brick.position.x + 8;
				_boundingBox.position.x = _stairPosition.x;
			}
			_simonEachStep = _boundingBox.position;
		}
	}
}

void CSimon::ModifyDirectionWithStair()
{
	if (_state != SimonState::STEPPING_UP && _state != SimonState::STEPPING_DOWN)
	{
		return;
	}

	if (((_leftDirection ^ _leftDirectionStair) && _state == SimonState::STEPPING_UP)
		|| (!(_leftDirection ^ _leftDirectionStair) && _state == SimonState::STEPPING_DOWN))
	{

		SetLeftDirection(!_leftDirection);
	}
}

void CSimon::AfterCollidingWithStair(bool a_leftDirectionStair)
{
	_steppable = true;
	_leftDirectionStair = a_leftDirectionStair;
}

void CSimon::setSteppable(bool a_steppable) {
	_steppable = a_steppable;
}

void CSimon::AfterCollision(RObject * collided, CollisionInfo info)
{
	if (collided->getGroupType() == ::GROUND) {
		if (collided->isNormalGroundObject()) {
			if (info.direction == eDirection::TOP) {
				_boundingBox.position.y += (info.collisionTime  * GSystem::GetInstance()->GetDeltaTime() * _boundingBox.vy + 1);
				_boundingBox.vy = 0;
				_collidingWithAnyGround = true;
			}

			if (info.direction == eDirection::LEFT && (collided->isNormalGroundObject())) {
				_boundingBox.position.x += info.collisionTime * _boundingBox.vx;
				_boundingBox.vx = 0;
			}
			if (info.direction == eDirection::RIGHT && (collided->isNormalGroundObject())) {
				_boundingBox.position.x += info.collisionTime * _boundingBox.vx;
				_boundingBox.vx = 0;
			}

		}
	}
	//switch (collided->getType())
	//{
	//case eTypeObject::Whip:
	//	_whip->upgrade();

	//	CInfoManager::GetInstance()->setStatusWhip(_whip->getState());
	//	break;
	//case eTypeObject::Dagger:
	//	CInfoManager::GetInstance()->SetSpecialWeapon(WeaponEnum::DaggeBullet);
	//	CSoundManager::GetInstance()->PlaySoundWithIndex(eSoundIndex::COLLECTING_WEAPON);
	//	break;
	//case eTypeObject::Axe:
	//case eTypeObject::GoldPotion:
	//case eTypeObject::Cross:
	//case eTypeObject::HiddenSwitchScene:
	//case eTypeObject::HiddenPassableGate:
	//	//if (directionColliding != eDirection::NONE)
	//	//{
	//	//	//a_object->AfterCollisionWithSimon(a_objectManager);
	//	//	a_object->setDestroyed(true);
	//	//	//a_objectManager->RemoveObjectWithIndex(a_object->GetIndex());
	//	//	break;
	//	//}
	//	break;
	//case eTypeObject::EnemeyGhoul:
	//case eTypeObject::EnemySpearKnight:
	//case eTypeObject::EnemyPanther:
	//case eTypeObject::EnemyVampireBat:
	//case eTypeObject::EnemyMedusa:
	//case eTypeObject::EnemyFishMan:
	//case eTypeObject::EnemyAxeMan:
	//case eTypeObject::EnemyDragonSkullCannon:

	//	if (_doneDamaged)
	//	{
	//		setState(SimonState::DAMAGED);
	//		CInfoManager::GetInstance()->ChangePlayerLife(-2);
	//	}
	//	break;
	//	break;
	//case eTypeObject::BrickBlueMoneyBag:
	//case eTypeObject::BrickDoubleShot:
	//case eTypeObject::BrickNothing:
	//case eTypeObject::BrickPorkChop:
	//	//float remainningtime = 1 - collisiontime;

	//	//if (directionColliding == eDirection::BOTTOM)
	//	//{
	//	//	a_object->SetY(a_object->GetY() + a_object->GetVY() * remainningtime);
	//	//	a_object->SetVY(0);
	//	//}
	//	//if (directionColliding == eDirection::LEFT)
	//	//{
	//	//	a_object->SetX(a_object->GetX() + a_object->GetVX() * remainningtime);
	//	//	a_object->SetVX(0);
	//	//}
	//	//if (directionColliding == eDirection::RIGHT)
	//	//{
	//	//	a_object->SetX(a_object->GetX() + a_object->GetVX() * remainningtime);
	//	//	a_object->SetVX(0);
	//	//}
	//	break;
	//}
}

void CSimon::afterCollision(RObject * collided, CollisionInfo info, int deltaTime)
{
	if (collided->getGroupType() == eGroupTypeObject::GROUND) {
		if (collided->isNormalGroundObject()) {
			if (info.direction == eDirection::TOP) {
				_boundingBox.position.y += (info.collisionTime  * deltaTime * _boundingBox.vy + 1);
				_boundingBox.vy = 0;
			}

			if ((info.direction == eDirection::LEFT || info.direction == eDirection::RIGHT) && (collided->isNormalGroundObject())) {
				GRect groundRect = collided->getTopLeftBoundingBox();
				GRect simon = collided->getTopLeftBoundingBox();
				if (!(groundRect.position.y - groundRect.height > simon.position.y || simon.position.y - simon.height > groundRect.position.y))
				{
					_boundingBox.position.x += (info.collisionTime  * deltaTime * _boundingBox.vx);
					_boundingBox.vx = 0;
				}
			}
		}
	}
	switch (collided->getType())
	{
	case eTypeObject::STAIR_1:
	case eTypeObject::STAIR_2:
		CStair * stair = (CStair*)collided;
		this->AfterCollidingWithStair(stair->isLeftDirection());
		this->SetTwoBricksFromStair(stair);
		break;
	}
}

void CSimon::onCollidingWithGround(RBaseObject * collided, CollisionInfo info)
{
}


bool CSimon::IsAttacking()
{
	return (_state == SimonState::STANDING_ATTACK_WHIP || _state == SimonState::CROUCHING_ATTACK_WHIP || _state == SimonState::JUMPING_ATTACK_WHIP);
}

bool CSimon::IsDoneSwitchingScene()
{
	return _doneSwitchingScene;
}


void CSimon::drawWhip()
{
	if (_attacking)
	{
		_whip->setY(_boundingBox.position.y);
		mapActionWithWhipIndex();
		_whip->SetLeft(_leftDirection);
		_whip->draw();
	}
}

void CSimon::draw()
{
	if (_leftDirection)
	{
		_sprite->draw(_boundingBox.position.x, _boundingBox.position.y);
	}
	else
	{
		_sprite->drawFlipX(_boundingBox.position.x, _boundingBox.position.y);
	}
}

void CSimon::drawWithCamera(GCamera * a_camera)
{
	if (a_camera == NULL)
	{
		return;
	}

	if (IsAttacking() && !_attackOtherWeapon)
	{
		_whip->setY(_boundingBox.position.y);

		int x = _whip->getX();
		int y = _whip->getY();
		mapActionWithWhipIndex();
		_whip->SetLeft(_leftDirection);
		_whip->drawWithCamera(a_camera);
	}
	int x = _boundingBox.position.x;
	int y = _boundingBox.position.y;
	D3DXVECTOR2 pos = a_camera->Transform(_boundingBox.position.x, _boundingBox.position.y);
	Log::getInstance()->addLog("vi tri simon camera" + std::to_string(_boundingBox.position.x) + " " + std::to_string(_boundingBox.position.y) + " " + std::to_string(pos.x) + " " + std::to_string(pos.y));
	_boundingBox.position.x = pos.x;
	_boundingBox.position.y = pos.y;
	draw();
	_boundingBox.position.x = x;
	_boundingBox.position.y = y;
	
}

void CSimon::runAnimation(int deltatime)
{
	bool tempt;
	int k = _sprite->getIndex();
	if (_doneStepping) {

	}
	//_animations[_state]->update(deltatime);
	_doneAction = _animations[_state]->update(deltatime, false);

	if (_doneStepping && _state == SimonState::STEPPING_UP) {
		_sprite->SelectIndex(12);
	}
	if (_doneStepping && _state == SimonState::STEPPING_DOWN) {
		_sprite->SelectIndex(10);
	}

	//if (_attacking && _readyToAttack)
	//{
	//	_sprite->update(deltatime, _count_whip);
	//}
	//else
	//{
	//	if (!_stepping)
	//	{
	//		_sprite->update(deltatime);
	//	}
	//	else
	//	{
	//		if (!_steppingMove)
	//		{
	//			_sprite->UpdateOnceTimeFinishWithStart(deltatime, _steppingMove);
	//		}
	//		//if (_numberSteps > -1 && _numberSteps <= 1)
	//		//{
	//		//	int k = _numberSteps;
	//		//	
	//		//	_sprite->update(deltatime, _numberSteps);
	//		//	if (_numberSteps > 1)
	//		//	{
	//		//		SetPositionStepping();
	//		//	}
	//		//}
	//	}
	//}
	//
}

GRect CSimon::GetBrickNearestSimon(int &a_index_brick)
{
	GRect box = getTopLeftBoundingBox();
	GRect brickBottomBox, brickTopBox;
	brickBottomBox.position = CInfoManager::GetInstance()->GetCurrentPosition("bottom_brick");
	brickTopBox.position = CInfoManager::GetInstance()->GetCurrentPosition("top_brick");
	
	brickBottomBox.height = brickTopBox.height = 32;
	brickBottomBox.width = brickTopBox.width = 32;
	
	brickBottomBox.position.x -= brickBottomBox.width / 2;
	brickBottomBox.position.y += brickBottomBox.height / 2;

	brickTopBox.position.x -= brickTopBox.width / 2;
	brickTopBox.position.y += brickTopBox.height / 2;

	if (IsAABBCheck(box, brickBottomBox))
	{
		a_index_brick = 1;
		return brickBottomBox;
	}
	if (IsAABBCheck(box, brickTopBox))
	{
		a_index_brick = 2;
		return brickTopBox;
	}
	a_index_brick = 0;
	return GRect(0, 0, -1, -1, 0, 0);
}

void CSimon::SetTwoBricksFromStair(RBaseObject * a_ground)
{
	CInfoManager::GetInstance()->SetNewPosition("bottom_brick", a_ground->GetFirstBrick().position);
	CInfoManager::GetInstance()->SetNewPosition("top_brick", a_ground->GetSecondBrick().position);
}

GPoint2D CSimon::GetNextStepPosition()
{
	float x, y;
	if (_leftDirection)
	{
		x = _simonEachStep.x - 16;
	}
	else
	{
		x = _simonEachStep.x + 16;
	}
	if (_state == SimonState::STEPPING_UP)
	{
		y = _simonEachStep.y + 16;
	}
	else
	{
		y = _simonEachStep.y - 16;
	}
	return GPoint2D(x, y);
}

void CSimon::SetDefaultVxWithDirection() {
	if (_state == SimonState::RUNNING) {
		float vx = Resources::getInstance()->getFloatConstWithName("simon-run-vx");
		setVxWithLeftDirection(vx);
	}
	if (_state == SimonState::JUMPING) {
		float vx = Resources::getInstance()->getFloatConstWithName("simon-jump-vx");
		setVxWithLeftDirection(vx);
	}
}

void CSimon::CorrectBoundingBox()
{
	if (_state != SimonState::CROUCHING && _state != SimonState::CROUCHING_ATTACK_WHIP) {
		_boundingBox.height = 58;
		//_boundingBox.position.y += 33;
	}
	else {
		_boundingBox.height = 33;
	}
}

void CSimon::ResetInput()
{
	// set all input not to happen
	_leftInput = false;
	_rightInput = false;
	_upInput = false;
	_jumpInput = false;
	_downInput = false;
	_attackInput = false;
}

void CSimon::ResetAction(int a_deltaTime) {
	if (CInfoManager::GetInstance()->IsMovingThroughGate()) {
		return;
	}
	if ((_state == SimonState::CROUCHING || _state == SimonState::CROUCHING_ATTACK_WHIP) && !_downInput) {
		_boundingBox.position.y += 33;
		setState(SimonState::STAY);
	}
	else if (_state == SimonState::JUMPING) {
		if (_boundingBox.vy <= 0) {
			setState(SimonState::FALLING);
		}
	}
	else if (_state == SimonState::STANDING_ATTACK_WHIP) {
		if (_doneAction) {
			_attackOtherWeapon = false;
			setState(SimonState::RUNNING);
			//setState(SimonState::CROUCHING);
			//_doneAction = false;
		}
	}
	else if (_state == SimonState::CROUCHING_ATTACK_WHIP) {
		if (_doneAction) {
			_attackOtherWeapon = false;

			if (_downInput) {
				setState(SimonState::CROUCHING);
			}
			else {
				setState(SimonState::STAY);
			}
		}
	}
	else if (_state == SimonState::RUNNING && (_leftInput || _rightInput)) {

	}
	else if (_state == SimonState::DAMAGED) {
		if (_doneDamaged) {
			setState(SimonState::STAY);
			//_doneAction = false;
		}
	}
	else if (_state == SimonState::STEPPING_UP || _state == SimonState::STEPPING_DOWN) {
		if (_doneAction) {
			_doneStepping = true;
		}
		int k;
		_boundingBox.vx = 0;
		_boundingBox.vy = 0;
		GRect brick = GetBrickNearestSimon(k);
		if (k == 2 && _state == SimonState::STEPPING_UP && _boundingBox.position.y > brick.position.y)
		{
			setState(SimonState::STAY);
			_boundingBox.position.y += 8;
			_boundingBox.vx = 0;
			_boundingBox.vy = 0;
		}
		else if (k == 1 && _state == SimonState::STEPPING_DOWN && _boundingBox.position.y < brick.position.y - 4)
		{
			setState(SimonState::STAY);
			_boundingBox.position.y += 10;
			_boundingBox.vx = 0;
			_boundingBox.vy = 0;
		}
		else {
			_timePercentageStep += a_deltaTime;
			_boundingBox.position = linearInterpolation(_simonEachStep, GetNextStepPosition(), _boundingBox.position, _timePercentageStep, 200);
		}
	}
	else {
		setState(SimonState::STAY);
	}
}

void CSimon::Run()
{
	if (_state == SimonState::CROUCHING
		|| _state == SimonState::CROUCHING_ATTACK_WHIP
		|| _state == SimonState::FALLING) {
		return;
	}
	if (_state == SimonState::JUMPING) {
		SetDefaultVxWithDirection();
		return;
	}
	else {
		setState(SimonState::RUNNING);
	}
	SetDefaultVxWithDirection();
}

void CSimon::Jump()
{
	if (_state == SimonState::JUMPING || _state == SimonState::FALLING
		|| _state == SimonState::STANDING_ATTACK_WHIP) {
		return;
	}
	// chuyen animtion
	setState(SimonState::JUMPING);

	// set lai toc do vy
	_boundingBox.vy = Resources::getInstance()->getFloatConstWithName("simon-jump-vy");
}

void CSimon::Crouch()
{
	if (_state == SimonState::CROUCHING || _state == SimonState::CROUCHING_ATTACK_WHIP) {
		return;
	}
	setState(SimonState::CROUCHING);
}

void CSimon::CrouchAttack()
{
}

void CSimon::AttackWhip()
{
	if (_state == SimonState::CROUCHING) {
		_attacking = true;
		setState(SimonState::CROUCHING_ATTACK_WHIP);
		mapActionWithWhipIndex();
	} else if (_state == SimonState::STAY) {
		_attacking = true;
		setState(SimonState::STANDING_ATTACK_WHIP);
		mapActionWithWhipIndex();
	}
	else if (_state == SimonState::STEPPING_UP) {
		_attacking = true;
		setState(SimonState::STEPPING_UP_ATTACK);
		mapActionWithWhipIndex();
	}
	else if (_state == SimonState::JUMPING) {
		_attacking = true;
		setState(SimonState::JUMPING_ATTACK_WHIP);
		mapActionWithWhipIndex();
	}
}

void CSimon::AttackOtherWeapon()
{
	if (!this->isTimeToShot()) {
		return;
	}
	_attackOtherWeapon = true;
	if (_state == SimonState::CROUCHING) {
		_attacking = true;
		setState(SimonState::CROUCHING_ATTACK_WHIP);
		mapActionWithWhipIndex();
	}
	else if (_state == SimonState::STAY) {
		_attacking = true;
		setState(SimonState::STANDING_ATTACK_WHIP);
		RObjectManager::GetInstance()->addObject(-(_index * 1000 + _numberShot), new CAxeBullet(_boundingBox.position.x, _boundingBox.position.y, _leftDirection));
		++_numberShot;
		CBulletManager::GetInstance()->shootBullet(this, new CDaggerBullet(_boundingBox.position.x, _boundingBox.position.y, _leftDirection));
		mapActionWithWhipIndex();
	}
	else if (_state == SimonState::STEPPING_UP) {
		_attacking = true;
		setState(SimonState::STEPPING_UP_ATTACK);
		mapActionWithWhipIndex();
	}
}

void CSimon::StepUp(int a_deltaTime) {
	if (_steppable)
	{
		int nearestbrick_index;
		int e = _boundingBox.position.y;
		GRect neareastBrick = GetBrickNearestSimon(nearestbrick_index);
		if ((nearestbrick_index == 1 && _state != SimonState::STEPPING_UP) || _state == SimonState::STEPPING_DOWN)
		{
			if (_boundingBox.vx != 0)
			{
				_boundingBox.vx = 0;
			}
			int old_state = _state;

			setState(SimonState::STEPPING_UP);
			ModifyDirectionWithStair();
			SetPositionToStartStepping(old_state, _state, neareastBrick);
			_steppingMove = false;
			_timePercentageStep = 0;
			_simonEachStep = _boundingBox.position;
			//_boundingBox.position = linearInterpolation(_simonEachStep, GetNextStepPosition(), _boundingBox.position, _timePercentageStep, 200);
		}
		else if (nearestbrick_index == 2 && ((!_leftDirection && _boundingBox.position.x >= neareastBrick.position.x + 16)
			|| (_leftDirection))) {
			setState(SimonState::STAY);
			_boundingBox.vx = 0;
			_boundingBox.position.y += 10;
		}
		else if (_state == SimonState::STEPPING_UP) {
			if (_doneStepping) {
				GPoint2D nextStep = GetNextStepPosition();
				if (_boundingBox.position.x != nextStep.x &&  _boundingBox.position.y != nextStep.y)
				{
					_timePercentageStep += a_deltaTime;
					_boundingBox.position = linearInterpolation(_simonEachStep, nextStep, _boundingBox.position, _timePercentageStep, 200);
				}
				_doneStepping = false;
				_steppingMove = false;
				_timePercentageStep = a_deltaTime;
				_simonEachStep = _boundingBox.position;
				_boundingBox.position = linearInterpolation(_simonEachStep, GetNextStepPosition(), _boundingBox.position, _timePercentageStep, 200);
			}
		}
	}
}

void CSimon::StepDown(int a_deltaTime)
{
	if (_steppable)
	{
		int nearestbrick_index;
		int e = _boundingBox.position.y;
		GRect neareastBrick = GetBrickNearestSimon(nearestbrick_index);
		if ((nearestbrick_index == 2 && _state != SimonState::STEPPING_DOWN) || (_state == SimonState::STEPPING_UP))
		{
			if (_boundingBox.vx != 0)
			{
				_boundingBox.vx = 0;
			}
			int old_state = _state;

			setState(SimonState::STEPPING_DOWN);
			ModifyDirectionWithStair();
			SetPositionToStartStepping(old_state, _state, neareastBrick);
			_steppingMove = false;
			_timePercentageStep = 0;
			_simonEachStep = _boundingBox.position;
			//_boundingBox.position = linearInterpolation(_simonEachStep, GetNextStepPosition(), _boundingBox.position, _timePercentageStep, 200);
		}
		else if (nearestbrick_index == 1 && ((!_leftDirection && _boundingBox.position.x >= neareastBrick.position.x + 48)
			|| (_leftDirection && _boundingBox.position.x <= neareastBrick.position.x))) {
			setState(SimonState::STAY);
			_boundingBox.vx = 0;
			_boundingBox.position.y = neareastBrick.position.y + 8;
		}
		else if (_state == SimonState::STEPPING_DOWN) {
			if (_doneStepping) {
				GPoint2D nextStep = GetNextStepPosition();
				if (_boundingBox.position.x != nextStep.x &&  _boundingBox.position.y != nextStep.y)
				{
					_timePercentageStep += a_deltaTime;
					_boundingBox.position = linearInterpolation(_simonEachStep, nextStep, _boundingBox.position, _timePercentageStep, 200);
				}
				_doneStepping = false;
				_steppingMove = false;
				_timePercentageStep = a_deltaTime;
				_simonEachStep = _boundingBox.position;
				_boundingBox.position = linearInterpolation(_simonEachStep, GetNextStepPosition(), _boundingBox.position, _timePercentageStep, 200);
			}
		}
	}
}

bool CSimon::runToPosition(GPoint2D a_point, int a_dt)
{
	if (_boundingBox.position == a_point) {
		return true;
	}

	if (_state != SimonState::RUNNING) {
		setState(SimonState::RUNNING);
	}

	this->runAnimation(a_dt);

	if (a_point.x < _boundingBox.position.x) {
		_leftDirection = true;
		SetDefaultVxWithDirection();
	}
	else if (a_point.x > _boundingBox.position.x) {
		SetDefaultVxWithDirection();
		_leftDirection = false;
	} else {
		_boundingBox.vx = 0;
		return true;
	}

	int defaultMovePositionX = _boundingBox.position.x + _boundingBox.vx * a_dt;
	if ((defaultMovePositionX > a_point.x && !_leftDirection)
		|| (defaultMovePositionX < a_point.x && _leftDirection)) {
		setState(SimonState::STAY);
		_boundingBox.vx = a_point.x;
		return true;
	} else if (defaultMovePositionX == a_point.x) {
		setState(SimonState::STAY);
		return true;
	}
	_boundingBox.position.x = defaultMovePositionX;
	return false;
}

void CSimon::onOverlapping(RObject * collided)
{
	switch (collided->getType())
	{
	case eTypeObject::STAIR_1:
	case eTypeObject::STAIR_2:
		CStair * stair = (CStair*)collided;
		this->AfterCollidingWithStair(stair->isLeftDirection());
		this->SetTwoBricksFromStair(stair);
		break;
	}
}

int CSimon::mapActionWithWhipIndex()
{
	switch (_whip->getState())
	{
	case WhipState::NORMAL_WHIP:
		if (_sprite->getIndex() == 5 || _sprite->getIndex() == 15
			|| _sprite->getIndex() == 18 || _sprite->getIndex() == 21) {
			_whip->setIndexFrame(0);
		}
		else if (_sprite->getIndex() == 6 || _sprite->getIndex() == 16
			|| _sprite->getIndex() == 19 || _sprite->getIndex() == 22) {
			_whip->setIndexFrame(1);
		} else if (_sprite->getIndex() == 7 || _sprite->getIndex() == 17
			|| _sprite->getIndex() == 20 || _sprite->getIndex() == 23) {
			_whip->setIndexFrame(2);
		}
		break;
	case WhipState::UPGRADE_1:
		if (_sprite->getIndex() == 5 || _sprite->getIndex() == 15
			|| _sprite->getIndex() == 18 || _sprite->getIndex() == 21) {
			_whip->setIndexFrame(3);
		}
		else if (_sprite->getIndex() == 6 || _sprite->getIndex() == 16
			|| _sprite->getIndex() == 19 || _sprite->getIndex() == 22) {
			_whip->setIndexFrame(4);
		}
		else if (_sprite->getIndex() == 7 || _sprite->getIndex() == 17
			|| _sprite->getIndex() == 20 || _sprite->getIndex() == 23) {
			_whip->setIndexFrame(5);
		}
		break;
	case WhipState::UPGRADE_2:
		if (_sprite->getIndex() == 5 || _sprite->getIndex() == 15
			|| _sprite->getIndex() == 18 || _sprite->getIndex() == 21) {
			_whip->setIndexFrame(6);
		}
		else if (_sprite->getIndex() == 6 || _sprite->getIndex() == 16
			|| _sprite->getIndex() == 19 || _sprite->getIndex() == 22) {
			_whip->setIndexFrame(7);
		}
		else if (_sprite->getIndex() == 7 || _sprite->getIndex() == 17
			|| _sprite->getIndex() == 20 || _sprite->getIndex() == 23) {
			_whip->setIndexFrame(8);
		}
		break;
	}
	return 0;
}

void CSimon::afterAttackingWhileStepping()
{
	if (_state == SimonState::STEPPING_UP_ATTACK) {
		_state = SimonState::STEPPING_UP;
		_sprite->SelectIndex(12);
	}
	else if (_state == SimonState::STEPPING_DOWN_ATTACK) {

		_state = SimonState::STEPPING_DOWN;
		_sprite->SelectIndex(11);
	}
}


CSimon::~CSimon()
{
}

CWhip * CSimon::GetWhip()
{
	return _whip;
}

bool CSimon::IsWhipAttackable()
{
	return (_attacking && _whip->getIndexFrame() % 3 == 2);
}
