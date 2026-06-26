#include "MainWindow.h"

namespace gui
{

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    QWidget* centralWidget = new QWidget(this);
    this->setCentralWidget(centralWidget);

    m_layout = std::make_unique<QVBoxLayout>(centralWidget);

    m_engine = std::make_unique<EngineCore>();
    m_viewport = std::make_unique<Viewport>(m_engine.get(), this);
    m_viewport->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_viewport->setMinimumHeight(800);

    m_layout->addWidget(m_viewport.get(), 9);
    int index = m_layout->indexOf(m_viewport.get());
    m_layout->setStretch(index, 1);

    m_controlLayout = std::make_unique<QHBoxLayout>();
    m_layout->addLayout(m_controlLayout.get(), 1);
    index = m_layout->indexOf(m_controlLayout.get());
    m_layout->setStretch(index, 0);


    setWidgetColours(this);
    this->setWindowTitle("Rendering Engine");
    this->resize(1280, 720);

    connect(m_engine.get(), &EngineCore::engineInitialised, this, &MainWindow::setupDisplays);
}


void MainWindow::setupDisplays()
{
    setupTextureManagerDisplay();
    setupShaderManagerDisplay();
    setupSceneModelManagerDisplay();
    setupEntityManagerDisplay();
}

void MainWindow::setupTextureManagerDisplay()
{
    m_textureDisplay = std::make_unique<TextureDisplay>(m_engine->getTextureManager(), this);
    m_controlLayout->addWidget(m_textureDisplay.get());
    m_textureDisplay.get()->show();
 }

void MainWindow::setupShaderManagerDisplay()
{
    m_shaderDisplay = std::make_unique<ShaderDisplay>(m_engine->getShaderManager(), this);
    m_controlLayout->addWidget(m_shaderDisplay.get());
    m_shaderDisplay->show();
 }

void MainWindow::setupSceneModelManagerDisplay()
{
    m_sceneModelDisplay = std::make_unique<SceneModelDisplay>(m_engine->getSceneModelManager(), m_viewport.get(), this);
    m_controlLayout->addWidget(m_sceneModelDisplay.get());
    m_sceneModelDisplay->show();
}

void MainWindow::setupEntityManagerDisplay()
{
    m_entityDisplay = std::make_unique<EntityModelDisplay>(m_engine->getEntityManager(), this);
    m_controlLayout->addWidget(m_entityDisplay.get());
    m_entityDisplay->show();
}

void MainWindow::setWidgetColours(QWidget* widget)
{
    QPalette palette = widget->palette();

    palette.setColor(QPalette::Window, backgroundColour);
    palette.setColor(QPalette::Base, backgroundColour);
    palette.setColor(QPalette::Button, buttonColour);

    widget->setPalette(palette);
    widget->setAutoFillBackground(true);
}

}