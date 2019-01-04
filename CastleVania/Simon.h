#ifndef __SIMON_H__
#define __SIMON_H__

#include "DynamicObject.h"
#include "Whip.h"
#include "Brick.h"
#include "ObjectManager.h"
#include "InfoManager.h"

class CSimon : public CDynamicObject
{
public:
	CSimon(float, float, int);
	~CSimon();
	CWhip* GetWhip();
	bool IsWhipAttackable();
	void setState(int);
	int getState();

	// lam cho simon o trang thai buoc len cau thang
	void MakeSimonStepUp();

	void MakeSimonStepDown();

	// lay cac trang thai input hien co tu ban phim luu vao simon de xu ly
	void GetInputRelatingToSimon(bool a_left, bool a_right, bool a_up, bool a_down, bool a_jump, bool a_attack);

	// xac dinh vi tri ban dau cua simon khi bat dau di vao cau thang
	void SetPositionToStartStepping(int a_old_state, int a_now_state, GRect a_nearest_brick);

	// dieu chinh huong cua simon so voi cau thang
	void ModifyDirectionWithStair();

	// thay doi cua simon khi va cham voi cau thang, _steppable = true, co the di len cau thang
	virtual void AfterCollidingWithStair(bool a_leftDirectionStair);

	void setSteppable(bool a_steppable);

	virtual void AfterCollision(RObject *collided, CollisionInfo info);
	virtual void afterCollision(RObject *collided, CollisionInfo info, int deltaTime);


	void onCollidingWithGround(RBaseObject *collided, CollisionInfo info);

	// simon dang tan cong
	bool IsAttacking();

	// tra ve true neu simon dang trong luc chuyen canh, khong cho phep simon di chuyen luc nay
	bool IsDoneSwitchingScene();
	
	// ve cay roi
	void drawWhip();
	
	void update(int a_deltaTime);
	void draw();
	void drawWithCamera(GCamera *a_camera);

	// animation cua simon
	// cung voi thay doi index cua whip kem theo tuong uong voi moi index trong animation cua simon
	//
	virtual void runAnimation(int deltatime);

	// tra ve thong so vien gach cau thang gan simon nhat kem theo index xac dinh vien gach o tren hay o duoi
	// tra ve 1 vien gach cau thang ben duoi, tra ve 2 vien gach cau thang ben tren
	// tra ve 0 khong va cham voi vien gach cau thang nao
	virtual GRect GetBrickNearestSimon(int &a_index_brick);

	// lay thong so cua 2 vien gach cau thang ngay khi steppable = true
	virtual void SetTwoBricksFromStair(RBaseObject *a_ground);
	GPoint2D GetNextStepPosition();
	void SetDefaultVxWithDirection();
	void CorrectBoundingBox();
	void ResetInput();
	void ResetAction(int a_deltaTime);
	void Run();
	void Jump();
	void Crouch();
	void CrouchAttack();
	void AttackWhip();
	void AttackOtherWeapon();
	void StepUp(int a_deltaTime);
	void StepDown(int a_deltaTime);
	bool runToPosition(GPoint2D a_point, int a_dt);
	virtual void onOverlapping(RObject *collided);

private:
	int mapActionWithWhipIndex();
	void afterAttackingWhileStepping();

	bool isAttacking();

	bool _doneAction;

	// simon co the vao trang thai di vao cau thang
	bool _steppable;


	// huong trai hoac phai cua cau thang theo chieu tu duoi len
	// tra ve true neu nhin tu duoi len theo chieu ben trai
	bool _leftDirectionStair;


	// input
	bool _leftInput, _rightInput, _upInput, _downInput, _attackInput, _jumpInput;
	
	// state damaged
	// khoang thoi gian Simon dang bi thuong, khong bi giam mau neu va cham voi enemy
	int _timeDamaged;

	// dang bi thuong
	bool _damaged;

	// ket thuc bi thuong
	bool _doneDamaged;

	// simon truoc luc nhay co dang trong trang thai chay, cho phep simon nhay co huong
	bool _havingDirectionWhenJumping;

	bool _attackOtherWeapon;

	// vi tri theo he truc toa do y cua vien gach ngay khi Simon buoc di vao cau thang
	// xac dinh vi tri ban dau cua simon o nac thang dau tien
	GPoint2D _stairPosition;

	bool _doneStepping;

	GPoint2D _simonEachStep;
	DWORD _timePercentageStep;

	bool _steppingMove;

	// xac dinh simon dang tan cong o index cua animation thu may
	// se ket thuc tan cong khi dat dc index can thiet
	// ho tro de ket thuc trang thai tan cong ngay khi tan cong xong
	int _count_whip;

	// simon san sang de tan cong tiep
	bool _readyToAttack;

	// simon dang tan cong
	bool _attacking;

	// ho tro xac dinh index animation cua whip can thiet
	// whip co nhieu trang thai tuong ung voi cac hanh dong cua simon
	// can bien di de xac dinh cac index cua whip trong animation
	int _theDifferenceIndexSimonWhip;

	// whip
	CWhip *_whip;
	
	// simon dang co vu khi dac biet
	bool _havingSpecialWeapon;

	// khoang cach ma simon dang chuyen canh se di chuyen mot khoang so voi ban dau
	int _distanceSwitchingScene;

	// hoan thanh chuyen canh, sau do, Simon co the tu dong di chuyen
	bool _doneSwitchingScene;
	bool _startStepping;
	DWORD _starttime;
};
#endif // !__SIMON_H__