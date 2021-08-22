#pragma once
#include <QJsonObject>
#include <QtGlobal>

#ifndef DEFAULT_KERNEL_PATH
#ifdef Q_OS_WIN
#define DEFAULT_KERNEL_PATH (QApplication::applicationDirPath() + "naiveproxy.exe")
#elif defined(Q_OS_MAC)
#define DEFAULT_KERNEL_PATH (QApplication::applicationDirPath() + "naiveproxy")
#else
#define DEFAULT_KERNEL_PATH "/bin/naiveproxy"
#endif
#endif

#include "QvPlugin/Gui/QvGUIPluginInterface.hpp"
#include "ui_SettingsWidget.h"

class SettingsWidget
    : public Qv2rayPlugin::Gui::PluginSettingsWidget
    , private Ui::SettingsWidget
{
    Q_OBJECT

  public:
    explicit SettingsWidget(QWidget *parent = nullptr);

  protected:
    void changeEvent(QEvent *e) override;

  private slots:
    void on_textKernelPath_textEdited(const QString &arg1);
    void on_buttonBrowseKernel_clicked();
    void on_buttonTestKernel_clicked();

    // PluginSettingsWidget interface
  public:
    virtual void Load() override;
    virtual void Store() override;
};
