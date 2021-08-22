#pragma once

#include "QvPlugin/Gui/QvGUIPluginInterface.hpp"
#include "core/Common.hpp"
#include "ui_TrojanGoOutboundWidget.h"

class TrojanGoOutboundWidget
    : public Qv2rayPlugin::Gui::PluginProtocolEditor
    , private Ui::TrojanGoOutboundWidget
{
    Q_OBJECT

  public:
    explicit TrojanGoOutboundWidget(QWidget *parent = nullptr);

  protected:
    TrojanGoShareLinkObject config;
    void changeEvent(QEvent *e) override;
    virtual void Load() override;
    virtual void Store() override;

  private slots:
    void on_sniTxt_textEdited(const QString &arg1);
    void on_typeCombo_currentIndexChanged(const QString &arg1);
    void on_hostTxt_textEdited(const QString &arg1);
    void on_pathTxt_textEdited(const QString &arg1);
    void on_encryptionTxt_textEdited(const QString &arg1);
    void on_passwordTxt_textEdited(const QString &arg1);
    void on_typeCombo_currentIndexChanged(int index);
    void on_muxCB_stateChanged(int arg1);
};
