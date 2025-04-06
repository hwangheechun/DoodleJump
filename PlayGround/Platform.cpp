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
	_active = true;
}

void Platform::Release()                                               
{
}

void Platform::Update()
{
}

void Platform::Render()
{
	if (this)
	{
		_D2DRenderer->FillRectangle(CAMERA->GetRelativeRect(_rect), D2DRenderer::DefaultBrush::White);
		_D2DRenderer->DrawRectangle(CAMERA->GetRelativeRect(_rect), D2DRenderer::DefaultBrush::Black, 1.0f);
	}
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
	SetRandomCreate(Vector2(rand() % 473 + 20, 900), BLOCKTYPEVALUE);
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
	if (_player && !_player->_isDead)	//player 존재 여부
	{
		//_rect = RectMakePivot(_position, _size, Pivot::Center);	//rect와 Image 맞추기

		#pragma region 블록 타입
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
					Move(Vector2(0, 10));
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
				Move(Vector2(100, 0));
			else
				Move(Vector2(-100, 0));
		}
		else //초록색 블록
			_blockImage = IMAGEMANAGER->FindImage(L"green");
#pragma endregion

		_blockAnimation->FrameUpdate(TIMEMANAGER->GetElapsedTime());

		if (CAMERA->GetRelativeVector2(_position).y > WINSIZEY)	//화면 밖을 벗어나면
		{
			//갈색 블록 관련
			_blockAnimation->Stop();	//위에 다시 생기면 부서진 형태가 index = 0이 되며 원래 모습으로 돌아오고 <= 이거 안 하면 부서진 모습 그대로 다시 나옴
			_isBreak = false;	//부서진 상태도 false가 되고 <= 이거 안 하면 다시 나온 멀쩡한 블록 밟아도 다시 안 부서짐
			_countTime = 0.f;	//부서진 이후 시간도 초기화된다 <= 이거 안 하면 다시 부서진 블록이 밑으로 안 떨어짐
		}
	}
	else if(_player && _player->_isDead) this->SetActive(false);
}

void PlatformBlock::Render()
{
	if (_blockType == BlockType::BROWN)
		_blockImage->AniRender(CAMERA->GetRelativeVector2(_position), _blockAnimation, 0.3f);
	else if (_blockType == BlockType::BLUE)
		_blockImage->Render(CAMERA->GetRelativeVector2(_position));
	else if (_blockType == BlockType::GREEN)
		_blockImage->Render(CAMERA->GetRelativeVector2(_position));

	_D2DRenderer->FillRectangle(CAMERA->GetRelativeRect(_rect), D2DRenderer::DefaultBrush::White);
}

void PlatformBlock::Move(Vector2 moveDirection)
{
	_position += moveDirection * TIMEMANAGER->GetElapsedTime();	// == deltaTime
}

void PlatformBlock::SetRandomCreate(Vector2 randPos, int typeValue)
{
	_position = randPos;

	if (typeValue < 1)
		_blockType = BlockType::BROWN;
	else if (typeValue < 5)
		_blockType = BlockType::BLUE;
	else _blockType = BlockType::GREEN;
}


