#include "CAnimation.h"

CAnimation::CAnimation(int maxFrame,float speed)
{
	this->maxFrame = maxFrame;
	this->speed = speed;
	nowFrame = 0;
	//frame = new CSprite*[maxFrame];
	//for(int i=0;i<maxFrame;i++) frame[i] = NULL;
	frame = (CSprite**) calloc (maxFrame,sizeof(CSprite*));
}
CAnimation::~CAnimation()
{
	for(int i=0;i<maxFrame;i++)
		if(frame[i] != NULL) delete frame[i];
}
void CAnimation::PushFrame(char *path,int prior)
{
	if(frame[prior] != NULL) 
		delete frame[prior];
	frame[prior] = new CSprite(path);
}
void CAnimation::Update(float eTime)
{
	nowFrame += speed * eTime;
	if(nowFrame >= maxFrame)
		nowFrame = 0;
}
void CAnimation::Render(D3DXMATRIX *pmat)
{
	IObject::Render(pmat);
	frame[(int)nowFrame]->Render(&this->mat);
}