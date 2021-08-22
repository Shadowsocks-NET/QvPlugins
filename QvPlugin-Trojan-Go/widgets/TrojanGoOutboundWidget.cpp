#include "TrojanGoOutboundWidget.hpp"

TrojanGoOutboundWidget::TrojanGoOutboundWidget(QWidget *parent) : Qv2rayPlugin::Gui::PluginProtocolEditor(parent)
{
    setupUi(this);
}

void TrojanGoOutboundWidget::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type())
    {
        case QEvent::LanguageChange: retranslateUi(this); break;
        default: break;
    }
}

void TrojanGoOutboundWidget::on_sniTxt_textEdited(const QString &arg1)
{
    config.sni = arg1;
}

void TrojanGoOutboundWidget::on_typeCombo_currentIndexChanged(const QString &arg1)
{
    config.type = TRANSPORT_TYPE_STRING_MAP.key(arg1);
}

void TrojanGoOutboundWidget::on_hostTxt_textEdited(const QString &arg1)
{
    config.host = arg1;
}

void TrojanGoOutboundWidget::on_pathTxt_textEdited(const QString &arg1)
{
    config.path = arg1;
}

void TrojanGoOutboundWidget::on_encryptionTxt_textEdited(const QString &arg1)
{
    config.encryption = arg1;
}

void TrojanGoOutboundWidget::on_passwordTxt_textEdited(const QString &arg1)
{
    config.password = arg1;
}

void TrojanGoOutboundWidget::on_typeCombo_currentIndexChanged(int index)
{
    hostTxt->setEnabled(index == 1);
    pathTxt->setEnabled(index == 1);
    encryptionTxt->setEnabled(index == 1);
}

void TrojanGoOutboundWidget::on_muxCB_stateChanged(int arg1)
{
    config.mux = arg1 == Qt::Checked;
}

void TrojanGoOutboundWidget::Load()
{
    config.loadJson(settings);
    sniTxt->setText(config.sni);
    hostTxt->setText(config.host);
    pathTxt->setText(config.path);
    typeCombo->setCurrentText(TRANSPORT_TYPE_STRING_MAP[config.type]);
    encryptionTxt->setText(config.encryption);
    passwordTxt->setText(config.password);
    muxCB->setChecked(config.mux);
    on_typeCombo_currentIndexChanged(typeCombo->currentIndex());
}

void TrojanGoOutboundWidget::Store()
{
    settings = IOProtocolSettings{ config.toJson() };
}
