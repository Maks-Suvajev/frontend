#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <iostream>
#include <memory>

#include "Viewport.h"
#include "TextureDisplay.h"
#include "ShaderDisplay.h"
#include "SceneModelDisplay.h"
#include "EntityModelDisplay.h"

// QT libs
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QLabel>

// Engine
#include "EngineCore.h"

namespace gui
{

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = nullptr);
        ~MainWindow() = default;

    private:
        void setWidgetColours(QWidget* widget);

        void setupDisplays();
        void setupTextureManagerDisplay();
        void setupShaderManagerDisplay();
        void setupSceneModelManagerDisplay();
        void setupEntityManagerDisplay();


        //TODO:: Don't use RAII for Qt specific objects, it already handles their destruction automatically. Only use it for engine core
        std::unique_ptr<QVBoxLayout>            m_layout;
        std::unique_ptr<QHBoxLayout>            m_controlLayout;
        std::unique_ptr<Viewport>               m_viewport;
        std::unique_ptr<TextureDisplay>         m_textureDisplay;
        std::unique_ptr<ShaderDisplay>          m_shaderDisplay;
        std::unique_ptr<SceneModelDisplay>      m_sceneModelDisplay;
        std::unique_ptr<EntityModelDisplay>     m_entityDisplay;
        std::unique_ptr<EngineCore>             m_engine;

};

}


#endif