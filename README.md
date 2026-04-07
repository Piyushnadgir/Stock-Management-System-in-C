# Stock-Management-System-in-C
# Stock Management System (C)

A menu-driven stock portfolio management system built using **C programming and file handling**.
The program simulates basic stock trading operations such as buying, selling, and tracking a portfolio.

## Features

* View available stocks from a database
* Buy stocks and add them to a portfolio
* Sell stocks from the portfolio
* Calculate risk-reward ratio of stocks
* Track total portfolio value
* Loan eligibility calculation based on portfolio value
* Persistent storage using file handling

## Technologies Used

* C Programming
* Structures
* File Handling
* Menu-Driven CLI

## Project Structure

stock-management-system/
│
├── stock_management.c
├── stock_database.txt
├── user_stocks.txt
└── README.md

## How to Compile

gcc stock_management.c -o stock

## How to Run

./stock

## Example Stocks (stock_database.txt)

AAPL 180 0.12 0.05
GOOG 140 0.10 0.04
TSLA 220 0.18 0.09
MSFT 320 0.11 0.04
AMZN 135 0.13 0.06

## Learning Outcomes

* Implemented structured programming in C
* Used file handling for persistent data storage
* Built a modular menu-driven CLI application
* Simulated portfolio tracking and financial calculations
