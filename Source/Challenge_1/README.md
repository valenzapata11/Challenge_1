### Challenge 1: PACS
Valentina Zapata Coronel
10985360

Objective: write a program to find the minimum of a function through its gradient. 

In the folder Source, you can find the implementation for the first challenge. The chosen structure consisted of two main classes: Method and Update Rule, 
and 1 (Gradient) and 3 sub-classes (Amijo Rule, Exponential Descent, and Inverse Decay) respectively. The corresponding class diagram is shown below. 
![image](https://github.com/valenzapata11/Challenge_1/assets/69641299/2e758931-8726-4b89-955f-309a6abeae8c)

The file: main.cpp contains the declaration of the function to minimize. To change it, the user must rewrite the functions fun and dfun. The latter corresponds to the evaluation of the
gradient of the function. 

A makefile is included. When executed, the user can choose between the 3 different update rules for ak and between the finite differences approximation or the 
exact gradient for the estimation of the gradient.

The result will be printed in the terminal.

