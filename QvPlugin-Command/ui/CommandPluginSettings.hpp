#pragma once
#include "QvPlugin/Gui/QvGUIPluginInterface.hpp"
#include "core/CommandConfig.hpp"

#include <QWidget>

namespace Ui
{
    class CommandPluginSettings;
}

class CommandPluginSettings : public Qv2rayPlugin::Gui::PluginSettingsWidget
{
    Q_OBJECT
  public:
    explicit CommandPluginSettings(QWidget *parent = nullptr);
    ~CommandPluginSettings();

    virtual void Load() override;
    virtual void Store() override;

  private slots:
    void on_preConnTxt_textChanged();
    void on_postConnTxt_textChanged();
    void on_preDisconnTxt_textChanged();
    void on_postDisconnTxt_textChanged();
    void on_connCreateTxt_textChanged();
    void on_connRenameTxt_textChanged();
    void on_connUpdateTxt_textChanged();
    void on_connDeleteTxt_textChanged();
    void on_setSystemProxyTxt_textChanged();
    void on_clearSystemProxyTxt_textChanged();

  private:
    CommandPluginConfig settingsObject;
    Ui::CommandPluginSettings *ui;
};
