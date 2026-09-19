#include <QMainWindow>

class LoginWindow : public QMainWindow {
    Q_OBJECT // MOC processes this
private:
    // Qt widgets (buttons, text ffields, etc.)
    void onLogicButtonClicked(); // This calls vault.unlock()
};
