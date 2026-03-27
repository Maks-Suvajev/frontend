#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    QWidget* centralWidget = new QWidget(this);
    this->setCentralWidget(centralWidget);

    m_layout = std::make_unique<QVBoxLayout>(centralWidget);

    m_engine = std::make_unique<EngineCore>();
    m_viewport = std::make_unique<Viewport>(m_engine.get(), this);

    m_layout->addWidget(m_viewport.get());
    int index = m_layout->indexOf(m_viewport.get());
    m_layout->setStretch(index, 1);

    m_controlLayout = std::make_unique<QHBoxLayout>();
    m_layout->addLayout(m_controlLayout.get());

    setWidgetColours(this);
    this->setWindowTitle("Rendering Engine");
    this->resize(1280, 720);

    connect(m_engine.get(), &EngineCore::engineInitialised, this, &MainWindow::setupDisplays);
}


void MainWindow::setupDisplays()
{
    setupTextureManagerDisplay();
    setupShaderManagerDisplay();
}

void MainWindow::setupTextureManagerDisplay()
{
    m_textureDisplay = std::make_unique<TextureDisplay>(m_engine->getTextureManager(), this);
    m_controlLayout->addWidget(m_textureDisplay.get());
    m_textureDisplay->show();
 }

void MainWindow::setupShaderManagerDisplay()
{
    m_shaderDisplay = std::make_unique<ShaderDisplay>(m_engine->getShaderManager(), this);
    m_controlLayout->addWidget(m_shaderDisplay.get());
    m_shaderDisplay->show();
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