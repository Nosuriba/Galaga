#include <tuple>
#include "Object.h"

enum class EN_STATE
{
	POS,
	SIZE,
	TYPE,
	ID,
	AIM,
	NUM,
	MAX
};

/// “G‚Ìí—Ş
enum class EN_TYPE
{
	NORMAL,
	BONUS,
	BOSS,
	MAX
};

/// “G‚ÌID
enum class EN_ID
{
	BEE,
	BUTTERFLY,
	SCORPION,
	MAX
};

//	0 : pos, 1 : size  2 : type, 3 : id, 4 : aimPos, 5 : num
using EnemyState = std::tuple<Vector2, Size, EN_TYPE, EN_ID, Vector2d, int>;

class Enemy :
	public Object
{
public:
	Enemy();
	Enemy(const EnemyState& state);
	~Enemy();
	
	void Update() override;
	void Draw() override;
	const Obj GetObjID() const override;
private:
	void Curve();
	void Target();
	void Rotation();
	void Move();
	void Shot();

	void CurveUpdate();
	void TargetUpdate();
	void RotationUpdate();
	void MoveUpdate();
	void ShotUpdate();

	void Init(EN_TYPE type, EN_ID id);
	void CalAngle(const Vector2d& sPos, const Vector2d& ePos);
	double Sigmoid(const double& gain, const double& x);	
	void (Enemy::*_updater)();

	Vector2d _aimPos;	// –Ú•WÀ•W
	Vector2d _nextPos;

	double sigCnt;		// ¼¸ŞÓ²ÄŞŠÖ”‚Ì’l
	double sigRange;	// ¼¸ŞÓ²ÄŞŠÖ”‚Ì”ÍˆÍ
};

