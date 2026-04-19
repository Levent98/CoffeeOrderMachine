#include "mainwindow.h"

#include "coffee.h"
#include "coffeemenu.h"
#include "coffeeorderservice.h"

#include <QFrame>
#include <QHBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QMessageBox>
#include <QPushButton>
#include <QSpinBox>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QWidget>
#include <QStringList>
#include <QScrollArea>
#include <QSizePolicy>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      menu(CoffeeMenu::getInstance()),
      orderService(new CoffeeOrderService(menu)),
      coffeeListWidget(nullptr),
      selectedCoffeeLabel(nullptr),
      priceLabel(nullptr),
      totalLabel(nullptr),
      statusLabel(nullptr),
      ingredientsList(nullptr),
      quantitySpinBox(nullptr),
      orderSummaryText(nullptr),
      orderButton(nullptr),
      resetButton(nullptr),
      detailCard(nullptr),
      summaryCard(nullptr) {
    buildUi();
    applyStyles();
    loadMenu();

    connect(coffeeListWidget, &QListWidget::itemSelectionChanged,
            this, &MainWindow::onCoffeeSelectionChanged);
    connect(quantitySpinBox, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &MainWindow::onQuantityChanged);
    connect(orderButton, &QPushButton::clicked, this, &MainWindow::onOrderClicked);
    connect(resetButton, &QPushButton::clicked, this, &MainWindow::onResetClicked);

    if (coffeeListWidget->count() > 0) {
        coffeeListWidget->setCurrentRow(0);
    }

    updateSelectedCoffeeDetails();
}

MainWindow::~MainWindow() {
    delete orderService;
}


void MainWindow::buildUi() {
    auto* scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    auto* central = new QWidget(this);
    auto* rootLayout = new QVBoxLayout(central);
    rootLayout->setContentsMargins(20, 20, 20, 20);
    rootLayout->setSpacing(16);

    auto* titleLabel = new QLabel("Coffee Order Machine", this);
    titleLabel->setObjectName("titleLabel");

    auto* subtitleLabel = new QLabel("Select a drink, choose a quantity, and place your order.", this);
    subtitleLabel->setObjectName("subtitleLabel");
    subtitleLabel->setWordWrap(true);

    auto* contentLayout = new QHBoxLayout();
    contentLayout->setSpacing(16);

    auto* menuCard = new QFrame(this);
    menuCard->setObjectName("menuCard");
    menuCard->setMinimumWidth(320);
    menuCard->setMaximumWidth(360);
    menuCard->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);

    auto* menuLayout = new QVBoxLayout(menuCard);
    menuLayout->setContentsMargins(16, 16, 16, 16);
    menuLayout->setSpacing(12);

    auto* menuTitle = new QLabel("Available Coffees", this);
    menuTitle->setObjectName("sectionTitle");

    coffeeListWidget = new QListWidget(this);
    coffeeListWidget->setObjectName("coffeeListWidget");
    coffeeListWidget->setMinimumHeight(420);
    coffeeListWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    menuLayout->addWidget(menuTitle);
    menuLayout->addWidget(coffeeListWidget);

    auto* rightPanelLayout = new QVBoxLayout();
    rightPanelLayout->setSpacing(16);

    detailCard = new QFrame(this);
    detailCard->setObjectName("detailCard");
    detailCard->setMinimumHeight(360);
    detailCard->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    auto* detailLayout = new QVBoxLayout(detailCard);
    detailLayout->setContentsMargins(18, 18, 18, 18);
    detailLayout->setSpacing(10);

    selectedCoffeeLabel = new QLabel("Coffee: -", this);
    selectedCoffeeLabel->setObjectName("coffeeNameLabel");
    selectedCoffeeLabel->setWordWrap(true);

    priceLabel = new QLabel("Unit Price: -", this);
    totalLabel = new QLabel("Total: -", this);

    auto* quantityTitle = new QLabel("Quantity", this);
    quantityTitle->setObjectName("sectionTitle");

    quantitySpinBox = new QSpinBox(this);
    quantitySpinBox->setRange(1, 10);
    quantitySpinBox->setValue(1);
    quantitySpinBox->setMinimumHeight(36);

    auto* ingredientsTitle = new QLabel("Ingredients", this);
    ingredientsTitle->setObjectName("sectionTitle");

    ingredientsList = new QListWidget(this);
    ingredientsList->setMinimumHeight(120);
    ingredientsList->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    auto* buttonRow = new QHBoxLayout();
    buttonRow->setSpacing(10);
    orderButton = new QPushButton("Place Order", this);
    orderButton->setObjectName("primaryButton");
    resetButton = new QPushButton("Reset", this);
    resetButton->setObjectName("secondaryButton");
    orderButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    resetButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    buttonRow->addWidget(orderButton, 1);
    buttonRow->addWidget(resetButton, 1);

    detailLayout->addWidget(selectedCoffeeLabel);
    detailLayout->addWidget(priceLabel);
    detailLayout->addWidget(totalLabel);
    detailLayout->addSpacing(6);
    detailLayout->addWidget(quantityTitle);
    detailLayout->addWidget(quantitySpinBox);
    detailLayout->addSpacing(6);
    detailLayout->addWidget(ingredientsTitle);
    detailLayout->addWidget(ingredientsList, 1);
    detailLayout->addSpacing(8);
    detailLayout->addLayout(buttonRow);

    summaryCard = new QFrame(this);
    summaryCard->setObjectName("summaryCard");
    summaryCard->setMinimumHeight(260);
    summaryCard->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    auto* summaryLayout = new QVBoxLayout(summaryCard);
    summaryLayout->setContentsMargins(18, 18, 18, 18);
    summaryLayout->setSpacing(10);

    auto* summaryTitle = new QLabel("Order Summary", this);
    summaryTitle->setObjectName("sectionTitle");

    statusLabel = new QLabel("Status: Waiting for your order", this);
    statusLabel->setObjectName("statusLabel");
    statusLabel->setWordWrap(true);

    orderSummaryText = new QTextEdit(this);
    orderSummaryText->setReadOnly(true);
    orderSummaryText->setMinimumHeight(160);
    orderSummaryText->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    orderSummaryText->setPlaceholderText("Your order details will appear here.");

    summaryLayout->addWidget(summaryTitle);
    summaryLayout->addWidget(statusLabel);
    summaryLayout->addWidget(orderSummaryText, 1);

    rightPanelLayout->addWidget(detailCard);
    rightPanelLayout->addWidget(summaryCard);
    rightPanelLayout->setStretch(0, 3);
    rightPanelLayout->setStretch(1, 2);

    contentLayout->addWidget(menuCard, 1);
    contentLayout->addLayout(rightPanelLayout, 2);

    rootLayout->addWidget(titleLabel);
    rootLayout->addWidget(subtitleLabel);
    rootLayout->addLayout(contentLayout, 1);

    scrollArea->setWidget(central);
    setCentralWidget(scrollArea);
    setWindowTitle("Coffee Order Machine");
    resize(1120, 760);
    setMinimumSize(980, 700);
}

void MainWindow::applyStyles() {
    setStyleSheet(R"(
        QMainWindow {
            background-color: #f4f1ea;
        }
        QLabel {
            color: #2f241f;
            font-size: 14px;
        }
        QLabel#titleLabel {
            font-size: 28px;
            font-weight: 700;
            color: #2d1f18;
        }
        QLabel#subtitleLabel {
            color: #6c5b53;
            font-size: 14px;
        }
        QLabel#sectionTitle {
            font-size: 16px;
            font-weight: 600;
            color: #4c3428;
        }
        QLabel#coffeeNameLabel {
            font-size: 22px;
            font-weight: 700;
            color: #3b2518;
        }
        QLabel#statusLabel {
            background-color: #efe7db;
            border: 1px solid #dbcab8;
            border-radius: 10px;
            padding: 10px;
            color: #5b4335;
        }
        QFrame#menuCard, QFrame#detailCard, QFrame#summaryCard {
            background-color: #fffdf9;
            border: 1px solid #dfd3c5;
            border-radius: 16px;
        }
        QListWidget, QTextEdit, QSpinBox {
            background-color: white;
            border: 1px solid #d9cbbb;
            border-radius: 10px;
            padding: 6px;
            selection-background-color: #8b5e3c;
            selection-color: white;
            font-size: 14px;
        }
        QListWidget::item {
            padding: 8px;
            margin: 2px 0;
            border-radius: 8px;
        }
        QListWidget::item:selected {
            background-color: #8b5e3c;
            color: white;
        }
        QPushButton {
            min-height: 44px;
            border-radius: 10px;
            font-size: 14px;
            font-weight: 600;
            padding: 8px 14px;
        }
        QPushButton#primaryButton {
            background-color: #6f4e37;
            color: white;
            border: none;
        }
        QPushButton#primaryButton:hover {
            background-color: #5d412d;
        }
        QPushButton#secondaryButton {
            background-color: #efe7db;
            color: #4d382c;
            border: 1px solid #d8c8b8;
        }
        QPushButton#secondaryButton:hover {
            background-color: #e3d7c8;
        }
    )");
}

void MainWindow::loadMenu() {
    coffeeListWidget->clear();

    for (int id : menu.getCoffeeIds()) {
        Coffee coffee = menu.getCoffeeById(id);
        auto* item = new QListWidgetItem(
            QString::fromStdString(coffee.getName()) +
            "  -  " + QString::number(coffee.getPrice()) + " TL");
        item->setData(Qt::UserRole, id);
        coffeeListWidget->addItem(item);
    }
}

int MainWindow::currentCoffeeId() const {
    QListWidgetItem* currentItem = coffeeListWidget->currentItem();
    if (currentItem == nullptr) {
        return -1;
    }
    return currentItem->data(Qt::UserRole).toInt();
}

void MainWindow::updateSelectedCoffeeDetails() {
    const int id = currentCoffeeId();
    if (id < 0) {
        selectedCoffeeLabel->setText("Coffee: -");
        priceLabel->setText("Unit Price: -");
        totalLabel->setText("Total: -");
        ingredientsList->clear();
        return;
    }

    Coffee coffee = orderService->getCoffeeById(id);
    selectedCoffeeLabel->setText(QString::fromStdString(coffee.getName()));
    priceLabel->setText("Unit Price: " + QString::number(coffee.getPrice()) + " TL");

    ingredientsList->clear();
    for (const auto& [name, quantity] : coffee.getIngredients()) {
        ingredientsList->addItem(QString::number(quantity) + " x " + QString::fromStdString(name));
    }

    updateTotal();
}

void MainWindow::updateTotal() {
    const int id = currentCoffeeId();
    if (id < 0) {
        totalLabel->setText("Total: -");
        return;
    }

    const Coffee coffee = orderService->getCoffeeById(id);
    const int quantity = quantitySpinBox->value();
    const int total = coffee.getPrice() * quantity;
    totalLabel->setText("Total: " + QString::number(total) + " TL");
}

void MainWindow::onCoffeeSelectionChanged() {
    updateSelectedCoffeeDetails();
}

void MainWindow::onQuantityChanged(int) {
    updateTotal();
}

void MainWindow::onOrderClicked() {
    const int id = currentCoffeeId();
    if (id < 0) {
        QMessageBox::warning(this, "Warning", "Please select a coffee first.");
        return;
    }

    const Coffee coffee = orderService->getCoffeeById(id);
    const int quantity = quantitySpinBox->value();
    const int total = coffee.getPrice() * quantity;

    statusLabel->setText("Status: Preparing your order");
    orderSummaryText->setPlainText(
        QString("Coffee: %1\nQuantity: %2\nUnit Price: %3 TL\nTotal: %4 TL\n\n%5")
            .arg(QString::fromStdString(coffee.getName()))
            .arg(quantity)
            .arg(coffee.getPrice())
            .arg(total)
            .arg(QString::fromStdString(orderService->createPreparationMessage(coffee, quantity))));

    QMessageBox::information(this, "Order Received",
                             QString("Your %1 order has been placed successfully.")
                                 .arg(QString::fromStdString(coffee.getName())));
}

void MainWindow::onResetClicked() {
    quantitySpinBox->setValue(1);
    orderSummaryText->clear();
    statusLabel->setText("Status: Waiting for your order");
    if (coffeeListWidget->count() > 0) {
        coffeeListWidget->setCurrentRow(0);
    }
    updateSelectedCoffeeDetails();
}
