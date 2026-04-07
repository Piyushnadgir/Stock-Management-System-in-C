
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    char symbol[10];
    float price;
    float expected_return;
    float risk;
} Stock;

typedef struct {
    char symbol[10];
    int quantity;
    float buy_price;
} Portfolio;

Stock stocks[MAX];
Portfolio portfolio[MAX];

int stock_count = 0;
int portfolio_count = 0;

void loadStocks() {
    FILE *fp = fopen("stock_database.txt", "r");
    if (!fp) {
        printf("Error opening stock database.\n");
        return;
    }

    while (fscanf(fp, "%s %f %f %f", stocks[stock_count].symbol,
                  &stocks[stock_count].price,
                  &stocks[stock_count].expected_return,
                  &stocks[stock_count].risk) != EOF) {
        stock_count++;
    }

    fclose(fp);
}

void savePortfolio() {
    FILE *fp = fopen("user_stocks.txt", "w");
    if (!fp) return;

    for (int i = 0; i < portfolio_count; i++) {
        fprintf(fp, "%s %d %f\n",
                portfolio[i].symbol,
                portfolio[i].quantity,
                portfolio[i].buy_price);
    }

    fclose(fp);
}

void loadPortfolio() {
    FILE *fp = fopen("user_stocks.txt", "r");
    if (!fp) return;

    while (fscanf(fp, "%s %d %f",
                  portfolio[portfolio_count].symbol,
                  &portfolio[portfolio_count].quantity,
                  &portfolio[portfolio_count].buy_price) != EOF) {
        portfolio_count++;
    }

    fclose(fp);
}

void viewStocks() {
    printf("\nAvailable Stocks\n");
    printf("----------------------------\n");

    for (int i = 0; i < stock_count; i++) {
        printf("%s  Price: %.2f  Return: %.2f  Risk: %.2f\n",
               stocks[i].symbol,
               stocks[i].price,
               stocks[i].expected_return,
               stocks[i].risk);
    }
}

void viewPortfolio() {
    printf("\nYour Portfolio\n");
    printf("----------------------------\n");

    for (int i = 0; i < portfolio_count; i++) {
        printf("%s  Qty: %d  Buy Price: %.2f\n",
               portfolio[i].symbol,
               portfolio[i].quantity,
               portfolio[i].buy_price);
    }
}

void buyStock() {
    if (portfolio_count >= MAX) {
        printf("Portfolio limit reached.\n");
        return;
    }

    char symbol[10];
    int quantity;

    printf("Enter stock symbol: ");
    scanf("%s", symbol);

    printf("Enter quantity: ");
    scanf("%d", &quantity);

    for (int i = 0; i < stock_count; i++) {
        if (strcmp(stocks[i].symbol, symbol) == 0) {

            strcpy(portfolio[portfolio_count].symbol, symbol);
            portfolio[portfolio_count].quantity = quantity;
            portfolio[portfolio_count].buy_price = stocks[i].price;

            portfolio_count++;

            printf("Stock purchased successfully.\n");
            return;
        }
    }

    printf("Stock not found.\n");
}

void sellStock() {
    char symbol[10];
    int quantity;

    printf("Enter stock symbol: ");
    scanf("%s", symbol);

    printf("Enter quantity: ");
    scanf("%d", &quantity);

    for (int i = 0; i < portfolio_count; i++) {
        if (strcmp(portfolio[i].symbol, symbol) == 0) {

            if (portfolio[i].quantity < quantity) {
                printf("Not enough shares.\n");
                return;
            }

            portfolio[i].quantity -= quantity;

            if (portfolio[i].quantity == 0) {
                for (int j = i; j < portfolio_count - 1; j++) {
                    portfolio[j] = portfolio[j + 1];
                }
                portfolio_count--;
            }

            printf("Stock sold successfully.\n");
            return;
        }
    }

    printf("Stock not found in portfolio.\n");
}

void showRiskRewardRatio() {
    printf("\nRisk Reward Ratios\n");
    printf("----------------------------\n");

    for (int i = 0; i < stock_count; i++) {
        float ratio = stocks[i].expected_return / stocks[i].risk;
        printf("%s  RR Ratio: %.2f\n", stocks[i].symbol, ratio);
    }
}

void portfolioValue() {
    float total = 0;

    for (int i = 0; i < portfolio_count; i++) {
        total += portfolio[i].quantity * portfolio[i].buy_price;
    }

    printf("Total Portfolio Value: %.2f\n", total);
}

void checkLoanEligibility() {
    float total = 0;

    for (int i = 0; i < portfolio_count; i++) {
        total += portfolio[i].quantity * portfolio[i].buy_price;
    }

    float loan = total * 0.5;

    printf("Eligible Loan Amount: %.2f\n", loan);
}

int main() {

    loadStocks();
    loadPortfolio();

    int choice;

    while (1) {
        printf("\n--- Stock Management System ---\n");
        printf("1. View Stocks\n");
        printf("2. View Portfolio\n");
        printf("3. Buy Stock\n");
        printf("4. Sell Stock\n");
        printf("5. Risk Reward Ratio\n");
        printf("6. Portfolio Value\n");
        printf("7. Loan Eligibility\n");
        printf("8. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1: viewStocks(); break;
            case 2: viewPortfolio(); break;
            case 3: buyStock(); break;
            case 4: sellStock(); break;
            case 5: showRiskRewardRatio(); break;
            case 6: portfolioValue(); break;
            case 7: checkLoanEligibility(); break;

            case 8:
                savePortfolio();
                printf("Exiting...\n");
                return 0;

            default:
                printf("Invalid option.\n");
        }
    }
}
