#include "stdafx.h"
#include "Platform.h"
#include <string>

#pragma region 바닥
Platform::Platform()
{
	Init();
}

Platform::~Platform()
{
}

void Platform::Init()
{
	_name = L"Platform";
	_position = Vector2(WINSIZEX / 2, WINSIZEY - 20);
	_size = Vector2(WINSIZEX, 5);
	_rect = RectMakePivot(_position, _size, Pivot::Center);
	_gravity = 1.0f;
	_active = true;
}

void Platform::Release()
{
}

void Platform::Update()
{
	_rect = RectMakePivot(CAMERA->GetRelativeVector2(_position), _size, Pivot::Center);	//카메라 따라 올라가므로 발판도 저 멀리 사라지기
}

void Platform::Render()
{
	_D2DRenderer->FillRectangle(_rect, D2DRenderer::DefaultBrush::White);			
	_D2DRenderer->DrawRectangle(_rect, D2DRenderer::DefaultBrush::Black, 1.0f);		
}
#pragma endregion

PlatformBlock::PlatformBlock()
{
	Init();
}

PlatformBlock::~PlatformBlock()
{

}

void PlatformBlock::Init()
{
	_name = L"Block";
	SetRandomCreate(Vector2(rand() % 473 + 20, rand() % 901), rand() % 20);
	_size = Vector2(75, 22);
	_active = true;

	IMAGEMANAGER->AddImage(L"green", L"Resources/block_green.png");
	IMAGEMANAGER->AddImage(L"blue", L"Resources/block_blue.png");
	_blockImage = IMAGEMANAGER->AddFrameImage(L"brown", L"Resources/block_brown.png", 4, 1);
	_blockImage->SetScale(0.3f);

	_blockAnimation = new Animation();
	_blockAnimation->Init(_blockImage->GetWidth(), _blockImage->GetHeight(), _blockImage->GetFrameSize().x, _blockImage->GetFrameSize().y);
	_blockAnimation->SetPlayFrame(0, 4, false, false);
	_blockAnimation->SetFPS(30);	// 조정하면서 살펴보기
	
	_player = dynamic_cast<Player*>(OBJECTMANAGER->FindObject(ObjectType::Player, L"Player"));

	_isRight = true;
	_isBreak = false;
}

void PlatformBlock::Release()
{
}

void PlatformBlock::Update()
{
	if (_blockType == BlockType::BROWN) //갈색 블록
	{
		_blockImage = IMAGEMANAGER->FindImage(L"brown");
		_blockImage->SetScale(0.3f);
		if (_position.x > _player->GetPosition().x - _player->GetSize().x / 2 && _position.x < _player->GetPosition().x + _player->GetSize().x / 2)	//두들의 x좌표가 블록의 x 범위 내부에 있다면
		{
			if (_position.y > _player->GetPosition().y - _player->GetSize().y / 2 && _position.y < _player->GetPosition().y + _player->GetSize().y / 2)
			{
				if (_player->_gravity > 0)
				{
					if (!_isBreak)
						_blockAnimation->Start();		// 이거 안 하면 시작 안 함

					_isBreak = true;
				}
			}
		}

		if (_isBreak)
		{
			_countTime += TIMEMANAGER->GetElapsedTime();

			if (_countTime < 1.0f)
				Move(Vector2(0, 10), 10);
		}
	}
	else if (_blockType == BlockType::BLUE) //파란색 블록
	{
		_blockImage = IMAGEMANAGER->FindImage(L"blue");

		if (CAMERA->GetRelativeVector2(_position).x > WINSIZEX)
			_isRight = false;
		if (CAMERA->GetRelativeVector2(_position).x < 0)
			_isRight = true;

		if (_isRight)
			Move(Vector2(10, 0), 10);
		else
			Move(Vector2(-10, 0), 10);
	}
	else //초록색 블록
		_blockImage = IMAGEMANAGER->FindImage(L"green");


	_rect = RectMakePivot(CAMERA->GetRelativeVector2(_position), _size, Pivot::Center);	//유무 확인
	_blockAnimation->FrameUpdate(TIMEMANAGER->GetElapsedTime());

	if (CAMERA->GetRelativeVector2(_position).y > WINSIZEY)	//화면 밖을 벗어나면
	{
		SetRandomCreate(Vector2(rand() % 473 + 20, (int)CAMERA->GetrcTop().y), rand() % 20);
		//갈색 블록 관련
		_blockAnimation->Stop();	//위에 다시 생기면 부서진 형태가 index = 0이 되며 원래 모습으로 돌아오고 <= 이거 안 하면 부서진 모습 그대로 다시 나옴
		_isBreak = false;	//부서진 상태도 false가 되고 <= 이거 안 하면 다시 나온 멀쩡한 블록 밟아도 다시 안 부서짐
		_countTime = 0.f;	//부서진 이후 시간도 초기화된다 <= 이거 안 하면 다시 부서진 블록이 밑으로 안 떨어짐
	}	
}

void PlatformBlock::Render()
{
	_D2DRenderer->FillRectangle(_rect, D2DRenderer::DefaultBrush::White);			// 채우기
	_D2DRenderer->DrawRectangle(_rect, D2DRenderer::DefaultBrush::Black, 2.0f);		// 라인
	
	if (_blockType == BlockType::BROWN)
		_blockImage->AniRender(CAMERA->GetRelativeVector2(_position), _blockAnimation, 0.3f);
	else if (_blockType == BlockType::BLUE)
		_blockImage->Render(CAMERA->GetRelativeVector2(_position));
	else
		_blockImage->Render(CAMERA->GetRelativeVector2(_position));
}

void PlatformBlock::Move(Vector2 moveDirection, float speed)
{
	_position += moveDirection * speed * TIMEMANAGER->GetElapsedTime();	// == deltaTime
	_rect = RectMakePivot(_position, _size, Pivot::Center);
}

void PlatformBlock::SetRandomY(int value)
{
	_position.y = value;
}

void PlatformBlock::SetRandomType(int value)
{
	if (value < 2)
		_blockType = BlockType::BROWN;
	else if (value < 5)
		_blockType = BlockType::BLUE;
	else _blockType = BlockType::GREEN;
}

void PlatformBlock::SetRandomCreate(Vector2 randPos, int typeValue)
{
	_position = randPos;

	if (typeValue < 2)
		_blockType = BlockType::BROWN;
	else if (typeValue < 5)
		_blockType = BlockType::BLUE;
	else _blockType = BlockType::GREEN;
}

//먼가 갈색이 안그려짐

