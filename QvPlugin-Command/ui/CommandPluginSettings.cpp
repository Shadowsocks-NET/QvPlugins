#include "CommandPluginSettings.hpp"

#include "CommandPlugin.hpp"
#include "ui_CommandPluginSettings.h"

CommandPluginSettings::CommandPluginSettings(QWidget *parent) : Qv2rayPlugin::Gui::PluginSettingsWidget(parent), ui(new Ui::CommandPluginSettings)
{
    ui->setupUi(this);
}

CommandPluginSettings::~CommandPluginSettings()
{
    delete ui;
}

void CommandPluginSettings::on_preConnTxt_textChanged()
{
    settingsObject.beforeConnection = ui->preConnTxt->toPlainText();
}

void CommandPluginSettings::on_postConnTxt_textChanged()
{
    settingsObject.afterConnection = ui->postConnTxt->toPlainText();
}

void CommandPluginSettings::on_preDisconnTxt_textChanged()
{
    settingsObject.beforeDisConnection = ui->preDisconnTxt->toPlainText();
}

void CommandPluginSettings::on_postDisconnTxt_textChanged()
{
    settingsObject.afterDisConnection = ui->postDisconnTxt->toPlainText();
}

void CommandPluginSettings::on_connCreateTxt_textChanged()
{
    settingsObject.connectionCreated = ui->connCreateTxt->toPlainText();
}

void CommandPluginSettings::on_connRenameTxt_textChanged()
{
    settingsObject.connectionRenamed = ui->connRenameTxt->toPlainText();
}

void CommandPluginSettings::on_connUpdateTxt_textChanged()
{
    settingsObject.connectionUpdated = ui->connUpdateTxt->toPlainText();
}

void CommandPluginSettings::on_connDeleteTxt_textChanged()
{
    settingsObject.connectionDeleted = ui->connDeleteTxt->toPlainText();
}

void CommandPluginSettings::on_setSystemProxyTxt_textChanged()
{
    settingsObject.setSystemProxy = ui->setSystemProxyTxt->toPlainText();
}

void CommandPluginSettings::on_clearSystemProxyTxt_textChanged()
{
    settingsObject.clearSystemProxy = ui->clearSystemProxyTxt->toPlainText();
}

void CommandPluginSettings::Load()
{
    this->settingsObject.loadJson(settings);
    ui->preConnTxt->setPlainText(settingsObject.beforeConnection);
    ui->postConnTxt->setPlainText(settingsObject.afterConnection);
    ui->preDisconnTxt->setPlainText(settingsObject.beforeDisConnection);
    ui->postDisconnTxt->setPlainText(settingsObject.afterDisConnection);
    //
    ui->connCreateTxt->setPlainText(settingsObject.connectionCreated);
    ui->connRenameTxt->setPlainText(settingsObject.connectionRenamed);
    ui->connUpdateTxt->setPlainText(settingsObject.connectionUpdated);
    ui->connDeleteTxt->setPlainText(settingsObject.connectionDeleted);
    //
    ui->setSystemProxyTxt->setPlainText(settingsObject.setSystemProxy);
    ui->clearSystemProxyTxt->setPlainText(settingsObject.clearSystemProxy);
}

void CommandPluginSettings::Store()
{
    settings = settingsObject.toJson();
}
