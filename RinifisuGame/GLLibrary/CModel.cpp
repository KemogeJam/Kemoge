#include "CModel.h"
#include "CLight.h"
#include "CCamera.h"


void CModel::UpdateMatrix() {
	CMatrix RX,RY,RZ;
	RX.RotationX(m_rot.x+m_baserot.x);
	RY.RotationY(m_rot.y+m_baserot.y);
	RZ.RotationZ(m_rot.z+m_baserot.z);
	m_rotMtx = RZ * RY * RX;
	m_transMtx.Transelate(m_pos.x,m_pos.y,m_pos.z);
	m_scaleMtx.Scale(m_scale.x,m_scale.y,m_scale.z);
	m_matrix = m_transMtx * m_rotMtx * m_scaleMtx;
}
void CModel::SendShaderParam() {
	/*
	  ライト設定
	*/
	glUniform3fv(glGetUniformLocation(m_shader->getProgram(),"lightPos"),CLight::LIGHT_MAX,(float*)CLight::getPosPointer());
	glUniform3fv(glGetUniformLocation(m_shader->getProgram(),"lightDir"),CLight::LIGHT_MAX,(float*)CLight::getDirPointer());
	glUniform3fv(glGetUniformLocation(m_shader->getProgram(),"lightAmbientColor"),CLight::LIGHT_MAX,(float*)CLight::getAmbientColorPointer());
	glUniform3fv(glGetUniformLocation(m_shader->getProgram(),"lightDiffuseColor"),CLight::LIGHT_MAX,(float*)CLight::getDiffuseColorPointer());
	glUniform1fv(glGetUniformLocation(m_shader->getProgram(),"lightAttenuation"),CLight::LIGHT_MAX,(float*)CLight::getAttenuationPointer());
	glUniform1fv(glGetUniformLocation(m_shader->getProgram(),"lightRadiationAngle"),CLight::LIGHT_MAX,(float*)CLight::getRadiationAnglePointer());
	glUniform1iv(glGetUniformLocation(m_shader->getProgram(),"lightType"),CLight::LIGHT_MAX,(int*)CLight::getTypeColorPointer());
	glUniform1i(glGetUniformLocation(m_shader->getProgram(),"lighting"),CLight::getLighting());
		
	/*
	  視線設定
	*/
	CVector3D vec=CCamera::getCurrent()->getDir();
	int eyeId = glGetUniformLocation(m_shader->getProgram(),"eyeVec");  //ライトの向きを設定
	glUniform3fv(eyeId,1,(float*)&vec);

		
	/*
	  ワールドトランスフォーム
	*/
	int worldId = glGetUniformLocation(m_shader->getProgram(),"WorldMatrix");  //ライトの向きを設定
	glUniformMatrix4fv(worldId,1,false,m_matrix.f);
}