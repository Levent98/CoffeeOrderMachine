#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QLabel;
class QListWidget;
class QListWidgetItem;
class QPushButton;
class QSpinBox;
class QTextEdit;
class QFrame;

class CoffeeMenu;
class CoffeeOrderService;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

private slots:
    void onCoffeeSelectionChanged();
    void onQuantityChanged(int quantity);
    void onOrderClicked();
    void onResetClicked();

private:
    CoffeeMenu& menu;
    CoffeeOrderService* orderService;

    QListWidget* coffeeListWidget;
    QLabel* selectedCoffeeLabel;
    QLabel* priceLabel;
    QLabel* totalLabel;
    QLabel* statusLabel;
    QListWidget* ingredientsList;
    QSpinBox* quantitySpinBox;
    QTextEdit* orderSummaryText;
    QPushButton* orderButton;
    QPushButton* resetButton;
    QFrame* detailCard;
    QFrame* summaryCard;

    void buildUi();
    void loadMenu();
    void applyStyles();
    void updateSelectedCoffeeDetails();
    void updateTotal();
    int currentCoffeeId() const;
};

#endif
