#pragma once

#include "QvPlugin/Gui/QvGUIPluginInterface.hpp"
#include "ui_TrojanGoSettingsWidget.h"

#include <QTimer>
#include <optional>

enum KernelPathCheckerResult : char
{
    KPCR_VERY_OK = 0,
    KPCR_WARNING = 1,
    KPCR_FAILURE = 2,
};

class TrojanGoSettingsWidget
    : public Qv2rayPlugin::Gui::PluginSettingsWidget
    , private Ui::TrojanGoSettingsWidget
{
    Q_OBJECT

  public:
    explicit TrojanGoSettingsWidget(QWidget *parent = nullptr);
    virtual void Load() override;
    virtual void Store() override;

  protected:
    void changeEvent(QEvent *e) override;
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;

  private slots:
    void debounceUnfreeze();
    void on_selectKernelBtn_clicked();
    void on_testKernelBtn_clicked();

  private:
    QTimer debounceTimer;

  private:
    // platform-dependent options.
#if defined(Q_OS_MAC)
    static constexpr auto platformDefaultKernelDir = "/usr/local/bin";
    static constexpr auto platformKernelPathFilter = "Trojan-Go Core(trojan-go*);;All Files(*)";
#elif defined(Q_OS_UNIX)
    static constexpr auto platformDefaultKernelDir = "/usr/bin";
    static constexpr auto platformKernelPathFilter = "Trojan-Go Core(trojan-go*);;All Files(*)";
#elif defined(Q_OS_WIN)
    static constexpr auto platformDefaultKernelDir = "";
    static constexpr auto platformKernelPathFilter = "Trojan-Go Core(trojan-go.exe);;All Files(*)";
#else
    static constexpr auto platformDefaultKernelDir = "";
    static constexpr auto platformKernelPathFilter = "";
#endif

  private:
    /**
     * @brief Priliminary Kernel Path Checker
     * @param pathToKernel the kernel path to be checked.
     * @return if the kernel path check passes, and if not, the detailed error message.
     */
    std::tuple<KernelPathCheckerResult, std::optional<QString>> preliminaryKernelPathChecker(const QString &pathToKernel);

    /**
     * @brief The UI routine to handle kernel path check.
     *        To be reused by multiple part of this program.
     * @param pathToCheck the path to be checked.
     * @return if the backend should accept the user input.
     */
    bool handleKernelPathCheck(const QString &pathToCheck);
};
