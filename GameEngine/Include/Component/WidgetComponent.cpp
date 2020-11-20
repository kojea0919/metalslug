#include "WidgetComponent.h"
#include "../Resource/Mesh2D.h"
#include "../Resource/Material.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "Transform.h"
#include "../UI/UIObject.h"
#include "Camera.h"
#include "../Device.h"
#include "../Scene/CameraManager.h"

CWidgetComponent::CWidgetComponent()
	: m_pUIObject(nullptr)
{
	m_eSceneComponentType = SCENECOMPONENT_TYPE::ST_2D;
	m_eSceneClassType = SCENECOMPONENT_CLASS_TYPE::WIDGET;
}

CWidgetComponent::CWidgetComponent(const CWidgetComponent& com)
	: CPrimitiveComponent(com)
{
}

CWidgetComponent::~CWidgetComponent()
{
}

bool CWidgetComponent::Init()
{
	if (!CPrimitiveComponent::Init())
		return false;

	SetMesh(nullptr);
	SetMaterial(nullptr);

	return true;
}

void CWidgetComponent::Start()
{
	CPrimitiveComponent::Start();

	if (m_pUIObject)
		m_pUIObject->Start();
}

void CWidgetComponent::Update(float fTime)
{
	CPrimitiveComponent::Update(fTime);

	if (m_pUIObject)
		m_pUIObject->Update(fTime);
}

void CWidgetComponent::PostUpdate(float fTime)
{
	CPrimitiveComponent::PostUpdate(fTime);

	if (m_pUIObject)
	{
		CCamera* pCamera = m_pScene->GetCameraManager()->GetMainCamera();

		Vector3	vCameraPos = pCamera->GetWorldPos() - Vector3(RESOLUTION.iWidth / 2.f, RESOLUTION.iHeight / 2.f, 0.f);

		// ȭ����� ��ġ�� �����ش�.
		Vector3	vPos = GetWorldPos() - vCameraPos;

		m_pUIObject->SetWorldPos(vPos);

		m_pUIObject->PostUpdate(fTime);
	}
}

void CWidgetComponent::Collision(float fTime)
{
	CPrimitiveComponent::Collision(fTime);
}

void CWidgetComponent::PrevRender(float fTime)
{
	CPrimitiveComponent::PrevRender(fTime);

	if (m_pUIObject)
		m_pUIObject->PrevRender();
}

void CWidgetComponent::Render(float fTime)
{
	if (m_pUIObject)
		m_pUIObject->Render();
}

void CWidgetComponent::PostRender(float fTime)
{
	CPrimitiveComponent::PostRender(fTime);

	if (m_pUIObject)
		m_pUIObject->PostRender();
}

CWidgetComponent* CWidgetComponent::Clone()
{
	return new CWidgetComponent(*this);
}

void CWidgetComponent::Save(FILE* pFile)
{
	CPrimitiveComponent::Save(pFile);
}

void CWidgetComponent::Load(FILE* pFile)
{
	CPrimitiveComponent::Load(pFile);

	CMesh* pMesh = m_pScene->GetResourceManager()->GetDefault2DMesh();
	SetMesh((CMesh2D*)pMesh);

	SAFE_RELEASE(pMesh);
}