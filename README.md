# decision-tree-learning
A decision tree learning implementation based on a credit rating context

## Build
```
make all
```

## Input Arguments
- [train] specifies the path to a set of training data (input-output pairs)
- [test] specifies the path to a set of testing data, which is a text file where the first line is a header containing the names of the columns, and each subsequent line contains the five financial ratios of a company; see file new.txt (available on MyUni) for an example.
- [minleaf] is an integer greater than zero which specifies the second input parameter to the DTL algorithm.

## Problem Description
Financial corporations regularly need to assess the creditworthiness of potential borrow- ers or debtors. Credit rating agencies (e.g., Standard & Poor’s, Moody’s, Fitch Ratings) provide a service by assigning credit ratings to organisations (companies, sovereign gov- ernments, etc.) based on their creditworthiness. The ratings are typically designated using letters, for example, AAA, AA, A, BBB, BB, B, CCC (in decreasing creditworthiness), and each agency has its own set of symbols. Given the fundamental importance of credit, credit ratings play a major role in the financial system.
Credit ratings are assigned by analysing financial information on the borrower. In the case of corporate borrowers, information such as working capital, total assets, total debts etc., are used to assess creditworthiness. More specifically, a set of financial ratios of a company are used, for example,
- Working capital / Total Assets (WC TA)
- Retained Earnings / Total Assets (RE TA)
- Earnings Before Interests and Taxes / Total Assets (EBIT TA)
- Market Value of Equity / Book Value of Total Debt (MVE BVTD)
- Sales / Total Assets (S TA)
