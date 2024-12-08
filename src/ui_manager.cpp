#include "ui_manager.h"
#include <iostream>

UIManager::UIManager(SceneRenderer& sceneRenderer, ShaderManager& shaderManager, GLFWwindow* window)
    : sceneRenderer(sceneRenderer), shaderManager(shaderManager), window(window)
{
}

UIManager::~UIManager()
{
    shutdown();
}

void UIManager::init()
{

}

void UIManager::shutdown()
{

}

void UIManager::render()
{

}

void UIManager::update(float deltaTime)
{

}

void UIManager::renderAutoChangeControls(const std::string& uniformName)
{

}

void UIManager::renderRayMarchingSettings()
{

}

void UIManager::renderSceneSettings()
{

}

void UIManager::renderLightingSettings()
{

}

void UIManager::renderPostProcessingSettings()
{

}

void UIManager::renderColouringSettings()
{

}

void UIManager::renderTransformationsSettings()
{

}

void UIManager::renderFractalSettings()
{

